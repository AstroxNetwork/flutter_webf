var text1 = document.createTextNode('Hello webf!');
var br = document.createElement('br');
var text2 = document.createTextNode('你好，webf！');
var p = document.createElement('p');
p.className = 'p';
p.style.display = 'inline-block';
p.style.textAlign = 'center';
p.style.animation = '3s ease-in 1s 1 reverse both running example';
p.appendChild(text1);
p.appendChild(br);
p.appendChild(text2);

var kkk = BigInt(3);
var ddd = 3n;
var kkkText = document.createTextNode(`BigInt: ${kkk}`);
var dddText = document.createTextNode(`BigInt: ${kkk}`);
p.appendChild(kkkText);
p.appendChild(dddText);

const t = new TextEncoder();
const bytes = t.encode('asdf');
console.log(bytes);

document.body.appendChild(p);
console.log(globalThis.callf('test', 's'));

(async () => {
  var aaa = new AudioPlayer('http://downsc.chinaz.net/Files/DownLoad/sound1/201906/11582.mp3');
  await aaa.initialize();
  await aaa.play();
})();
