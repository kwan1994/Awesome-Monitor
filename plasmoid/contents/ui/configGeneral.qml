import QtQuick 2.13
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as Qt2
import org.kde.kirigami 2.5 as Kirigami
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform
import Qt.labs.settings 1.0
//import org.kde.plasma.plasmoid 2.0
import AwesomeMonitor 1.0
import QtQuick.Layouts 1.15

Item {
    id:root


    //property Component editor: Qt.createComponent("Editor.qml")
    property int textFieldWidth: 500
    property var changed: false
    width: childrenRect.width
    height: childrenRect.height


    function urlToPath(urlString) {
        var s
        if (urlString.startsWith("file:///")) {
            var k = urlString.charAt(9) === ':' ? 8 : 7
            s = urlString.substring(k)
        } else {
            s = urlString
        }
        return decodeURIComponent(s);
    }

    Settings {
       fileName: Platform.StandardPaths.locate(Platform.StandardPaths.ConfigLocation,"AwesomeMonitor/AwesomeMonitor",Platform.StandardPaths.LocateFile).toString().substring(7)
       id: settings;
       property alias basicComponents: basicComponentsFolder.text
       property alias dataModelsFolder: dataModelsFolder.text
       property alias modelFile: modelFile.text
       property alias timerInterval: timerInterval.value
    }

    FileDialog {
        id: fileDialogJson
        selectExisting: true
        selectFolder: false
        nameFilters: ["Json Files (*.json)"]
        onAccepted: {

            modelFile.text = urlToPath(fileDialogJson.fileUrl)
            Qt.quit()
        }
    }

    FileDialog {
        id: fileDialogModels
        selectExisting: true
        selectFolder: true
        onAccepted: {

            dataModelsFolder.text = urlToPath(fileDialogModels.fileUrl)
            Qt.quit()
        }
    }

    FileDialog {
        id: fileDialogComponents
        selectExisting: true
        selectFolder: true
        onAccepted: {

            dataModelsFolder.text = urlToPath(fileDialogComponents.fileUrl)
            Qt.quit()
        }
    }

    Kirigami.FormLayout {
        anchors.fill: parent
        SpinBox {
            value: Number(settings.value("timerInterval","1000"))
            Qt2.ToolTip.delay: 500
            Qt2.ToolTip.visible: timerInterval.hovered
            Qt2.ToolTip.text: "Refresh interval for data models, when not set specificaly"
            implicitWidth: 125
            maximumValue: Number.POSITIVE_INFINITY
            Kirigami.FormData.label: "Timer interval:"
            onValueChanged: root.changed= true;
            id: timerInterval
        }
        Row {
            spacing: 10
            bottomPadding: 10
            Kirigami.FormData.label: "Data models folder:"
            TextField {
                Layout.fillWidth: true
                text: settings.value("dataModelsFolder")
                Qt2.ToolTip.delay: 500
                Qt2.ToolTip.visible: dataModelsFolder.hovered
                Qt2.ToolTip.text: "Folder where to search for data models"
                width: textFieldWidth
                id: dataModelsFolder
                onEditingFinished: changed = true;
            }
            Button {
                onClicked: {
                    fileDialogModels.open()
                }
                iconSource: "../icons/folderIcon.png"
            }
        }

        Row {
            spacing: 10
            bottomPadding: 10
            Kirigami.FormData.label: "Basic Components Folder:"
            TextField {
                Layout.fillWidth: true
                text: settings.value("basicComponentsFolder")
                Qt2.ToolTip.delay: 500
                Qt2.ToolTip.visible: basicComponentsFolder.hovered
                Qt2.ToolTip.text: "Folder where to search for basic components"
                width: textFieldWidth
                id: basicComponentsFolder
                onEditingFinished: changed = true;
            }
            Button {
                onClicked: {
                    fileDialogModels.open()
                }
                iconSource: "../icons/folderIcon.png"
            }
        }

        Row {
            spacing: 10
            bottomPadding: 10
            Kirigami.FormData.label: "Model file:"
            TextField {
                Layout.fillWidth: true
                text: settings.value("modelFile")
                Qt2.ToolTip.delay: 500
                Qt2.ToolTip.visible: modelFile.hovered
                Qt2.ToolTip.text: "File from which Awesome Monitor is Loaded"
                width: textFieldWidth
                id: modelFile
                onEditingFinished:  root.changed= true;

            }
            Button {
                onClicked: {
                    fileDialogJson.open()
                }
                iconSource: "../icons/folderIcon.png"
            }

            Button {
                onClicked: {
                        let editor = Qt.createComponent("Editor.qml");
                        console.log("sda",editor,editor.errorString());
                        let win = editor.createObject(root);
                        console.log("asdas",win);
                        win.show();
                }
                iconSource: "../icons/editor.svg"
            }

        }
    }

    Component.onCompleted: {
        console.log(settings.value("componentsFolder"),settings.value("dataModelsFolder"))
        changed = false;
    }
    Component.onDestruction:  {
        console.log(settings.fileName);
        settings.setValue("basicComponentsFolder",basicComponentsFolder.text)
        settings.setValue("timerInterval",timerInterval.value);
        settings.setValue("dataModelsFolder",dataModelsFolder.text);
        settings.setValue("modelFile",modelFile.text);
        console.log(settings.fileName)

        if(changed)plasmoid.action("reset").trigger();
    }
}
