'use strict'

const EventEmitter = require('events').EventEmitter;
const MyWrapper = require('bindings')('addon').MyWrapper;
const inherits = require('util').inherits;

inherits(MyWrapper, EventEmitter);

const myWrapper = new MyWrapper();

console.log(myWrapper.hello()); // 'hello world'
console.log(myWrapper.add(3, 6)); // 9

myWrapper.on('data', (evt) => {
    console.log(evt)
});

myWrapper.callEmit();