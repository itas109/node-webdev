'use strict';

const fs = require('fs');
const util = require('util');

const http = require('http');
const https = require('https');
const express = require('express');

const httpPort = 8080;
const httpsPort = 8081;

const app = express();

// 1. create private key
// openssl genrsa 1024 > private.key
// 2. create csr pem by private.key
// openssl req -new -key private.key -out csr.pem
// 3. create file.crt by private.key and csr.pem
// openssl x509 -req -days 365 -in csr.pem -signkey private.key -out file.crt
let options = {
  key: fs.readFileSync('./keys/private.key'),
  cert: fs.readFileSync('./keys/file.crt')
}

let httpServer = http.createServer(app);
let httpsServer = https.createServer(options, app);

app.get('/', function(req, res, next) {
    let info = util.format('%s - %s %s %s %s', new Date().toLocaleString(), req.protocol, req.method, req.originalUrl, req.ip);
    console.log(info);
    res.send(info);
});

app.all('/all', function(req, res, next) {
    let info = util.format('%s - %s %s %s %s', new Date().toLocaleString(), req.protocol, req.method, req.originalUrl, req.ip);
    console.log(info);
    res.send(info);
});

httpServer.listen(httpPort);
httpsServer.listen(httpsPort);

console.log(util.format('http://localhost:%s', httpPort));
console.log(util.format('https://localhost:%s', httpsPort));