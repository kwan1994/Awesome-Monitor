import * as edit from "@json-editor/json-editor"
import *  as Qt from "qwebchannel"
import "spectre.css"
import "@fortawesome/fontawesome-free/js/all"


//var json = require("@json-editor/json-editor");

var s;
var editor;

var backend;
  


  window.onload = function() {
    console.log("sdasd");
    new Qt.QWebChannel(qt.webChannelTransport, function(channel) {
        // all published objects are available in channel.objects under
        // the identifier set in their attached WebChannel.id property
        //channel.objects.backend.someFunction = setSchemaForm;
        window.document.getElementById("submit-button-my").addEventListener("click",() => backend.setFormData(editor.getValue()));
        backend = channel.objects.backend;
        backend.formDataChanged.connect((schema,data) => {
          if(editor){
            editor.destroy();
            
          }
          editor = new  edit.JSONEditor(window.document.getElementById("root"),{iconlib: "fontawesome5",schema:schema,theme:"spectre",disable_collapse:false,startval:data});
        });
        backend.getTreeCurrentData((result) =>{ 
        editor = new  edit.JSONEditor(window.document.getElementById("root"),{iconlib: "fontawesome5",schema:result.schemaForm,startval:result.formData,theme:"spectre",disable_collapse:false});
        });
        backend.styleChanged.connect((style) => window.document.getElementById("style").innerHTML = style);
        backend.style(style => window.document.getElementById("style").innerHTML = style);
        
    });}
// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
// reportWebVitals()
