import './App.css';
//import { withTheme } from '@rjsf/core';
import   Form  from '@rjsf/material-ui';
import * as React from "react"
import *  as Qt from "qwebchannel"

var backend;
//const Form = withTheme(AntDTheme)

const App = () => {
  const [formData, setFormData] = React.useState(formdata2);
  const [schemaForm,setSchemaForm] = React.useState(schemaForm2);
  const [style,setStyle] = React.useState({ __html:''});
  
  
  window.onload = function() {
    console.log("sdasd");
    new Qt.QWebChannel(qt.webChannelTransport, function(channel) {
        // all published objects are available in channel.objects under
        // the identifier set in their attached WebChannel.id property
        //channel.objects.backend.someFunction = setSchemaForm;
        backend = channel.objects.backend;
        backend.formDataChanged.connect((schema,data) => {setSchemaForm(schema);setFormData(data)});
        backend.styleChanged.connect((style) => setStyle({__html:style}));
        backend.style((r) => console.log(r));
        backend.style((r) => setStyle({__html:r}));
    });
 }
  return <div><style dangerouslySetInnerHTML={style} /><Form schema={schemaForm} formData={formData} showErrorList={false} liveValidate={true} onSubmit={({formData}) => backend.someFunction(formData)}/></div> ;
};


 

//etTimeout(() => backend.)

var schemaForms = {
  "title": "A registration form",
  "description": "A simple form example.",
  "type": "object",
  "required": [
    "firstName",
    "lastName"
  ],
  "properties": {
    "firstName": {
      "type": "string",
      "title": "First name",
      "default": "Chuck"
    },
    "lastName": {
      "type": "string",
      "title": "Last name"
    },
    "telephone": {
      "type": "string",
      "title": "Telephone",
      "minLength": 10
    }
  }
}

var schemaForm2 = {
  "definitions": {
    "largeEnum": {
      "type": "string",
      "enum": [
        "option #0",
        "option #1",
        "option #2",
        "option #3",
        "option #4",
        "option #5",
        "option #6",
        "option #7",
        "option #8",
        "option #9",
        "option #10",
        "option #11",
        "option #12",
        "option #13",
        "option #14",
        "option #15",
        "option #16",
        "option #17",
        "option #18",
        "option #19",
        "option #20",
        "option #21",
        "option #22",
        "option #23",
        "option #24",
        "option #25",
        "option #26",
        "option #27",
        "option #28",
        "option #29",
        "option #30",
        "option #31",
        "option #32",
        "option #33",
        "option #34",
        "option #35",
        "option #36",
        "option #37",
        "option #38",
        "option #39",
        "option #40",
        "option #41",
        "option #42",
        "option #43",
        "option #44",
        "option #45",
        "option #46",
        "option #47",
        "option #48",
        "option #49",
        "option #50",
        "option #51",
        "option #52",
        "option #53",
        "option #54",
        "option #55",
        "option #56",
        "option #57",
        "option #58",
        "option #59",
        "option #60",
        "option #61",
        "option #62",
        "option #63",
        "option #64",
        "option #65",
        "option #66",
        "option #67",
        "option #68",
        "option #69",
        "option #70",
        "option #71",
        "option #72",
        "option #73",
        "option #74",
        "option #75",
        "option #76",
        "option #77",
        "option #78",
        "option #79",
        "option #80",
        "option #81",
        "option #82",
        "option #83",
        "option #84",
        "option #85",
        "option #86",
        "option #87",
        "option #88",
        "option #89",
        "option #90",
        "option #91",
        "option #92",
        "option #93",
        "option #94",
        "option #95",
        "option #96",
        "option #97",
        "option #98",
        "option #99"
      ]
    }
  },
  "title": "A rather large form",
  "type": "object",
  "properties": {
    "string": {
      "type": "string",
      "title": "Some string"
    },
    "choice1": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice2": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice3": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice4": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice5": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice6": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice7": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice8": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice9": {
      "$ref": "#/definitions/largeEnum"
    },
    "choice10": {
      "$ref": "#/definitions/largeEnum"
    }
  }
}

var formDatas = {
  "firstName": "Chuck",
  "lastName": "Norris",
  "age": 75,
  "bio": "Roundhouse kicking asses since 1940",
  "password": "noneed"
}

var formdata2 = {}
//setTimeout(() => {window.setSchemaForm(schemaForm2);window.setSchemaData(formdata2)},5000)

export default App;
