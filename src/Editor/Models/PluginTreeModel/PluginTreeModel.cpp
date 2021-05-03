//
// Created by kwan on 18.11.20.
//

#include "PluginTreeModel.h"

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonParseError>
#include <QtCore/QStack>

#include "../../../ComponentFramework/JsonToTreeParser/JsonToTreeParser.h"

using namespace std;

TreeItem::TreeItem(const QVariant &formData, const QVariant &schemaData,
                   const QString name, TreeItem *parent, QObject *parentO)
    : m_formData(formData.toMap()),
      m_schemaForm(schemaData),
      m_name(name),
      parentItem(parent),
      childItems(),
      QObject(parentO) {}

TreeItem::~TreeItem() {
  // qDeleteAll(childItems);
}

bool DataModelTreeItem::isDataModel() { return true; }

bool TreeItem::isDataModel() { return false; }

TreeItem *TreeItem::child(int number) {
  if (number < 0 || number >= childItems.size()) return nullptr;
  return childItems.at(number);
}

int TreeItem::childCount() const { return childItems.count(); }

int TreeItem::childNumber() const {
  if (parentItem)
    return parentItem->childItems.indexOf(const_cast<TreeItem *>(this));
  return 0;
}

QVariant TreeItem::data() { return QVariant::fromValue(this); }

bool TreeItem::insertChild(int position, TreeItem *item) {
  childItems.insert(position, item);
  return true;
}

TreeItem *TreeItem::parent() { return parentItem; }

bool TreeItem::removeChildren(int position, int count) {
  if (position < 0 || position + count > childItems.size()) return false;

  for (int row = 0; row < count; ++row) delete childItems.takeAt(position);

  return true;
}

QVariant TreeItem::getJsomRepresentation() {
  auto map = m_formData;
  QVariantList childernRep;
  QVariantMap dataModels;
  for (auto child : childItems) {
    auto dataModelNode = dynamic_cast<DataModelTreeItem *>(child);
    if (dataModelNode != nullptr) {
      qDebug()
          << QJsonDocument(QVariant(child->m_formData).toJsonObject()).toJson();
      dataModels.insert(dataModelNode->m_key, dataModelNode->m_formData);
    } else {
      childernRep.append(child->getJsomRepresentation());
    }
  }
  map.insert("childern", childernRep);
  if (!dataModels.isEmpty()) map.insert("dataModels", dataModels);
  return map;
}

QModelIndex PluginTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  qDebug() << parent << endl;

  auto parentItem = getItem(parent);
  if (!parentItem) return QModelIndex();
  auto childItem = parentItem->child(row);
  qDebug() << createIndex(row, column, childItem) << endl;
  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
}
QModelIndex PluginTreeModel::parent(const QModelIndex &child) const {
  if (!child.isValid()) return QModelIndex();

  auto *childItem = getItem(child);
  auto *parentItem = childItem ? childItem->parent() : nullptr;

  if (parentItem == rootItem || !parentItem) return QModelIndex();

  return createIndex(parentItem->childNumber(), 0, parentItem);
}
TreeItem *PluginTreeModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    return item;
  }
  return rootItem;
}
int PluginTreeModel::rowCount(const QModelIndex &parent) const {
  const auto parentItem = getItem(parent);

  qDebug() << (parentItem ? parentItem->childCount() : 0);
  return parentItem ? parentItem->childCount() : 0;
}
int PluginTreeModel::columnCount(const QModelIndex &parent) const { return 1; }

