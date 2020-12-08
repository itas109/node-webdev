'use strict';

const express = require('express');
let router = express.Router();

const main = require('./main.js');
const user = require('./user.js');
const download = require('./download.js');

router.use('/', function(req, res, next) {
  req.url = decodeURIComponent(req.url);  // decodeURIComponent('%23') => "#"
  next();
});

router.use('/', main);
router.use('/user', user);
router.use('/download', download);

module.exports = router;