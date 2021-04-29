//
// Created by kwan on 06.08.19.
//

#ifndef AWESOMEMONITOR_BATTERYSTATUSDATAMODEL_H
#define AWESOMEMONITOR_BATTERYSTATUSDATAMODEL_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include "../DataModelBase.h"
class BatteryStatusDataModel : public DataModelBase {
  Q_OBJECT
  Q_PROPERTY(QString batteryName READ batteryName WRITE setBatteryName NOTIFY
                 batteryNameChanged FINAL);

  QString _batteryName = "BAT0";
  QStringList files = QStringList();
  void initialize();
  void computeValue();

 public:
  enum State { Charging, Discharging, Full, Trickling };
  QString batteryName();
  void setBatteryName(QString name);
  BatteryStatusDataModel(QObject* parent = nullptr);

 signals:
  void batteryNameChanged();

 private:
  QMap<QString, State> values =
      QMap<QString, State>{{"Charging", State::Charging},
                           {"Full", State::Full},
                           {"Discharging", State::Discharging},
                           {"Trickling", State::Trickling}};
};

#endif  // AWESOMEMONITOR_BATTERYSTATUSDATAMODEL_H
