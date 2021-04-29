//
// Created by kwan on 05.08.19.
//

#ifndef COMPONENTS_UPLOADSPEEDDATAMODEL_H
#define COMPONENTS_UPLOADSPEEDDATAMODEL_H

#include <QtCore/QArgument>
#include <QtCore/QStringList>
#include "../DataModelBase.h"
class UploadSpeedDataModel : public DataModelBase {
  Q_OBJECT
  Q_PROPERTY(QString interfaceName READ interfaceName WRITE setInterfaceName
                 NOTIFY interfaceNameChanged FINAL);
  QStringList interfaceTraficPaths = QStringList();
  long long previous = 0;
  QString _interfaceName = "";
  void initialize();
  void computeValue();

 public:
  UploadSpeedDataModel(QObject *parent = nullptr);
  QString interfaceName();
  void setInterfaceName(QString interfaceName);

 signals:
  void interfaceNameChanged();
};

#endif  // COMPONENTS_UPLOADSPEEDDATAMODEL_H
