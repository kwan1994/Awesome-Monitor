//
// Created by kwan on 08.07.19.
//

#include "utils.h"

#include <wordexp.h>

#include <QDebug>
#include <QDir>
#include <QJSEngine>
#include <QVector>
#include <QtCore/QFile>
#include <QtCore/QMap>
#include <QtCore/QStandardPaths>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::filesystem;

QQmlEngine* Utils::qjsEngine = nullptr;
QSettings Utils::settings = QSettings(
    QStandardPaths::locate(QStandardPaths::StandardLocation::ConfigLocation,
                           "AwesomeMonitor/AwesomeMonitor",
                           QStandardPaths::LocateOption::LocateFile),
    QSettings::IniFormat);

QStringList Utils::getApicIdList() {
  QStringList list;
  QFile file("/proc/cpuinfo");
  if (file.exists() && file.open(QFile::ReadOnly)) {
    auto cpuInfos = QString::fromLatin1(file.readAll())
                        .split(QRegExp("\\n\\n"), QString::SkipEmptyParts);

    QMap<QString, QVector<QString>*> sortedInfos;

    for (auto cpuInfo : cpuInfos) {
      QRegExp regex("core id\\t\\t: \\d+");
      regex.indexIn(cpuInfo);
      if (!sortedInfos.contains(regex.capturedTexts().first()))
        sortedInfos[regex.capturedTexts().first()] = new QVector<QString>();

      sortedInfos[regex.capturedTexts().first()]->push_back(cpuInfo);
    }

    for (auto cpuInfoSiblings : sortedInfos) {
      for (auto cpuInfo : *cpuInfoSiblings) {
        QRegExp regex("apicid\t: \\d+");
        regex.indexIn(cpuInfo);
        auto line = regex.capturedTexts().first();
        QRegExp number("\\d+");
        number.indexIn(line);
        list << number.capturedTexts().first();
      }
    }
  }

  return list;
}

CpuArch Utils::getCpuArch() { return Amd; }

QJSValue Utils::getTransformer(QString name, QQmlEngine* jsEngine) {
  auto module = jsEngine->importModule(
      QStandardPaths::locate(QStandardPaths::StandardLocation::ConfigLocation,
                             "defaultJavascriptTransformers.mjs",
                             QStandardPaths::LocateOption::LocateFile));
  return module.property(name);
}

QString Utils::getModelFileSetting() {
  qDebug() << expandHome(
      getSetting("modelFile", "defaultModel.json").toString());
  return expandHome(getSetting("modelFile", "defaultModel.json").toString());
}

QString Utils::getDataModelsFolderSetting() {
  return expandHome(getSetting("dataModelsFolder", "dataModels").toString());
}

int Utils::getTimeIntervalSetting() {
  return getSetting("timeInterval", 1000).toInt();
}
QVariant Utils::getSetting(QString name, QVariant defaultValue = QVariant()) {
  qDebug() << settings.allKeys() << settings.fileName() << endl;
  settings.sync();
  return settings.value(name, defaultValue);
}

QString Utils::getBasicComponentFolder() {
  return expandHome(
      getSetting("basicComponentsFolder", "componentsModels").toString());
}
QString Utils::expandHome(QString string) {
  if (string.startsWith("~/")) {
    return QDir::homePath().append(QDir::separator()).append(string.mid(2));
  }
  return string;
}
