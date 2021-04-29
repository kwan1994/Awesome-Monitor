//
// Created by kwan on 11/22/18.
//

#include "Model.h"

void Node::initialize() {
  me->completeCreate();
  for (auto comp : components) {
    comp->initialize();
  }
  for (auto child : childern) {
    child->initialize();
  }
}
Node::Node(QQmlContext *parentContext) {
  this->childern = QVector<QSharedPointer<Node>>();
  this->context = new QQmlContext(parentContext);
}

Model::Model() { _roots = QVector<QSharedPointer<Node>>(); }
