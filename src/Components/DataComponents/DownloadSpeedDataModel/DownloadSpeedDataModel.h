//
// Created by kwan on 05.08.19.
//

#ifndef COMPONENTS_DOWNLOADSPEEDDATAMODEL_H
#define COMPONENTS_DOWNLOADSPEEDDATAMODEL_H

#include "../DataModelBase.h"
class DownloadSpeedDataModel: public DataModelBase {
  Q_OBJECT
  Q_PROPERTY(QString interfaceName READ interfaceName WRITE setInterfaceName
                 NOTIFY interfaceNameChanged FINAL);
  QStringList interfaceTraficPaths = QStringList();
  long long previous = 0;
  QString _interfaceName = "";
  void initialize();
  void computeValue();
public:
    DownloadSpeedDataModel(QObject *parent = nullptr);
  QString interfaceName();
  void setInterfaceName(QString interfaceName);

  signals:
    void interfaceNameChanged();

};



#endif //COMPONENTS_DOWNLOADSPEEDDATAMODEL_H
