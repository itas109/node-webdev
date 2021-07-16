# NodeJS C++插件 function arguments

## 前言
推荐使用node-addon-api和N-API方式编写C++插件，不推荐使用v8方式编写C++插件。

本示例代码展示的是带参数的函数调用示例。

## 1. 编译nodejs的c++插件addon
```
$ node-gyp configure build --debug
```

## 2. 运行NodeJS的javascript测试程序
```
$ node index.js 
hello world
9
function arguments
```

## 其他

linux需要先安装 gcc g++ gdb，只有debug版本的程序才能打断点调试