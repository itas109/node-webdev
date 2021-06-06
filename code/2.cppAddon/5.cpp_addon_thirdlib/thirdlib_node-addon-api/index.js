'use strict';

const addon = require('bindings')('addon');

console.log('JS output : ',addon.hello()); // hello world

console.log('JS output : ', addon.add(3, 6)); // 3+6=9