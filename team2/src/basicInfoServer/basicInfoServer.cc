#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <mutex>

#include "mysql.h"
#include <grpcpp/grpcpp.h>
#include "protos/basicInfoService.grpc.pb.h"
#include "configmodule.h"
#include "const.h"
#include "userdao.h"
#include "gooddao.h"
#include "bagdao.h"
#include "datetime.h"

using namespace std;

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

using myApplication::BasicInfoService;
using myApplication::loginReq;
using myApplication::loginRsq;
using myApplication::modifyGoodReq;
using myApplication::modifyGoodRsq;
using myApplication::modifyUserReq;
using myApplication::modifyUserRsq;
using myApplication::registerReq;
using myApplication::registerRsq;
using myApplication::searchGoodReq;
using myApplication::searchGoodRsq;
using myApplication::searchUserReq;
using myApplication::searchUserRsq;

// std::mutex mtx;

/**
 *  RPC回调方法
 */
class BasicInfoServiceImpl final : public BasicInfoService::Service
{

    Status doLogin(ServerContext *context, const loginReq *request,
                   loginRsq *reply) override
    {
        if ("" == request->username())
        {
            // 账号不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));

            return Status::OK;
        }

        if ("" == request->password())
        {
            // 密码不能为空
            reply->set_status(Const::StatusCode::PASS_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::PASS_EMPTY));
            return Status::OK;
        }

        // mtx.lock();

