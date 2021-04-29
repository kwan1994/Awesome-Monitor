//
// Created by kwan on 29.07.19.
//

#ifndef AWESOMEMONITOR_CPUCURRENTFREQUENCY_H
#define AWESOMEMONITOR_CPUCURRENTFREQUENCY_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.h"
#include <QtCore/QObject>
#include <QtQml/QQmlPropertyMap>
class CpuCurrentFrequencyDataModel : public DataModelBase {
  QMap<QString, SingleCpuCoreCurrentFrequencyDataModel*> coreFrequencies;
  QVariantMap  value =  QVariantMap();

 public:
  CpuCurrentFrequencyDataModel(QObject* parent = nullptr);
  void Initilize();
  void ComputeCurrentValue(QString);
};

#endif  // AWESOMEMONITOR_CPUCURRENTFREQUENCY_H
