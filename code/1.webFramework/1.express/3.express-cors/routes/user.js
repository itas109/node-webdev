'use strict';

const util = require('util');

const express = require('express');
const router = express.Router();

router.get('/:userid', function(req, res, next) {
  let info = util.format('%s - %s %s url: %s, ip: %s, params: %s', new Date().toLocaleString(), req.protocol, req.method, req.originalUrl, req.ip, req.params);
  console.log(info);
  res.send(info);
});

module.exports = router;