var LDPC_HANDLER = function(LDPC_HANDLER) {
  LDPC_HANDLER = LDPC_HANDLER || {};
  var Module = LDPC_HANDLER;

var b;b||(b=eval("(function() { try { return LDPC_HANDLER || {} } catch(e) { return {} } })()"));var h={},p;for(p in b)b.hasOwnProperty(p)&&(h[p]=b[p]);var r=!1,t=!1,u=!1,v=!1;
if(b.ENVIRONMENT)if("WEB"===b.ENVIRONMENT)r=!0;else if("WORKER"===b.ENVIRONMENT)t=!0;else if("NODE"===b.ENVIRONMENT)u=!0;else if("SHELL"===b.ENVIRONMENT)v=!0;else throw Error("The provided Module['ENVIRONMENT'] value is not valid. It must be one of: WEB|WORKER|NODE|SHELL.");else r="object"===typeof window,t="function"===typeof importScripts,u="object"===typeof process&&"function"===typeof require&&!r&&!t,v=!r&&!u&&!t;
if(u){b.print||(b.print=console.log);b.printErr||(b.printErr=console.warn);var w,x;b.read=function(a,c){w||(w=require("fs"));x||(x=require("path"));a=x.normalize(a);var d=w.readFileSync(a);return c?d:d.toString()};b.readBinary=function(a){a=b.read(a,!0);a.buffer||(a=new Uint8Array(a));assert(a.buffer);return a};b.load=function(a){aa(read(a))};b.thisProgram||(b.thisProgram=1<process.argv.length?process.argv[1].replace(/\\/g,"/"):"unknown-program");b.arguments=process.argv.slice(2);"undefined"!==typeof module&&
(module.exports=b);process.on("uncaughtException",function(a){if(!(a instanceof y))throw a;});b.inspect=function(){return"[Emscripten Module object]"}}else if(v)b.print||(b.print=print),"undefined"!=typeof printErr&&(b.printErr=printErr),b.read="undefined"!=typeof read?read:function(){throw"no read() available";},b.readBinary=function(a){if("function"===typeof readbuffer)return new Uint8Array(readbuffer(a));a=read(a,"binary");assert("object"===typeof a);return a},"undefined"!=typeof scriptArgs?b.arguments=
scriptArgs:"undefined"!=typeof arguments&&(b.arguments=arguments),"function"===typeof quit&&(b.quit=function(a){quit(a)}),eval("if (typeof gc === 'function' && gc.toString().indexOf('[native code]') > 0) var gc = undefined");else if(r||t)b.read=function(a){var c=new XMLHttpRequest;c.open("GET",a,!1);c.send(null);return c.responseText},t&&(b.readBinary=function(a){var c=new XMLHttpRequest;c.open("GET",a,!1);c.responseType="arraybuffer";c.send(null);return new Uint8Array(c.response)}),b.readAsync=function(a,
c,d){var e=new XMLHttpRequest;e.open("GET",a,!0);e.responseType="arraybuffer";e.onload=function(){200==e.status||0==e.status&&e.response?c(e.response):d()};e.onerror=d;e.send(null)},"undefined"!=typeof arguments&&(b.arguments=arguments),"undefined"!==typeof console?(b.print||(b.print=function(a){console.log(a)}),b.printErr||(b.printErr=function(a){console.warn(a)})):b.print||(b.print=function(){}),t&&(b.load=importScripts),"undefined"===typeof b.setWindowTitle&&(b.setWindowTitle=function(a){document.title=
a});else throw"Unknown runtime environment. Where are we?";function aa(a){eval.call(null,a)}!b.load&&b.read&&(b.load=function(a){aa(b.read(a))});b.print||(b.print=function(){});b.printErr||(b.printErr=b.print);b.arguments||(b.arguments=[]);b.thisProgram||(b.thisProgram="./this.program");b.quit||(b.quit=function(a,c){throw c;});b.print=b.print;b.c=b.printErr;b.preRun=[];b.postRun=[];for(p in h)h.hasOwnProperty(p)&&(b[p]=h[p]);
var h=void 0,A={w:function(a){return tempRet0=a},u:function(){return tempRet0},l:function(){return z},e:function(a){z=a},n:function(a){switch(a){case "i1":case "i8":return 1;case "i16":return 2;case "i32":return 4;case "i64":return 8;case "float":return 4;case "double":return 8;default:return"*"===a[a.length-1]?A.g:"i"===a[0]?(a=parseInt(a.substr(1)),assert(0===a%8),a/8):0}},t:function(a){return Math.max(A.n(a),A.g)},A:16,Q:function(a,c){"double"===c||"i64"===c?a&7&&(assert(4===(a&7)),a+=4):assert(0===
(a&3));return a},K:function(a,c,d){return d||"i64"!=a&&"double"!=a?a?Math.min(c||(a?A.t(a):0),A.g):Math.min(c,8):8},i:function(a,c,d){return d&&d.length?b["dynCall_"+a].apply(null,[c].concat(d)):b["dynCall_"+a].call(null,c)},b:[],p:function(a){for(var c=0;c<A.b.length;c++)if(!A.b[c])return A.b[c]=a,2*(1+c);throw"Finished up all reserved function pointers. Use a higher value for RESERVED_FUNCTION_POINTERS.";},v:function(a){A.b[(a-2)/2]=null},a:function(a){A.a.k||(A.a.k={});A.a.k[a]||(A.a.k[a]=1,b.c(a))},
j:{},M:function(a,c){assert(c);A.j[c]||(A.j[c]={});var d=A.j[c];d[a]||(d[a]=1===c.length?function(){return A.i(c,a)}:2===c.length?function(d){return A.i(c,a,[d])}:function(){return A.i(c,a,Array.prototype.slice.call(arguments))});return d[a]},L:function(){throw"You must build with -s RETAIN_COMPILER_SETTINGS=1 for Runtime.getCompilerSetting or emscripten_get_compiler_setting to work";},d:function(a){var c=z;z=z+a|0;z=z+15&-16;return c},o:function(a){var c=B;B=B+a|0;B=B+15&-16;return c},s:function(a){var c=
D[E>>2];a=(c+a+15|0)&-16;D[E>>2]=a;if(a=a>=F)G(),a=!0;return a?(D[E>>2]=c,0):c},m:function(a,c){return Math.ceil(a/(c?c:16))*(c?c:16)},P:function(a,c,d){return d?+(a>>>0)+4294967296*+(c>>>0):+(a>>>0)+4294967296*+(c|0)},f:1024,g:4,B:0};A.addFunction=A.p;A.removeFunction=A.v;var H=0;function assert(a,c){a||I("Assertion failed: "+c)}
function ba(a){var c=b["_"+a];if(!c)try{c=eval("_"+a)}catch(d){}assert(c,"Cannot call unknown function "+a+" (perhaps LLVM optimizations or closure removed it?)");return c}var ca;
(function(){var a={stackSave:function(){A.l()},stackRestore:function(){A.e()},arrayToC:function(a){var c=A.d(a.length);J.set(a,c);return c},stringToC:function(a){var c=0;if(null!==a&&void 0!==a&&0!==a){var f=(a.length<<2)+1,c=A.d(f);K(a,L,c,f)}return c}},c={string:a.stringToC,array:a.arrayToC};ca=function(a,e,f,g,l){a=ba(a);var k=[],m=0;if(g)for(var q=0;q<g.length;q++){var n=c[f[q]];n?(0===m&&(m=A.l()),k[q]=n(g[q])):k[q]=g[q]}f=a.apply(null,k);"string"===e&&(f=da(f));if(0!==m){if(l&&l.async){EmterpreterAsync.C.push(function(){A.e(m)});
return}A.e(m)}return f}})();b.ccall=ca;function ea(a){var c;c="i32";"*"===c.charAt(c.length-1)&&(c="i32");switch(c){case "i1":return J[a>>0];case "i8":return J[a>>0];case "i16":return M[a>>1];case "i32":return D[a>>2];case "i64":return D[a>>2];case "float":return N[a>>2];case "double":return O[a>>3];default:I("invalid type for setValue: "+c)}return null}
function P(a,c,d){var e,f,g;"number"===typeof a?(f=!0,g=a):(f=!1,g=a.length);var l="string"===typeof c?c:null,k;4==d?k=e:k=["function"===typeof Q?Q:A.o,A.d,A.o,A.s][void 0===d?2:d](Math.max(g,l?1:c.length));if(f){e=k;assert(0==(k&3));for(a=k+(g&-4);e<a;e+=4)D[e>>2]=0;for(a=k+g;e<a;)J[e++>>0]=0;return k}if("i8"===l)return a.subarray||a.slice?L.set(a,k):L.set(new Uint8Array(a),k),k;e=0;for(var m,q;e<g;){var n=a[e];"function"===typeof n&&(n=A.N(n));d=l||c[e];if(0===d)e++;else{"i64"==d&&(d="i32");f=k+
e;var C=d,C=C||"i8";"*"===C.charAt(C.length-1)&&(C="i32");switch(C){case "i1":J[f>>0]=n;break;case "i8":J[f>>0]=n;break;case "i16":M[f>>1]=n;break;case "i32":D[f>>2]=n;break;case "i64":tempI64=[n>>>0,(tempDouble=n,1<=+fa(tempDouble)?0<tempDouble?(ga(+ha(tempDouble/4294967296),4294967295)|0)>>>0:~~+ia((tempDouble-+(~~tempDouble>>>0))/4294967296)>>>0:0)];D[f>>2]=tempI64[0];D[f+4>>2]=tempI64[1];break;case "float":N[f>>2]=n;break;case "double":O[f>>3]=n;break;default:I("invalid type for setValue: "+C)}q!==
d&&(m=A.n(d),q=d);e+=m}}return k}function da(a){var c;if(0===c||!a)return"";for(var d=0,e,f=0;;){e=L[a+f>>0];d|=e;if(0==e&&!c)break;f++;if(c&&f==c)break}c||(c=f);e="";if(128>d){for(;0<c;)d=String.fromCharCode.apply(String,L.subarray(a,a+Math.min(c,1024))),e=e?e+d:d,a+=1024,c-=1024;return e}return b.UTF8ToString(a)}"undefined"!==typeof TextDecoder&&new TextDecoder("utf8");
function K(a,c,d,e){if(0<e){e=d+e-1;for(var f=0;f<a.length;++f){var g=a.charCodeAt(f);55296<=g&&57343>=g&&(g=65536+((g&1023)<<10)|a.charCodeAt(++f)&1023);if(127>=g){if(d>=e)break;c[d++]=g}else{if(2047>=g){if(d+1>=e)break;c[d++]=192|g>>6}else{if(65535>=g){if(d+2>=e)break;c[d++]=224|g>>12}else{if(2097151>=g){if(d+3>=e)break;c[d++]=240|g>>18}else{if(67108863>=g){if(d+4>=e)break;c[d++]=248|g>>24}else{if(d+5>=e)break;c[d++]=252|g>>30;c[d++]=128|g>>24&63}c[d++]=128|g>>18&63}c[d++]=128|g>>12&63}c[d++]=128|
g>>6&63}c[d++]=128|g&63}}c[d]=0}}function ja(a){for(var c=0,d=0;d<a.length;++d){var e=a.charCodeAt(d);55296<=e&&57343>=e&&(e=65536+((e&1023)<<10)|a.charCodeAt(++d)&1023);127>=e?++c:c=2047>=e?c+2:65535>=e?c+3:2097151>=e?c+4:67108863>=e?c+5:c+6}return c}"undefined"!==typeof TextDecoder&&new TextDecoder("utf-16le");
function ka(a){return a.replace(/__Z[\w\d_]+/g,function(a){var d;a:{var e=b.___cxa_demangle||b.__cxa_demangle;if(e)try{var f=a.substr(1),g=ja(f)+1,l=Q(g);K(f,L,l,g);var k=Q(4),m=e(l,0,0,k);if(0===ea(k)&&m){d=da(m);break a}}catch(q){}finally{l&&R(l),k&&R(k),m&&R(m)}else A.a("warning: build with  -s DEMANGLE_SUPPORT=1  to link in libcxxabi demangling");d=a}return a===d?a:a+" ["+d+"]"})}
function la(){var a;a:{a=Error();if(!a.stack){try{throw Error(0);}catch(c){a=c}if(!a.stack){a="(no stack trace available)";break a}}a=a.stack.toString()}b.extraStackTrace&&(a+="\n"+b.extraStackTrace());return ka(a)}var buffer,J,L,M,ma,D,na,N,O;
function oa(){b.HEAP8=J=new Int8Array(buffer);b.HEAP16=M=new Int16Array(buffer);b.HEAP32=D=new Int32Array(buffer);b.HEAPU8=L=new Uint8Array(buffer);b.HEAPU16=ma=new Uint16Array(buffer);b.HEAPU32=na=new Uint32Array(buffer);b.HEAPF32=N=new Float32Array(buffer);b.HEAPF64=O=new Float64Array(buffer)}var S,B,T,z,U,pa,E;S=B=T=z=U=pa=E=0;
function G(){I("Cannot enlarge memory arrays. Either (1) compile with  -s TOTAL_MEMORY=X  with X higher than the current value "+F+", (2) compile with  -s ALLOW_MEMORY_GROWTH=1  which allows increasing the size at runtime, or (3) if you want malloc to return NULL (0) instead of this abort, compile with  -s ABORTING_MALLOC=0 ")}var qa=b.TOTAL_STACK||5242880,F=b.TOTAL_MEMORY||16777216;F<qa&&b.c("TOTAL_MEMORY should be larger than TOTAL_STACK, was "+F+"! (TOTAL_STACK="+qa+")");
b.buffer?buffer=b.buffer:"object"===typeof WebAssembly&&"function"===typeof WebAssembly.Memory?(b.wasmMemory=new WebAssembly.Memory({initial:F/65536,maximum:F/65536}),buffer=b.wasmMemory.buffer):buffer=new ArrayBuffer(F);oa();D[0]=1668509029;M[1]=25459;if(115!==L[2]||99!==L[3])throw"Runtime error: expected the system to be little-endian!";b.HEAP=void 0;b.buffer=buffer;b.HEAP8=J;b.HEAP16=M;b.HEAP32=D;b.HEAPU8=L;b.HEAPU16=ma;b.HEAPU32=na;b.HEAPF32=N;b.HEAPF64=O;
function V(a){for(;0<a.length;){var c=a.shift();if("function"==typeof c)c();else{var d=c.J;"number"===typeof d?void 0===c.h?b.dynCall_v(d):b.dynCall_vi(d,c.h):d(void 0===c.h?null:c.h)}}}var ra=[],sa=[],ta=[],ua=[],va=[],W=!1;function wa(){var a=b.preRun.shift();ra.unshift(a)}function xa(a){var c=Array(ja(a)+1);K(a,c,0,c.length);return c}Math.imul&&-5===Math.imul(4294967295,5)||(Math.imul=function(a,c){var d=a&65535,e=c&65535;return d*e+((a>>>16)*e+d*(c>>>16)<<16)|0});Math.O=Math.imul;
if(!Math.fround){var ya=new Float32Array(1);Math.fround=function(a){ya[0]=a;return ya[0]}}Math.I=Math.fround;Math.clz32||(Math.clz32=function(a){a=a>>>0;for(var c=0;32>c;c++)if(a&1<<31-c)return c;return 32});Math.F=Math.clz32;Math.trunc||(Math.trunc=function(a){return 0>a?Math.ceil(a):Math.floor(a)});Math.trunc=Math.trunc;var fa=Math.abs,ia=Math.ceil,ha=Math.floor,ga=Math.min,X=0,za=null,Y=null;function Aa(){X++;b.monitorRunDependencies&&b.monitorRunDependencies(X)}
function Ba(){X--;b.monitorRunDependencies&&b.monitorRunDependencies(X);if(0==X&&(null!==za&&(clearInterval(za),za=null),Y)){var a=Y;Y=null;a()}}b.preloadedImages={};b.preloadedAudios={};var Z=null;
(function(a){function c(c){var d=a.usingWasm?65536:16777216;0<c%d&&(c+=d-c%d);var d=a.buffer,e=d.byteLength;if(a.usingWasm)try{return-1!==a.wasmMemory.grow((c-e)/65536)?a.buffer=a.wasmMemory.buffer:null}catch(g){return null}else return m.__growWasmMemory((c-e)/65536),a.buffer!==d?a.buffer:null}function d(){return a.wasmBinary||"function"!==typeof fetch?new Promise(function(c){var d;a:{try{var e;if(a.wasmBinary)e=a.wasmBinary,e=new Uint8Array(e);else if(a.readBinary)e=a.readBinary(g);else throw"on the web, we need the wasm binary to be preloaded and set on Module['wasmBinary']. emcc.py will do that for you when generating HTML (but not JS)";
d=e;break a}catch(f){I(f)}d=void 0}c(d)}):fetch(g,{G:"same-origin"}).then(function(a){if(!a.ok)throw"failed to load wasm binary file at '"+g+"'";return a.arrayBuffer()})}function e(c,e){function f(c){m=c.exports;if(m.memory){c=m.memory;var d=a.buffer;c.byteLength<d.byteLength&&a.printErr("the new buffer in mergeMemory is smaller than the previous one. in native wasm, we should grow memory here");var d=new Int8Array(d),e=new Int8Array(c);Z||d.set(e.subarray(a.STATIC_BASE,a.STATIC_BASE+a.STATIC_BUMP),
a.STATIC_BASE);e.set(d);b.buffer=buffer=c;oa()}a.asm=m;a.usingWasm=!0;Ba()}if("object"!==typeof WebAssembly)return a.printErr("no native wasm support detected"),!1;if(!(a.wasmMemory instanceof WebAssembly.Memory))return a.printErr("no native wasm Memory in use"),!1;e.memory=a.wasmMemory;k.global={NaN:NaN,Infinity:Infinity};k["global.Math"]=c.Math;k.env=e;Aa();if(a.instantiateWasm)try{return a.instantiateWasm(k,f)}catch(g){return a.printErr("Module.instantiateWasm callback failed with error: "+g),
!1}d().then(function(a){return WebAssembly.instantiate(a,k)}).then(function(a){f(a.instance)}).catch(function(c){a.printErr("failed to asynchronously prepare wasm: "+c);I(c)});return{}}a.wasmJSMethod=a.wasmJSMethod||"native-wasm";var f=a.wasmTextFile||"ldpc-wasm.wast",g=a.wasmBinaryFile||"ldpc-wasm.wasm",l=a.asmjsCodeFile||"ldpc-wasm.temp.asm.js";"function"===typeof a.locateFile&&(f=a.locateFile(f),g=a.locateFile(g),l=a.locateFile(l));var k={global:null,env:null,asm2wasm:{"f64-rem":function(a,c){return a%
c},"f64-to-int":function(a){return a|0},"i32s-div":function(a,c){return(a|0)/(c|0)|0},"i32u-div":function(a,c){return(a>>>0)/(c>>>0)>>>0},"i32s-rem":function(a,c){return(a|0)%(c|0)|0},"i32u-rem":function(a,c){return(a>>>0)%(c>>>0)>>>0},"debugger":function(){debugger}},parent:a},m=null;a.asmPreload=a.asm;var q=a.reallocBuffer;a.reallocBuffer=function(a){return"asmjs"===n?q(a):c(a)};var n="";a.asm=function(c,d){if(!d.table){var f=a.wasmTableSize;void 0===f&&(f=1024);var g=a.wasmMaxTableSize;d.table=
"object"===typeof WebAssembly&&"function"===typeof WebAssembly.Table?void 0!==g?new WebAssembly.Table({initial:f,maximum:g,element:"anyfunc"}):new WebAssembly.Table({initial:f,element:"anyfunc"}):Array(f);a.wasmTable=d.table}d.memoryBase||(d.memoryBase=a.STATIC_BASE);d.tableBase||(d.tableBase=0);return e(c,d)}})(b);S=A.f;B=S+1888;sa.push();Z=0<=b.wasmJSMethod.indexOf("asmjs")||0<=b.wasmJSMethod.indexOf("interpret-asm2wasm")?"ldpc-wasm.js.mem":null;b.STATIC_BASE=S;b.STATIC_BUMP=1888;var Ca=B;B+=16;
function Da(a){b.exit(a)}E=P(1,"i32",2);T=z=A.m(B);U=T+qa;pa=A.m(U);D[E>>2]=pa;b.wasmTableSize=0;b.wasmMaxTableSize=0;b.q={Math:Math,Int8Array:Int8Array,Int16Array:Int16Array,Int32Array:Int32Array,Uint8Array:Uint8Array,Uint16Array:Uint16Array,Uint32Array:Uint32Array,Float32Array:Float32Array,Float64Array:Float64Array,NaN:NaN,Infinity:Infinity};
b.r={abort:I,assert:assert,enlargeMemory:function(){G()},getTotalMemory:function(){return F},abortOnCannotGrowMemory:G,_exit:function(a){Da(a)},__exit:Da,___setErrNo:function(a){b.___errno_location&&(D[b.___errno_location()>>2]=a);return a},DYNAMICTOP_PTR:E,tempDoublePtr:Ca,ABORT:H,STACKTOP:z,STACK_MAX:U};var Ea=b.asm(b.q,b.r,buffer);b.asm=Ea;var Q=b._malloc=function(){return b.asm._malloc.apply(null,arguments)};b.getTempRet0=function(){return b.asm.getTempRet0.apply(null,arguments)};
var R=b._free=function(){return b.asm._free.apply(null,arguments)};b.runPostSets=function(){return b.asm.runPostSets.apply(null,arguments)};b.setTempRet0=function(){return b.asm.setTempRet0.apply(null,arguments)};b.establishStackSpace=function(){return b.asm.establishStackSpace.apply(null,arguments)};b._decode=function(){return b.asm._decode.apply(null,arguments)};b._memset=function(){return b.asm._memset.apply(null,arguments)};b._sbrk=function(){return b.asm._sbrk.apply(null,arguments)};
b._encode=function(){return b.asm._encode.apply(null,arguments)};b._emscripten_get_global_libc=function(){return b.asm._emscripten_get_global_libc.apply(null,arguments)};b.stackAlloc=function(){return b.asm.stackAlloc.apply(null,arguments)};b.setThrew=function(){return b.asm.setThrew.apply(null,arguments)};b.stackRestore=function(){return b.asm.stackRestore.apply(null,arguments)};b.stackSave=function(){return b.asm.stackSave.apply(null,arguments)};A.d=b.stackAlloc;A.l=b.stackSave;A.e=b.stackRestore;
A.H=b.establishStackSpace;A.w=b.setTempRet0;A.u=b.getTempRet0;b.asm=Ea;
if(Z)if("function"===typeof b.locateFile?Z=b.locateFile(Z):b.memoryInitializerPrefixURL&&(Z=b.memoryInitializerPrefixURL+Z),u||v){var Fa=b.readBinary(Z);L.set(Fa,A.f)}else{var Ha=function(){b.readAsync(Z,Ga,function(){throw"could not load memory initializer "+Z;})};Aa();var Ga=function(a){a.byteLength&&(a=new Uint8Array(a));L.set(a,A.f);b.memoryInitializerRequest&&delete b.memoryInitializerRequest.response;Ba()};if(b.memoryInitializerRequest){var Ia=function(){var a=b.memoryInitializerRequest;200!==
a.status&&0!==a.status?(console.warn("a problem seems to have happened with Module.memoryInitializerRequest, status: "+a.status+", retrying "+Z),Ha()):Ga(a.response)};b.memoryInitializerRequest.response?setTimeout(Ia,0):b.memoryInitializerRequest.addEventListener("load",Ia)}else Ha()}b.then=function(a){if(b.calledRun)a(b);else{var c=b.onRuntimeInitialized;b.onRuntimeInitialized=function(){c&&c();a(b)}}return b};
function y(a){this.name="ExitStatus";this.message="Program terminated with exit("+a+")";this.status=a}y.prototype=Error();y.prototype.constructor=y;var Ja=null,Y=function Ka(){b.calledRun||La();b.calledRun||(Y=Ka)};
b.callMain=b.D=function(a){function c(){for(var a=0;3>a;a++)e.push(0)}a=a||[];W||(W=!0,V(sa));var d=a.length+1,e=[P(xa(b.thisProgram),"i8",0)];c();for(var f=0;f<d-1;f+=1)e.push(P(xa(a[f]),"i8",0)),c();e.push(0);e=P(e,"i32",0);try{var g=b._main(d,e,0);Ma(g,!0)}catch(l){l instanceof y||("SimulateInfiniteLoop"==l?b.noExitRuntime=!0:((a=l)&&"object"===typeof l&&l.stack&&(a=[l,l.stack]),b.c("exception thrown: "+a),b.quit(1,l)))}finally{}};
function La(a){function c(){if(!b.calledRun&&(b.calledRun=!0,!H)){W||(W=!0,V(sa));V(ta);if(b.onRuntimeInitialized)b.onRuntimeInitialized();b._main&&Na&&b.callMain(a);if(b.postRun)for("function"==typeof b.postRun&&(b.postRun=[b.postRun]);b.postRun.length;){var c=b.postRun.shift();va.unshift(c)}V(va)}}a=a||b.arguments;null===Ja&&(Ja=Date.now());if(!(0<X)){if(b.preRun)for("function"==typeof b.preRun&&(b.preRun=[b.preRun]);b.preRun.length;)wa();V(ra);0<X||b.calledRun||(b.setStatus?(b.setStatus("Running..."),
setTimeout(function(){setTimeout(function(){b.setStatus("")},1);c()},1)):c())}}b.run=b.run=La;function Ma(a,c){if(!c||!b.noExitRuntime){if(!b.noExitRuntime&&(H=!0,z=void 0,V(ua),b.onExit))b.onExit(a);u&&process.exit(a);b.quit(a,new y(a))}}b.exit=b.exit=Ma;var Oa=[];
function I(a){if(b.onAbort)b.onAbort(a);void 0!==a?(b.print(a),b.c(a),a=JSON.stringify(a)):a="";H=!0;var c="abort("+a+") at "+la()+"\nIf this abort() is unexpected, build with -s ASSERTIONS=1 which can give more information.";Oa&&Oa.forEach(function(d){c=d(c,a)});throw c;}b.abort=b.abort=I;if(b.preInit)for("function"==typeof b.preInit&&(b.preInit=[b.preInit]);0<b.preInit.length;)b.preInit.pop()();var Na=!0;b.noInitialRun&&(Na=!1);b.noExitRuntime=!0;La();

  return LDPC_HANDLER;
};
if (typeof module === "object" && module.exports) {
  module['exports'] = LDPC_HANDLER;
};
