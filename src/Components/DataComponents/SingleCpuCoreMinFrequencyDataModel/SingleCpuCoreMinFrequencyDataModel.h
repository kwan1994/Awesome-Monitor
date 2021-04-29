//
// Created by kwan on 29.07.19.
//

#ifndef AWESOMEMONITOR_SINGLECPUCOREMINFREQUENCYDATAMODEL_H
#define AWESOMEMONITOR_SINGLECPUCOREMINFREQUENCYDATAMODEL_H

#include <QtCore/qstring.h>
#include "../DataModelBase.h"
class SingleCpuCoreMinFrequencyDataModel : public DataModelBase {
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
  SingleCpuCoreMinFrequencyDataModel(QObject* parent = nullptr);
  SingleCpuCoreMinFrequencyDataModel(QString acpiId, QObject* parent = nullptr);
  void Initialize();
  void ComputeValue();
};

#endif  // AWESOMEMONITOR_SINGLECPUCORECURRENTFREQUENCYDATAMODEL_H
