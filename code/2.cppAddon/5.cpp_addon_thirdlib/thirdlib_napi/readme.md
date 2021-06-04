# NodeJS C++插件 引用第三方库

## 1. 编译第三方myadd动态库

```
$ cd cpp_addon_thirdlib_napi/thirdlib
$ ./compile.sh
```

## 2. 编译nodejs的c++插件addon
```
$ cd cpp_addon_thirdlib_napi
$ ./compile.sh
```

## 3. 运行NodeJS 的javascript测试程序
```
$ cd cpp_addon_thirdlib_napi
$ ./run_test.sh 
JS output :  hello world
C++ output : 3+6=9
JS output :  9
```

## 其他

linux需要先安装 gcc g++ gdb，只有debug版本的程序才能打断点调试