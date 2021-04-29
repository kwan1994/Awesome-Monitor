//
// Created by kwan on 04.08.19.
//

#ifndef COMPONENTS_SINGLECPUCOREUTILISATIONDATAMODEL_H
#define COMPONENTS_SINGLECPUCOREUTILISATIONDATAMODEL_H

#include "../DataModelBase.h"
class SingleCpuCoreUtilisationDataModel : public DataModelBase {
  Q_OBJECT
  QString id = "";
  double idle = 0;
  double total = 0;
  // void computeValue();
  void initialize();
  Q_PROPERTY(
      QString acpiId READ acpiId WRITE setAcpiId NOTIFY acpiIdChanged FINAL);

 public:
  QString acpiId() { return id; }

  void setAcpiId(QString ids) {
    id = ids;

  }

 signals:
  void acpiIdChanged();

 public:
  void computeValue();
  explicit SingleCpuCoreUtilisationDataModel(QObject* parent = nullptr);
  SingleCpuCoreUtilisationDataModel(QString acpiId, QObject* parent = nullptr);
};

#endif  // COMPONENTS_SINGLECPUCOREUTILISATIONDATAMODEL_H
