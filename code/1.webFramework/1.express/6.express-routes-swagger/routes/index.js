'use strict';

const express = require('express');
let router = express.Router();

const main = require('./main.js');
const user = require('./user.js');
const swagger = require('../swagger/index.js');

router.use('/', function(req, res, next) {
  req.url = decodeURIComponent(req.url);  // decodeURIComponent('%23') => "#"
  next();
});

router.use('/', main);
router.use('/user', user);

// swagger router Method 1
router.use(swagger);

// swagger router Method 2
// router.use('/', function (req, res, next) {
//     swagger(req,res);
// });

module.exports = router;