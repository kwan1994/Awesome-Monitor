//
// Created by kwan on 04.08.19.
//

#ifndef AWESOMEMONITOR_CPUMAXFREQUENCYDATAMODEL_H
#define AWESOMEMONITOR_CPUMAXFREQUENCYDATAMODEL_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.h"
#include <QtCore/QObject>
#include <QtQml/QQmlPropertyMap>
class CpuMaxFrequencyDataModel : public DataModelBase {
  QMap<QString, SingleCpuCoreMaxFrequencyDataModel*> coreFrequencies;
  QVariantMap  value =  QVariantMap();

 public:
  CpuMaxFrequencyDataModel(QObject* parent = nullptr);
  void Initilize();
  void ComputeCurrentValue(QString);
};

#endif  // AWESOMEMONITOR_CPUMAXFREQUENCYDATAMODEL_H
