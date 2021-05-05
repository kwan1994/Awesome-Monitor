//
// Created by kwan on 11/22/18.
//

#include "JsonToTreeParser.h"

#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlExpression>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickWindow>
#include <QSettings>
#include <QtCore>
#include <nlohmann/json-schema.hpp>
#include <sstream>
#include <string>
#include <variant>

// TODO a.obrtel: create separate context for each component into which we
// inject corresponding data models for component
// make sure qmlContext are parented so components can access global context
// with model

JsonToTreeParser::JsonToTreeParser(QString directoryOfDataModelDefinitions,
                                   QString directoryOfBaseComponentsDefinitions,
                                   JsonValueConverter converter)
    : filePathsToQmlDataModels(), filePathsToQmlComponents() {
  filePathsToQmlComponents =
      createFileMap(directoryOfBaseComponentsDefinitions);
  filePathsToQmlDataModels = createFileMap(directoryOfDataModelDefinitions);
  engine = Utils::qjsEngine;
  qDebug() << QStringList(filePathsToQmlComponents.keys()).join(" ");
  qDebug() << QStringList(filePathsToQmlDataModels.keys()).join(" ");
  this->converter = converter;
}
Model *JsonToTreeParser::createModelFromFile(QString pathToModel) {
  engine->installExtensions(QQmlEngine::AllExtensions);
  QFile file(pathToModel);

  if (!file.exists()) throw;

  if (!file.open(QFile::OpenModeFlag::ReadOnly)) throw;
  return createModel(file.readAll());
}

Model *JsonToTreeParser::createModel(QString modelString) {
  Model *model = new Model;

  nlohmann::json_schema::json_validator validator;  // create validator
  nlohmann::json json;
  try {
    auto schema = generateSchema(Utils::getBasicComponentFolder(),
                                 Utils::getDataModelsFolderSetting());
    json = nlohmann::json::parse(modelString.toStdString());
  } catch (exception &e) {
    qDebug() << "Error parsing model json" << e.what();
    return createErrorModel(
        (QString("Error parsing model json").append(e.what())));
  }
  try {
    validator.set_root_schema(schema);  // insert root-schema
  } catch (const std::exception &e) {
    qDebug() << "Validation of schema failed, here is why: " << e.what()
             << "\n";
    return createErrorModel(
        QString("Validations of schema failed, here is why: ")
            .append(e.what()));  // TODO: adderorModel
  }

  try {
    validator.validate(json);  // insert root-schema
  } catch (const std::exception &e) {
    qDebug() << "Validation of schema failed, here is why: " << e.what()
             << "\n";
    return createErrorModel(
        QString("Validation of schema failed, here is why: ")
            .append(e.what()));  // TODO: adderorModel;
  }

  try {
    for (auto &child : json["windows"].items()) {
      auto window = createWindow(child.value(), &model->mainWindow);
      QQuickWindow *s = qobject_cast<QQuickWindow *>(window->data.get());
      qobject_cast<QObject *>(s)->setParent(model);
      // s->setParent(&model->mainWindow);
      model->roots().push_back(window);
    }
  } catch (const std::exception &e) {
    qDebug() << "Model cannot be parsed to tree";
    return createErrorModel(
        QString("Model cannot be parsed to tree").append(e.what()));
  }

  for (auto roots : model->roots()) {
    roots->initialize();
  }

  for (auto expr : bindings) {
    if (expr != nullptr) expr->evaluate();
    if (expr->hasError()) {
      qDebug() << expr->error().toString();
    }
  }

  return model;
}

nlohmann::json JsonToTreeParser::generateSchema(
    QString baseComponentsSchemasPath, QString dataModelsSchemasPath) {
  auto schemas = nlohmann::json::parse(schema);
  auto &array = schemas["/definitions/Component/allOf/1/anyOf"_json_pointer];
  QDir directory(baseComponentsSchemasPath, "*.jsonSchema",
                 QDir::SortFlag::NoSort, QDir::Filter::Files);
  QDirIterator it(directory, QDirIterator::Subdirectories);

  QString st;
  while (it.hasNext()) {
    try {
      st = it.next();
      QFile file(st);
      if (file.open(QFile::ReadOnly)) {
        array.push_back(
            nlohmann::json::parse(QString(file.readAll()).toStdString()));
      }
    } catch (const std::exception &e) {
      throw invalid_argument(QString(e.what())
                                 .append("in file ")
                                 .append(st)
                                 .toStdString()
                                 .c_str());
    }
  }

  auto &arrays = schemas["/definitions/DataModel/allOf/0/anyOf"_json_pointer];
  directory = QDir(dataModelsSchemasPath, "*.jsonSchema",
                   QDir::SortFlag::NoSort, QDir::Filter::Files);
  QDirIterator itDataModels(directory, QDirIterator::Subdirectories);

  while (itDataModels.hasNext()) {
    auto st = itDataModels.next();
    QFile file(st);
    if (file.open(QFile::ReadOnly)) {
      arrays.push_back(
          nlohmann::json::parse(QString(file.readAll()).toStdString()));
    }
  }

  cout << schemas.dump(4) << endl;
  return schemas;
}

