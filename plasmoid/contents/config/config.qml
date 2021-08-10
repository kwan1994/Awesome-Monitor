import QtQuick 2.0

import org.kde.plasma.configuration 2.0

ConfigModel {
    //icon in /usr/share/icons how to install ???
    ConfigCategory {
         icon: "generalSettingsIcon"
         name: i18nc("@title", "General")
         source: "configGeneral.qml"
    }


}
