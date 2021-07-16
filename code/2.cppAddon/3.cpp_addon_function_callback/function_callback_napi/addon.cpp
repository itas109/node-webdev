#include "../../js-native-api/common.h"
#include <node_api.h>

static napi_value helloMethod(napi_env env, napi_callback_info info)
{
    napi_value result;

    NAPI_CALL(env, napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, &result));

    return result;
}

static napi_value helloCallbackMethod(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));
    NAPI_ASSERT(env, argc == 1, "Wrong number of arguments. Expects a single argument.");

    napi_valuetype valuetype0;
    NAPI_CALL(env, napi_typeof(env, args[0], &valuetype0));
    NAPI_ASSERT(env, valuetype0 == napi_function, "Wrong type of arguments. Expects a function as first argument.");

    napi_value argv[1];
    const char *str = "hello world callback";
    NAPI_CALL(env, napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, argv));

    napi_value global;
    NAPI_CALL(env, napi_get_global(env, &global));

    napi_value cb = args[0]; // callback function
    NAPI_CALL(env, napi_call_function(env, global, cb, 1, argv, NULL));

    return NULL;
}

static napi_value callbackWithRecvMethod(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

    napi_value recv = args[0];
    napi_value cb = args[1]; // callback function
    NAPI_CALL(env, napi_call_function(env, recv, cb, 0, NULL, NULL));
    return NULL;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {DECLARE_NAPI_PROPERTY("hello", helloMethod),
                                             DECLARE_NAPI_PROPERTY("helloCallback", helloCallbackMethod),
                                             DECLARE_NAPI_PROPERTY("callbackWithRecv", callbackWithRecvMethod)};

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(*properties), properties));

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)