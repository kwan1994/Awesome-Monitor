//
// Created by kwan on 10.05.21.
//

#ifndef AWESOMEMONITOR_AVAILABLESWAPSPACEDATAMODEL_H
#define AWESOMEMONITOR_AVAILABLESWAPSPACEDATAMODEL_H

#include <QtCore/QRegularExpression>

#include "../DataModelBase.h"

class AvailableSwapSpaceDataModel : public DataModelBase {
  Q_OBJECT

  QRegularExpression regularExpression =
      QRegularExpression("SwapTotal:\\s+\\K\\d+");

  void Initialize();
  void ComputeValue();

 public:
  AvailableSwapSpaceDataModel(QObject* parent = nullptr)
      : DataModelBase(parent) {
    Initialize();
  };
};

#endif  // AWESOMEMONITOR_FREESWAPSPACEDATAMODEL_H
