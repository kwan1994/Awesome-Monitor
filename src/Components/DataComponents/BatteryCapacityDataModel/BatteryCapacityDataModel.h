//
// Created by kwan on 06.08.19.
//

#ifndef COMPONENTS_BATTERYCAPACITYDATAMODEL_H
#define COMPONENTS_BATTERYCAPACITYDATAMODEL_H

#include "../DataModelBase.h"
class BatteryCapacityDataModel : public DataModelBase {
  Q_OBJECT
  Q_PROPERTY(QString batteryName READ batteryName WRITE setBatteryName NOTIFY
                 batteryNameChanged FINAL);

  QString _batteryName = "";
  QStringList files = QStringList();
  void initialize();
  void computeValue();

 public:
  QString batteryName();
  void setBatteryName(QString name);
  BatteryCapacityDataModel(QObject* parent = nullptr);

 signals:
  void batteryNameChanged();
};

#endif  // COMPONENTS_BATTERYCAPACITYDATAMODEL_H
