//
// Created by kwan on 1/26/19.
//

#ifndef AWESOMEMONITOR_CPUTEMPERATUREDATAMODEL_H
#define AWESOMEMONITOR_CPUTEMPERATUREDATAMODEL_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreTemperatureDataModel/SingleCpuCoreTemperatureDataModel.h"
#include <QtCore/QDirIterator>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtQml/QQmlPropertyMap>

class CpuTemperatureDataModel : public DataModelBase {
  Q_OBJECT
  QVariantMap  value =  QVariantMap();
  void initializeForAmd();
  void initializeForIntel();
  QMap<QString, SingleCpuCoreTemperatureDataModel*> individualSensors;
  void construnctCurrentValue(QString);

 public:
  CpuTemperatureDataModel(QObject* parent = nullptr);
};

#endif  // AWESOMEMONITOR_CPUTEMPERATUREDATAMODEL_H
