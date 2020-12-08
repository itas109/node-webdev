'use strict';

const path = require('path');

const express = require('express');
const router = express.Router();

const mainDir = path.dirname(require.main.filename);

// download files
router.get('/*', function(req, res, next) {
  // req.url = decodeURIComponent(req.url); // decodeURIComponent('%23') => "#"
  let f = path.join(mainDir, '/download/', path.basename(req.url));
  console.log('Download file: %s', f);
  res.download(f);
});

module.exports = router;