import QtQuick 2.14
import QtQuick.Controls 2.14
ApplicationWindow {
    width: 500
    height: 600
    property var error:"sdasdasdsa";
    Rectangle {
        color: "red"
        anchors.fill: parent
        Text {
            width: 500
            wrapMode: Text.Wrap
            color: "white"
            text: error
        }

    }
}
