'use strict';

const addon = require('bindings')('addon');

addon.init(res => { console.log(res); });
addon.threadCallback('', res => { console.log(res); })