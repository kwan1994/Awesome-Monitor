//
// Created by kwan on 29.07.19.
//

#include "CpuCurrentFrequencyDataModel.h"

#include <QDebug>
#include <iostream>

#include "../../ComponentUtils/utils.h"
using namespace std;

CpuCurrentFrequencyDataModel::CpuCurrentFrequencyDataModel(QObject *parent)
    : DataModelBase(parent), coreFrequencies() {
  Initilize();
}

void CpuCurrentFrequencyDataModel::Initilize() {
  auto acpiIds = Utils::getApicIdList();
  for (auto acpiId : acpiIds) {
    coreFrequencies[acpiId] =
        new SingleCpuCoreCurrentFrequencyDataModel(acpiId, this);
    QObject::connect(
        coreFrequencies[acpiId],
        &SingleCpuCoreCurrentFrequencyDataModel::currentValueChanged,
        [this, acpiId]() -> void { ComputeCurrentValue(acpiId); });
  }
}
void CpuCurrentFrequencyDataModel::ComputeCurrentValue(QString acpiId) {
  value.insert(acpiId, coreFrequencies[acpiId]->currentValue());

  setCurrentValue(QVariant::fromValue(value));
}
