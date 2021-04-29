//
// Created by kwan on 09.07.19.
//

#ifndef AWESOMEMONITOR_DATAMODELBASE_H
#define AWESOMEMONITOR_DATAMODELBASE_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtQml/QJSValue>
class DataModelBase : public QObject {
  Q_OBJECT
  Q_PROPERTY(QJSValue transformFunc READ transformFunc WRITE setTransformFunc
                 NOTIFY transformFuncChanged FINAL);

  Q_PROPERTY(QVariant currentValue READ currentValue WRITE setCurrentValue
                 NOTIFY currentValueChanged FINAL);

  Q_PROPERTY(int timerInterval READ timerInterval WRITE setTimerInterval NOTIFY
                 timerIntervalChanged FINAL);

 protected:
  QTimer *_timer;
  int _timerInterval = 1000;
  QJSValue _transformFunc = QJSValue();
  QVariant _currentValue;
  void setCurrentValue(QVariant currentValue, bool transform);

 public:
  void restartTimer();
  DataModelBase(QObject *parent);
  DataModelBase(QObject *parent, QString);
  QJSValue transformFunc();
  void setTransformFunc(QJSValue transformFunc);
  const QVariant currentValue();
  void setCurrentValue(QVariant currentValue);
  int timerInterval();
  void setTimerInterval(int timerInterval);
 signals:
  void currentValueChanged(QVariant currentValue);
  void transformFuncChanged();
  void timerIntervalChanged();

 private:
  QString _transformerName = "";
};

#endif  // AWESOMEMONITOR_DATAMODELBASE_H
