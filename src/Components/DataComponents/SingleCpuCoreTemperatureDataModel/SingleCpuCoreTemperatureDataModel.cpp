//
// Created by kwan on 14.07.19.
//

#include "SingleCpuCoreTemperatureDataModel.h"

#include <QtCore/QDirIterator>
#include <iostream>

#include "../../ComponentUtils/utils.h"

using namespace std;

SingleCpuCoreTemperatureDataModel::SingleCpuCoreTemperatureDataModel(
    QObject* parent)
    : DataModelBase(parent, "defaultCpuTemperatureTransformer") {
  cpuAcpiId = Utils::getApicIdList().first();
  initialize();
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreTemperatureDataModel::computeCpuTemp);
  setTimerInterval(1000);
}

SingleCpuCoreTemperatureDataModel::SingleCpuCoreTemperatureDataModel(
    int timerInterval, QString acpiId, QObject* parent)
    : DataModelBase(parent, "defaultCpuTemperatureTransformer") {
  acpiId = acpiId;
  initialize();
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreTemperatureDataModel::computeCpuTemp);
  setTimerInterval(timerInterval);
  _timer->start(timerInterval);
}

void SingleCpuCoreTemperatureDataModel::initialize() {
  Utils::getCpuArch() == Intel ? initializeIntel() : initializeAmd();
}

void SingleCpuCoreTemperatureDataModel::initializeIntel() {}
void SingleCpuCoreTemperatureDataModel::initializeAmd() {
  QString path = "/sys/class/hwmon";
  QDirIterator it(path, QDir::Filter::Dirs,
                  QDirIterator::IteratorFlag::NoIteratorFlags);
  while (it.hasNext()) {
    auto dir = it.next();
    QFile file(dir + "/name");
    if (file.exists() && file.open(QFile::ReadOnly) &&
        QString(file.readAll()).contains(QRegExp("k10temp"))) {
      QDirIterator innerIt(dir, QStringList("*_label"), QDir::Files);
      while (innerIt.hasNext()) {
        auto innerFilePath = innerIt.next();
        QFile innerFile(innerFilePath);
        if (innerFile.exists() && innerFile.open(QFile::ReadOnly) &&
            QString(innerFile.readAll()).contains(QRegExp("Tdie"))) {
          innerFilePath.chop(6);
          sensorPath = innerFilePath.append("_input");
          break;
        }
      }
      break;
    }
  }
}

void SingleCpuCoreTemperatureDataModel::computeCpuTemp() {
  QFile file(sensorPath);
  if (file.exists() && file.open(QFile::ReadOnly)) {
    // auto engine = Utils::qjsEngine;
    setCurrentValue(file.readAll(), true);
    return;
  }
  setCurrentValue("0", true);
}
