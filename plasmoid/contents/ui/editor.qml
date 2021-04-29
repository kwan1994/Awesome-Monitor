import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.13

Window {
    modality: Qt.WindowModal
    title: "Model editor"
    width: 1240
    height: 1024
    SplitView {
        Rectangle{
            color: "red"
            width:220
            SplitView {
                orientation: Qt.Vertical
                Rectangle {
                    width: 700
                    color:"lightsteelblue"
                }

                Rectangle {

                    color:"pink"
                }
            }
        }

        Rectangle{
            color: "gray"

        }


        Rectangle{
            color: "green"
            width: 220
        }

    }
}
