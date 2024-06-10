'use strict'

const EventEmitter = require('events').EventEmitter;
const addon = require('bindings')('addon');

const emitter = new EventEmitter();

emitter.on('start', () => {
    console.log('### START ###')
})

emitter.on('data', (data) => {
    console.log(data);
})

addon.callEmit(emitter.emit.bind(emitter))