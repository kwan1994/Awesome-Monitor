//
// Created by kwan on 10.05.21.
//
#include "AvailableSwapSpaceDataModel.h"

#include <QtCore/QFile>

#include "QDebug"

void AvailableSwapSpaceDataModel::Initialize() {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &AvailableSwapSpaceDataModel::ComputeValue);
  restartTimer();
}

void AvailableSwapSpaceDataModel::ComputeValue() {
  QFile file("/proc/meminfo");
  if (file.exists() && file.open(QFile::ReadOnly)) {
    auto match = regularExpression.match(QString(file.readAll()));
    if (match.hasMatch()) {
      setCurrentValue(match.captured().toLongLong(), true);
    }
    return;
  }

  setCurrentValue(0, true);
}
