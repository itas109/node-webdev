'use strict';

const addon = require('bindings')('addon');

console.log(addon.hello()); // 'hello world'

addon.helloCallback(function (result) {
    console.log(result); // 'hello world callback'
});

let recv = 'callback with receive';
addon.callbackWithRecv(recv, function () {
    console.log('input: ', recv, ', output: ', this);
});