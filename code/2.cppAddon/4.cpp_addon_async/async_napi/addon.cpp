#include "../../js-native-api/common.h"
#include <node_api.h>
#include <string>

#define SHOW_THREAD_INFO

#ifdef SHOW_THREAD_INFO
#include <iostream>
#include <thread>
#endif

typedef struct
{
    std::string _input;       // input param
    std::string _output;      // output param
    napi_ref _callback;       // callback function
    napi_async_work _request; // async work
} carrier;

// carrier the_carrier;

void Execute(napi_env env, void *data)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] Execute thread id: " << std::this_thread::get_id() << std::endl;
#endif
    carrier *the_carrier = static_cast<carrier *>(data);

    // do something
    the_carrier->_output = the_carrier->_input;
}

void Complete(napi_env env, napi_status status, void *data)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] Complete thread id: " << std::this_thread::get_id() << std::endl;
#endif
    carrier *the_carrier = static_cast<carrier *>(data);

    if (status != napi_ok)
    {
        napi_throw_type_error(env, nullptr, "Execute callback failed.");
        return;
    }

    // string result
    napi_value argv[1];
    NAPI_CALL_RETURN_VOID(env, napi_create_string_utf8(env, the_carrier->_output.c_str(), NAPI_AUTO_LENGTH, &argv[0]));

    napi_value callback;
    NAPI_CALL_RETURN_VOID(env, napi_get_reference_value(env, the_carrier->_callback, &callback));
    napi_value global;
    NAPI_CALL_RETURN_VOID(env, napi_get_global(env, &global));

    napi_value result;
    NAPI_CALL_RETURN_VOID(env, napi_call_function(env, global, callback, 1, argv, &result));

    NAPI_CALL_RETURN_VOID(env, napi_delete_reference(env, the_carrier->_callback));
    NAPI_CALL_RETURN_VOID(env, napi_delete_async_work(env, the_carrier->_request));

    // release asyncDoWorkMethod's the_carrier point when complete
    if (the_carrier)
    {
        delete the_carrier;
        the_carrier = nullptr;
    }
}

napi_value asyncDoWorkMethod(napi_env env, napi_callback_info info)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] asyncDoWorkMethod thread id: " << std::this_thread::get_id() << std::endl;
#endif
    size_t argc = 2;
    napi_value argv[2];
    napi_value _this;
    napi_value resource_name;
    napi_value resource;
    void *data;

    // chekc arg number
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &_this, &data));
    NAPI_ASSERT(env, argc >= 2, "Not enough arguments, expected 2.");

    // check arg type
    napi_valuetype t;
    NAPI_CALL(env, napi_typeof(env, argv[0], &t));
    NAPI_ASSERT(env, t == napi_string, "Wrong first argument, string expected.");
    NAPI_CALL(env, napi_typeof(env, argv[1], &t));
    NAPI_ASSERT(env, t == napi_function, "Wrong second argument, function expected.");

    carrier *the_carrier = nullptr;
    the_carrier = new carrier();
    the_carrier->_output = std::string("");

    // get input json string
    size_t realSize = 0;
    NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], nullptr, 0, &realSize)); // get real length
    char *input = nullptr;
    input = new char[realSize + 1];                                                           // +1 for '\0'
    NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], input, realSize + 1, &realSize)); // +1 for '\0'
    the_carrier->_input = input;

    // create async work
    NAPI_CALL(env, napi_create_reference(env, argv[1], 1, &the_carrier->_callback));
    NAPI_CALL(env, napi_create_string_utf8(env, "TestResource", NAPI_AUTO_LENGTH, &resource_name));
    NAPI_CALL(env, napi_create_string_utf8(env, "TestResource", NAPI_AUTO_LENGTH, &resource));
    NAPI_CALL(env, napi_create_async_work(env, resource, resource_name, Execute, Complete, the_carrier,
                                          &the_carrier->_request));
    NAPI_CALL(env, napi_queue_async_work(env, the_carrier->_request));

    delete[] input;
    input = nullptr;

    return nullptr;
}

static napi_value Init(napi_env env, napi_value exports)
{
#ifdef SHOW_THREAD_INFO
    std::cout << "[C++] Init thread id: " << std::this_thread::get_id() << std::endl;
#endif
    napi_property_descriptor properties[] = {DECLARE_NAPI_PROPERTY("asyncDoWork", asyncDoWorkMethod)};

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(*properties), properties));

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)