'use strict';

const addon = require('bindings')('addon');

console.log(addon.hello()); // 'hello world'

console.log(addon.add(3, 6)); // 9

console.log(addon.returnSelf("function arguments")); // 'function arguments'