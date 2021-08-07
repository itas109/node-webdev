# express-routes-swagger

本demo基于：

1. express routes 路由代码 (1.webFramework\1.express\2.express-routes)

2. swagger-codegen生成的nodejs-server代码 (1.webFramework\2.swagger\2.swagger-codegen)。



```
http://localhost:8080/docs/
http://127.0.0.1:8080/v1/user/login?username=aaa&password=bbb
http://127.0.0.1:8080/v1/user/aaa

http://127.0.0.1:8080/v1/user/resetPassword    【body:{"userId": 1,"oldPwd": "xxx","newPwd": "xxx"}】

http://127.0.0.1:8080
http://127.0.0.1:8080/user/aaa
```



注意：

swagger自带的访问路径为 /v1/xxx，因此express的路由只能使用`/`根路径(再加路径会附加到v1之前，导致找不到路径)