add_library(AwesomeMonitor SHARED AppPlugin.h Plugin.h Plugin.cpp)


target_link_libraries(AwesomeMonitor KF5::Plasma nlohmann_json::nlohmann_json  Qt5::Qml Qt5::Quick Qt5::Gui Qt5::Widgets nlohmann_json_schema_validator)

target_include_directories(
        AwesomeMonitor
        PUBLIC
        ../json/single_include/nlohmann
)

add_custom_command(
        TARGET AwesomeMonitor
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy
        qmldir
        $<TARGET_FILE_DIR:AwesomeMonitor>/qmldir
)

##add_custom_command(TARGET AwesomeMonitor POST_BUILD WORKING_DIRECTORY ../jsonEditor COMMAND npm install COMMAND npm run-script build)

set(DESTDIR "${CMAKE_INSTALL_PREFIX}/lib/qml/")
install(TARGETS AwesomeMonitor DESTINATION ${DESTDIR})
install(FILES qmldir plugins.qmltypes DESTINATION ${DESTDIR})
install(FILES ../plasmoid/contents/config/generalSettingsIcon.svg DESTINATION $ENV{HOME}/.local/share/icons )
install(FILES ComponentFramework/JsonToTreeParser/errorComponent.qml
        DESTINATION $ENV{HOME}/.config/AwesomeMonitor)

install(FILES Components/ComponentUtils/defaultJavascriptTransformers.mjs  DESTINATION $ENV{HOME}/.config   )

install(DIRECTORY ../defaultConfig/
        DESTINATION $ENV{HOME}/.config/AwesomeMonitor )

message(${CMAKE_INSTALL_PREFIX} )

add_subdirectory(Editor)
add_subdirectory(ComponentFramework)
add_subdirectory(Components)
