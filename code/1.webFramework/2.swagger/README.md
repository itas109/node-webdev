# swagger - RESTFUL接口文档在线自动生成、代码自动生成工具

环境：

nodejs : 12.13.0

swagger-editor : 3.15.8(2021-03-04)

swagger-codegen : 2.4.9(2019-10-14)

swagger-ui : 3.44.1(2021-03-04)

## 前言

[Swagger](http://swagger.io/) 是一款RESTFUL接口的、基于YAML、JSON语言的文档在线自动生成、代码自动生成的工具。

## 1. RESTful API规范

swagger使用[swagger 2.0(2014-09-08)](https://swagger.io/specification/v2/) 规范，其依赖于openapi 3.0版本的规范。

[openapi](https://swagger.io/specification/) 规范，是定义一个标准的、与具体编程语言无关的RESTful API的规范。官方文档(中文)：[OpenAPI 开放API规范](https://github.com/fishead/OpenAPI-Specification)

swagger 2.0规范示例：

```
swagger: '2.0' # 语义化版本号规范
info: # 【必选】API相关的元数据
  title: Swagger Demo # 【必选】应用的名称
  version: 1.0.0 # 【必选】版本信息
  description: # 描述
    Swagger Demo - https://github.com/itas109/node-webdev
  termsOfService: # 服务条款的URL地址
    https://github.com/itas109/node-webdev
  contact: # 联系人信息
    name: itas109
    email: itas109@qq.com
  license: # 协议
    name: MIT License
    url: https://opensource.org/licenses/mit/
host:  # 服务端host
    127.0.0.1:8080
basePath: # url基路径
    /v1
tags: # 元数据的一系列标签
  - name: user
    description: Operations about user
    externalDocs:
      description: user external docs
      url: https://github.com/itas109
schemes: # 协议，http,https,ws,wss
  - http
  - https
externalDocs: # 附加的文档
  description: external docs
  url: https://github.com/itas109
paths: # 【必选】API有效的路径和操作
  /user/login: # 端点的相对路径，路径必须以 / 打头
    get:
      tags: # 标签分类
        - user
      summary: Logs user into the system
      description: ''
      produces:
        - application/json
        - application/xml
      parameters: # 参数 
        - name: username # 【必选】参数的名称
          in: query # 【参数】 入参类型，query, header, path 或 cookie
          description: user name for login # 描述
          required: true # 是否必须
          type: string
        - name: password
          in: query
          description: user password for login
          required: true
          type: string
      responses: # 【必须】返回值
        '200':
          description: json, {"code":0,"message":"success","data":[{"token_type":"bearer","access_token":"adcc4dc09a4f9ac278d019605f00f33c9a08e0e3","expires_in":3600,"refresh_token":"418470a87cb3d9320a092bb550790ae2c13182f1"}]}
          schema:
            $ref: '#/definitions/ApiResponse'
          headers:
            X-Rate-Limit:
              type: integer
              format: int32
              description: calls per hour allowed by the user
            X-Expires-After:
              type: string
              format: date-time
              description: date in UTC when token expires
        '400':
          description: Invalid username/password
          schema:
            $ref: '#/definitions/ApiErrorResponse'
  '/user/{username}':
    get:
      tags:
        - user
      summary: Get user by user name
      description: ''
      produces:
        - application/json
        - application/xml
      parameters:
        - name: username
          in: path
          description: The name that needs to be fetched
          required: true
          type: string
      responses:
        '200':
          description: successful operation
          schema:
            $ref: '#/definitions/ApiResponse'
        '400':
          description: Invalid username supplied
          schema:
            $ref: '#/definitions/ApiErrorResponse'
        '404':
          description: User not found
          schema:
            $ref: '#/definitions/ApiErrorResponse'
      security:
        - user_auth:
            - 'write:user'
            - 'read:user'
        - token: []
        - BasicAuth: []
securityDefinitions: # 安全定义
  user_auth:
    type: oauth2
    authorizationUrl: localhost:8080/oauth/token
    flow: implicit
    scopes:
      'write:user': modify user in your account
      'read:user': read your user
  token:
    type: apiKey
    name: Authorization
    description: "Authorization: Bearer xxx"
    in: header
  BasicAuth:
    type: basic
definitions:
  ApiResponse:
    example: {"code":0, "message":"success","data":[{'xxx':'xxx'}]}
    type: object
    properties:
      code:
        type: integer
        format: int32
        description: "System Level Code:\n 0 success \n 100101 system inner error \n 100201 interface maintenance \n 200202 interface disabled \n\n Service Level Code:\n 200101 input params empty \n 200102 input params error \n 200103 no auth"
      message:
        type: string
        description: "code details information"
      data:
        type: string
        description: "return datas array when code equal 0"
  ApiErrorResponse:
    example: {"code":200102, "message":"input params error"}
    type: object
    properties:
      code:
        type: integer
        format: int32
        description: "System Level Code:\n 0 success \n 100101 system inner error \n 100201 interface maintenance \n 200202 interface disabled \n\n Service Level Code:\n 200101 input params empty \n 200102 input params error \n 200103 no auth"
      message:
        type: string
        description: "code details information"
```

## 2. swagger editor生成swagger配置文件

上节中对`RESTful API规范`做了介绍，本节介绍使用`swagger editor`进行可视化的生成`RESTful API`的yaml或json文件。

### 2.1 swagger editor使用

在`swagger editor`的左边可以进行接口定义，右边可以实时看到对应的api信息。

最后，点击顶部的菜单栏`File -> Save as YAML`生成yaml文件。

---

### 2.2 `swagger editor`地址

https://github.com/swagger-api/swagger-editor

https://github.com/swagger-api/swagger-editor/archive/v3.15.8.tar.gz

- 在线编辑：http://editor.swagger.io

- 本地编辑：
  - `git clone https://github.com/swagger-api/swagger-editor.git && cd swagger-editor` 
  
  - 双击index.html在浏览器中打开
  
```
+--- swagger-editor
|   +--- dist
|   |   +--- swagger-editor-bundle.js
|   |   +--- swagger-editor-standalone-preset.js
|   |   +--- swagger-editor.css
|   |   +--- swagger-editor.js
|   +--- index.html
```

## 3. swagger-codegen生成代码(以服务端为例)

经过上节我们可以生成`RESTful API`的yaml文件，本节介绍如何通过yaml文件生成代码(这里以NodeJS服务端为例)。

### 3.1 swagger-codegen简介

swagger-codegen是OpenAPI (f.k.a Swagger) 规范的开源代码生成器，支持 API 客户端, API 服务单和 API 文档。

-  客户端 :  ActionScript ,  Ada ,  Apex ,  Bash ,  C# ,  C++  ,  Clojure ,  Dart ,  Elixir ,  Elm ,  Eiffel ,  Erlang ,  Go ,  Groovy ,  Haskell  ,  Java  ,  Kotlin ,  Lua ,  Node.js ,  Objective-C ,  Perl ,  PHP ,  PowerShell ,  Python ,  R ,  Ruby ,  Rust ,  Scala ,  Swift ,  Typescript  
-  服务端 :  Ada ,  C# ,  C++  ,  Erlang ,  Go ,  Haskell ,  Java ,  Kotlin ,  PHP ,  Python  ,  NodeJS ,  Ruby  ,  Rust ,  Scala 
-  API文档 :  HTML ,  Confluence Wiki 
-  配置文件 :  Apache2 
-  其他 :  JMeter 

### 3.2 swagger-codegen生成代码(以NodeJS服务端为例)

* 查看swagger-codegen支持语言

```
$ java -jar swagger-codegen-cli-2.4.9.jar langs

Available languages: [ada, ada-server, akka-scala, android, apache2, apex, aspnetcore, bash, csharp, clojure, cwiki, cpprest, csharp-dotnet2, dart, dart-jaguar, elixir, elm, eiffel, erlang-client, erlang-server, finch, flash, python-flask, go, go-server, groovy, haskell-http-client, haskell, jmeter, jaxrs-cxf-client, jaxrs-cxf, java, inflector, jaxrs-cxf-cdi, jaxrs-spec, jaxrs, msf4j, java-pkmst, java-play-framework, jaxrs-resteasy-eap, jaxrs-resteasy, javascript, javascript-closure-angular, java-vertx, kotlin, lua, lumen, nancyfx, nodejs-server, objc, perl, php, powershell, pistache-server, python, qt5cpp, r, rails5, restbed, ruby, rust, rust-server, scala, scala-gatling, scala-lagom-server, scalatra, scalaz, php-silex, sinatra, slim, spring, dynamic-html, html2, html, swagger, swagger-yaml, swift4, swift3, swift, php-symfony, tizen, typescript-aurelia, typescript-angular, typescript-inversify, typescript-angularjs, typescript-fetch, typescript-jquery, typescript-node, undertow, ze-ph, kotlin-server]
```

* 查看swagger-codegen的生成代码帮助信息

```
java -jar swagger-codegen-cli-2.4.9.jar help generate
```

* 生成nodejs服务端代码

  generate主要参数：

  -i swagger restful api文件的路径,url或本地文件

  -l 生成客户端代码的语言,该参数为必须

  -o 生成文件的位置(默认当前目录)

```
java -jar swagger-codegen-cli-2.4.9.jar generate -i swagger.yaml -l nodejs-server -o samples
```

```
+--- samples
|   +--- .swagger-codegen
|   |   +--- VERSION
|   +--- .swagger-codegen-ignore
|   +--- api
|   |   +--- swagger.yaml
|   +--- controllers
|   |   +--- User.js
|   +--- index.js
|   +--- package.json
|   +--- README.md
|   +--- service
|   |   +--- UserService.js
|   +--- utils
|   |   +--- writer.js
```

### 3.3 swagger-codegen地址

```
+--- swagger-codegen
|   +--- gen.bat
|   +--- gen.sh
|   +--- swagger.yaml
|   +--- swagger-codegen-cli-2.4.9.jar
```

https://github.com/swagger-api/swagger-codegen
https://repo1.maven.org/maven2/io/swagger/swagger-codegen-cli/2.4.9/swagger-codegen-cli-2.4.9.jar

java Version 8 Update 271 (2020-10-20)
https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html

## 4. swagger-ui

### 4.1 swagger-ui简介

上节中的swagger-codegen生成的nodejs-server代码运行后也可以查看在线API文档。

本节中的swagger-ui是`无依赖`的在线API文档，其仅包含HTML、JS和CSS。

### 4.2 swagger-ui使用

```
+--- swagger-ui
|   +--- favicon-16x16.png
|   +--- favicon-32x32.png
|   +--- index.html
|   +--- swagger-ui-bundle.js
|   +--- swagger-ui-standalone-preset.js
|   +--- swagger-ui.css
|   +--- swagger-ui.js
```

index.html修改

```
SwaggerUIBundle({
    "url": "swagger.yaml", // 本文件相同目录下的本地文件，也可以为远程文件
    "validatorUrl": false, // 不校验
})
```

运行

```
cd swagger-ui
http-server -p 8080
```

### 4.3 swagger-ui地址

https://github.com/swagger-api/swagger-ui

https://github.com/swagger-api/swagger-ui/archive/v3.44.1.tar.gz

---

Refrence:

1. https://swagger.io/specification/
2. https://github.com/fishead/OpenAPI-Specification