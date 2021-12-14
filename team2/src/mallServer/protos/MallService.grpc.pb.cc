// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: MallService.proto

#include "MallService.pb.h"
#include "MallService.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace myApplication {

static const char* MallService_method_names[] = {
  "/myApplication.MallService/doSearchOnSaleGoods",
  "/myApplication.MallService/doListSpecialGood",
  "/myApplication.MallService/doPurchase",
  "/myApplication.MallService/doManageTrades",
  "/myApplication.MallService/doSale",
};

std::unique_ptr< MallService::Stub> MallService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MallService::Stub> stub(new MallService::Stub(channel, options));
  return stub;
}

MallService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_doSearchOnSaleGoods_(MallService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doListSpecialGood_(MallService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doPurchase_(MallService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doManageTrades_(MallService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_doSale_(MallService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MallService::Stub::doSearchOnSaleGoods(::grpc::ClientContext* context, const ::myApplication::SearchOnSaleGoodsReq& request, ::myApplication::SearchOnSaleGoodsRsq* response) {
  return ::grpc::internal::BlockingUnaryCall< ::myApplication::SearchOnSaleGoodsReq, ::myApplication::SearchOnSaleGoodsRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doSearchOnSaleGoods_, context, request, response);
}

void MallService::Stub::async::doSearchOnSaleGoods(::grpc::ClientContext* context, const ::myApplication::SearchOnSaleGoodsReq* request, ::myApplication::SearchOnSaleGoodsRsq* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::myApplication::SearchOnSaleGoodsReq, ::myApplication::SearchOnSaleGoodsRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doSearchOnSaleGoods_, context, request, response, std::move(f));
}

void MallService::Stub::async::doSearchOnSaleGoods(::grpc::ClientContext* context, const ::myApplication::SearchOnSaleGoodsReq* request, ::myApplication::SearchOnSaleGoodsRsq* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doSearchOnSaleGoods_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::myApplication::SearchOnSaleGoodsRsq>* MallService::Stub::PrepareAsyncdoSearchOnSaleGoodsRaw(::grpc::ClientContext* context, const ::myApplication::SearchOnSaleGoodsReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::myApplication::SearchOnSaleGoodsRsq, ::myApplication::SearchOnSaleGoodsReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doSearchOnSaleGoods_, context, request);
}

::grpc::ClientAsyncResponseReader< ::myApplication::SearchOnSaleGoodsRsq>* MallService::Stub::AsyncdoSearchOnSaleGoodsRaw(::grpc::ClientContext* context, const ::myApplication::SearchOnSaleGoodsReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoSearchOnSaleGoodsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MallService::Stub::doListSpecialGood(::grpc::ClientContext* context, const ::myApplication::ListSpecialGoodReq& request, ::myApplication::ListSpecialGoodRsq* response) {
  return ::grpc::internal::BlockingUnaryCall< ::myApplication::ListSpecialGoodReq, ::myApplication::ListSpecialGoodRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doListSpecialGood_, context, request, response);
}

void MallService::Stub::async::doListSpecialGood(::grpc::ClientContext* context, const ::myApplication::ListSpecialGoodReq* request, ::myApplication::ListSpecialGoodRsq* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::myApplication::ListSpecialGoodReq, ::myApplication::ListSpecialGoodRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doListSpecialGood_, context, request, response, std::move(f));
}

void MallService::Stub::async::doListSpecialGood(::grpc::ClientContext* context, const ::myApplication::ListSpecialGoodReq* request, ::myApplication::ListSpecialGoodRsq* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doListSpecialGood_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::myApplication::ListSpecialGoodRsq>* MallService::Stub::PrepareAsyncdoListSpecialGoodRaw(::grpc::ClientContext* context, const ::myApplication::ListSpecialGoodReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::myApplication::ListSpecialGoodRsq, ::myApplication::ListSpecialGoodReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doListSpecialGood_, context, request);
}

::grpc::ClientAsyncResponseReader< ::myApplication::ListSpecialGoodRsq>* MallService::Stub::AsyncdoListSpecialGoodRaw(::grpc::ClientContext* context, const ::myApplication::ListSpecialGoodReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoListSpecialGoodRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MallService::Stub::doPurchase(::grpc::ClientContext* context, const ::myApplication::PurchaseReq& request, ::myApplication::PurchaseRsq* response) {
  return ::grpc::internal::BlockingUnaryCall< ::myApplication::PurchaseReq, ::myApplication::PurchaseRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doPurchase_, context, request, response);
}

void MallService::Stub::async::doPurchase(::grpc::ClientContext* context, const ::myApplication::PurchaseReq* request, ::myApplication::PurchaseRsq* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::myApplication::PurchaseReq, ::myApplication::PurchaseRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doPurchase_, context, request, response, std::move(f));
}

void MallService::Stub::async::doPurchase(::grpc::ClientContext* context, const ::myApplication::PurchaseReq* request, ::myApplication::PurchaseRsq* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doPurchase_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::myApplication::PurchaseRsq>* MallService::Stub::PrepareAsyncdoPurchaseRaw(::grpc::ClientContext* context, const ::myApplication::PurchaseReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::myApplication::PurchaseRsq, ::myApplication::PurchaseReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doPurchase_, context, request);
}

::grpc::ClientAsyncResponseReader< ::myApplication::PurchaseRsq>* MallService::Stub::AsyncdoPurchaseRaw(::grpc::ClientContext* context, const ::myApplication::PurchaseReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoPurchaseRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MallService::Stub::doManageTrades(::grpc::ClientContext* context, const ::myApplication::ManageTradesReq& request, ::myApplication::ManageTradesRsq* response) {
  return ::grpc::internal::BlockingUnaryCall< ::myApplication::ManageTradesReq, ::myApplication::ManageTradesRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doManageTrades_, context, request, response);
}

void MallService::Stub::async::doManageTrades(::grpc::ClientContext* context, const ::myApplication::ManageTradesReq* request, ::myApplication::ManageTradesRsq* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::myApplication::ManageTradesReq, ::myApplication::ManageTradesRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doManageTrades_, context, request, response, std::move(f));
}

