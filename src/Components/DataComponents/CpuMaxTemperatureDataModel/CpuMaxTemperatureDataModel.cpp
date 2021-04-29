//
// Created by kwan on 21.07.19.
//

#include "CpuMaxTemperatureDataModel.h"
#include "../../ComponentUtils/utils.h"
void CpuMaxTemperatureDataModel::initializeForAmd() {
  auto apicIdList = Utils::getApicIdList();

  individualSensors[apicIdList.first()] =
      new SingleCpuCoreMaxTemperatureDataModel(timerInterval(),
                                               apicIdList.first(), this);
  QObject::connect(individualSensors[apicIdList.first()],
                   &SingleCpuCoreMaxTemperatureDataModel::currentValueChanged,
                   [this,apicIdList]()->void{construnctCurrentValue(apicIdList.first());});
}

void CpuMaxTemperatureDataModel::initializeForIntel() {}
void CpuMaxTemperatureDataModel::construnctCurrentValue(QString acpiId) {
  value.insert(acpiId,individualSensors[acpiId]->currentValue());
  setCurrentValue(QVariant::fromValue(value));
}

CpuMaxTemperatureDataModel::CpuMaxTemperatureDataModel(QObject *parent)
    : DataModelBase(parent) {
  Utils::getCpuArch() == Amd ? initializeForAmd() : initializeForIntel();
}
