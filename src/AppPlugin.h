//
// Created by kwan on 21.07.19.
//

#ifndef AWESOMEMONITOR_APPPLUGIN_H
#define AWESOMEMONITOR_APPPLUGIN_H

#include <QtQml/qqml.h>

#include <QtQml/QQmlExtensionPlugin>

#include "Editor/Models/ComponentListModel/ComponentListModel.h"
#include "Editor/Models/PluginTreeModel/PluginTreeModel.h"
#include "Plugin.h"

class AppPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "something")

 public:
  AppPlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent) {}
  void registerTypes(const char *uri) {
    QScopedPointer<Plugin> example(new Plugin);
    QQmlEngine engine;
    qmlRegisterType<ComponentListModel>(uri, 1, 0, "ComponentListModel");
    qmlRegisterType<ComponentNode>(uri, 1, 0, "ComponentNode");
    qmlRegisterType<PluginTreeModel>(uri, 1, 0, "PluginTreeModel");
    qmlRegisterType<TreeItem>(uri, 1, 0, "TreeItem");

    qmlRegisterSingletonType<Plugin>(uri, 1, 0, "Plugin",
                                     &example_qjsvalue_singletontype_provider);
  };
  static QObject *example_qjsvalue_singletontype_provider(
      QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine)
    auto plugin = new Plugin();
    QQmlEngine::setObjectOwnership(plugin, QQmlEngine::CppOwnership);
    return plugin;
  }
};

#endif  // AWESOMEMONITOR_APPPLUGIN_H
