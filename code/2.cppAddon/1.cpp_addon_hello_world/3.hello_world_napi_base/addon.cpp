#include <assert.h>
#include <node_api.h>

static napi_value helloMethod(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value result;

    status = napi_create_string_utf8(env, "hello world", 11, &result);
    assert(status == napi_ok);

    return result;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_status status;
    napi_property_descriptor desc = {"hello", 0, helloMethod, 0, 0, 0, napi_default, 0};

    status = napi_define_properties(env, exports, 1, &desc);
    assert(status == napi_ok);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)