QVariant PluginTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  qDebug() << role << endl;
  if (role == Qt::DisplayRole) {
    TreeItem *item = getItem(index);
    auto dataModelNode = dynamic_cast<DataModelTreeItem *>(item);
    return QVariant(dataModelNode != nullptr
                        ? dataModelNode->m_key + " " + dataModelNode->m_name
                        : item->m_name);
  }
  if (role == Qt::UserRole) {
    TreeItem *item = getItem(index);
    return QVariant::fromValue(item);
  }
  return QVariant();
}
void PluginTreeModel::initialize() {
  beginResetModel();
  QFile modelFile(Utils::getModelFileSetting());
  if (!modelFile.exists() || !modelFile.open(QFile::OpenModeFlag::ReadOnly)) {
    qDebug() << modelFile.error() << " " << modelFile.errorString() << endl;
    return;
  }
  QJsonParseError e;
  auto jsonModel = QJsonDocument::fromJson(modelFile.readAll(), &e);
  if (e.error != QJsonParseError::NoError) {
    qDebug() << e.errorString();
    return;
  }

  if (!jsonModel.isObject()) {
    qDebug() << "Model file should start with object" << endl;
    endResetModel();
    return;
  }
  auto jsonObject = jsonModel.object();
  rootItem =
      new TreeItem(QVariant(QVariant::Type::Invalid),
                   QVariant(QVariant::Type::Invalid), "SDSDS", nullptr, this);
  QQmlEngine::setObjectOwnership(rootItem, QQmlEngine::CppOwnership);
  QStack<QPair<TreeItem *, QJsonValue>> stack;

  stack.push(QPair(rootItem, jsonObject["windows"].toArray()));
  qDebug() << "init";
  while (!stack.isEmpty()) {
    auto item = stack.pop();
    auto jsonArray = item.second;
    qDebug() << item.second.toString();
    addChildern(jsonArray, stack, item, e, jsonModel);
    addDataModels(item.second, item.first);
  }

  endResetModel();
}
void PluginTreeModel::addChildern(const QJsonValue &jsonObject,
                                  QStack<QPair<TreeItem *, QJsonValue>> &stack,
                                  const QPair<TreeItem *, QJsonValue> &item,
                                  QJsonParseError &e,
                                  QJsonDocument &jsonModel) {
  auto treeItem = item.first;
  qDebug() << jsonObject.type();
  if (!jsonObject.isArray()) return;
  for (auto jsonNode : jsonObject.toArray()) {
    if (!jsonNode.isObject()) continue;
    auto formData = jsonNode.toObject();
    if (!formData.contains("_") && !formData["_"].isString()) {
      continue;
    }
    auto compType = formData["_"].toString();

    if (!filePathsToQmlComponents.contains(compType)) {
      qDebug() << compType;
      continue;
    }

    formData.remove("childern");
    formData.remove("dataModels");
    QFile file(filePathsToQmlComponents[compType]);
    if (!file.open(QFile::OpenModeFlag::ReadOnly)) {
      qDebug() << file.errorString();
      continue;
    }

    auto schema = file.readAll();
    if (schema.isEmpty()) {
      qDebug() << "empty echama" << compType;

      continue;
    }

    jsonModel = QJsonDocument::fromJson(schema, &e);
    if (e.error != QJsonParseError::NoError) {
      qDebug() << "cant read json" << compType;

      continue;
    }

    if (jsonModel.isEmpty() || !jsonModel.isObject() ||
        jsonModel.object().count() <= 0) {
      qDebug() << "cant read object epty" << compType;

      continue;
    }

    auto jsonSchema = jsonModel.object().toVariantMap();
    auto child = new TreeItem(formData.toVariantMap(), jsonSchema, compType,
                              treeItem, treeItem);
    // addDataModels(jsonNode.toObject(), child);
    QQmlEngine::setObjectOwnership(child, QQmlEngine::CppOwnership);
    treeItem->childItems.append(child);
    if (hasChildern(jsonNode)) {
      stack.push(QPair(child, jsonNode.toObject()["childern"].toArray()));
    }
    if (hasDataModels(jsonNode)) {
      qDebug() << jsonNode.toObject()["dataModels"].toObject().keys();
      stack.push(QPair(child, jsonNode.toObject()["dataModels"].toObject()));
    }
  }
}

void PluginTreeModel::addDataModels(QJsonValue value, TreeItem *pItem) {
  if (!value.isObject()) {
    return;
  }
  auto dataModelObject = value.toObject();
  for (auto key : dataModelObject.keys()) {
    auto item = dataModelObject[key];
    if (!item.isObject()) return;
    auto itemObject = item.toObject();

    auto compType = itemObject["_"].toString();
    if (!filePathsToQmlDataModels.contains(compType)) continue;

    QFile file(filePathsToQmlDataModels[compType]);
    if (!file.open(QFile::OpenModeFlag::ReadOnly)) {
      qDebug() << "cant read" << compType;
      continue;
    }

    auto schema = file.readAll();
    if (schema.isEmpty()) {
      qDebug() << "schemaEmpty" << compType;
      continue;
    }

    QJsonParseError e;
    auto jsonModel = QJsonDocument::fromJson(schema, &e);
    if (e.error != QJsonParseError::NoError) {
      qDebug() << "cant read json" << compType;

      continue;
    }

    if (jsonModel.isEmpty() || !jsonModel.isObject() ||
        jsonModel.object().count() <= 0) {
      qDebug() << "empty object" << compType;

      continue;
    }
    auto jsonSchema = jsonModel.object().toVariantMap();
    auto child = new DataModelTreeItem(itemObject.toVariantMap(), jsonSchema,
                                       compType, pItem);
    QQmlEngine::setObjectOwnership(child, QQmlEngine::CppOwnership);

    child->m_key = key;
    pItem->childItems.append(child);
  }
}

