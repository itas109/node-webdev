'use strict';

const fs = require("fs");
// const path = require("path");
const util = require('util');
const http = require('http');
// const https = require("https");
const express = require('express');

const router = require('./routes/index.js');

const httpPort = 8080;

const app = express();

let httpServer = http.createServer(app);

app.use('/', router);

httpServer.listen(httpPort);

console.log(util.format('http://localhost:%s',httpPort));

console.log('\ntry:');
console.log('  all /');
console.log('  GET(swagger) /v1/user/login?username=:username&password=:password');
console.log('  GET(swagger) /v1/user/:userid');
console.log('  POST(swagger body) /v1/user/resetPassword');
console.log('  GET(swagger) /docs');
console.log('  GET /user/:userid');