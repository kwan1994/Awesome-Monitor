//
// Created by kwan on 20.07.19.
//

#ifndef AWESOMEMONITOR_AWESOMECOMPONENTSPLUGIN_H
#define AWESOMEMONITOR_AWESOMECOMPONENTSPLUGIN_H
#include <QtQml/qqml.h>

#include <QJSEngine>
#include <QtQml/QQmlExtensionPlugin>
#include <iostream>

#include "ComponentUtils/UtilsWrapper.h"
#include "ComponentUtils/utils.h"
#include "DataComponents/AvailableMemoryDataModel/AvailableMemoryDataModel.h"
#include "DataComponents/AvailableSwapSpaceDataModel/AvailableSwapSpaceDataModel.h"
#include "DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.h"
#include "DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.h"
#include "DataComponents/CommandLineDataModel/CommandLineDataModel.h"
#include "DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.h"
#include "DataComponents/FreeMemoryDataModel/FreeMemoryDataModel.h"
#include "DataComponents/FreeSwapSpaceDataModel/FreeSwapSpaceDataModel.h"
#include "DataComponents/SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.h"
#include "DataComponents/SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.h"
#include "DataComponents/SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.h"
#include "DataComponents/SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.h"
#include "DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.h"

using namespace std;

class AwesomeComponentsPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

 public:
  AwesomeComponentsPlugin(QObject* parent = nullptr)
      : QQmlExtensionPlugin(parent) {
    Utils::qjsEngine = new QQmlEngine();
    Utils::qjsEngine->installExtensions(QJSEngine::ConsoleExtension);
  }

  void registerTypes(const char* uri) override {
    // Q_ASSERT(uri == QString("CpuTemperatureDataModel"));
    qmlRegisterType<SingleCpuCoreMinFrequencyDataModel>(
        uri, 1, 0, "SingleCpuCoreMinFrequencyDataModel");

    qmlRegisterType<SingleCpuCoreCurrentFrequencyDataModel>(
        uri, 1, 0, "SingleCpuCoreCurrentFrequencyDataModel");
    qmlRegisterType<SingleCpuCoreMaxFrequencyDataModel>(
        uri, 1, 0, "SingleCpuCoreMaxFrequencyDataModel");
    qmlRegisterType<SingleCpuCoreUtilisationDataModel>(
        uri, 1, 0, "SingleCpuCoreUtilisationDataModel");

    qmlRegisterType<BatteryStatusDataModel>(uri, 1, 0,
                                            "BatteryStatusDataModel");
    qmlRegisterType<UploadSpeedDataModel>(uri, 1, 0, "UploadSpeedDataModel");
    qmlRegisterType<DownloadSpeedDataModel>(uri, 1, 0,
                                            "DownloadSpeedDataModel");
    qmlRegisterType<BatteryCapacityDataModel>(uri, 1, 0,
                                              "BatteryCapacityDataModel");
    qmlRegisterType<UtilsWrapper>(uri, 1, 0, "Utils");
    qmlRegisterType<CommandLineDataModel>(uri, 1, 0, "CommandLineDataModel");
    qmlRegisterType<FreeSwapSpaceDataModel>(uri, 1, 0,
                                            "FreeSwapSpaceDataModel");
    qmlRegisterType<AvailableSwapSpaceDataModel>(uri, 1, 0,
                                                 "AvailableSwapSpaceDataModel");

    qmlRegisterType<AvailableMemoryDataModel>(uri, 1, 0,
                                              "AvailableMemoryDataModel");

    qmlRegisterType<FreeMemoryDataModel>(uri, 1, 0, "FreeMemoryDataModel");
  }
};

#endif  // AWESOMEMONITOR_AWESOMECOMPONENTSPLUGIN_H