bool PluginTreeModel::hasDataModels(const QJsonValue &jsonNode) const {
  return (jsonNode.toObject().contains("dataModels") &&
          jsonNode.toObject()["dataModels"].isObject());
}

bool PluginTreeModel::hasChildern(const QJsonValue &jsonNode) const {
  return (jsonNode.toObject().contains("childern") &&
          jsonNode.toObject()["childern"].isArray());
}

PluginTreeModel::PluginTreeModel() {
  filePathsToQmlComponents = JsonToTreeParser::createFileMap(
      Utils::getBasicComponentFolder(), "*.jsonSchema");
  qDebug(QStringList(filePathsToQmlComponents.values())
             .join(" ")
             .toStdString()
             .c_str());
  qDebug() << "datamOdels"
           << QStringList(filePathsToQmlDataModels.values()).join(" ");
  filePathsToQmlDataModels = JsonToTreeParser::createFileMap(

      Utils::getDataModelsFolderSetting(), "*.jsonSchema");
  qDebug(QStringList(filePathsToQmlDataModels.values())
             .join(" ")
             .toStdString()
             .c_str());
  initialize();
}
bool PluginTreeModel::insertRow(int row, const QModelIndex &parent,
                                QString schemaPath) {
  auto pItem = getItem(parent);
  if (!pItem) return false;
  QFile file(schemaPath);
  if (!file.open(QFile::ReadOnly)) {
    qDebug() << "ReadOnly";
    return false;
  }
  auto name = (QFileInfo(file)).baseName();
  auto schemaFormData = file.readAll();
  if (schemaFormData.isEmpty()) return false;
  QJsonParseError e;
  auto jsonSchemaDocument = QJsonDocument::fromJson(schemaFormData, &e);
  if (e.error != QJsonParseError::NoError) {
    qDebug() << "error";
    ;
    return false;
  }
  if (!jsonSchemaDocument.isObject()) {
    qDebug() << "isObject";
    return false;
  }
  auto jsonSchemaObject = jsonSchemaDocument.object();
  if (jsonSchemaObject.isEmpty()) {
    qDebug() << "isEmptyObject";
    return false;
  }
  beginInsertRows(parent, row, row);
  auto child =
      new TreeItem(QJsonObject().toVariantMap(),
                   jsonSchemaObject.toVariantMap(), name, pItem, pItem);
  QQmlEngine::setObjectOwnership(child, QQmlEngine::CppOwnership);

  pItem->insertChild(row, child);
  endInsertRows();
  return true;
}

bool PluginTreeModel::insertRow(int row, const QModelIndex &parent,
                                QString schemaPath, QString key) {
  auto pItem = getItem(parent);
  if (!pItem) return false;
  QFile file(schemaPath);
  if (!file.open(QFile::ReadOnly)) return false;
  auto name = (QFileInfo(file)).baseName();
  auto schemaFormData = file.readAll();
  if (schemaFormData.isEmpty()) return false;
  QJsonParseError e;
  auto jsonSchemaDocument = QJsonDocument::fromJson(schemaFormData, &e);
  if (e.error != QJsonParseError::NoError) return false;
  if (!jsonSchemaDocument.isObject()) return false;
  auto jsonSchemaObject = jsonSchemaDocument.object();
  if (jsonSchemaObject.isEmpty()) return false;
  beginInsertRows(parent, row, row);
  auto child = new DataModelTreeItem(QJsonObject().toVariantMap(),
                                     jsonSchemaObject.toVariantMap(), name,
                                     pItem, pItem);
  QQmlEngine::setObjectOwnership(child, QQmlEngine::CppOwnership);
  child->m_key = key;
  pItem->insertChild(row, child);
  endInsertRows();
  return true;
}

bool PluginTreeModel::removeRows(int row, int count,
                                 const QModelIndex &parent) {
  auto parentItem = getItem(parent);
  if (!parentItem || count != 1) return false;
  beginRemoveRows(parent, row, row);
  parentItem->removeChildren(row, count);
  endRemoveRows();
  return true;
}

bool PluginTreeModel::moveRows(const QModelIndex &sourceParent, int sourceRow,
                               int count, const QModelIndex &destinationParent,
                               int destinationChild) {
  return QAbstractItemModel::moveRows(sourceParent, sourceRow, count,
                                      destinationParent, destinationChild);
}

QJsonObject PluginTreeModel::getJsonModelRepresentation() {
  auto result = rootItem->getJsomRepresentation().toMap();
  result.insert("windows", result["childern"]);
  result.remove("childern");
  return QJsonObject::fromVariantMap(result);
}
