#include <node.h>

// recommend use N-API instead of v8

namespace demo
{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

void helloMethod(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world", NewStringType::kNormal).ToLocalChecked());
}

void Initialize(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "hello", helloMethod);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo