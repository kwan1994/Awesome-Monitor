//
// Created by kwan on 10.05.21.
//

#ifndef AWESOMEMONITOR_FREEMEMORYDATAMODEL_H
#define AWESOMEMONITOR_FREEMEMORYDATAMODEL_H

#include <QRegularExpression>

#include "../DataModelBase.h"
class FreeMemoryDataModel : public DataModelBase {
  Q_OBJECT

  QRegularExpression regularExpression =
      QRegularExpression("MemFree:\\s+\\K\\d+");

  void Initialize();
  void ComputeValue();

 public:
  FreeMemoryDataModel(QObject* parent = nullptr) : DataModelBase(parent) {
    Initialize();
  };
};

#endif  // AWESOMEMONITOR_FREEMEMORYDATAMODEL_H
