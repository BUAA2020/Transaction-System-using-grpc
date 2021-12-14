#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <ctime>
#include <cstdlib>

#include "mysql.h"
#include <grpcpp/grpcpp.h>
#include "protos/MallService.grpc.pb.h"
#include "configmodule.h"
#include "const.h"
#include "userdao.h"
#include "gooddao.h"
#include "bagdao.h"
#include "onsalegooddao.h"
#include "tradedao.h"
#include "datetime.h"

using namespace std;

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

using myApplication::ListSpecialGoodReq;
using myApplication::ListSpecialGoodRsq;
using myApplication::MallService;
using myApplication::ManageTradesReq;
using myApplication::ManageTradesRsq;
using myApplication::PurchaseReq;
using myApplication::PurchaseRsq;
using myApplication::SaleReq;
using myApplication::SaleRsq;
using myApplication::SearchOnSaleGoodsReq;
using myApplication::SearchOnSaleGoodsRsq;

/**
 *  RPC回调方法
 */
class MallServiceImpl final : public MallService::Service
{

    Status doSearchOnSaleGoods(ServerContext *context, const SearchOnSaleGoodsReq *request,
                               SearchOnSaleGoodsRsq *reply) override
    {
        OnSaleGoodDao onsalegood;
        if ("" == request->goodname())
        {
            // 名称不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }
        bool ret = onsalegood.GetByName(request->goodname()); //通过道具名称查找
        if (!ret)
        {
            reply->set_status(Const::StatusCode::SERACH_FAILD);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::SERACH_FAILD));
            return Status::OK;
        }
        //查找此名字道具的相关信息
        vector<OnSaleGoodDao> allgood;
        OnSaleGoodDao goodInfo;
        goodInfo.GetByName(request->goodname());
        allgood = goodInfo.Get(goodInfo.onsalegoodid());

