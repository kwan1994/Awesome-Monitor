//
// Created by kwan on 21.07.19.
//

#ifndef AWESOMEMONITOR_PLUGIN_H
#define AWESOMEMONITOR_PLUGIN_H

#include <KF5/Plasma/Theme>
#include <QtCore/QObject>
#include <QtCore/QSettings>

#include "ComponentFramework/ApplicationModel/Model.h"
#include "Editor/Models/ImageLivePreviewProvider.h"
class Plugin : public QObject {
  QString css =
      "body{background:%viewbackgroundcolor !important; padding-right: 10px; "
      "padding-left: 10px}"
      "label {color:%viewtextcolor !important}"
      "span {color:%viewtextcolor !important}"
      "button span {color:%buttontextcolor !important}"
      "button {background:%buttonbackgroundcolor !important}"
      "button:hover span {color:%buttonhighlightedtextcolor !important}"
      "button:hover {background:%buttonhovercolor !important}"
      "input {color:%viewtextcolor !important; background:%backgroundcolor "
      "!important}"
      "input:hover:not(:disabled) {color:%highlightedtextcolor !important; "
      "background:%highlightcolor !important}"
      "input:focus {color:%highlightedtextcolor !important; "
      "background:%highlightcolor !important}"
      ".form-select {color:%textcolor "
      "!important;background-color:%backgroundcolor !important}"
      ".form-select:hover:not(:disabled) "
      "{color:%highlightedtextcolor "
      "!important;background-color:%highlightcolor "
      "!important }"
      ".form-select:focus "
      "{color:%highlightedtextcolor "
      "!important;background-color:%highlightcolor "
      "!important}"
      ".je-modal {background-color: %backgroundcolor;box-shadow: initial;}"
      "p {color:%viewtextcolor}"
      "button .svg-inline--fa {color: %buttontextcolor;}"
      "button:hover .svg-inline--fa {color: %buttonhighlightedtextcolor;}"
      ".je-switcher {margin-bottom: 10px;}"
      ".columns {padding-right: 10px;padding-left: 10px;}";

  Q_OBJECT
  QSharedPointer<Model> model;

  QSettings settings = QSettings("AwesomeMonitor", QSettings::IniFormat);
  ImageProvider *imageProvider;
  bool addProvider = true;
  bool shouldHideWindows = false;

 public:
  Q_INVOKABLE int numberOfWindows();
  Plugin(QObject *parent = nullptr);
  void initializePlugin();
  Q_INVOKABLE void resetPlugin();
  Q_INVOKABLE void deletePlugin();
  Q_INVOKABLE void initializePluginFromString(QString modelString);
  Q_INVOKABLE QString stylesheet() { return Plasma::Theme().styleSheet(css); }
  Q_INVOKABLE bool saveToFile(QJsonObject json);
  Q_INVOKABLE void setHideWindows();
  Q_INVOKABLE bool tryCreateDefaultModelFile(QString);
  ~Plugin();
 signals:
  void intializing();
  void initialized(QVector<QQuickWindow *> windows);
};

#endif  // AWESOMEMONITOR_PLUGIN_H
