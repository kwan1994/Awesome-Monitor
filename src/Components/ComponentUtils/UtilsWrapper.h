//
// Created by kwan on 13.08.19.
//

#ifndef AWESOMEMONITOR_UTILSWRAPPER_H
#define AWESOMEMONITOR_UTILSWRAPPER_H

#include <QtCore/QObject>
#include <QtQml/QJSValue>
#include "utils.h"
class UtilsWrapper : public QObject {
  Q_OBJECT
  Q_ENUM(CpuArch)
 public:
  Q_INVOKABLE CpuArch getCpuArch();
  Q_INVOKABLE QStringList getApicIdList();
  Q_INVOKABLE QJSValue getTransformer(QString name);
};

#endif  // AWESOMEMONITOR_UTILSWRAPPER_H
