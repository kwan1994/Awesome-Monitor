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
#include "DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.h"
#include "DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.h"
#include "DataComponents/CommandLineDataModel/CommandLineDataModel.h"
#include "DataComponents/CpuCurrentFrequencyDataModel/CpuCurrentFrequencyDataModel.h"
#include "DataComponents/CpuMaxFrequencyDataModel/CpuMaxFrequencyDataModel.h"
#include "DataComponents/CpuMaxTemperatureDataModel/CpuMaxTemperatureDataModel.h"
#include "DataComponents/CpuMinFrequencyDataModel/CpuMinFrequencyDataModel.h"
#include "DataComponents/CpuTemperatureDataModel/CpuTemperatureDataModel.h"
#include "DataComponents/CpuUtilisationDataModel/CpuUtilisationDataModel.h"
#include "DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.h"
#include "DataComponents/SingleCpuCoreMaxTemperatureDataModel/SingleCpuCoreMaxTemperatureDataModel.h"
#include "DataComponents/SingleCpuCoreTemperatureDataModel/SingleCpuCoreTemperatureDataModel.h"
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
    qmlRegisterType<CpuTemperatureDataModel>(uri, 1, 0,
                                             "CpuTemperatureDataModel");
    qmlRegisterType<SingleCpuCoreTemperatureDataModel>(
        uri, 1, 0, "SingleCpuCoreTemperatureDataModel");
    qmlRegisterType<CpuMaxTemperatureDataModel>(uri, 1, 0,
                                                "CpuMaxTemperatureDataModel");
    qmlRegisterType<SingleCpuCoreMaxTemperatureDataModel>(
        uri, 1, 0, "SingleCpuCoreMaxTemperatureDataModel");
    qmlRegisterType<CpuCurrentFrequencyDataModel>(
        uri, 1, 0, "CpuCurrentFrequencyDataModel");
    qmlRegisterType<SingleCpuCoreCurrentFrequencyDataModel>(
        uri, 1, 0, "SingleCpuCoreCurrentFrequencyDataModel");
    qmlRegisterType<CpuMaxFrequencyDataModel>(uri, 1, 0,
                                              "CpuMaxFrequencyDataModel");
    qmlRegisterType<SingleCpuCoreMaxFrequencyDataModel>(
        uri, 1, 0, "SingleCpuCoreMaxFrequencyDataModel");
    qmlRegisterType<CpuMinFrequencyDataModel>(uri, 1, 0,
                                              "CpuMinFrequencyDataModel");
    qmlRegisterType<SingleCpuCoreUtilisationDataModel>(
        uri, 1, 0, "SingleCpuCoreUtilisationDataModel");
    qmlRegisterType<CpuUtilisationDataModel>(uri, 1, 0,
                                             "CpuUtilisationDataModel");

    qmlRegisterType<BatteryStatusDataModel>(uri, 1, 0,
                                            "BatteryStatusDataModel");
    qmlRegisterType<UploadSpeedDataModel>(uri, 1, 0, "UploadSpeedDataModel");
    qmlRegisterType<DownloadSpeedDataModel>(uri, 1, 0,
                                            "DownloadSpeedDataModel");
    qmlRegisterType<BatteryCapacityDataModel>(uri, 1, 0,
                                              "BatteryCapacityStatusDataModel");
    qmlRegisterType<UtilsWrapper>(uri, 1, 0, "Utils");
    qmlRegisterType<CommandLineDataModel>(uri, 1, 0, "CommandLineDataModel");
  }
};

#endif  // AWESOMEMONITOR_AWESOMECOMPONENTSPLUGIN_H
