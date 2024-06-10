#include <napi.h>

class MyWrapper : public Napi::ObjectWrap<MyWrapper>
{
public:
    MyWrapper(const Napi::CallbackInfo &info);
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

private:
    static Napi::FunctionReference constructor;

    Napi::Value helloMethod(const Napi::CallbackInfo &info);
    Napi::Value addMethod(const Napi::CallbackInfo &info);
    Napi::Value callEmitMethod(const Napi::CallbackInfo &info);
};