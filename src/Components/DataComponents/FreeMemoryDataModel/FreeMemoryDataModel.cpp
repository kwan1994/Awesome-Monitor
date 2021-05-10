//
// Created by kwan on 10.05.21.
//

#include "FreeMemoryDataModel.h"
#include <QtCore/QFile>

#include "QDebug"

void FreeMemoryDataModel::Initialize() {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &FreeMemoryDataModel::ComputeValue);
  restartTimer();
}

void FreeMemoryDataModel::ComputeValue() {
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