        UserDao userdao;
        bool ret = userdao.GetByName(request->username());
        userdao.set_last_login_time(Datetime::getCurrentDate());
        if (!ret)
        {
            reply->set_status(Const::StatusCode::ACCOUNT_NOTEXIST);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::ACCOUNT_NOTEXIST));
            return Status::OK;
        }
        stringstream stream;
        stream << Datetime::getTimeustamp();
        string stamp = stream.str();

        if (userdao.pass() != request->password())
        {
            reply->set_status(Const::StatusCode::PASS_ERROR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::PASS_ERROR));
            return Status::OK;
        }

        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        reply->set_groupid(userdao.group_id());
        reply->set_id(userdao.id());
        // mtx.unlock();
        return Status::OK;
    }

    Status doRegister(ServerContext *context, const registerReq *request,
                      registerRsq *reply) override
    {
        if ("" == request->username())
        {
            // 账号不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }

        if ("" == request->password())
        {
            // 密码不能为空
            reply->set_status(Const::StatusCode::PASS_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::PASS_EMPTY));
            return Status::OK;
        }

        if (request->groupid() != 1 && request->groupid() != 2)
        {
            reply->set_status(Const::StatusCode::INPUT_ERROR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::INPUT_ERROR));
            return Status::OK;
        }
        // mtx.lock();

        UserDao userdao;
        // 用户存在，则返回用户信息
        if (userdao.GetByName(request->username()))
        {
            reply->set_status(Const::StatusCode::ACCOUNT_EXIST);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::ACCOUNT_EXIST));
            reply->set_id(userdao.id());
            return Status::OK;
        }

        userdao.set_name(request->username());
        userdao.set_pass(request->password());
        userdao.set_groupid(request->groupid());
        userdao.set_last_login_time(Datetime::getCurrentDate());
        bool ret = userdao.Create();
        if (!ret)
        {
            reply->set_status(Const::StatusCode::SIGNUP_FAILED);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::SIGNUP_FAILED));
            return Status::OK;
        }
        //根据用户ID初始化其拥有的道具，道具ID使用时间随机
        unsigned seed;
        seed = time(0);
        srand(seed);
        for (int i = 0; i < 10; i++)
        {
            // 随机生成的道具ID在1-1500之间
            int goodid = rand() % 1500 + 1;
            BagDao bag;
            bag.set_goodid(goodid);
            bag.set_userid(userdao.id());
            if (bag.GetById(goodid, userdao.id()))
            {
                bag.set_num(bag.num() + 1);
                bag.Update();
            }
            else
            {
                bag.set_num(1);
                GoodDao good;
                good.GetByID(goodid);
                bag.set_name(good.name());
                if (!bag.Create())
                {
                    reply->set_status(Const::StatusCode::BAG_FAILD);
                    reply->set_message(Const::GetStatusMsg(Const::StatusCode::BAG_FAILD));
                    return Status::OK;
                }
            }
        }
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        reply->set_id(userdao.id());
        // mtx.unlock();
        return Status::OK;
    }

    Status doModifyUserInfo(ServerContext *context, const modifyUserReq *request,
                            modifyUserRsq *reply) override
    {
        if ("" == request->username())
        {
            // 账号不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }

        if ("" == request->password())
        {
            // 更改的密码不能为空
            reply->set_status(Const::StatusCode::PASS_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::PASS_EMPTY));
            return Status::OK;
        }
        // mtx.lock();

        UserDao userdao;
        userdao.set_name(request->username());
        userdao.GetByName(request->username());

        userdao.set_pass(request->password());
        if (userdao.group_id() == 1 && request->has_money())
        {
            reply->set_status(Const::StatusCode::PERMISSION_DEFINED);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::PERMISSION_DEFINED));
            return Status::OK;
        }
        if (request->has_money())
        {
            userdao.set_money(request->money());
        }
        bool ret = userdao.Update();
        if (!ret)
        {
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        // mtx.unlock();
        return Status::OK;
    }

    Status doModifyGoodInfo(ServerContext *context, const modifyGoodReq *request,
                            modifyGoodRsq *reply) override
    {
        if ("" == request->goodname())
        {
            // 名称不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }
        // mtx.lock();
        GoodDao gooddao;

        gooddao.GetByName(request->goodname());
        if (request->has_kind())
        {
            gooddao.set_kind(request->kind());
        }
        if (request->has_level())
        {
            gooddao.set_level(request->level());
        }
        if (request->has_career())
        {
            gooddao.set_career(request->career());
        }
        if (request->has_grade())
        {
            gooddao.set_grade(request->grade());
        }
        if (request->has_color())
        {
            gooddao.set_color(request->color());
        }

        bool ret = gooddao.Update();
        if (!ret)
        {
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        reply->set_id(gooddao.id());
        // mtx.unlock();
        return Status::OK;
    }

    Status doSearchUserInfo(ServerContext *context, const searchUserReq *request,
                            searchUserRsq *reply) override
    {

        if (0 > request->id())
        {
            // ID不能为负
            reply->set_status(Const::StatusCode::ACCOUNT_NOTEXIST);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::ACCOUNT_NOTEXIST));
            return Status::OK;
        }
        // mtx.lock();

        UserDao userdao;
        bool ret = userdao.GetByID(request->id());
        if (!ret)
        {
            reply->set_status(Const::StatusCode::SERACH_FAILD);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::SERACH_FAILD));
            return Status::OK;
        }
        reply->set_money(userdao.money());
        reply->set_name(userdao.name());
        vector<BagDao> bags;
        BagDao bag;
        bags = bag.Get(request->id());
        for (BagDao b : bags)
        {
            searchUserRsq::baggood *good = reply->add_good();
            good->set_goodid(b.goodid());
            good->set_goodname(b.name());
            good->set_number(b.num());
        }
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));

        // mtx.unlock();
        return Status::OK;
    }

    Status doSearchGoodInfo(ServerContext *context, const searchGoodReq *request,
                            searchGoodRsq *reply) override
    {
        if (0 > request->id())
        {
            // ID不能为负
            reply->set_status(Const::StatusCode::GOOD_NOTEXIST);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_NOTEXIST));
            return Status::OK;
        }
        // mtx.lock();

        GoodDao gooddao;
        bool ret = gooddao.GetByID(request->id());
        if (!ret)
        {
            reply->set_status(Const::StatusCode::SERACH_FAILD);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::SERACH_FAILD));
            return Status::OK;
        }
        reply->set_goodname(gooddao.name());
        reply->set_kind(gooddao.kind());
        reply->set_level(gooddao.level());
        reply->set_career(gooddao.career());
        reply->set_grade(gooddao.grade());
        reply->set_color(gooddao.color());
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));

        // mtx.unlock();
        return Status::OK;
    }
};

void RunServer()
{

    // 读取配置文件
    config::ConfigModule conf;
    bool ret = conf.onLoad("./conf/config.ini");
    if (!ret)
    {
        exit(1);
        return;
    }
    string server_address = conf.getStringByKey("server_host") + ":" + conf.getStringByKey("server_port");

    ServerBuilder builder;
    BasicInfoServiceImpl service;

    // 在没有身份验证机制的情况下侦听给定地址。
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // 将"service"注册为我们将通过它与客户端通信的实例。 在这种情况下，它对应于synchronous服务。
    builder.RegisterService(&service);
    // 最后组装服务器。
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "BasicInfoServer Listening on " << server_address << endl;
    // 最后组装服务器。
    server->Wait();
}

int main(int argc, const char *argv[])
{

    // 读取配置文件
    config::ConfigModule conf;
    conf.onLoad("./conf/config.ini");

    // 从mysql连接池选择连接
    MysqlPool *pool = MysqlPool::Pool();
    pool->Init(&conf, conf.getIntByKey("mysql_pool"));

    RunServer();
    MysqlPool::Free();

    return 0;
}