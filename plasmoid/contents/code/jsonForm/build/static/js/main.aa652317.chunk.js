(this["webpackJsonpmy-app"]=this["webpackJsonpmy-app"]||[]).push([[0],[,,function(e,n,t){"use strict";var o=1,r=2,a=3,i=4,c=5,s=6,d=7,p=8,l=9,_=10;function f(e,n,t){this.__id__=e,t.objects[e]=this,this.__objectSignals__={},this.__propertyCache__={};var o=this;function r(e,n){var r=e[0],a=e[1];o[r]={connect:function(e){"function"===typeof e?(o.__objectSignals__[a]=o.__objectSignals__[a]||[],o.__objectSignals__[a].push(e),n||"destroyed"===r||t.exec({type:d,object:o.__id__,signal:a})):console.error("Bad callback given to connect to signal "+r)},disconnect:function(e){if("function"===typeof e){o.__objectSignals__[a]=o.__objectSignals__[a]||[];var i=o.__objectSignals__[a].indexOf(e);-1!==i?(o.__objectSignals__[a].splice(i,1),n||0!==o.__objectSignals__[a].length||t.exec({type:p,object:o.__id__,signal:a})):console.error("Cannot find connection of signal "+r+" to "+e.name)}else console.error("Bad callback given to disconnect from signal "+r)}}}function a(e,n){var t=o.__objectSignals__[e];t&&t.forEach((function(e){e.apply(e,n)}))}for(var e in this.unwrapQObject=function(e){if(e instanceof Array){for(var n=new Array(e.length),r=0;r<e.length;++r)n[r]=o.unwrapQObject(e[r]);return n}if(!e||!e["__QObject*__"]||void 0===e.id)return e;var a=e.id;if(t.objects[a])return t.objects[a];if(e.data){var i=new f(a,e.data,t);return i.destroyed.connect((function(){if(t.objects[a]===i){delete t.objects[a];var e=[];for(var n in i)e.push(n);for(var o in e)delete i[e[o]]}})),i.unwrapProperties(),i}console.error("Cannot unwrap unknown QObject "+a+" without data.")},this.unwrapProperties=function(){for(var e in o.__propertyCache__)o.__propertyCache__[e]=o.unwrapQObject(o.__propertyCache__[e])},this.propertyUpdate=function(e,n){for(var t in n){var r=n[t];o.__propertyCache__[t]=r}for(var i in e)a(i,e[i])},this.signalEmitted=function(e,n){a(e,n)},n.methods.forEach((function(e){var n=e[0],r=e[1];o[n]=function(){for(var e,n=[],a=0;a<arguments.length;++a)"function"===typeof arguments[a]?e=arguments[a]:n.push(arguments[a]);t.exec({type:s,object:o.__id__,method:r,args:n},(function(n){if(void 0!==n){var t=o.unwrapQObject(n);e&&e(t)}}))}})),n.properties.forEach((function(e){var n=e[0],a=e[1],i=e[2];o.__propertyCache__[n]=e[3],i&&(1===i[0]&&(i[0]=a+"Changed"),r(i,!0)),Object.defineProperty(o,a,{configurable:!0,get:function(){var e=o.__propertyCache__[n];return void 0===e&&console.warn('Undefined value in property cache for property "'+a+'" in object '+o.__id__),e},set:function(e){void 0!==e?(o.__propertyCache__[n]=e,t.exec({type:l,object:o.__id__,property:n,value:e})):console.warn("Property setter for "+a+" called with undefined value!")}})})),n.signals.forEach((function(e){r(e,!1)})),n.enums)o[e]=n.enums[e]}e.exports={QWebChannel:function(e,n){if("object"===typeof e&&"function"===typeof e.send){var t=this;this.transport=e,this.send=function(e){"string"!==typeof e&&(e=JSON.stringify(e)),t.transport.send(e)},this.transport.onmessage=function(e){var n=e.data;switch("string"===typeof n&&(n=JSON.parse(n)),n.type){case o:t.handleSignal(n);break;case _:t.handleResponse(n);break;case r:t.handlePropertyUpdate(n);break;default:console.error("invalid message received:",e.data)}},this.execCallbacks={},this.execId=0,this.exec=function(e,n){n?(t.execId===Number.MAX_VALUE&&(t.execId=Number.MIN_VALUE),e.hasOwnProperty("id")?console.error("Cannot exec message with property id: "+JSON.stringify(e)):(e.id=t.execId++,t.execCallbacks[e.id]=n,t.send(e))):t.send(e)},this.objects={},this.handleSignal=function(e){var n=t.objects[e.object];n?n.signalEmitted(e.signal,e.args):console.warn("Unhandled signal: "+e.object+"::"+e.signal)},this.handleResponse=function(e){e.hasOwnProperty("id")?(t.execCallbacks[e.id](e.data),delete t.execCallbacks[e.id]):console.error("Invalid response message received: ",JSON.stringify(e))},this.handlePropertyUpdate=function(e){for(var n in e.data){var o=e.data[n],r=t.objects[o.object];r?r.propertyUpdate(o.signals,o.properties):console.warn("Unhandled property update: "+o.object+"::"+o.signal)}t.exec({type:i})},this.debug=function(e){t.send({type:c,data:e})},t.exec({type:a},(function(e){for(var o in e)new f(o,e[o],t);for(var o in t.objects)t.objects[o].unwrapProperties();n&&n(t),t.exec({type:i})}))}else console.error("The QWebChannel expects a transport object with a send function and onmessage callback property. Given is: transport: "+typeof e+", transport.send: "+typeof e.send)}}},function(e,n,t){"use strict";t.r(n);var o,r,a=t(1),i=t(2);t(4),t(5);window.onload=function(){console.log("sdasd"),new i.QWebChannel(qt.webChannelTransport,(function(e){window.document.getElementById("submit-button-my").addEventListener("click",(function(){return r.setFormData(o.getValue())})),(r=e.objects.backend).formDataChanged.connect((function(e,n){o&&o.destroy(),o=new a.JSONEditor(window.document.getElementById("root"),{iconlib:"fontawesome5",schema:e,theme:"spectre",disable_collapse:!1,startval:n})})),r.getTreeCurrentData((function(e){o=new a.JSONEditor(window.document.getElementById("root"),{iconlib:"fontawesome5",schema:e.schemaForm,startval:e.formData,theme:"spectre",disable_collapse:!1})})),r.styleChanged.connect((function(e){return window.document.getElementById("style").innerHTML=e})),r.style((function(e){return window.document.getElementById("style").innerHTML=e}))}))}}],[[3,1,2]]]);
//# sourceMappingURL=main.aa652317.chunk.js.map