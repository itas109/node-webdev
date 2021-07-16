'use strict';

const got = require('got');
const util = require('util');

// url参数
const url_protocol = 'http';
const url_ip = '127.0.0.1';
const url_port = 8080;
const url_path = 'test';

setInterval(runRequestRandom, 1000);

function runRequestRandom() {
    let startTime = new Date().getTime();
    const url = encodeURI(util.format('%s://%s:%s/%s', url_protocol, url_ip, url_port, url_path));

    (async () => {
        const response  = await got.get(url, {responseType: 'json'});
        console.log((new Date().getTime() - startTime) + 'ms, '+ JSON.stringify(response.body));
    })();
}