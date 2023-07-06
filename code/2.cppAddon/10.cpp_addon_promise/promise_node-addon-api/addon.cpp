#include "napi.h"

class AsyncDoWorker : public Napi::AsyncWorker
{
public:
    AsyncDoWorker(Napi::Promise::Deferred deferred, std::string &input)
        : Napi::AsyncWorker(deferred.Env()), m_deferred(deferred), input(input), isEnableCallback(false)
    {
    }

    AsyncDoWorker(Napi::Promise::Deferred deferred, std::string &input, Napi::Function &callback)
        : Napi::AsyncWorker(callback), m_deferred(deferred), input(input), isEnableCallback(true)
    {
    }

    ~AsyncDoWorker() {}

    void Execute() override
    {
        // This code will be executed on the worker thread
        // do something
        output = input;
    }

    void OnOK() override
    {
        if (isEnableCallback)
        {
            Napi::HandleScope scope(Env());
            Callback().Call(Env().Global(), {Napi::String::New(Env(), output)});
        }

        m_deferred.Resolve(Napi::String::New(Env(), output));
    }

    void OnError(const Napi::Error &e) override
    {
        if (isEnableCallback)
        {
            Napi::HandleScope scope(Env());
            Callback().Call(Env().Global(), {Napi::String::New(Env(), e.Message())});
        }

        m_deferred.Resolve(Napi::String::New(Env(), e.Message()));
    }

private:
    Napi::Promise::Deferred m_deferred;
    bool isEnableCallback;

    std::string input;
    std::string output;
};

Napi::Value asyncDoWorkPromiseMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>();
    Napi::Function callback = info[1].As<Napi::Function>();

    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

    AsyncDoWorker *work =
        callback.IsFunction() ? new AsyncDoWorker(deferred, input, callback) : new AsyncDoWorker(deferred, input);
    work->Queue();

    return deferred.Promise();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["asyncDoWorkPromise"] = Napi::Function::New(env, asyncDoWorkPromiseMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)