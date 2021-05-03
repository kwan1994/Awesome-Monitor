cmake_minimum_required(VERSION 3.13)
project(AwesomeMonitor)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 5.15.2 COMPONENTS REQUIRED  Widgets Qml Quick Gui Test)
find_package(ECM REQUIRED NO_MODULE)
# Needed by find_package(KF5Plasma) below.
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

find_package(KF5Plasma REQUIRED plasma)


# set this path to schema-test-suite to get tests compiled - optional
# if you want to inherit tests

add_subdirectory(json-schema-validator)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Components/ComponentUtils/defaultJavascriptTransformers.mjs ${CMAKE_CURRENT_BINARY_DIR}/src/Components/ComponentUtils COPYONLY)
#target_link_libraries(AwesomeMonitor KF5::Plasma  Qt5::Qml Qt5::Quick Qt5::Gui Qt5::Widgets Boost::filesystem json-schema-validator)
#target_include_directories(AwesomeMonitor PUBLIC /usr/local/lib)
#

##add_custom_target( jsonForm ALL WORKING_DIRECTORY jsonEditor COMMAND npm run-script build)



# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files

# Locate plasma_install_package macro.

add_subdirectory(src)



#add_library(AwesomeMonitor
#        SHARED
#
#
#        src/ComponentFramework/ApplicationModel/tree.cpp
#        src/ComponentFramework/ApplicationModel/tree.h
#        src/ComponentFramework/JsonToTreeParser/JsonSchemaEnhancer.cpp
#        src/ComponentFramework/JsonToTreeParser/JsonSchemaEnhancer.h
#        src/ComponentFramework/JsonToTreeParser/JsonToTreeParser.cpp
#        src/ComponentFramework/JsonToTreeParser/JsonToTreeParser.h
#        src/Components/BasicComponents/ProgresBar/ProgresBar.qml
#
#        src/Components/BasicComponents/Text/Text.qml
#        src/Components/DataComponents/CpuTemperatureDataModel/CpuTemperatureDataModel.h
#        src/Components/DataComponents/CpuTemperatureDataModel/CpuTemperatureDataModel.cpp
#        src/Components/DataComponents/ProcessesDataModel/ProcessDataModel.cpp
#        src/Components/DataComponents/ProcessesDataModel/ProcessDataModel.h
#        src/Settings/BaseSettingGroup.h
#        src/Settings/GeneralSettings.h
#        src/Utils/JsonValueConverter/JsonValueConverter.cpp
#        src/Utils/JsonValueConverter/JsonValueConverter.h
#        src/Utils/Logger/Logger.cpp
#        src/Utils/Logger/Logger.h
#
#        src/Editor/Models/JsonSchemaModel/JsonNode.cpp
#        src/Editor/Models/JsonSchemaModel/JsonNode.h
#        src/Editor/Models/JsonSchemaModel/JsonSchemaModel.cpp
#        src/Editor/Models/JsonSchemaModel/JsonSchemaModel.h
#        src/Components/ComponentUtils/utils.cpp
#        src/Components/ComponentUtils/utils.h
#        src/Components/DataComponents/DataModelBase.cpp
#        src/Components/DataComponents/DataModelBase.h
#        src/Components/DataComponents/SingleCpuCoreTemperatureDataModel/SingleCpuCoreTemperatureDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreTemperatureDataModel/SingleCpuCoreTemperatureDataModel.h
#        src/Components/DataComponents/CpuMaxTemperatureDataModel/CpuMaxTemperatureDataModel.cpp
#        src/Components/DataComponents/CpuMaxTemperatureDataModel/CpuMaxTemperatureDataModel.h
#        src/Components/DataComponents/SingleCpuCoreMaxTemperatureDataModel/SingleCpuCoreMaxTemperatureDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreMaxTemperatureDataModel/SingleCpuCoreMaxTemperatureDataModel.h
#        src/AppPlugin.h
#        Plugin.cpp
#        Plugin.h
#        src/Components/DataComponents/CpuCurrentFrequencyDataModel/CpuCurrentFrequencyDataModel.cpp
#        src/Components/DataComponents/CpuCurrentFrequencyDataModel/CpuCurrentFrequencyDataModel.h
#        src/Components/DataComponents/SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.h
#        src/Components/DataComponents/CpuMaxFrequencyDataModel/CpuMaxFrequencyDataModel.cpp
#        src/Components/DataComponents/CpuMaxFrequencyDataModel/CpuMaxFrequencyDataModel.h
#        src/Components/DataComponents/SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.h
#        src/Components/DataComponents/CpuMinFrequencyDataModel/CpuMinFrequencyDataModel.cpp
#        src/Components/DataComponents/CpuMinFrequencyDataModel/CpuMinFrequencyDataModel.h
#        src/Components/DataComponents/SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.h
#        src/Components/DataComponents/SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.cpp
#        src/Components/DataComponents/SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.h
#        src/Components/DataComponents/CpuUtilisationDataModel/CpuUtilisationDataModel.cpp
#        src/Components/DataComponents/CpuUtilisationDataModel/CpuUtilisationDataModel.h
#        src/Components/DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.cpp
#        src/Components/DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.h
#        src/Components/DataComponents/CommandLineDataModel/CommandLineDataModel.cpp
#        src/Components/DataComponents/CommandLineDataModel/CommandLineDataModel.h
#        src/Components/DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.cpp
#        src/Components/DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.h
#        src/Components/DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.cpp
#
#        src/Components/DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.h
#        src/Components/DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.cpp src/Components/DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.h src/Components/DataComponents/IpAddressDataModel/IpAdressDataModel.cpp src/Components/DataComponents/IpAddressDataModel/IpAdressDataModel.h src/Components/ComponentUtils/UtilsWrapper.cpp src/Components/ComponentUtils/UtilsWrapper.h src/Editor/Models/ComponentListModel/ComponentListModel.cpp src/Editor/Models/ComponentListModel/ComponentListModel.h src/Editor/Models/PluginTreeModel/PluginTreeModel.h src/Editor/Models/PluginTreeModel/PluginTreeModel.cpp src/Editor/Models/ImageLivePreviewProvider.cpp src/Editor/Models/ImageLivePreviewProvider.h)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/ComponentUtils/defaultJavascriptTransformers.mjs
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/Components/ComponentUtils/)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/ComponentFramework/JsonToTreeParser/errorComponent.qml
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/ComponentFramework/JsonToTreeParser/)
#
#
#set(CMAKE_AUTOMOC OFF)

