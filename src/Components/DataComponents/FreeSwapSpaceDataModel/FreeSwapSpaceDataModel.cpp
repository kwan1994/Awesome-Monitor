//
// Created by kwan on 10.05.21.
//
#include "FreeSwapSpaceDataModel.h"

#include <QtCore/QFile>

#include "QDebug"

void FreeSwapSpaceDataModel::Initialize() {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &FreeSwapSpaceDataModel::ComputeValue);
  restartTimer();
}

void FreeSwapSpaceDataModel::ComputeValue() {
  QFile file("/proc/meminfo");
  if (file.exists() && file.open(QFile::ReadOnly)) {
    auto match = regularExpression.match(QString(file.readAll()));
    qDebug() << "neco" << match;
    if (match.hasMatch()) {
      setCurrentValue(match.captured().toLongLong(), true);
    }
    return;
  }

  setCurrentValue(0, true);
}
