#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "../lib/configmodule.h"

#include "../lib/datetime.h"
#include "protos/basicInfoService.grpc.pb.h"

using namespace std;

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
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

class BasicInfoClient
{
public:
    BasicInfoClient(shared_ptr<Channel> channel)
        : stub_(BasicInfoService::NewStub(channel)) {}

    string doLogin(const string &user, const string &pass)
    {
        loginReq request;
        request.set_username(user);
        request.set_password(pass);
        loginRsq reply;
        ClientContext context;

        Status status = stub_->doLogin(&context, request, &reply);

        if (status.ok())
        {
            cout << "doLogin Status : " << reply.status() << endl;
            return reply.message();
        }
        else
        {
            cout << status.error_code() << ": " << status.error_message() << endl;

            return "RPC failed";
        }
    }

private:
    unique_ptr<BasicInfoService::Stub> stub_;
};

void SyncRPC()
{
    config::ConfigModule conf;
    bool ret = conf.onLoad("config.ini");
    if(!ret) {
        exit(1);

        return ;
    }
    string server_address = conf.getStringByKey("server_host") + ":" + conf.getStringByKey("server_port");
    string user(conf.getStringByKey("user"));
    string pass(conf.getStringByKey("pass"));
    BasicInfoClient login(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
    string sign = login.doLogin(user, pass);
    cout << "OnSign message: " << sign << endl;
    return;
}

int main(int argc, const char *argv[])
{
    SyncRPC();
    return 0;
}