#include "../../js-native-api/common.h"
#include <node_api.h>

#include "myadd.h" // function myAdd

static napi_value helloMethod(napi_env env, napi_callback_info info)
{
    napi_value result;

    NAPI_CALL(env, napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, &result));

    return result;
}

static napi_value addMethod(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

    NAPI_ASSERT(env, argc >= 2, "Not enough arguments, expected 2.");

    napi_valuetype valuetype0, valuetype1;
    NAPI_CALL(env, napi_typeof(env, args[0], &valuetype0));
    NAPI_CALL(env, napi_typeof(env, args[1], &valuetype1));
    NAPI_ASSERT(env, valuetype0 == napi_number && valuetype1 == napi_number, "Wrong argument type. Numbers expected.");

    int x;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &x));
    int y;
    NAPI_CALL(env, napi_get_value_int32(env, args[1], &y));
    napi_value sum;
    NAPI_CALL(env, napi_create_double(env, myAdd(x, y), &sum));

    return sum;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {DECLARE_NAPI_PROPERTY("hello", helloMethod),
                                             DECLARE_NAPI_PROPERTY("add", addMethod)};

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(*properties), properties));

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)