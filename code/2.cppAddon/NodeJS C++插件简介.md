# NodeJS C++插件简介

## 前言

NodeJS C++ 插件是用 C++ 编写的动态链接共享对象。 require() 函数可以将插件加载为普通的 Node.js 模块。 C++ 插件提供了 JavaScript 和 C/C++ 库之间的接口。

实现NodeJS C++插件有三种选择：
- N-API【推荐】
- NAN
- 直接使用内部的 V8、libuv 和 Node.js 库

## 1. NodeJS C++插件的实现方式

### 1.1 NodeJS原生方式

NodeJS原生方式,需要开发者直接深入到 NodeJS 的各种 API，以及 Google V8 的 API。

但是，如果NodeJS 或 V8 的API发生变化，就需要开发者进行同步修改，否则就不能在新版本使用。

### 1.2 NAN

NAN, 全称为Native Abstractions for Node.js，即 Node.js 原生模块抽象接口。

NAN通过宏定义解决了NodeJS原生方式非常混乱和兼容的问题。

NAN的好处是跟随NodeJS进行升级，帮开发者完成NodeJS不同版本的兼容，使其在任意版本都可以编译。

NAN的坏处是遇到高版本需要重新进行编译，也就是需要多次编译。


### 1.3 N-API【推荐】

NodeJS v8.0.0 发布之后，推出了全新的用于开发 C++ 原生模块的接口 N-API。对于v8.0.0之前的版本通过`node-addon-api`进行外挂式兼容。

 N-API独立于底层JavaScript运行时（例如V8），并作为NodeJS自身的一部分维护。

 N-API是NodeJS稳定的跨版本的应用程序二进制接口（ABI）。

 N-API旨在将插件与底层JavaScript引擎中的更改隔离开来，并允许为一个主版本编译的C++插件在之后的主版本上无需重新编译。

 N-API 定义了如下特性：

- 提供头文件node_api.h；
- 任何 N-API 调用都返回一个napi_status枚举，来表示这次调用成功与否
- N-API 真实返回值通过形参来传递
- 所有JavaScript数据类型使用napi_value封装，不再是类似于 v8::Object、v8::Number等类型
- 如果函数调用不成功，可以通过napi_get_last_error_info函数来获取最后一次出错的信息


N-API是一种C API，可确保在NodeJS版本和不同编译器级别之间的ABI稳定性，但是
C++ API更易于使用。为了支持使用C++，该项目维护了一个称为node-addon-api的C ++包装器模块。 该包装器提供了一个可内联的C ++ API。 使用node-addon-api构建的二进制文件将取决于Node.js导出的基于N-API C的函数的符号。 node-addon-api是编写调用N-API的代码的更有效方法。

## 2. NodeJS C++插件构建工具简介

### 2.1 node-gyp

node-gyp是一个基于Google的gyp工具的构建系统，与npm捆绑在一起。gyp和node-gyp都要求安装Python。

很长一段时间以来，node-gyp都是构建本地插件的首选工具，已被广泛使用。

### 2.2 CMake.js

CMake.js是一个Node.js/io.js的本地插件构建工具，其工作原理几乎与node-gyp完全相同，但它不是gyp，而是基于CMake构建系统。

CMake.js对于已经使用CMake的项目或受node-gyp限制影响的开发人员来说，是一个很好的选择。

## 3. NodeJS C++插件demo

https://github.com/nodejs/node-addon-examples

https://github.com/itas109/node-webdev

---

Reference：
1. http://nodejs.cn/api/addons.html
2. https://xcoder.in/2017/07/01/nodejs-addon-history
3. https://github.com/nodejs/node-addon-examples