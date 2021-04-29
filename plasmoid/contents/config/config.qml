import QtQuick 2.0

import org.kde.plasma.configuration 2.0

ConfigModel {
    //icon in /usr/share/icons how to install ???
    ConfigCategory {
icon: "generalSettingsIcon"
         name: i18nc("@title", "General")
         source: "configGeneral.qml"
    }

    ConfigCategory {
        icon: "customer-support"
         name: i18nc("@title", "Custom")
         source: "configCustom.qml"
    }
}
