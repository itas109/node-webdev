'use strict';

const fs = require("fs");
// const path = require("path");
const util = require('util');
const http = require('http');
const https = require("https");
const express = require('express');

const router = require('./routes/index.js');

const httpPort = 8080;
const httpsPort = 8081;

const app = express();

// 1. create private key
// openssl genrsa 1024 > private.key
// 2. create csr pem by private.key
// openssl req -new -key private.key -out csr.pem
// 3. create file.crt by private.key and csr.pem
// openssl x509 -req -days 365 -in csr.pem -signkey private.key -out file.crt
let option = {
    key: fs.readFileSync('./keys/private.key'),
    cert: fs.readFileSync('./keys/file.crt')
}

let httpServer = http.createServer(app);
let httpsServer = https.createServer(option, app);

router(app);

httpServer.listen(httpPort);
httpsServer.listen(httpsPort);

console.log(util.format('http://localhost:%s',httpPort));
console.log(util.format('https://localhost:%s',httpsPort));