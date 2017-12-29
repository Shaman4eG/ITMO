let date = new Date();
//clock.innerHTML = `${date.getDay()} ${date.getMonth()} ${date.getFullYear()} ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;
let clock = document.getElementById('clock');
clock.innerHTML = `${date.getDate()}.${date.getMonth() + 1}.${date.getFullYear()} ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;

setInterval(() => {
    date = new Date();
    clock.innerHTML = `${date.getDate()}.${date.getMonth() + 1}.${date.getFullYear()} ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;
}, 9000);