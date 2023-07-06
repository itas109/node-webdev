'use strict';

const addon = require('bindings')('addon');

async function foo() {
    console.log('result: ', await addon.asyncDoWorkPromise('{"code":0,"message":"success","data":[]}', res => {
        console.log(res);
    }))

    console.log('result: ', await addon.asyncDoWorkPromise('{"code":-1,"message":"error -1"}', res => {
        console.log(res);
    }))
}

foo();