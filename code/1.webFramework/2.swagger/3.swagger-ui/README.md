# swagger-ui

## 1. 运行

安装http-server

```
npm install -g http-server
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

## 2. 注意事项

* URL scheme must be “http“ or “https“ for CORS request

浏览器不能直接加载本地文件的原因。