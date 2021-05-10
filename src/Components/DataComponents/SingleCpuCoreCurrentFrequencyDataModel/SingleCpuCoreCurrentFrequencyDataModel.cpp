//
// Created by kwan on 29.07.19.
//

#include "SingleCpuCoreCurrentFrequencyDataModel.h"

#include <QtCore/QFile>
#include <iostream>

#include "../../ComponentUtils/utils.h"
using namespace std;

SingleCpuCoreCurrentFrequencyDataModel::SingleCpuCoreCurrentFrequencyDataModel(
    QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = Utils::getApicIdList().first();
  Initialize();
}

SingleCpuCoreCurrentFrequencyDataModel::SingleCpuCoreCurrentFrequencyDataModel(
    QString acpiId, QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = acpiId;
  Initialize();
}



void SingleCpuCoreCurrentFrequencyDataModel::Initialize() {
  sensorPath = QString("/sys/devices/system/cpu/cpu%0/cpufreq/scaling_cur_freq")
                   .arg(_acpiId);
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreCurrentFrequencyDataModel::ComputeValue);
  restartTimer();
}

void SingleCpuCoreCurrentFrequencyDataModel::ComputeValue() {
  QFile file(sensorPath);
  if (file.exists() && file.open(QFile::ReadOnly)) {
    setCurrentValue(QString(file.readAll()), true);
    return;
  }

  setCurrentValue("0", true);
}
