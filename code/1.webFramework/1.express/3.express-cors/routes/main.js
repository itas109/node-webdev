'use strict';

const util = require('util');

const express = require('express');
const router = express.Router();

router.get('/', function(req, res, next) {
    let info = util.format('%s - %s %s url: %s, ip: %s', new Date().toLocaleString(), req.protocol, req.method, req.originalUrl, req.ip);
    console.log(info);
    res.send(info);
});

router.all('/', function(req, res, next) {
    let info = util.format('%s - %s %s url: %s, ip: %s', new Date().toLocaleString(), req.protocol, req.method, req.originalUrl, req.ip);
    console.log(info);
    res.send(info);
});

module.exports = router;