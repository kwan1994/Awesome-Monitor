//
// Created by kwan on 10.05.21.
//

#ifndef AWESOMEMONITOR_AVAILABLEMEMORYDATAMODEL_H
#define AWESOMEMONITOR_AVAILABLEMEMORYDATAMODEL_H

#include <QtCore/QArgument>
#include <QtCore/QRegularExpression>

#include "../DataModelBase.h"
class AvailableMemoryDataModel : public DataModelBase {
  Q_OBJECT

  QRegularExpression regularExpression =
      QRegularExpression("MemTotal:\\s+\\K\\d+");

  void Initialize();
  void ComputeValue();

 public:
  AvailableMemoryDataModel(QObject* parent = nullptr) : DataModelBase(parent) {
    Initialize();
  };
};
#endif  // AWESOMEMONITOR_AVAILABLEMEMORYDATAMODEL_H
