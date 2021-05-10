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

    Plasmoid.fullRepresentation:Image {

        source: "../images/plasmoidIcon.svg"
    }



    function action_reset(){
        Plugin.resetPlugin();
    }

    Component.onCompleted: {

        plasmoid.setAction("reset","Resets Visualization")
        Plugin.resetPlugin();

    }

    Component.onDestruction: Plugin.deletePlugin()
}
