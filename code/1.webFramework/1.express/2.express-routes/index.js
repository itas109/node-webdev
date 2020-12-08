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

console.log('try:');
console.log('  all /');
console.log('  GET /user/:userid');
console.log('  GET /download/download.json');
console.log('  GET /download/中文.txt');