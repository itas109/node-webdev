const fs = require('fs');

const FILE_NAME = `memory_${process.pid}.csv`;
const INTERVAL_MS = 1000; // 1s

function FormatBytes(bytes) {
    return (bytes / 1048576).toFixed(2);
}

function showMemory() {
    const memoryObj = process.memoryUsage();
    // time, rss(MB), heapTotal(MB), heapUsed(MB), external(MB), arrayBuffers(MB)
    let result = `${new Date().toLocaleString('chinese', { hour12: false })}, ${FormatBytes(memoryObj.rss)}, ${FormatBytes(memoryObj.heapTotal)}, ${FormatBytes(memoryObj.heapUsed)}, ${FormatBytes(memoryObj.external)}, ${FormatBytes(memoryObj.arrayBuffers)}\n`;
    // console.log(result);
    fs.writeFileSync(FILE_NAME, result, { flag: 'a+' });
}

showMemory();
setInterval(() => { showMemory(); }, INTERVAL_MS);
