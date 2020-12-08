'use strict';

const fs = require('fs');
const path = require("path");
const util = require('util');
const http = require('http');
// const https = require('https');
const express = require('express');

const router = require('./routes/index.js');

const logger = require('morgan');

const httpPort = 8080;

const app = express();

let httpServer = http.createServer(app);

// An Express application can use the following types of middleware:
// 1. Application-level middleware
// 2. Router-level middleware
// 3. Error-handling middleware
// 4. Built-in middleware
// 5. Third-party middleware

// Third-party middleware
// morgan logger dev
app.use(logger('dev'));
console.log('load Third-party middleware - morgan logger dev');

// Built-in middleware
// a.express.static
app.use('/static', express.static(path.join(__dirname, 'download')));
console.log('load Built-in middleware - express.static ' + path.join(__dirname, 'download'));
// b.express.json
app.use(express.json()); // application/json => req.body 
console.log('load Built-in middleware - express.json');
// c.express.urlencoded
app.use(express.urlencoded({ extended: false })) // application/x-www-form-urlencoded => req.body
console.log('load Built-in middleware - express.urlencoded');

// Application-level middleware
app.get('/error', function (req, res) {
  throw new Error('Application-level middleware error test') // Express will catch this on its own.
})
console.log('load Application-level middleware');

// Error-handling middleware
app.use((err, req, res, next) => {
  // err is next(err) object
  res.status(500).send(err.message);
})
console.log('load Error-handling middleware');

// Router-level middleware
app.use('/', router);
console.log('load Router-level middleware');

httpServer.listen(httpPort);

console.log(util.format('\nhttp://localhost:%s', httpPort));

console.log('\ntry:');
console.log('  all /');
console.log('  GET /user/:userid');
console.log('  GET /error');
console.log('  GET(static) /static/download.json');
console.log('  GET(static)  /static/中文.txt');
console.log('  GET /download/download.json');
console.log('  GET /download/中文.txt');