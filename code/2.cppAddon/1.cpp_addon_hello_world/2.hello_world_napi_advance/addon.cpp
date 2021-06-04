#include "../../js-native-api/common.h"
#include <node_api.h>

static napi_value helloMethod(napi_env env, napi_callback_info info)
{
    napi_value result;

    NAPI_CALL(env, napi_create_string_utf8(env, "hello world", 11, &result));

    return result;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {DECLARE_NAPI_PROPERTY("hello", helloMethod)};

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(*properties), properties));

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)