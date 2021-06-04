#include <napi.h>

Napi::String Method(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, "hello world");
}

void helloCallbackMethod(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function callback = info[0].As<Napi::Function>();
  callback.Call(env.Global(), {Napi::String::New(env, "hello world callback")});
}

void callbackWithRecvMethod(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function callback = info[1].As<Napi::Function>();
  callback.Call(info[0], {});
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["hello"] = Napi::Function::New(env, Method);
    exports["helloCallback"] = Napi::Function::New(env, helloCallbackMethod);
    exports["callbackWithRecv"] = Napi::Function::New(env, callbackWithRecvMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)