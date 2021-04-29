//
// Created by kwan on 11/22/18.
//

#ifndef AWESOMEMONITOR_MODEL_H
#define AWESOMEMONITOR_MODEL_H

#include <QQmlListProperty>
#include <QWidget>
#include <QtCore>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Node : public QObject, public QEnableSharedFromThis<Node> {
  Q_OBJECT
  QQmlContext *context;

 public:
  Node(QQmlContext *parentContext);

  QQmlComponent *me;
  QSharedPointer<QObject> data;
  QSharedPointer<Node> parent;
  QVector<QSharedPointer<Node>> childern;
  QQueue<QSharedPointer<Node>> components = QQueue<QSharedPointer<Node>>();
  void initialize();
};

class Model : public QObject {
  Q_OBJECT
  QVector<QSharedPointer<Node>> _roots = QVector<QSharedPointer<Node>>();

 public:
  QWindow mainWindow = QWindow();
  Model();
  inline QVector<QSharedPointer<Node>> &roots() { return _roots; };
};

#endif  // AWESOMEMONITOR_MODEL_H
