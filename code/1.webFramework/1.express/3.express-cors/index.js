'use strict';

const fs = require('fs');
// const path = require("path");
const util = require('util');
const http = require('http');
// const https = require('https');
const express = require('express');

const router = require('./routes/index.js');

const logger = require('morgan');

const httpPort = 8080;
const httpsPort = 8081;

const app = express();

// log requests
app.use(logger('dev'));

// enable req.body
app.use(express.json()); // application/json => req.body 
app.use(express.urlencoded({ extended: false })) // x-ww-form-urlencoded => req.body

let httpServer = http.createServer(app);

// 1.cors 2.custom router 3.http-proxy 4.static 5.swagger

// 1.cors
app.all('*', function(req, res, next) {
  // Notice: only for development environment
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Headers', 'X-Requested-With');
  res.header('Access-Control-Allow-Methods', 'PUT,POST,GET,DELETE,OPTIONS');
  if (req.method === 'OPTIONS') {
    res.send(200);
  } else {
    next();
  }
});

// 2.custom router
app.use('/', router);

httpServer.listen(httpPort);

console.log(util.format('http://localhost:%s', httpPort));

console.log('try:');
console.log('  all /');
console.log('  GET /user/:userid');
console.log('  GET /download/download.json');
console.log('  GET /download/中文.txt');