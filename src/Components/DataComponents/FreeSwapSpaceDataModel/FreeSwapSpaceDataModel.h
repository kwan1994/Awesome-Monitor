//
// Created by kwan on 10.05.21.
//

#ifndef AWESOMEMONITOR_FREESWAPSPACEDATAMODEL_H
#define AWESOMEMONITOR_FREESWAPSPACEDATAMODEL_H

#include <QtCore/QRegularExpression>

#include "../DataModelBase.h"

class FreeSwapSpaceDataModel : public DataModelBase {
  Q_OBJECT

  QRegularExpression regularExpression =
      QRegularExpression("SwapFree:\\s+\\K\\d+");

  void Initialize();
  void ComputeValue();

 public:
  FreeSwapSpaceDataModel(QObject* parent = nullptr)
      : DataModelBase(parent) {
    Initialize();
  };
};

#endif  // AWESOMEMONITOR_FREESWAPSPACEDATAMODEL_H
