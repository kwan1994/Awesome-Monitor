//
// Created by kwan on 29.07.19.
//

#include "SingleCpuCoreMinFrequencyDataModel.h"
#include <QtCore/QFile>
#include <iostream>
#include "../../ComponentUtils/utils.h"
using namespace std;
SingleCpuCoreMinFrequencyDataModel::SingleCpuCoreMinFrequencyDataModel(
    QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = Utils::getApicIdList().first();
  Initialize();
}

SingleCpuCoreMinFrequencyDataModel::SingleCpuCoreMinFrequencyDataModel(
    QString acpiId, QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = acpiId;
  Initialize();
}

void SingleCpuCoreMinFrequencyDataModel::Initialize() {
  sensorPath = QString("/sys/devices/system/cpu/cpu%0/cpufreq/scaling_min_freq")
                   .arg(_acpiId);
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreMinFrequencyDataModel::ComputeValue);
  restartTimer();
}

void SingleCpuCoreMinFrequencyDataModel::ComputeValue() {
  QFile file(sensorPath);
  if (file.exists() && file.open(QFile::ReadOnly)) {
    setCurrentValue(file.readAll(),true);
    return;
  }

  setCurrentValue("0",true);
}
