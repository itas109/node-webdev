#include "napi.h"

class MyObject : public Napi::ObjectWrap<MyObject>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    MyObject(const Napi::CallbackInfo &info);

private:
    Napi::Value Method(const Napi::CallbackInfo &info);
};

Napi::Object MyObject::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "MyObject", {InstanceMethod("hello", &MyObject::Method)});

    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("MyObject", func);
    return exports;
}

MyObject::MyObject(const Napi::CallbackInfo &info) : Napi::ObjectWrap<MyObject>(info)
{

}

Napi::Value MyObject::Method(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, "hello world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    return MyObject::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)