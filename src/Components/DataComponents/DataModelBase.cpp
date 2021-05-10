//
// Created by kwan on 09.07.19.
//

#include "DataModelBase.h"

#include <qdebug.h>

#include <QJSEngine>
#include <QQmlContext>
#include <iostream>

#include "../ComponentUtils/utils.h"
using namespace std;
DataModelBase::DataModelBase(QObject *parent) : QObject(parent) {
  _timer = new QTimer(this);
  _timerInterval = Utils::getTimeIntervalSetting();
  _transformerName = "defaultReturnTransformer";
}

DataModelBase::DataModelBase(QObject *parent, QString transformerName)
    : QObject(parent) {
  _timer = new QTimer(this);
  _timerInterval = Utils::getTimeIntervalSetting();
  _transformerName = transformerName;
}

QJSValue DataModelBase::transformFunc() { return _transformFunc; }

void DataModelBase::setTransformFunc(QJSValue transformFunc) {
  _transformFunc = transformFunc;
}
const QVariant DataModelBase::currentValue() { return _currentValue; }

void DataModelBase::setCurrentValue(QVariant currentValue) {
  _currentValue = currentValue;
  emit currentValueChanged(_currentValue);
}
int DataModelBase::timerInterval() { return _timerInterval; }
void DataModelBase::setTimerInterval(int timerInterval) {
  _timerInterval = timerInterval;
  restartTimer();
  emit timerIntervalChanged();
}
void DataModelBase::restartTimer() { _timer->start(_timerInterval); }

void DataModelBase::setCurrentValue(QVariant currentValue, bool transform) {
  if (transform) {
    auto engine = QQmlEngine::contextForObject(this);
    if (engine && (_transformerName != "" || _transformFunc.isCallable())) {
      auto nec = engine->engine();
      if (!_transformFunc.isCallable()) {
        setTransformFunc(Utils::getTransformer(_transformerName, nec));
      }
      auto s = transformFunc().call({nec->toScriptValue(currentValue)});
      setCurrentValue(s.toVariant());
    }
    return;
  }
  setCurrentValue(currentValue);
};
