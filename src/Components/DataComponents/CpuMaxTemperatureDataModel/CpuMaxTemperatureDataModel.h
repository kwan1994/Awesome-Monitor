//
// Created by kwan on 21.07.19.
//

#ifndef AWESOMEMONITOR_CPUMAXTEMPERATUREDATAMODEL_H
#define AWESOMEMONITOR_CPUMAXTEMPERATUREDATAMODEL_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreMaxTemperatureDataModel/SingleCpuCoreMaxTemperatureDataModel.h"
#include <QtQml/QQmlPropertyMap>
class CpuMaxTemperatureDataModel : public DataModelBase {
  Q_OBJECT
  QVariantMap  value =  QVariantMap();

  void initializeForAmd();
  void initializeForIntel();
  QMap<QString, SingleCpuCoreMaxTemperatureDataModel*> individualSensors;
  void construnctCurrentValue(QString);

 public:
  CpuMaxTemperatureDataModel(QObject* parent = nullptr);
};

#endif  // AWESOMEMONITOR_CPUMAXTEMPERATUREDATAMODEL_H
