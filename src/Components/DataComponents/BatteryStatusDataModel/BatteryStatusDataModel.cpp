//
// Created by kwan on 06.08.19.
//

#include "BatteryStatusDataModel.h"

#include <QtCore/QDirIterator>
#include <iostream>

using namespace std;

void BatteryStatusDataModel::initialize() {
  files.clear();
  auto path = QString("/sys/class/power_supply/%0/status").arg(_batteryName);
  if (QFile::exists(path)) {
    cout << path.toStdString() << endl;
    files << path;
  }
}

BatteryStatusDataModel::BatteryStatusDataModel(QObject *parent)
    : DataModelBase(parent) {
  initialize();
  QObject::connect(_timer, &QTimer::timeout, this,
                   &BatteryStatusDataModel::computeValue);
  restartTimer();
}

void BatteryStatusDataModel::computeValue() {
  if(!files.isEmpty()){
  QFile file(files.first());
  if (!file.open(QFile::ReadOnly)) {
      setCurrentValue("Full", true);
      return;
  }
  setCurrentValue(QString(file.readAll()).trimmed(), true);
  }
}

QString BatteryStatusDataModel::batteryName() { return _batteryName; }

void BatteryStatusDataModel::setBatteryName(QString name) {
  _batteryName = name;
  initialize();
  emit batteryNameChanged();
}
