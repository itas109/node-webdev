#include <napi.h>

#define SHOW_THREAD_INFO

#ifdef SHOW_THREAD_INFO
#include <iostream>
#include <thread>
#endif

class AsyncDoWorker : public Napi::AsyncWorker
{
public:
    AsyncDoWorker(std::string &input, Napi::Function &callback) : Napi::AsyncWorker(callback), input(input) {}

    ~AsyncDoWorker() {}

    void Execute() override
    {
#ifdef SHOW_THREAD_INFO
        std::cout << "[C++] AsyncDoWorker::Execute thread id: " << std::this_thread::get_id() << std::endl;
#endif
        // This code will be executed on the worker thread
        // do something
        output = input;
    }

    void OnOK() override
    {
#ifdef SHOW_THREAD_INFO
        std::cout << "[C++] AsyncDoWorker::OnOK thread id: " << std::this_thread::get_id() << std::endl;
#endif
        Napi::HandleScope scope(Env());
        Callback().Call(Env().Global(),{Napi::String::New(Env(), output)});
    }

    void OnError(const Napi::Error &e)
    {
        Napi::HandleScope scope(Env());
        // Pass error onto JS, no data for other parameters
        Callback().Call(Env().Global(),{Napi::String::New(Env(), e.Message())});
    }

private:
    std::string input;
    std::string output;
};

Napi::Value asyncDoWorkMethod(const Napi::CallbackInfo &info)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] asyncDoWorkMethod thread id: " << std::this_thread::get_id() << std::endl;
#endif

    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>();
    Napi::Function callback = info[1].As<Napi::Function>();

    AsyncDoWorker *work = new AsyncDoWorker(input, callback);
    work->Queue();

    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] Init thread id: " << std::this_thread::get_id() << std::endl;
#endif

    exports["asyncDoWork"] = Napi::Function::New(env, asyncDoWorkMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)