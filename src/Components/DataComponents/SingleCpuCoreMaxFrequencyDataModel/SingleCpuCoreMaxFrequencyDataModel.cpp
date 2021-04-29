//
// Created by kwan on 04.08.19.
//

#include "SingleCpuCoreMaxFrequencyDataModel.h"
#include <QtCore/QFile>
#include <iostream>
#include "../../ComponentUtils/utils.h"
using namespace std;
SingleCpuCoreMaxFrequencyDataModel::SingleCpuCoreMaxFrequencyDataModel(
    QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = Utils::getApicIdList().first();
  Initialize();
}
SingleCpuCoreMaxFrequencyDataModel::SingleCpuCoreMaxFrequencyDataModel(
    QString acpiId, QObject *parent)
    : DataModelBase(parent, "defaultCpuFrequencyTransformer") {
  _acpiId = acpiId;
  Initialize();
}
void SingleCpuCoreMaxFrequencyDataModel::Initialize() {
  sensorPath = QString("/sys/devices/system/cpu/cpu%0/cpufreq/scaling_max_freq")
                   .arg(_acpiId);
  QObject::connect(_timer, &QTimer::timeout, this,
                   &SingleCpuCoreMaxFrequencyDataModel::ComputeValue);
  restartTimer();
};
void SingleCpuCoreMaxFrequencyDataModel::ComputeValue() {
  QFile file(sensorPath);
  if (file.exists() && file.open(QFile::ReadOnly)) {
    setCurrentValue(QString(file.readAll()),true);
    return;
  }

  setCurrentValue("0",true);
};
