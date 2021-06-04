#include "../../js-native-api/common.h"
#include <node_api.h>

static napi_value helloMethod(napi_env env, napi_callback_info info)
{
    napi_value result;

    NAPI_CALL(env, napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, &result));

    return result;
}

static napi_value AddMethod(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

    NAPI_ASSERT(env, argc >= 2, "Not enough arguments, expected 2.");

    napi_valuetype valuetype0, valuetype1;
    NAPI_CALL(env, napi_typeof(env, args[0], &valuetype0));
    NAPI_CALL(env, napi_typeof(env, args[1], &valuetype1));
    NAPI_ASSERT(env, valuetype0 == napi_number && valuetype1 == napi_number, "Wrong argument type. Numbers expected.");

    double value0;
    NAPI_CALL(env, napi_get_value_double(env, args[0], &value0));
    double value1;
    NAPI_CALL(env, napi_get_value_double(env, args[1], &value1));
    napi_value sum;
    NAPI_CALL(env, napi_create_double(env, value0 + value1, &sum));

    return sum;
}

static napi_value returnSelfMethod(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));

    NAPI_ASSERT(env, argc >= 1, "Not enough arguments, expected 1.");

    napi_valuetype valuetype;
    NAPI_CALL(env, napi_typeof(env, argv[0], &valuetype));
    NAPI_ASSERT(env, valuetype == napi_string, "Wrong argument type. String expected.");

    size_t realSize = 0;
    NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], nullptr, 0, &realSize)); // get real length

    char *str = nullptr;
    str = new char[realSize + 1];                                                           // +1 for '\0'
    NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], str, realSize + 1, &realSize)); // +1 for '\0'

    napi_value result;
    NAPI_CALL(env, napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, &result));

    delete[] str;
    str = nullptr;

    return result;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {DECLARE_NAPI_PROPERTY("hello", helloMethod),
                                             DECLARE_NAPI_PROPERTY("add", AddMethod),
                                             DECLARE_NAPI_PROPERTY("returnSelf", returnSelfMethod)};

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(*properties), properties));

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)