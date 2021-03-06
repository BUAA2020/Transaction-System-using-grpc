// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: SecKillService.proto
#ifndef GRPC_SecKillService_2eproto__INCLUDED
#define GRPC_SecKillService_2eproto__INCLUDED

#include "SecKillService.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace myApplication {

class SeckillService final {
 public:
  static constexpr char const* service_full_name() {
    return "myApplication.SeckillService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::myApplication::SecKillRsq* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>> AsyncdoSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>>(AsyncdoSecKillRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>> PrepareAsyncdoSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>>(PrepareAsyncdoSecKillRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response, std::function<void(::grpc::Status)>) = 0;
      virtual void doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>* AsyncdoSecKillRaw(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::myApplication::SecKillRsq>* PrepareAsyncdoSecKillRaw(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::myApplication::SecKillRsq* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>> AsyncdoSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>>(AsyncdoSecKillRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>> PrepareAsyncdoSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>>(PrepareAsyncdoSecKillRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response, std::function<void(::grpc::Status)>) override;
      void doSecKill(::grpc::ClientContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>* AsyncdoSecKillRaw(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::myApplication::SecKillRsq>* PrepareAsyncdoSecKillRaw(::grpc::ClientContext* context, const ::myApplication::SecKillReq& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_doSecKill_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status doSecKill(::grpc::ServerContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_doSecKill() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestdoSecKill(::grpc::ServerContext* context, ::myApplication::SecKillReq* request, ::grpc::ServerAsyncResponseWriter< ::myApplication::SecKillRsq>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_doSecKill<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_doSecKill() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::myApplication::SecKillReq, ::myApplication::SecKillRsq>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::myApplication::SecKillReq* request, ::myApplication::SecKillRsq* response) { return this->doSecKill(context, request, response); }));}
    void SetMessageAllocatorFor_doSecKill(
        ::grpc::MessageAllocator< ::myApplication::SecKillReq, ::myApplication::SecKillRsq>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::myApplication::SecKillReq, ::myApplication::SecKillRsq>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* doSecKill(
      ::grpc::CallbackServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_doSecKill<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_doSecKill() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_doSecKill() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestdoSecKill(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_doSecKill() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->doSecKill(context, request, response); }));
    }
    ~WithRawCallbackMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* doSecKill(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_doSecKill : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_doSecKill() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::myApplication::SecKillReq, ::myApplication::SecKillRsq>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::myApplication::SecKillReq, ::myApplication::SecKillRsq>* streamer) {
                       return this->StreameddoSecKill(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_doSecKill() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status doSecKill(::grpc::ServerContext* /*context*/, const ::myApplication::SecKillReq* /*request*/, ::myApplication::SecKillRsq* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreameddoSecKill(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::myApplication::SecKillReq,::myApplication::SecKillRsq>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_doSecKill<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_doSecKill<Service > StreamedService;
};

}  // namespace myApplication


#endif  // GRPC_SecKillService_2eproto__INCLUDED
