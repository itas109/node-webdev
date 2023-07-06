'use strict';

const addon = require('bindings')('addon');
const obj = new addon.MyObject();

console.log(obj.hello()); // 'hello world'