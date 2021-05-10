//
// Created by kwan on 06.08.19.
//

#include "BatteryCapacityDataModel.h"

#include <QtCore/QDirIterator>
#include <iostream>

using namespace std;

void BatteryCapacityDataModel::initialize() {
  files.clear();
  if (_batteryName == "") {
    QDirIterator it(QDir("/sys/class/power_supply", {"BAT*"}));
    while (it.hasNext()) {
      auto path = it.next();
      cout << path.toStdString() << endl;
      if (QFile::exists(path + "/capacity")) {
        files << path + "/capacity";
      }
    }
    return;
  }

  auto path = QString("/sys/class/power_supply/%0/capacity").arg(_batteryName);
  if (QFile::exists(path)) {
    cout << path.toStdString() << endl;
    files << path;
  }
}

BatteryCapacityDataModel::BatteryCapacityDataModel(QObject *parent)
    : DataModelBase(parent) {
  initialize();
  QObject::connect(_timer, &QTimer::timeout, this,
                   &BatteryCapacityDataModel::computeValue);
  restartTimer();
}

void BatteryCapacityDataModel::computeValue() {
  float totalPercent = 0;
  for (auto path : files) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) continue;
    totalPercent += QString(file.readAll()).toInt();
  }
  setCurrentValue(totalPercent / files.length());
}

QString BatteryCapacityDataModel::batteryName() { return _batteryName; }

void BatteryCapacityDataModel::setBatteryName(QString name) {
  _batteryName = name;
  initialize();
  emit batteryNameChanged();
}
