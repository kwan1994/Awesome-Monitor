//
// Created by kwan on 18.11.20.
//

#ifndef AWESOMEMONITOR_PLUGINTREEMODEL_H
#define AWESOMEMONITOR_PLUGINTREEMODEL_H

#include <QJsonValue>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QJsonParseError>
#include <boost/filesystem/path.hpp>
class TreeItem;

using namespace std;
class PluginTreeModel : public QAbstractItemModel {
  Q_OBJECT

 private:
  TreeItem *rootItem;
  void initialize();
  void addChildern(const QJsonValue &jsonObject,
                   QStack<QPair<TreeItem *, QJsonValue>> &stackChildern,
                   const QPair<TreeItem *, QJsonValue> &item,
                   QJsonParseError &e, QJsonDocument &jsonModel);
  QMap<QString, QString> filePathsToQmlComponents;
  QMap<QString, QString> filePathsToQmlDataModels;
  bool hasChildern(const QJsonValue &jsonNode) const;
  bool hasDataModels(const QJsonValue &jsonNode) const;
  void addDataModels(QJsonValue object, TreeItem *treeItem);

 public:
  PluginTreeModel();
  QModelIndex index(int row, int column,
                    const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  TreeItem *getItem(const QModelIndex &index) const;

  Q_INVOKABLE bool removeRows(int row, int count,
                              const QModelIndex &parent) override;
  bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                const QModelIndex &destinationParent,
                int destinationChild) override;
  Q_INVOKABLE bool insertRow(int row, const QModelIndex &parent,
                             QString schemaPath);
  Q_INVOKABLE QJsonObject getJsonModelRepresentation();
  Q_INVOKABLE bool insertRow(int row, const QModelIndex &parent,
                             QString schemaPath, QString key);
};

class TreeItem : public QObject {
  Q_OBJECT

  Q_PROPERTY(QVariantMap formData MEMBER m_formData NOTIFY formDataChanged)
  Q_PROPERTY(QVariant schemaForm MEMBER m_schemaForm NOTIFY schemaFormChanged)
  Q_PROPERTY(bool selected MEMBER m_selected NOTIFY selectedChanged)
  Q_PROPERTY(QString name MEMBER m_name FINAL)

 public:
  TreeItem() : QObject(), childItems() {}
  TreeItem(const QVariant &formData, const QVariant &schemaData,
           const QString name, TreeItem *parent = nullptr,QObject* parentO = nullptr);
  ~TreeItem();

  TreeItem *child(int number);
  Q_INVOKABLE virtual bool isDataModel();
  int childCount() const;
  bool insertChild(int position, TreeItem *item);

  QVariant getJsomRepresentation();
  TreeItem *parent();
  bool removeChildren(int position, int count);
  int childNumber() const;
  QVariant data();

  QVector<TreeItem *> childItems;
  QVariantMap m_formData;
  QVariant m_schemaForm;
  bool m_selected = false;
  QString m_name;

 signals:
  void selectedChanged();
  void formDataChanged(QVariant formData);
  void schemaFormChanged(QVariant schemaForm);

 private:
  QFileSystemWatcher schemaWatcher;
  TreeItem *parentItem;
};

class DataModelTreeItem : public TreeItem {
  Q_OBJECT
  Q_PROPERTY(QString key MEMBER m_key NOTIFY keyChanged);

 public:
  using TreeItem::TreeItem;
  bool isDataModel() override;
  QString m_key;
 signals:
  void keyChanged();
};

#endif  // AWESOMEMONITOR_PLUGINTREEMODEL_H
