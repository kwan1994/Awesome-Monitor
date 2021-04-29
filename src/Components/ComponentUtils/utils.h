//
// Created by kwan on 08.07.19.
//

#ifndef AWESOMEMONITOR_UTILS_H
#define AWESOMEMONITOR_UTILS_H

#include <QQmlEngine>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore/QSettings>
#include <QtQml/QJSValue>

enum CpuArch { Intel, Amd };
class Utils {
  static QSettings settings;

  static QVariant computeUtilisation(QVector<QString> stats);

 public:
  static QString getModelFileSetting();
  static QString getDataModelsFolderSetting();
  static QString getBasicComponentFolder();
  static int getTimeIntervalSetting();
  static QVariant getSetting(QString name, QVariant defaultValue);
  static QQmlEngine* qjsEngine;
  static CpuArch getCpuArch();
  static QStringList getApicIdList();
  static QJSValue getTransformer(QString name, QQmlEngine* engine);
  static QString expandHome(QString qString);
};

#endif  // AWESOMEMONITOR_UTILS_H