QSharedPointer<Node> JsonToTreeParser::createNode(nlohmann::json &object,
                                                  QQmlContext *parentContext) {
  auto nodeContext = new QQmlContext(parentContext);
  QSharedPointer<Node> node(new Node(nodeContext));
  node->data = initializeComponet(object, node);

  if (!object.contains("childern")) return node;

  for (auto &item : object["childern"].items()) {
    auto ptr =
        QSharedPointer<Node>(this->createNode(item.value(), nodeContext));
    ptr->parent = node;
    ptr->data->setParent(node->data.get());
    qobject_cast<QQuickItem *>(ptr->data)->setParentItem(
        qobject_cast<QQuickItem *>(node->data.get()));
    node->childern.push_back(ptr);
  }
  return node;
}

QSharedPointer<QObject> JsonToTreeParser::initializeComponet(
    nlohmann::json &object, QSharedPointer<Node> parent) {
  auto objectType =
      this->filePathsToQmlComponents[object["_"].get<std::string>().c_str()];
  auto path = QString(objectType);
  QQmlComponent *component = new QQmlComponent(engine, path);
  QString errorString = "";
  if (!component->isReady()) {
    errorString.append(QString("Component of type ")
                           .append(QString(object["_"].get<string>().c_str())));
    qWarning() << "Component of type" << objectType;
    for (auto error : component->errors()) {
      errorString.append(error.toString());
      qWarning() << error.toString();
    }
    throw invalid_argument(errorString.toStdString().c_str());
  }

  QObject *widget = component->beginCreate(engine->rootContext());

  // TODO a.obrtel Investigate if necessary to destroy app
  if (widget == nullptr) {
    throw invalid_argument("Couldnt create component, aborting intiated/n");
  }

  engine->setObjectOwnership(widget, QQmlEngine::ObjectOwnership::CppOwnership);

  converter.setComponent(widget);
  if (object.contains("dataModels")) {
    addDataModelsToComponent(widget, object["dataModels"], parent);
  }

  // TODO a.obrtel: Skip properties defined on Component model. Find a way to
  // make it easily extensible
  for (auto &entry : object.items()) {
    if (ignoredPropertyNames.contains(entry.key().c_str())) continue;
    QQmlProperty qmlProperty(widget, entry.key().c_str(), this->engine);

    auto value = converter.convert(entry.value());
    if (value.canConvert<BindingDto *>()) {
      auto expr = new QQmlExpression(
          context, widget,
          QString("%1 = Qt.binding(function () {%2})")
              .arg(entry.key().c_str(), value.value<BindingDto *>()->binding));
      bindings.append(expr);
      continue;
    }

    if (value.canConvert<ComponentDto *>()) {
      auto component =
          new QQmlComponent(engine, value.value<ComponentDto *>()->url, widget);
      value = QVariant::fromValue(component);
    }

    if (value.canConvert<ItemDto *>()) {
      auto item = createNode(entry.value(), context);
      parent->components << item;
      item->data->setParent(widget);
      value = QVariant::fromValue(item->data.get());
    }
    if (!qmlProperty.write(value))
      qWarning() << "Property with name " << entry.key().c_str()
                 << "wasnt writen into object of type" << objectType;
    qDebug() << value << " " << qmlProperty.read() << qmlProperty.name();
  }

  parent->me = component;
  return QSharedPointer<QObject>(widget);
}

boost::filesystem::path expand(boost::filesystem::path in) {
  if (in.size() < 1) return in;

  const char *home = getenv("HOME");
  if (home == NULL) {
    cerr << "error: HOME variable not set." << endl;
    throw std::invalid_argument("error: HOME environment variable not set.");
  }

  string s = in.c_str();
  if (s[0] == '~') {
    s = string(home) + s.substr(1, s.size() - 1);
    return boost::filesystem::path(s);
  } else {
    return in;
  }
}

QMap<QString, QString> JsonToTreeParser::createFileMap(QString path,
                                                       QString extension) {
  qDebug() << path << extension << "createFileMap";
  QMap<QString, QString> map;
  QDirIterator dirIterator(QDir(path, extension, QDir::SortFlag::Name),
                           QDirIterator::IteratorFlag::Subdirectories);

  while (dirIterator.hasNext()) {
    auto entry = dirIterator.next();

    map[QFileInfo(entry).baseName()] = QFileInfo(entry).absoluteFilePath();
  }

  return map;
}

