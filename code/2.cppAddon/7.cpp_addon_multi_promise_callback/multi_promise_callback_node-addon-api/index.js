'use strict';

const addon = require('bindings')('addon');

void async function () {
    addon.multiPromiseCallback(res => {
        console.log(res);
    })
}();