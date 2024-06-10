#include "napi.h"

#include <chrono>
#include <thread>

// thread-safe function context
struct ThreadSafeFunContext
{
    ThreadSafeFunContext(){};

    std::thread m_thread; // Native thread
    Napi::ThreadSafeFunction m_threadSafeFun;

    Napi::Function m_emit;
};

// 4. js callback
void CallJS(Napi::Env env, Napi::Function callback, void *data)
{
    if (env && callback)
    {
        callback.Call({Napi::String::New(env, "data"), Napi::String::New(env, (char *)data)});
    }
}

// 3. thread
void threadFunction(ThreadSafeFunContext *ctx)
{
    uint32_t count = 0;
    bool flag = true;
    while (flag)
    {
        // do something
        char *data = nullptr;
        if (++count > 3)
        {
            // stop when count > 3
            flag = false;
            data = "stop when count > 3";
        }
        else
        {
            data = "do something";
        }

        // Perform a call into JavaScript.
        napi_status status = ctx->m_threadSafeFun.BlockingCall((void *)data, CallJS);
        if (napi_ok != status)
        {
            Napi::Error::Fatal("threadFunction", "Napi::ThreadSafeNapi::Function.BlockingCall() failed");
        }

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
Napi::Value callEmitMethod(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    Napi::Function emit = info[0].As<Napi::Function>();

    emit.Call({Napi::String::New(env, "start")});

    ThreadSafeFunContext *ctx = new ThreadSafeFunContext();

    // Create ThreadSafeFunction
    ctx->m_threadSafeFun = Napi::ThreadSafeFunction::New(env,                    // Environment
                                                         emit,                   // JS function from caller
                                                         "ThreadSafeFun",        // Resource name
                                                         0,                      // Max queue size (0 = unlimited).
                                                         1,                      // Initial thread count
                                                         ctx,                    // Context,
                                                         threadSafeFunFinalizer, // Finalizer
                                                         (void *)nullptr         // Finalizer data
    );

    ctx->m_thread = std::thread(threadFunction, ctx);

    ctx->m_emit = emit;

    return Napi::Boolean::New(env, true);
}

// 1. init
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["callEmit"] = Napi::Function::New(env, callEmitMethod);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)