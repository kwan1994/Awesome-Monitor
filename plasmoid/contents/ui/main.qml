import QtQuick 2.0
import QtQuick.Controls 1.4
import AwesomeMonitor 1.0
import Qt.labs.platform 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import Qt.labs.settings 1.0

Item {
    Plasmoid.compactRepresentation:Image {

        source: "../images/plasmoidIcon.svg"
    }


    Plasmoid.fullRepresentation: Rectangle {
        visible: false
        height: 20
        width: 40
        color: "blue"
        TextArea {
            id: s;
            text : "sadasd"
            onFocusChanged: {
                set.test = s.text

            }
        }



        Component.onCompleted: {

            Plugin.resetPlugin();

        }
    }

    Settings {
        id: set
        fileName: StandardPaths.locate(StandardPaths.ConfigLocation,"AwesomeMonitor",StandardPaths.LocateFile).toString().substring(7)
    }

    function action_reset(){
        Plugin.resetPlugin();
    }

    Component.onCompleted: {

        plasmoid.setAction("reset","Resets Visualization")
        Plugin.resetPlugin();

    }

    Component.onDestruction: plugin.deletePlugin()

    Connections {
        target: plasmoid.configuration
        onValueChanged: {
            console.log(key,value)
        }
    }





}
