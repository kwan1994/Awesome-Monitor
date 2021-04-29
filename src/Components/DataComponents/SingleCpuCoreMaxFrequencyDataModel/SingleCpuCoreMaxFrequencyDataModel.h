//
// Created by kwan on 04.08.19.
//

#ifndef AWESOMEMONITOR_SINGLECPUCOREMAXFREQUENCYDATAMODEL_H
#define AWESOMEMONITOR_SINGLECPUCOREMAXFREQUENCYDATAMODEL_H

#include "../DataModelBase.h"
class SingleCpuCoreMaxFrequencyDataModel : public DataModelBase {
  Q_OBJECT
  QString _acpiId;
  QString sensorPath;

  Q_PROPERTY(QString acpiId READ acpiId WRITE setAcpiId
                 NOTIFY acpiIdChanged FINAL);

 public:
  QString acpiId(){
    return _acpiId;
  }

  void setAcpiId(QString id){
    _acpiId = id;
    Initialize();
  }

 signals:
  void acpiIdChanged();


 public:
  SingleCpuCoreMaxFrequencyDataModel(QObject* parent = nullptr);
  SingleCpuCoreMaxFrequencyDataModel(QString acpiId, QObject* parent = nullptr);
  void Initialize();
  void ComputeValue();
};

#endif  // AWESOMEMONITOR_SINGLECPUCOREMAXFREQUENCYDATAMODEL_H