void MallService::Stub::async::doManageTrades(::grpc::ClientContext* context, const ::myApplication::ManageTradesReq* request, ::myApplication::ManageTradesRsq* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doManageTrades_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::myApplication::ManageTradesRsq>* MallService::Stub::PrepareAsyncdoManageTradesRaw(::grpc::ClientContext* context, const ::myApplication::ManageTradesReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::myApplication::ManageTradesRsq, ::myApplication::ManageTradesReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doManageTrades_, context, request);
}

::grpc::ClientAsyncResponseReader< ::myApplication::ManageTradesRsq>* MallService::Stub::AsyncdoManageTradesRaw(::grpc::ClientContext* context, const ::myApplication::ManageTradesReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoManageTradesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MallService::Stub::doSale(::grpc::ClientContext* context, const ::myApplication::SaleReq& request, ::myApplication::SaleRsq* response) {
  return ::grpc::internal::BlockingUnaryCall< ::myApplication::SaleReq, ::myApplication::SaleRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_doSale_, context, request, response);
}

void MallService::Stub::async::doSale(::grpc::ClientContext* context, const ::myApplication::SaleReq* request, ::myApplication::SaleRsq* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::myApplication::SaleReq, ::myApplication::SaleRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doSale_, context, request, response, std::move(f));
}

void MallService::Stub::async::doSale(::grpc::ClientContext* context, const ::myApplication::SaleReq* request, ::myApplication::SaleRsq* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_doSale_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::myApplication::SaleRsq>* MallService::Stub::PrepareAsyncdoSaleRaw(::grpc::ClientContext* context, const ::myApplication::SaleReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::myApplication::SaleRsq, ::myApplication::SaleReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_doSale_, context, request);
}

::grpc::ClientAsyncResponseReader< ::myApplication::SaleRsq>* MallService::Stub::AsyncdoSaleRaw(::grpc::ClientContext* context, const ::myApplication::SaleReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdoSaleRaw(context, request, cq);
  result->StartCall();
  return result;
}

MallService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MallService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MallService::Service, ::myApplication::SearchOnSaleGoodsReq, ::myApplication::SearchOnSaleGoodsRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MallService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::myApplication::SearchOnSaleGoodsReq* req,
             ::myApplication::SearchOnSaleGoodsRsq* resp) {
               return service->doSearchOnSaleGoods(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MallService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MallService::Service, ::myApplication::ListSpecialGoodReq, ::myApplication::ListSpecialGoodRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MallService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::myApplication::ListSpecialGoodReq* req,
             ::myApplication::ListSpecialGoodRsq* resp) {
               return service->doListSpecialGood(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MallService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MallService::Service, ::myApplication::PurchaseReq, ::myApplication::PurchaseRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MallService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::myApplication::PurchaseReq* req,
             ::myApplication::PurchaseRsq* resp) {
               return service->doPurchase(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MallService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MallService::Service, ::myApplication::ManageTradesReq, ::myApplication::ManageTradesRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MallService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::myApplication::ManageTradesReq* req,
             ::myApplication::ManageTradesRsq* resp) {
               return service->doManageTrades(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MallService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MallService::Service, ::myApplication::SaleReq, ::myApplication::SaleRsq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MallService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::myApplication::SaleReq* req,
             ::myApplication::SaleRsq* resp) {
               return service->doSale(ctx, req, resp);
             }, this)));
}

MallService::Service::~Service() {
}

::grpc::Status MallService::Service::doSearchOnSaleGoods(::grpc::ServerContext* context, const ::myApplication::SearchOnSaleGoodsReq* request, ::myApplication::SearchOnSaleGoodsRsq* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MallService::Service::doListSpecialGood(::grpc::ServerContext* context, const ::myApplication::ListSpecialGoodReq* request, ::myApplication::ListSpecialGoodRsq* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MallService::Service::doPurchase(::grpc::ServerContext* context, const ::myApplication::PurchaseReq* request, ::myApplication::PurchaseRsq* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MallService::Service::doManageTrades(::grpc::ServerContext* context, const ::myApplication::ManageTradesReq* request, ::myApplication::ManageTradesRsq* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MallService::Service::doSale(::grpc::ServerContext* context, const ::myApplication::SaleReq* request, ::myApplication::SaleRsq* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace myApplication
