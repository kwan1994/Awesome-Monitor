//
// Created by kwan on 29.07.19.
//

#ifndef AWESOMEMONITOR_SINGLECPUCORECURRENTFREQUENCYDATAMODEL_H
#define AWESOMEMONITOR_SINGLECPUCORECURRENTFREQUENCYDATAMODEL_H

#include <QtCore/qstring.h>

#include "../DataModelBase.h"

class SingleCpuCoreCurrentFrequencyDataModel : public DataModelBase {
  Q_OBJECT
  QString _acpiId;
  QString sensorPath;

  Q_PROPERTY(QString acpiId READ acpiId WRITE setAcpiId NOTIFY acpiIdChanged FINAL);

 public:
  QString acpiId() { return _acpiId; }

  void setAcpiId(QString id) {
    _acpiId = id;
    Initialize();
  }

 signals:
  void acpiIdChanged();

 public:
  SingleCpuCoreCurrentFrequencyDataModel(QObject* parent = nullptr);
  SingleCpuCoreCurrentFrequencyDataModel(QString acpiId,
                                         QObject* parent = nullptr);
  void Initialize();
  void ComputeValue();
};

#endif  // AWESOMEMONITOR_SINGLECPUCORECURRENTFREQUENCYDATAMODEL_H
