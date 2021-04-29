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
  if (_interfaceName == "") {
    QDirIterator it(QDir("/sys/class/net"), QDirIterator::Subdirectories);
    while (it.hasNext()) {
      auto path = it.next();
      auto statPath = path + "/statistics/rx_bytes";
      if (QFile::exists(statPath)) {
        interfaceTraficPaths << statPath;
      }
    }
    return;
  }
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
      current += QString(file.readAll()).toInt();
    }
  }
  auto transfered = current - previous;
  previous = current;
  qDebug() << transfered;
  setCurrentValue(transfered, true);
}
