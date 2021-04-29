//
// Created by kwan on 04.08.19.
//

#ifndef COMPONENTS_CPUUTILISATIONDATAMODEL_H
#define COMPONENTS_CPUUTILISATIONDATAMODEL_H

#include "../DataModelBase.h"
#include "../SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.h"
#include <QtQml/QQmlPropertyMap>
class CpuUtilisationDataModel : public DataModelBase {
  QMap<QString, SingleCpuCoreUtilisationDataModel *> sensors =
      QMap<QString, SingleCpuCoreUtilisationDataModel *>();
  QVariantMap  value =  QVariantMap();
  void initialize();
  void computeValue(QString);

 public:
  CpuUtilisationDataModel(QObject *parent = nullptr);
};

#endif  // COMPONENTS_CPUUTILISATIONDATAMODEL_H
