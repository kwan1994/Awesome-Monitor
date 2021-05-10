set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_AUTOMOC ON)
add_library(
        awesomeComponentsPlugin
        SHARED

        ComponentUtils/defaultJavascriptTransformers.mjs

        DataComponents/SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.cpp
        DataComponents/SingleCpuCoreCurrentFrequencyDataModel/SingleCpuCoreCurrentFrequencyDataModel.h

        DataComponents/SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.cpp
        DataComponents/SingleCpuCoreMinFrequencyDataModel/SingleCpuCoreMinFrequencyDataModel.h

        DataComponents/SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.cpp
        DataComponents/SingleCpuCoreMaxFrequencyDataModel/SingleCpuCoreMaxFrequencyDataModel.h

        DataComponents/SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.cpp
        DataComponents/SingleCpuCoreUtilisationDataModel/SingleCpuCoreUtilisationDataModel.h

        DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.cpp
        DataComponents/DownloadSpeedDataModel/DownloadSpeedDataModel.h

        DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.cpp
        DataComponents/UploadSpeedDataModel/UploadSpeedDataModel.h

        DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.cpp
        DataComponents/BatteryCapacityDataModel/BatteryCapacityDataModel.h

        DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.h
        DataComponents/BatteryStatusDataModel/BatteryStatusDataModel.cpp

        DataComponents/CommandLineDataModel/CommandLineDataModel.cpp
        DataComponents/CommandLineDataModel/CommandLineDataModel.h

        DataComponents/FreeSwapSpaceDataModel/FreeSwapSpaceDataModel.cpp
        DataComponents/FreeSwapSpaceDataModel/FreeSwapSpaceDataModel.h

        DataComponents/AvailableSwapSpaceDataModel/AvailableSwapSpaceDataModel.cpp
        DataComponents/AvailableSwapSpaceDataModel/AvailableSwapSpaceDataModel.h

        DataComponents/AvailableMemoryDataModel/AvailableMemoryDataModel.cpp
        DataComponents/AvailableMemoryDataModel/AvailableMemoryDataModel.h

        DataComponents/FreeMemoryDataModel/FreeMemoryDataModel.cpp
        DataComponents/FreeMemoryDataModel/FreeMemoryDataModel.h

        DataComponents/DataModelBase.h
        DataComponents/DataModelBase.cpp

        ComponentUtils/utils.cpp
        ComponentUtils/utils.h

        ComponentUtils/defaultJavascriptTransformers.mjs

        ComponentUtils/UtilsWrapper.cpp
        ComponentUtils/UtilsWrapper.h

        AwesomeComponentsPlugin.h

        # It's not important to include 'qmldir' or 'plugins.qmltypes' here,
        # but it will make IDEs (such as Qt Creator) to include them in project tree
        qmldir

)


set(CMAKE_AUTOMOC ON)
find_package(Qt5 5.14 COMPONENTS REQUIRED  Widgets Qml Quick Gui)
target_sources(AwesomeMonitor PUBLIC ComponentUtils/utils.cpp ComponentUtils/utils.h)

target_compile_options(
        awesomeComponentsPlugin
        PRIVATE
        -Wall
        -Wextra
)

target_link_libraries(
        awesomeComponentsPlugin
        PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

# During plugin searching Qt will be looking for 'qmldir' file
# So we should place it next to our plugin lib.
add_custom_command(
        TARGET awesomeComponentsPlugin
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy
        qmldir
        $<TARGET_FILE_DIR:awesomeComponentsPlugin>/qmldir
)

install(FILES ComponentUtils/defaultJavascriptTransformers.mjs  DESTINATION ~/.config)

set(URI AwesomeComponents)
string(REPLACE "." "/" TARGETPATH ${URI})
execute_process(COMMAND qmake -query QT_INSTALL_QML OUTPUT_VARIABLE QT_INSTALL_QML_RAW)
string(REPLACE "\n" "" QT_INSTALL_QML ${QT_INSTALL_QML_RAW})
set(DESTDIR "${QT_INSTALL_QML}/${TARGETPATH}")
install(TARGETS awesomeComponentsPlugin DESTINATION ${DESTDIR})
install(FILES qmldir plugins.qmltypes DESTINATION ${DESTDIR})
