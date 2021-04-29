//
// Created by kwan on 1/26/19.
//

#include "CpuTemperatureDataModel.h"

#include <QDirIterator>
#include <QFile>
#include <QIODevice>
#include <QTimer>

#include "../../ComponentUtils/utils.h"
using namespace std;
CpuTemperatureDataModel::CpuTemperatureDataModel(QObject* parent)
    : DataModelBase(parent) {
  Utils::getCpuArch() == Intel ? initializeForIntel() : initializeForAmd();
}
void CpuTemperatureDataModel::initializeForAmd() {
  auto apicIdList = Utils::getApicIdList();

  individualSensors[apicIdList.first()] = new SingleCpuCoreTemperatureDataModel(
      timerInterval(), apicIdList.first(), this);
  QObject::connect(individualSensors[apicIdList.first()],
                   &SingleCpuCoreTemperatureDataModel::currentValueChanged,
                   [this, apicIdList]() -> void {
                     construnctCurrentValue(apicIdList.first());
                   });
}
void CpuTemperatureDataModel::initializeForIntel() {}
void CpuTemperatureDataModel::construnctCurrentValue(QString acpiId) {
  value.insert(acpiId, individualSensors[acpiId]->currentValue());
  setCurrentValue(QVariant::fromValue(value));
}
