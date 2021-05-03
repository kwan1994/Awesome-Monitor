//
// Created by kwan on 17.08.19.
//

#include "ComponentListModel.h"

#include <QDebug>
#include <QDirIterator>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
ComponentListModel::ComponentListModel(QObject *parent)
    : QAbstractListModel(parent) {
  watcherConfig = new QFileSystemWatcher(
      {QStandardPaths::locate(QStandardPaths::StandardLocation::ConfigLocation,
                              "AwesomeMonitor",
                              QStandardPaths::LocateOption::LocateFile)},
      this),

  watcherFolders = new QFileSystemWatcher(
      {basicComponentsFolderPath, dataModelsFolderPath}, this);

  QObject::connect(watcherFolders, &QFileSystemWatcher::directoryChanged,
                   [this]() -> void { initialize(); });

  QObject::connect(
      watcherConfig, &QFileSystemWatcher::fileChanged, [this]() -> void {
        basicComponentsFolderPath = Utils::getBasicComponentFolder();
        dataModelsFolderPath = Utils::getDataModelsFolderSetting();
        initialize();
      });
  initialize();
}

int ComponentListModel::rowCount(const QModelIndex &parent) const {
  return components.length() + +dataModels.length() +
         customComponents.length() + customDataModels.length();
}

QVariant ComponentListModel::data(const QModelIndex &index, int role) const {
  ComponentNode *node = nullptr;
  if (role != Qt::DisplayRole) return QVariant();

  if (index.row() < components.length()) node = components[index.row()];

  // qDebug() << QVariant::fromValue(node) << endl;
  return node != nullptr ? QVariant::fromValue(node) : QVariant();
}

void ComponentListModel::initialize() {
  beginResetModel();

  components.clear();
  customComponents.clear();

  dataModels.clear();
  customDataModels.clear();

  initializeSection(QDirIterator(QDir(dataModelsFolderPath, "*.jsonSchema",
                                      QDir::SortFlag::Name),
                                 QDirIterator::IteratorFlag::Subdirectories),
                    components, components, dataModelNames, "Data Models");

  initializeSection(
      QDirIterator(
          QDir(basicComponentsFolderPath, "*.jsonSchema", QDir::SortFlag::Name),
          QDirIterator::IteratorFlag::Subdirectories),
      components, components, basicComponentNames, "Base Components");

  qSort(components.begin(), components.end(),
        [](ComponentNode *a, ComponentNode *b) {
          return a->section() < b->section();
        });
  endResetModel();
}

void ComponentListModel::initializeSection(
    QDirIterator it, QVector<ComponentNode *> &collection,
    QVector<ComponentNode *> &customCollection,
    const QStringList &namesCollection, const QString &sectionName) const {
  while (it.hasNext()) {
    auto path = it.next();
    auto info = QFileInfo(path);
    auto qmlPath = info.path() + QDir::separator() + info.baseName() + ".qml";
    if (QFile::exists(qmlPath)) {
      auto name = info.baseName();
      auto isCustom = namesCollection.contains(name);
      auto section = isCustom ? sectionName : "Custom " + sectionName;
      auto possiblePath =
          info.path() + QDir::separator() + info.baseName() + ".svg";
      auto iconPath = QFile::exists(possiblePath) ? possiblePath : "";
      auto description = "";
      auto node = new ComponentNode(path, qmlPath, section, iconPath,
                                    description, name, (QObject *)this);
      isCustom ? customCollection.push_back(node) : collection.push_back(node);
    }
  }
}

ComponentNode::ComponentNode(QObject *parent) : QObject(parent) {}

ComponentNode::ComponentNode(QString schemaPath, QString qmlPath,
                             QString section, QString iconPath,
                             QString description, QString name, QObject *parent)
    : QObject(parent),
      _schemaPath(schemaPath),
      _qmlPath(qmlPath),
      _section(section),
      _iconPath(iconPath),
      _description(description),
      _name(name) {}

QString ComponentNode::schemaPath() { return _schemaPath; };
QString ComponentNode::qmlPath() { return _qmlPath; };
QString ComponentNode::section() { return _section; };
QString ComponentNode::iconPath() { return _iconPath; };
QString ComponentNode::description() { return _description; };
QString ComponentNode::name() { return _name; };
