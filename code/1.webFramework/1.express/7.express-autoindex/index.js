'use strict';

const util = require('util');
const http = require('http');
const express = require('express');
const serveIndex = require('serve-index');

const httpPort = 8080;

const app = express();

let httpServer = http.createServer(app);

// similar node_modules: serve-static st autoindex-json
app.use('/static', express.static('static'), serveIndex('static', {'icons' : true}));

httpServer.listen(httpPort);

console.log(util.format('\nhttp://localhost:%s', httpPort));

console.log('\ntry:');
console.log('  GET /static');