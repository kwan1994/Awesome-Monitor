//
// Created by kwan on 21.07.19.
//

#include "Plugin.h"

#include "ComponentFramework/JsonToTreeParser/JsonToTreeParser.h"
#include "Components/ComponentUtils/utils.h"

Plugin::Plugin(QObject *parent) : QObject(parent) {
  imageProvider = new ImageProvider();
  connect(this, &Plugin::intializing,
          [this] { imageProvider->pluginInitializing(); });
  connect(this, &Plugin::initialized, [this](QVector<QQuickWindow *> windows) {
    imageProvider->pluginInitialize(windows, shouldHideWindows);
  });
}

bool Plugin::saveToFile(QJsonObject json) {
  QFile file(QFileInfo(Utils::getModelFileSetting()).absoluteFilePath());
  if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate |
                 QIODevice::Text)) {
    qDebug() << file.error();
    return false;
  }
  QJsonDocument doc(json);
  qDebug() << doc.toJson();
  return file.write(doc.toJson());
}

void Plugin::initializePlugin() {
  emit intializing();
  Utils::qjsEngine = new QQmlEngine;

  qDebug() << Utils::qjsEngine;
  auto modelFile = Utils::getModelFileSetting();
  auto dataModelsFolder = Utils::getDataModelsFolderSetting();
  auto baseComponentsFolder = Utils::getBasicComponentFolder();

  JsonToTreeParser s(dataModelsFolder, baseComponentsFolder,
                     JsonValueConverter());
  this->model = nullptr;
  this->model = QSharedPointer<Model>(s.createModelFromFile(modelFile));

  this->model->setParent(this);
  auto windows = QVector<QQuickWindow *>();
  for (auto windowNode : this->model->roots()) {
    windows.append(
        qobject_cast<QQuickWindow *>(windowNode.data()->data.data()));
  }
  if (QQmlEngine::contextForObject(this) &&
      QQmlEngine::contextForObject(this)->engine() && addProvider) {
    addProvider = false;
    QQmlEngine::contextForObject(this)->engine()->addImageProvider(
        "livePreview", imageProvider);
  };
  emit initialized(windows);
}

void Plugin::initializePluginFromString(QString modelString) {
  emit intializing();
  Utils::qjsEngine = new QQmlEngine;

  qDebug() << Utils::qjsEngine;
  auto modelFile = Utils::getModelFileSetting();
  auto dataModelsFolder = Utils::getDataModelsFolderSetting();
  auto baseComponentsFolder = Utils::getBasicComponentFolder();

  JsonToTreeParser s(dataModelsFolder, baseComponentsFolder,
                     JsonValueConverter());
  this->model = nullptr;
  this->model = QSharedPointer<Model>(s.createModel(modelString));

  this->model->setParent(this);
  auto windows = QVector<QQuickWindow *>();
  for (auto windowNode : this->model->roots()) {
    windows.append(
        qobject_cast<QQuickWindow *>(windowNode.data()->data.data()));
  }
  if (QQmlEngine::contextForObject(this) &&
      QQmlEngine::contextForObject(this)->engine() && addProvider) {
    addProvider = false;
    QQmlEngine::contextForObject(this)->engine()->addImageProvider(
        "livePreview", imageProvider);
  };

  emit initialized(windows);
}

int Plugin::numberOfWindows() { return this->model->roots().count(); }

Plugin::~Plugin() { this->model = nullptr; }

void Plugin::resetPlugin() { initializePlugin(); }

void Plugin::deletePlugin() { this->model = nullptr; }

void Plugin::setHideWindows() { shouldHideWindows = true; }

bool Plugin::tryCreateDefaultModelFile(QString path) {
  QFile file(path);
  if (file.exists()) {
    return true;
  };

  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return file.write("{\"windows\":[]}") == 14;
  }

  return false;
}