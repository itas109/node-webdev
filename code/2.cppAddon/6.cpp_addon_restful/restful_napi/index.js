'use strict';

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
