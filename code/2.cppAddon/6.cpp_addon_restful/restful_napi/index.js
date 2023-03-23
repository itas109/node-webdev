'use strict';

// memory output to file
require('./dump.js');

const http = require('http');
const express = require('express');
const app = express();
const port = 8080;
let httpServer = http.createServer(app);

const addon = require('bindings')('addon');

function random(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
}

// morgan logger dev
const logger = require('morgan');
app.use(logger('dev'));
console.log('load Third-party middleware - morgan logger dev');

const path = require('path');
app.use(express.static(path.join(__dirname, 'public')));

app.get('/', function (req, res, next) {
    res.send('index');
})

app.get('/pid', function (req, res, next) {
    res.send(`${process.pid}`);
})

app.get('/gc', function (req, res, next) {
    try {
        global.gc();
        res.send(JSON.stringify(process.memoryUsage()));
    } catch (error) {
        res.send("Please start app with --expose-gc, such as node --expose-gc index.js");
    }
})

app.get('/exit', function (req, res, next) {
    res.send('exit');
    process.exit(0);
})

app.get('/test/:text', function (req, res, next) {
    let text = req.params.text;
    addon.asyncDoWork(text, result => {
        res.send(result);
    })
})

httpServer.listen(port);

console.log('http://localhost:' + port);

console.log('\ntry:');
console.log('  GET /');
console.log('  GET /test');
