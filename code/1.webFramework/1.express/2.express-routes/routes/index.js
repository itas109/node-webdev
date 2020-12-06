'use strict';

const main = require('./main.js');
const user = require('./user.js');
const download = require('./download.js');

module.exports = app => {
  app.use('/', function(req, res, next) {
    req.url = decodeURIComponent(req.url);  // decodeURIComponent('%23') => "#"
    next();
  });

  app.use('/', main);
  app.use('/user', user);
  app.use('/download', download);
}