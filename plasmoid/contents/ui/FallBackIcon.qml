import QtQuick 2.15
import QtGraphicalEffects 1.13
import QtQuick.Controls 2.15 as Qt2
import QtQuick.Controls 1.4 as Qt1
import org.kde.plasma.components 3.0
import org.kde.plasma.core 2.0
import org.kde.plasma.components 2.0 as Plasma2


Item {
    id:root
    property var source;
    property var fallBackSource;
    property var active;
    IconItem {
        colorGroup: Theme.ButtonColorGroup
        anchors.fill: parent
        anchors.centerIn: parent
        id: iconItem
        visible: valid
        source: root.source
        active: root.active
    }

    Image {
        id: fallbackIcon
        visible: !iconItem.valid && !active
        anchors.fill: parent
        anchors.centerIn: parent
        source: fallBackSource



    }


    ColorOverlay{
        anchors.fill: fallbackIcon
        visible: !fallbackIcon.visible && !iconItem.valid
        color: Theme.highlightColor
        source: fallbackIcon
    }

}
