#include <napi.h>

Napi::String Method(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, "hello world");
}

Napi::Value AddMethod(const Napi::CallbackInfo &info)
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

Napi::String returnSelfMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    return info[0].As<Napi::String>();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["hello"] = Napi::Function::New(env, Method);
    exports["add"] = Napi::Function::New(env, AddMethod);
    exports["returnSelf"] = Napi::Function::New(env, returnSelfMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)