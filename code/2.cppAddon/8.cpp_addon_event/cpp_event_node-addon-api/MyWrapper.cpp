#include <chrono>
#include <iostream>
#include <thread>

#include "MyWrapper.h"

Napi::FunctionReference MyWrapper::constructor;

Napi::Object MyWrapper::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "MyWrapper",
                                      {
                                          InstanceMethod("hello", &MyWrapper::helloMethod),      // hello
                                          InstanceMethod("add", &MyWrapper::addMethod),          // add
                                          InstanceMethod("callEmit", &MyWrapper::callEmitMethod) // callEmit
                                      });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("MyWrapper", func);
    return exports;
}

MyWrapper::MyWrapper(const Napi::CallbackInfo &info) : Napi::ObjectWrap<MyWrapper>(info) {}

Napi::Value MyWrapper::helloMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, "hello world");
}

Napi::Value MyWrapper::addMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    double arg0 = info[0].As<Napi::Number>().DoubleValue();
    double arg1 = info[1].As<Napi::Number>().DoubleValue();
    Napi::Number sum = Napi::Number::New(env, arg0 + arg1);

    return sum;
}

Napi::Value MyWrapper::callEmitMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Function emit = info.This().As<Napi::Object>().Get("emit").As<Napi::Function>();
    for (int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        emit.Call(info.This(), {Napi::String::New(env, "data"), Napi::String::New(env, "data ...")});
    }
    return Napi::String::New(env, "OK");
}