//
// Created by kwan on 29.07.19.
//

#ifndef AWESOMEMONITOR_CPUMINFREQUENCY_H
#define AWESOMEMONITOR_CPUMINFREQUENCY_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.h"
#include <QtCore/QObject>
#include <QtQml/QQmlPropertyMap>
class CpuMinFrequencyDataModel : public DataModelBase {
  QMap<QString,SingleCpuCoreMinFrequencyDataModel *> coreFrequencies;
  QVariantMap  value =  QVariantMap();

public:
    CpuMinFrequencyDataModel(QObject* parent = nullptr);
  void Initilize();
  void ComputeCurrentValue(QString);
};

#endif  // AWESOMEMONITOR_CPUCURRENTFREQUENCY_H
