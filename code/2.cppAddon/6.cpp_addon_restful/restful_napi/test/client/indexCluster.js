'use strict';

const got = require('got');
const util = require('util');

let args = process.argv.slice(2);
console.log('args: ' + args);

const cluster = require('cluster');
let CPUNums = require('os').cpus().length;

if(args[0] !== undefined && args[0] > 0){
    CPUNums = args[0];
}else{
    CPUNums *= 2; // CPU核数的双倍
}
// CPUNums = 8;

// url参数
const url_protocol = 'http';
const url_ip = '127.0.0.1';
const url_port = 8080;
const url_path = 'test';

var count = 1;

if (cluster.isMaster) {
    console.log(`主进程 ${process.pid} 正在运行  集群个数: ${CPUNums}`);

    // 衍生进程
    for (let i = 0; i < CPUNums; i++) {
        cluster.fork();
    }

    cluster.on('exit', (work, code, signal) => {
        console.log(`工作进程 ${work.process.pid} 已退出`);
    })
} else {

    console.log(`工作进程 ${count} ${process.pid} 正在运行  `);

    count++;

    setInterval(runRequestRandom, 1000);
}

function runRequestRandom() {
    let startTime = new Date().getTime();
    const url = encodeURI(util.format('%s://%s:%s/%s', url_protocol, url_ip, url_port, url_path));

    (async () => {
        const response  = await got.get(url, {responseType: 'json'});
        console.log((new Date().getTime() - startTime) + 'ms, '+ JSON.stringify(response.body));
    })();
}