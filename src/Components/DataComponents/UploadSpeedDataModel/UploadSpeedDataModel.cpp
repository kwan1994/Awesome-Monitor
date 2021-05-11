//
// Created by kwan on 05.08.19.
//

#include "UploadSpeedDataModel.h"

#include <QDirIterator>
#include <QtCore/QDir>

#include "QtDebug"
UploadSpeedDataModel::UploadSpeedDataModel(QObject *parent)
    : DataModelBase(parent, "defautlSpeedTransformer") {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &UploadSpeedDataModel::computeValue);
  restartTimer();
}
QString UploadSpeedDataModel::interfaceName() { return _interfaceName; }
void UploadSpeedDataModel::setInterfaceName(QString interfaceName) {
  _interfaceName = interfaceName;
  initialize();
  emit interfaceNameChanged();
}
void UploadSpeedDataModel::initialize() {
  interfaceTraficPaths.clear();
  auto posiblePath =
      QString("/sys/class/net/%0/statistics/rx_bytes").arg(_interfaceName);
  if (QFile::exists(posiblePath)) {
    interfaceTraficPaths << posiblePath;
  }
}
void UploadSpeedDataModel::computeValue() {
  long long current = 0;
  for (auto path : interfaceTraficPaths) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
      current += QString(file.readAll()).toLongLong();
    }
  }
  auto transfered = (current - previous);
  previous = current;
  setCurrentValue(transfered, true);
}
