//
// Created by kwan on 04.08.19.
//

#include "CpuUtilisationDataModel.h"
#include <QVariantMap>
#include "../../ComponentUtils/utils.h"
#include <QDebug>
void CpuUtilisationDataModel::initialize() {
  auto acpiIds = Utils::getApicIdList();
  for (auto acpiId : acpiIds) {
    sensors[acpiId] = new SingleCpuCoreUtilisationDataModel(acpiId,this);
    QObject::connect(sensors[acpiId],
                     &SingleCpuCoreUtilisationDataModel::currentValueChanged,
                     [this,acpiId]()-> void{computeValue(acpiId);});
  }
}

void CpuUtilisationDataModel::computeValue(QString acpiId) {
  value.insert(acpiId,sensors[acpiId]->currentValue());
   setCurrentValue(QVariant::fromValue(value));

}

CpuUtilisationDataModel::CpuUtilisationDataModel(QObject* parent)
    : DataModelBase(parent) {
  initialize();
}
