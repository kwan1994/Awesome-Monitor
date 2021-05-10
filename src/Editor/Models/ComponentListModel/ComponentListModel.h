//
// Created by kwan on 17.08.19.
//

#ifndef AWESOMEMONITOR_COMPONENTLISTMODEL_H
#define AWESOMEMONITOR_COMPONENTLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QDirIterator>
#include <QtCore/QFileSystemWatcher>

#include "../../../Components/ComponentUtils/utils.h"
class ComponentNode;

class ComponentListModel : public QAbstractListModel {
  Q_OBJECT
  QVector<ComponentNode *> components = QVector<ComponentNode *>();
  QVector<ComponentNode *> customComponents = QVector<ComponentNode *>();
  QVector<ComponentNode *> dataModels = QVector<ComponentNode *>();
  QVector<ComponentNode *> customDataModels = QVector<ComponentNode *>();

  QStringList dataModelNames = {"BatteryCapacityDataModel",
                                "BatteryStatusDataModel",
                                "CommandLineDataModel",
                                "CpuCurrentFrequencyDataModel",
                                "CpuMaxFrequencyDataModel",
                                "CpuMaxTemperatureDataModel",
                                "CpuMinFrequencyDataModel",
                                "CpuTemperatureDataModel",
                                "CpuUtilisationDataModel",
                                "DownloadSpeedDataModel",
                                "SingleCpuCoreCurrentFrequencyDataModel",
                                "SingleCpuCoreMaxFrequencyDataModel",
                                "SingleCpuCoreMaxTemperatureDataModel",
                                "SingleCpuCoreMinFrequencyDataModel",
                                "SingleCpuCoreTemperatureDataModel",
                                "SingleCpuCoreUtilisationDataModel",
                                "UploadSpeedDataModel",
                                "AvailableSwapSpaceDataModel",
                                "AvailableMemoryDataModel",
                                "FreeSwapSpaceDataModel",
                                "FreeMemoryDataModel"};

  QStringList basicComponentNames = {
      "Text",  "ProgresBar",  "Row",           "Window",   "Column",
      "Image", "BorderImage", "AnimatedImage", "Rectangle"};

  QString basicComponentsFolderPath = Utils::getBasicComponentFolder();
  QString dataModelsFolderPath = Utils::getDataModelsFolderSetting();

  QFileSystemWatcher *watcherConfig;
  QFileSystemWatcher *watcherFolders;

  void initialize();

 public:
  ComponentListModel(QObject *parent = nullptr);
  Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
  Q_INVOKABLE QVariant data(const QModelIndex &index,
                            int role = Qt::DisplayRole) const;
  void initializeSection(QDirIterator it, QVector<ComponentNode *> &collection,
                         QVector<ComponentNode *> &customCollection,
                         const QStringList &namesCollection,
                         const QString &sectionName) const;
};

class ComponentNode : public QObject {
  Q_OBJECT
  QString _schemaPath;
  QString _qmlPath;
  QString _section;
  QString _iconPath;
  QString _description;
  QString _name;
  bool m_visible = true;

  Q_PROPERTY(QString schemaPath READ schemaPath NOTIFY schemaPathChanged);

  Q_PROPERTY(QString qmlPath READ qmlPath NOTIFY qmlPathChanged);

  Q_PROPERTY(QString section READ section FINAL);

  Q_PROPERTY(QString iconPath READ iconPath FINAL);

  Q_PROPERTY(QString description READ description FINAL);

  Q_PROPERTY(QString name READ name FINAL);

  Q_PROPERTY(bool visible MEMBER m_visible NOTIFY visibleChanged)

 public:
  ComponentNode(QString schemaPath, QString qmlPath, QString section,
                QString iconPath, const QString description, QString name,
                QObject *parent = nullptr);
  ComponentNode(QObject *parent = nullptr);

  QString schemaPath();
  QString qmlPath();
  QString section();
  QString iconPath();
  QString description();
  QString name();
  Q_INVOKABLE bool isDataModel() {
    return _section == "Custom Data Models" || _section == "Data Models";
  }
 signals:
  void qmlPathChanged();
  void schemaPathChanged();
  void visibleChanged();
};

#endif  // AWESOMEMONITOR_COMPONENTLISTMODEL_H