QSharedPointer<Node> JsonToTreeParser::createWindow(nlohmann::json &object,
                                                    QWindow *parent) {
  auto windowContext = new QQmlContext(this->context);
  auto node = QSharedPointer<Node>(new Node(windowContext));
  auto windowPtr = initializeComponet(object, node);
  QQuickWindow *window = qobject_cast<QQuickWindow *>(windowPtr.get());
  if (!window) {
    window = new QQuickWindow();
    qobject_cast<QQuickItem *>(windowPtr.data())
        ->setParentItem(window->contentItem());
    windowPtr->setParent(window);
    window->setFlag(Qt::Tool);
    window->setFlag(Qt::FramelessWindowHint);
    window->setFlag(Qt::WindowStaysOnBottomHint);
    window->setVisible(true);
    node->data = QSharedPointer<QObject>(window);
    return node;
  }
  window->setFlag(Qt::Tool);
  window->setFlag(Qt::FramelessWindowHint);
  window->setFlag(Qt::WindowStaysOnBottomHint);
  window->setMouseGrabEnabled(false);
  window->contentItem()->setEnabled(false);
  node->data = windowPtr;

  for (auto &entry : object["childern"].items()) {
    auto child = this->createNode(entry.value(), windowContext);
    node->childern.push_back(child);
    qobject_cast<QQuickItem *>(child->data)
        ->setParentItem(window->contentItem());

    child->data->setParent(window);
  }

  window->setVisible(true);

  return node;
}

// TODO a.obrtel this method not yet tested beacuse im not able to create
// plugin extension for QML
void JsonToTreeParser::addDataModelsToComponent(QObject *pObject,
                                                nlohmann::json &object,
                                                QSharedPointer<Node> parent) {
  QQmlProperty prop(pObject, "dataModels", engine);
  auto con = new QQmlContext(this->engine->rootContext());
  QVariantMap dataModels = QVariantMap();
  for (auto &entry : object.items()) {
    auto dataModelObject = entry.value();
    cout << object.dump(4) << endl;
    auto objectType = this->filePathsToQmlDataModels
                          [dataModelObject["_"].get<std::string>().c_str()];
    auto path = QString(objectType);
    QSharedPointer<QQmlComponent> component =
        QSharedPointer<QQmlComponent>(new QQmlComponent(engine, path));

    if (!component->isReady()) {
      QStringList err;
      qWarning() << "Component of type" << objectType;
      err << "Component of type" << objectType << "\n";
      for (auto error : component->errors()) {
        qWarning() << error.toString();
        err << error.toString() << "\n";
      }
      throw std::invalid_argument(err.join("").toStdString().c_str());
    }

    QObject *widget = component->create(con);

    engine->setObjectOwnership(widget,
                               QQmlEngine::ObjectOwnership::CppOwnership);

    if (widget == nullptr)
      throw invalid_argument("Couldnt create dataModel reason uknown " +
                             objectType.toStdString());
    widget->setParent(pObject);
    for (auto &entrys : dataModelObject.items()) {
      if (entrys.key() == "dataModels") continue;
      QQmlProperty qmlProperty(widget, entrys.key().c_str(), this->engine);

      auto value = converter.convert(entrys.value());
      if (value.canConvert<BindingDto *>()) {
        auto expr =
            new QQmlExpression(con, widget,
                               QString("%1 = Qt.binding(function () {%2})")
                                   .arg(entrys.key().c_str(),
                                        value.value<BindingDto *>()->binding));
        bindings.append(expr);
        continue;
      }

      if (!qmlProperty.write(value))
        qWarning() << "Property with name " << entry.key().c_str()
                   << "wasnt writen into object of type" << objectType;
      qDebug() << value << " " << qmlProperty.read();
    }

    dataModels.insert(entry.key().c_str(), QVariant::fromValue(widget));
  }
  /// make it dynamic prop
  if (!prop.isValid() || !prop.write(QVariant::fromValue(dataModels))) {
    qDebug() << "prop of datamodels wasnt writen to model " << dataModels.keys()
             << prop.isValid() << prop.write(QVariant::fromValue(dataModels));
  }
}

Model *JsonToTreeParser::createErrorModel(QString error) {
  auto model = new Model;
  QQmlComponent component(engine, errorComponentpath);
  qDebug() << component.errorString();
  auto s = component.create(engine->rootContext());
  qobject_cast<QWindow *>(s)->setProperty("error", error);
  auto node = QSharedPointer<Node>(new Node(engine->rootContext()));
  node.data()->data = QSharedPointer<QObject>(s);
  model->roots().push_back(QSharedPointer<Node>(node));
  qobject_cast<QWindow *>(s)->setVisible(true);
  return model;
}