        for (OnSaleGoodDao b : allgood)
        {
            SearchOnSaleGoodsRsq::goods *good = reply->add_good();
            good->set_goodid(b.onsalegoodid());
            good->set_goodname(b.name());
            good->set_tradeamount(b.price());
            good->set_userid(b.userid());
            good->set_storeid(b.storeid());
        }

        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        return Status::OK;
    }

    Status doListSpecialGood(ServerContext *context, const ListSpecialGoodReq *request,
                             ListSpecialGoodRsq *reply) override
    {
        OnSaleGoodDao onsalegood;
        vector<OnSaleGoodDao> allgood;

        if (request->specailnum() < 0)
        {
            reply->set_status(Const::StatusCode::INPUT_ERROR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::INPUT_ERROR));
            return Status::OK;
        }

        allgood = onsalegood.GetSpecial(request->specailnum());
        for (OnSaleGoodDao b : allgood)
        {
            ListSpecialGoodRsq::goods *good = reply->add_good();
            good->set_goodid(b.onsalegoodid());
            good->set_goodname(b.name());
            good->set_tradeamount(b.price());
            good->set_userid(b.userid());
        }
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        return Status::OK;
    }

    Status doPurchase(ServerContext *context, const PurchaseReq *request,
                      PurchaseRsq *reply) override
    {
        OnSaleGoodDao onsalegood;
        BagDao bag;
        GoodDao good;
        UserDao user;  //买家
        UserDao saler; //卖家

        if (request->goodspecial() != 0 && request->goodspecial() != 1)
        {
            reply->set_status(Const::StatusCode::GOODSPECIAL_MISTAKE);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOODSPECIAL_MISTAKE));
            return Status::OK;
        }

        if (request->goodid() < 0 || request->salerid() < 0 || request->id() < 0 || request->num() < 0 || request->money() < 0 || request->id() == request->salerid())
        {
            reply->set_status(Const::StatusCode::INPUT_ERROR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::INPUT_ERROR));
            return Status::OK;
        }

        if (!user.GetByID(request->id()) || !saler.GetByID(request->salerid()))
        {
            reply->set_status(Const::StatusCode::ACCOUNT_NOTEXIST);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::ACCOUNT_NOTEXIST));
            return Status::OK;
        }

        user.GetByID(request->id());
        saler.GetByID(request->salerid());
        bool ret = onsalegood.GetById(request->salerid(), request->goodid());
        vector<TradeDao> trades;
        if (user.money() < request->money() * request->num()) //单价*数量
        {
            reply->set_status(Const::StatusCode::MONEY_POOR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::MONEY_POOR));
            return Status::OK;
        }
        if (!ret)
        {
            reply->set_status(Const::StatusCode::GOOD_POOR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_POOR));
            return Status::OK;
        }

        //1.更新OnSaleGood表
        if (onsalegood.number() > request->num())
        {
            onsalegood.set_number(onsalegood.number() - request->num());
            if (!onsalegood.Update())
            {
                reply->set_status(Const::StatusCode::GOOD_POOR);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_POOR));
                return Status::OK;
            }
        }
        else if (onsalegood.number() == request->num())
        {
            if (!onsalegood.Delete())
            {
                reply->set_status(Const::StatusCode::GOOD_POOR);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_POOR));
                return Status::OK;
            }
        }
        else
        {
            reply->set_status(Const::StatusCode::GOOD_POOR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_POOR));
            return Status::OK;
        }

        //2.更新trade表
        //i=1 购买； i=2 出售

        TradeDao trade;
        trade.set_goodid(request->goodid());
        trade.set_trade_group_id(1);
        trade.set_trade_money(request->money() * request->num());
        trade.set_userid(request->id());
        trade.Create();
        trade.set_trade_group_id(2);
        trade.set_userid(request->salerid());
        trade.Create();

        //3.更新买家金币
        user.set_money(user.money() - request->money() * request->num());
        user.Update();

        //3.更新卖家金币
        saler.set_money(saler.money() + request->money() * request->num());
        saler.Update();

        //5.更新买家bag表
        if (bag.GetById(request->goodid(), request->id()))
        {
            bag.set_num(bag.num() + request->num());
            bag.Update();
        }
        else
        {
            bag.set_num(request->num());
            bag.set_name(onsalegood.name());
            bag.set_userid(request->id());
            bag.set_goodid(request->goodid());
            if (!bag.Create())
            {
                reply->set_status(Const::StatusCode::BAG_FAILD);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::BAG_FAILD));
                return Status::OK;
            }
        }

        //成功回执
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        return Status::OK;
    }

    Status doManageTrades(ServerContext *context, const ManageTradesReq *request,
                          ManageTradesRsq *reply) override
    {
        if (0 >= request->userid())
        {
            // 搜索的用户id不能为空
            reply->set_status(Const::StatusCode::NAME_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::NAME_EMPTY));
            return Status::OK;
        }
        TradeDao tradedao;
        vector<TradeDao> trades;
        trades = tradedao.Get(request->userid());

        if (trades.size() == 0)
        {
            reply->set_status(Const::StatusCode::TRADE_EMPTY);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::TRADE_EMPTY));
            return Status::OK;
        }
        for (TradeDao t : trades)
        {
            ManageTradesRsq::trade *td = reply->add_trades();
            td->set_goodid(t.goodid());
            td->set_kind(t.trade_group_id());
            td->set_tradeid(t.id());
            td->set_trademoney(t.trade_money());
            td->set_tradetime(t.trade_time());
            td->set_userid(t.userid());
        }
        //成功回执
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
        return Status::OK;
    }

    Status doSale(ServerContext *context, const SaleReq *request,
                  SaleRsq *reply) override
    {
        OnSaleGoodDao onsalegood;
        BagDao bag;
        GoodDao good;

        if (request->goodspecial() != 0 && request->goodspecial() != 1)
        {
            reply->set_status(Const::StatusCode::GOODSPECIAL_MISTAKE);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOODSPECIAL_MISTAKE));
            return Status::OK;
        }

        if (request->goodid() < 0 || request->id() < 0 || request->num() < 0 || request->money() < 0)
        {
            reply->set_status(Const::StatusCode::INPUT_ERROR);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::INPUT_ERROR));
            return Status::OK;
        }

        if (request->kind() == 1) //上架道具
        {
            //更新bag表
            if (bag.GetById(request->goodid(), request->id()))
            {
                if (bag.num() > request->num())
                {
                    bag.set_num(bag.num() - request->num());
                    bag.Update();
                }

                else if (bag.num() == request->num())
                {
                    bag.Delete();
                    // 删除后，不需要更新
                    // bag.Update();
                }

                else
                {
                    reply->set_status(Const::StatusCode::GOOD_POOR);
                    reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_POOR));
                    return Status::OK;
                }
            }
            else
            {
                reply->set_status(Const::StatusCode::GOOD_NOTEXIST);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::GOOD_NOTEXIST));
                return Status::OK;
            }

            //更新OnSaleGood表
            if (onsalegood.GetById(request->id(), request->goodid()))
            {
                onsalegood.set_number(onsalegood.number() + request->num());
                onsalegood.Update();
            }
            else
            {
                GoodDao forsalegood;
                forsalegood.GetByID(request->goodid());
                onsalegood.set_onsalegoodid(request->goodid());
                onsalegood.set_userid(request->id());
                onsalegood.set_price(request->money());
                onsalegood.set_number(request->num());
                onsalegood.set_name(forsalegood.name());
                onsalegood.set_isSpecial(request->goodspecial());
                if (!onsalegood.Create())
                {
                    reply->set_status(Const::StatusCode::ONSALE_FAILD);
                    reply->set_message(Const::GetStatusMsg(Const::StatusCode::ONSALE_FAILD));
                    return Status::OK;
                }
            }
        }
        else if (request->kind() == 2) //下架道具
        {
            //更新OnSaleGood表
            if (!onsalegood.GetById(request->id(), request->goodid()))
            {
                reply->set_status(Const::StatusCode::OFFSALE_FAILD);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::OFFSALE_FAILD));
                return Status::OK;
            }
            else if (onsalegood.userid() != request->id())
            {
                reply->set_status(Const::StatusCode::OFFSALE_FAILD);
                reply->set_message(Const::GetStatusMsg(Const::StatusCode::OFFSALE_FAILD));
                return Status::OK;
            }

            else
            {
                if (onsalegood.number() > request->num())
                {
                    onsalegood.set_number(onsalegood.number() - request->num());
                    onsalegood.Update();
                }
                else if (onsalegood.number() == request->num())
                {
                    onsalegood.Delete();
                    // onsalegood.Update();
                }
                else
                {
                    reply->set_status(Const::StatusCode::OFFSALE_FAILD);
                    reply->set_message(Const::GetStatusMsg(Const::StatusCode::OFFSALE_FAILD));
                    return Status::OK;
                }
            }

            //更新bag表
            if (bag.GetById(request->goodid(), request->id()))
            {
                bag.set_num(bag.num() + request->num());
                bag.Update();
            }
            else
            {
                bag.set_num(request->num());
                good.GetByID(request->goodid());
                bag.set_name(good.name());
                bag.set_goodid(good.id());
                bag.set_userid(request->id());
                if (!bag.Create())
                {
                    reply->set_status(Const::StatusCode::BAG_FAILD);
                    reply->set_message(Const::GetStatusMsg(Const::StatusCode::BAG_FAILD));
                    return Status::OK;
                }
            }
        }
        else
        {
            reply->set_status(Const::StatusCode::KIND_MISTAKE);
            reply->set_message(Const::GetStatusMsg(Const::StatusCode::KIND_MISTAKE));
            return Status::OK;
        }
        //成功回执
        reply->set_status(Const::StatusCode::OK);
        reply->set_message(Const::GetStatusMsg(Const::StatusCode::OK));
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
    MallServiceImpl service;

    // 在没有身份验证机制的情况下侦听给定地址。
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // 将"service"注册为我们将通过它与客户端通信的实例。 在这种情况下，它对应于synchronous服务。
    builder.RegisterService(&service);
    // 最后组装服务器。
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "MallServer Listening on " << server_address << endl;
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