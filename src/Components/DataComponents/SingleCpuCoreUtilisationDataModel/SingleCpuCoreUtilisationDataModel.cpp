//
// Created by kwan on 04.08.19.
//

#include "SingleCpuCoreUtilisationDataModel.h"
#include <QDebug>
#include <QtCore/QFile>
#include <iostream>
using namespace std;
void SingleCpuCoreUtilisationDataModel::computeValue() {
  QFile file("/proc/stat");

  if (file.exists() && file.open(QFile::ReadOnly)) {
    QRegExp regex(QString("cpu%0 .*").arg(id));
    if(regex.indexIn(QString(file.readAll())) == -1)
  {return;}
    auto line = regex.capturedTexts().first();
    auto values = regex.capturedTexts()
                      .first()
                      .remove(0, id.length())
                      .split(" ")
                      .toVector();
    auto prevTotal = total;
    auto prevIdle = idle;
    idle = values[3].toInt() + values[4].toInt();
    auto userTime = values[0].toDouble() - values[8].toInt();
    auto niceTime = values[1].toInt() - values[9].toInt();
    auto systemTime = values[2].toInt() + values[5].toInt() + values[6].toInt();
    auto virtualTime = values[8].toInt() + values[9].toInt();
    total = userTime + niceTime + systemTime + idle + values[7].toInt() +
            virtualTime;

    setCurrentValue(
        ((total - prevTotal) - (idle - prevIdle)) / (total - prevTotal), true);
  }
}
void SingleCpuCoreUtilisationDataModel::initialize() {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreUtilisationDataModel::computeValue);
  _timer->start(_timerInterval);
}
SingleCpuCoreUtilisationDataModel::SingleCpuCoreUtilisationDataModel(
    QObject *parent)
    : DataModelBase(parent, "defaultIntPercentTransformer") {
  initialize();
}
SingleCpuCoreUtilisationDataModel::SingleCpuCoreUtilisationDataModel(
    QString acpiId, QObject *parent)
    : DataModelBase(parent, "defaultIntPercentTransformer") {
  id = id + acpiId;

  initialize();
}