#add_library(json-hpp INTERFACE)
#target_include_directories(json-hpp
#        INTERFACE
#        /usr/include/nlohmann/)

# set this path to schema-test-suite to get tests compiled - optional
# if you want to inherit tests

include_directories(json-schema-validator)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Components/ComponentUtils/defaultJavascriptTransformers.mjs ${CMAKE_CURRENT_BINARY_DIR}/src/Components/ComponentUtils COPYONLY)
#target_link_libraries(AwesomeMonitor KF5::Plasma  Qt5::Qml Qt5::Quick Qt5::Gui Qt5::Widgets Boost::filesystem json-schema-validator)
#target_include_directories(AwesomeMonitor PUBLIC /usr/local/lib)
#
#



add_executable(AwesomeMonitor-bin main.cpp)
#
add_dependencies(AwesomeMonitor-bin AwesomeMonitor)
target_include_directories(
        AwesomeMonitor-bin
        PUBLIC
        ${header_dir_list} # Recursive
)
target_include_directories( AwesomeMonitor-bin PUBLIC /usr/local/include)
target_link_libraries( AwesomeMonitor-bin  Qt5::Qml Qt5::Quick Qt5::Gui Qt5::Widgets Qt5::Test AwesomeMonitor)
target_include_directories(AwesomeMonitor-bin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
link_directories(AwesomeMonitor-bin ${CMAKE_CURRENT_SOURCE_DIR})
##
#add_custom_command(
#        TARGET AwesomeMonitor
#        POST_BUILD
#        COMMAND
#        ${CMAKE_COMMAND} -E copy
#        qmldir
#        $<TARGET_FILE_DIR:AwesomeMonitor>/qmldir
#)
#
#set(URI AwesomeMonitor)
#string(REPLACE "." "/" TARGETPATH ${URI})
#execute_process(COMMAND qmake -query QT_INSTALL_QML OUTPUT_VARIABLE QT_INSTALL_QML_RAW)
#string(REPLACE "\n" "" QT_INSTALL_QML ${QT_INSTALL_QML_RAW})
#set(DESTDIR "${QT_INSTALL_QML}/${TARGETPATH}")
#install(TARGETS AwesomeMonitor DESTINATION ${DESTDIR})
#install(FILES qmldir plugins.qmltypes DESTINATION ${DESTDIR})
#
#
## Use Extra CMake Modules (ECM) for common functionality.
## See http://api.kde.org/ecm/manual/ecm.7.html
## and http://api.kde.org/ecm/manual/ecm-kde-modules.7.html
#
#
## Add installatation target ("make install").
plasma_install_package(plasmoid AwesomeMonitor)