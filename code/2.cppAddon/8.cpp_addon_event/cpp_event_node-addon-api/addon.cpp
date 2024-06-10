#include <napi.h>
#include "MyWrapper.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    MyWrapper::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)