//
// Created by kwan on 21.07.19.
//

#include "SingleCpuCoreMaxTemperatureDataModel.h"
#include "../../ComponentUtils/utils.h"
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <iostream>

using namespace std;

void SingleCpuCoreMaxTemperatureDataModel::initializeIntel() {}
void SingleCpuCoreMaxTemperatureDataModel::initializeAmd() {
  QString path = "/sys/class/hwmon";
  QDirIterator it(path, QDir::Filter::Dirs,
                  QDirIterator::IteratorFlag::NoIteratorFlags);

  while (it.hasNext()) {
    auto dir = it.next();
    QFile file(dir + "/name");
    if (file.exists() && file.open(QFile::ReadOnly) &&
        QString(file.readAll()).contains(QRegExp("k10temp"))) {
      if (QFile::exists(dir + "/temp1_crit")) {
        sensorPath = dir + "/temp1_crit";
      }
      break;
    }
  }
}

SingleCpuCoreMaxTemperatureDataModel::SingleCpuCoreMaxTemperatureDataModel(
    int timerInterval, QString acpiId, QObject *parent)
    : DataModelBase(parent,"defaultCpuTemperatureTransformer") {
  this->cpuAcpiId = acpiId;
  initialize();
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreMaxTemperatureDataModel::computeCpuTemp);
  setTimerInterval(timerInterval);
}

SingleCpuCoreMaxTemperatureDataModel::SingleCpuCoreMaxTemperatureDataModel(
    QObject *parent)
    : DataModelBase(parent,"defaultCpuTemperatureTransformer") {
  initialize();
}

void SingleCpuCoreMaxTemperatureDataModel::computeCpuTemp() {
  QFile file(sensorPath);
  if (file.exists() && file.open(QFile::ReadOnly)) {
    setCurrentValue(file.readAll(),true);
    return;
  }
  setCurrentValue("105000",true);
}

void SingleCpuCoreMaxTemperatureDataModel::initialize() {
  Utils::getCpuArch() == Amd?initializeAmd():initializeIntel();
}
