#include "napi.h"

#include <thread>

Napi::FunctionReference gCallback;

// thread-safe function context
struct ThreadSafeFunContext
{
    ThreadSafeFunContext(){};

    std::thread m_thread; // Native thread
    Napi::ThreadSafeFunction m_threadSafeFun;
};

// 4. js callback
void CallJS(Napi::Env env, Napi::Function callback, std::string *data)
{
    if (env && callback)
    {
        callback.Call({Napi::String::New(env, *data)});
    }
}

// 3. thread
void threadFunction(ThreadSafeFunContext *ctx)
{
    uint32_t count = 0;
    bool flag = true;

    // Perform a call into JavaScript.
    std::string result("init ok");
    napi_status status = ctx->m_threadSafeFun.BlockingCall(&result, CallJS);
    if (napi_ok != status)
    {
        Napi::Error::Fatal("threadFunction", "Napi::ThreadSafeNapi::Function.BlockingCall() failed");
    }

    while (flag)
    {
        if (++count > 3)
        {
            gCallback.Reset();
            break;
        }

        std::string str("callback from other thread");
        ctx->m_threadSafeFun.BlockingCall(&str,
                                          [](Napi::Env env, Napi::Function callback, std::string *str)
                                          {
                                              if (!gCallback.IsEmpty())
                                              {
                                                  gCallback.Call({Napi::String::New(gCallback.Env(), *str)});
                                              }
                                          });

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ctx->m_threadSafeFun.Release(); // Release the thread-safe function
}

// 5. Napi::ThreadSafeFunction Finalizer
void threadSafeFunFinalizer(Napi::Env env, void *finalDataPtr, ThreadSafeFunContext *ctx)
{
    if (ctx)
    {
        ctx->m_thread.join(); // Join the thread

        delete ctx;
        ctx = nullptr;
    }
}

// 2. call method
Napi::Value initMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    Napi::Function callback = info[0].As<Napi::Function>();

    ThreadSafeFunContext *ctx = new ThreadSafeFunContext();

    // Create ThreadSafeFunction
    ctx->m_threadSafeFun = Napi::ThreadSafeFunction::New(env,                    // Environment
                                                         callback,               // JS function from caller
                                                         "ThreadSafeFun",        // Resource name
                                                         0,                      // Max queue size (0 = unlimited).
                                                         1,                      // Initial thread count
                                                         ctx,                    // Context,
                                                         threadSafeFunFinalizer, // Finalizer
                                                         (void *)nullptr         // Finalizer data
    );

    ctx->m_thread = std::thread(threadFunction, ctx);

    return Napi::Boolean::New(env, true);
}

Napi::Value threadCallbackMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>();
    Napi::Function callback = info[1].As<Napi::Function>();

    gCallback = Napi::Persistent(callback);

    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["init"] = Napi::Function::New(env, initMethod);
    exports["threadCallback"] = Napi::Function::New(env, threadCallbackMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)