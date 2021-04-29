//
// Created by kwan on 21.07.19.
//

#ifndef AWESOMEMONITOR_SINGLECPUCOREMAXTEMPERATUREDATAMODEL_H
#define AWESOMEMONITOR_SINGLECPUCOREMAXTEMPERATUREDATAMODEL_H

#include <QtCore/QString>
#include "../DataModelBase.h"
class SingleCpuCoreMaxTemperatureDataModel : public DataModelBase {
  QString cpuAcpiId;

  void computeCpuTemp();
  QString sensorPath = "";

  void initializeIntel();
  void initializeAmd();


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
  void initialize();
  SingleCpuCoreMaxTemperatureDataModel(int timerInterval, QString acpiId,
                                       QObject* parent = nullptr);

  SingleCpuCoreMaxTemperatureDataModel(QObject* parent = nullptr);
};

#endif  // AWESOMEMONITOR_SINGLECPUCOREMAXTEMPERATUREDATAMODEL_H
