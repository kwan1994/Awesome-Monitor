//
// Created by kwan on 11/22/18.
//
#ifndef AWESOMEMONITOR_JSONTOTREEPARSER_H
#define AWESOMEMONITOR_JSONTOTREEPARSER_H

#include <rapidjson/schema.h>

#include <QtCore>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlPropertyMap>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../Components/ComponentUtils/utils.h"
#include "../ApplicationModel/Model.h"
#include "../JsonValueConverter/JsonValueConverter.h"

using namespace std;

class JsonToTreeParser {
 public:
  QQmlEngine *engine = Utils::qjsEngine;
  JsonToTreeParser(QString, QString, JsonValueConverter);
  Model *createModel(QString);
  Model *createModelFromFile(QString pathToModel);
  static QMap<QString, QString> createFileMap(QString path,
                                              QString extension = "*.qml");

 private:
  QString errorComponentpath =
      QStandardPaths::locate(QStandardPaths::StandardLocation::ConfigLocation,
                             "AwesomeMonitor/errorComponent.qml",
                             QStandardPaths::LocateOption::LocateFile);
  QList<QString> ignoredPropertyNames = {"dataModels", "childern", "name", "_"};
  QList<QQmlExpression *> bindings = QList<QQmlExpression *>();
  JsonValueConverter converter;

  QQmlContext *context = new QQmlContext(engine->rootContext());
  QMap<QString, QString> filePathsToQmlComponents;
  QMap<QString, QString> filePathsToQmlDataModels;
  nlohmann::json generateSchema(QString baseComponentsSchemasPath,
                                QString dataModelsSchemasPath);
  QSharedPointer<Node> createNode(nlohmann::json &object, QQmlContext *);
  QSharedPointer<QObject> initializeComponet(nlohmann::json &object,
                                             QSharedPointer<Node>);
  QSharedPointer<Node> createWindow(nlohmann::json &object, QWindow *parent);
  void addDataModelsToComponent(QObject *pObject, nlohmann::json &object,
                                QSharedPointer<Node> parent);
  QSharedPointer<QObject> createErrorComponent(QString string);
  Model *createErrorModel(QString error);
};

inline std::string schema =
    R"({
       "$schema":"http://json-schema.org/draft-07/schema#",
       "name":"Component",
       "definitions":{
            "DataModel":{
         "allOf":[
            {
            "anyOf": []
            },
            {
               "type":"object",
               "properties":{
                  "_":{
                     "type":"string"
                  },
                 "transformFunc":{
                 	"type":"object",
                   	"properties":{"type":{"enum":["function"]},"value":{"type":"string"}}
,
                 	"additionalProperties":false
                 }
               }

            }
         ]
      },
          "Component":{
             "allOf":[

            {
              "type": "object",
              "properties": {
                "_": {
                  "type": "string"
                },
                "childern": {
                  "type": "array",
                  "items": {
                    "$ref": "#/definitions/Component"
                  }
                },"dataModels": {
                    "type":"object",
                    "additionalProperties":{"$ref": "#/definitions/DataModel"}
                }
              },
              "required": [
                "_"
              ]
            }, {
              "anyOf": []
            }
          ]
        },"Model": {
          "type": "object",
          "properties": {
            "windows": {
              "type": "array",
              "items": {
                "$ref": "#/definitions/Window"
              }
            }

          },
            "required":["windows"]
        },
        "Window":{
              "type": "object",
              "properties": {
                "_": { "allOf":[{
                  "type": "string"}]
                },
                "childern": {
                  "type": "array",
                  "items": {
                    "$ref": "#/definitions/Component"
                  }
                }
              },
              "required": [
                "_"
              ]
            }

      },
      "$ref": "#/definitions/Model"
    })";
#endif  // AWESOMEMONITOR_JSONTOTREEPARSER_H
