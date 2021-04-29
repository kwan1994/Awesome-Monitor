//
// Created by kwan on 13.08.19.
//

#include "UtilsWrapper.h"
CpuArch UtilsWrapper::getCpuArch() { return Amd; }
QStringList UtilsWrapper::getApicIdList() { return Utils::getApicIdList(); }
QJSValue UtilsWrapper::getTransformer(QString name) {
  // return Utils::getTransformer(name);
  return QJSValue();
}
