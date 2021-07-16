'use strict';

const got = require('got');
const util = require('util');

let args = process.argv.slice(2);
console.log('args: ' + args);

const cluster = require('cluster');
let CPU_NUM = require('os').cpus().length;

if(args[0] !== undefined && args[0] > 0){
    CPU_NUM = args[0];
}else{
    CPU_NUM *= 2; // CPU核数的双倍
}
// CPUNums = 8;

// url参数
const url_protocol = 'http';
const url_ip = '127.0.0.1';
const url_port = 8080;
const url_path = 'test';

let EXECUTE_PERIOD_MS = 1000; // 1秒
if (args[1] !== undefined && args[1] > 0) {
    EXECUTE_PERIOD_MS = args[1];
} else {
    EXECUTE_PERIOD_MS = 1000; // 1秒
}

if (cluster.isMaster) {
    console.log(`主进程 ${process.pid} 正在运行  集群个数: ${CPU_NUM}`);

    // 衍生进程
    let workers = [];
    for (let i = 0; i < CPU_NUM; i++) {
        workers.push(cluster.fork());
    }

    setInterval(() => {
        workers.forEach(worker => {
            worker.send('run');
        });
    }, EXECUTE_PERIOD_MS);

    cluster.on('exit', (work, code, signal) => {
        console.log(`工作进程 ${work.process.pid} 已退出`);
    })
} else {

    console.log(`工作进程 ${process.pid} 正在运行`);

    process.on('message', (msg) => {
        runRequestRandom();
    });

    setInterval(runRequestRandom, 1000);
}

function runRequestRandom() {
    let startTime = new Date().getTime();
    const url = encodeURI(util.format('%s://%s:%s/%s', url_protocol, url_ip, url_port, url_path));

    (async () => {
        const response  = await got.get(url, {responseType: 'json'});
        let result = JSON.stringify(response.body);
            if (result.length < 100) {
                console.log((new Date().getTime() - startTime), 'ms, ', result);
            } else {
                console.log((new Date().getTime() - startTime), 'ms, resutl length ', result.length);
            }
    })();
}