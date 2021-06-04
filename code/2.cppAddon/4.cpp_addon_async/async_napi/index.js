'use strict';

const addon = require('bindings')('addon');

addon.asyncDoWork('{"code":0,"message":"success","data":[]}', res => {
    console.log(res);
})

addon.asyncDoWork('{"code":-1,"message":"error -1"}', res => {
    console.log(res);
})
