//
// Created by kwan on 05.08.19.
//

#include "DownloadSpeedDataModel.h"

#include <QDirIterator>
#include <QtCore/QDir>
DownloadSpeedDataModel::DownloadSpeedDataModel(QObject *parent)
    : DataModelBase(parent, "defautlSpeedTransformer") {
  QObject::connect(_timer, &QTimer::timeout, this,
                   &DownloadSpeedDataModel::computeValue);

  restartTimer();
}
QString DownloadSpeedDataModel::interfaceName() { return _interfaceName; }
void DownloadSpeedDataModel::setInterfaceName(QString interfaceName) {
  _interfaceName = interfaceName;
  initialize();
  emit interfaceNameChanged();
}
void DownloadSpeedDataModel::initialize() {
  interfaceTraficPaths.clear();
  if (_interfaceName == "") {
    QDirIterator it(QDir("/sys/class/net"), QDirIterator::Subdirectories);
    while (it.hasNext()) {
      auto path = it.next();
      auto statPath = path + "/statistics/tx_bytes";
      if (QFile::exists(statPath)) {
        interfaceTraficPaths << statPath;
      }
    }
    return;
  }
  auto posiblePath =
      QString("/sys/class/net/%0/statistics/tx_bytes").arg(_interfaceName);
  if (QFile::exists(posiblePath)) {
    interfaceTraficPaths << posiblePath;
  }
}
void DownloadSpeedDataModel::computeValue() {
  long long current = 0;
  for (auto path : interfaceTraficPaths) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
      current += QString(file.readAll()).toLongLong();
    }
  }
  auto transfered = current - previous;
  previous = current;
  setCurrentValue(transfered, true);
}
