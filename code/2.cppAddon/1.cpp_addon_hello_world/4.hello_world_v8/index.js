'use strict';

const addon = require('bindings')('addon');

console.log(addon.hello()); // 'hello world'