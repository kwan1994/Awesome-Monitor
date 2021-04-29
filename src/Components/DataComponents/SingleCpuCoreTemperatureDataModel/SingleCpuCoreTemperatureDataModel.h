//
// Created by kwan on 14.07.19.
//

#ifndef AWESOMEMONITOR_SINGLECPUCORETEMPERATUREDATAMODEL_H
#define AWESOMEMONITOR_SINGLECPUCORETEMPERATUREDATAMODEL_H

#include "../DataModelBase.h"

class SingleCpuCoreTemperatureDataModel : public DataModelBase {
  QString cpuAcpiId;

  Q_PROPERTY(QString acpiId READ acpiId WRITE setAcpiId
                 NOTIFY acpiIdChanged FINAL);

public:
  QString acpiId(){
    return cpuAcpiId;
  }

  void setAcpiId(QString id){
     cpuAcpiId = id;
     initialize();
  }

  signals:
  void acpiIdChanged();
 public:
  void initializeIntel();
  void initializeAmd();
  void initialize();
  SingleCpuCoreTemperatureDataModel(int timerInterval, QString acpiId,
                                    QObject* parent = nullptr);

  SingleCpuCoreTemperatureDataModel(QObject* parent = nullptr);

  void computeCpuTemp();
  QString sensorPath = "";
};

#endif  // AWESOMEMONITOR_SINGLECPUCORETEMPERATUREDATAMODEL_H
