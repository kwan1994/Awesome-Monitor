//
// Created by kwan on 29.07.19.
//

#include "CpuMinFrequencyDataModel.h"
#include <QDebug>
#include <iostream>
#include "../../ComponentUtils/utils.h"
using namespace std;
CpuMinFrequencyDataModel::CpuMinFrequencyDataModel(QObject *parent)
    : DataModelBase(parent), coreFrequencies() {
  Initilize();
}
void CpuMinFrequencyDataModel::Initilize() {
  auto acpiIds = Utils::getApicIdList();
  for (auto acpiId : acpiIds) {
    coreFrequencies[acpiId] =
        new SingleCpuCoreMinFrequencyDataModel(acpiId, this);
    QObject::connect(
        coreFrequencies[acpiId],
        &SingleCpuCoreMinFrequencyDataModel::currentValueChanged,[this,acpiId]()->void {ComputeCurrentValue(acpiId);});
  }
}
void CpuMinFrequencyDataModel::ComputeCurrentValue(QString acpiId) {
  value.insert(acpiId,coreFrequencies[acpiId]->currentValue());
  setCurrentValue(QVariant::fromValue(value));
}
