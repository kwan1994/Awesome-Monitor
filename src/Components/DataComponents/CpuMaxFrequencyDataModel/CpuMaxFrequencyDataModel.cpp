//
// Created by kwan on 04.08.19.
//

#include "CpuMaxFrequencyDataModel.h"
#include <QDebug>
#include <iostream>
#include "../../ComponentUtils/utils.h"
using namespace std;

CpuMaxFrequencyDataModel::CpuMaxFrequencyDataModel(QObject *parent)
    : DataModelBase(parent) {
  Initilize();
}
void CpuMaxFrequencyDataModel::Initilize() {
  auto acpiIds = Utils::getApicIdList();

  for (auto acpiId : acpiIds) {
    coreFrequencies[acpiId] =
        new SingleCpuCoreMaxFrequencyDataModel(acpiId, this);
    QObject::connect(coreFrequencies[acpiId],
                     &SingleCpuCoreMaxFrequencyDataModel::currentValueChanged,
                     this, [this,acpiId]()->void{ComputeCurrentValue(acpiId);});
  }
}
void CpuMaxFrequencyDataModel::ComputeCurrentValue(QString acpiId) {

  value.insert(acpiId, coreFrequencies[acpiId]->currentValue());

  setCurrentValue(QVariant::fromValue(value));
}
