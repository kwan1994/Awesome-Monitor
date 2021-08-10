import QtQuick 2.14
import QtQuick.Dialogs 1.3
import QtGraphicalEffects 1.13
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.14 as Qt2
import QtWebEngine 1.10
import QtWebChannel 1.15
import AwesomeMonitor 1.0
import QtQuick.Controls 1.4 as Qt1
import QtQml.Models 2.14
import org.kde.plasma.components 3.0
import org.kde.plasma.core 2.0
import org.kde.plasma.components 2.0 as Plasma2
import QtQuick.Controls.Styles.Plasma 2.0
import QtQuick.Controls.Styles 1.4 as Qt1Styles

Qt2.ApplicationWindow {
    //ColorScope.colorGroup: Theme.NormalColorGroup
    id:window
    visible: true
    property alias scale: slider.value
    property bool isChanged: false
    minimumWidth: 1240
    minimumHeight: 900
    

    menuBar: Qt2.MenuBar {
        z:20
        height: contentHeight
        MouseArea{

        }
        Qt2.Menu {
            title: qsTr("&File")
            //                Qt2.Action { text: qsTr("&New...") }
            //                Qt2.Action { text: qsTr("&Open...") }
            Qt2.Action { text: qsTr("&Save")
                shortcut: "Ctrl+S"
                onTriggered: save()
            }

        }
    }

    property var sectionTooltips: ({
                                       "Custom Base Components": {
                                           "icon":"expand",
                                           "title":"Custom Base Components",
                                           "description": "These are base components"
                                       },

                                       "Base Components": {
                                           "icon":"expand",
                                           "title":"Custom Base Components",
                                           "description": "These are base components"
                                       },

                                       "Custom Data Models": {
                                           "icon":"expand",
                                           "title":"Custom Base Components",
                                           "dscription": "These are base components"
                                       },
                                       "Data Models": {
                                           "icon":"expand",
                                           "title":"Custom Base Components",
                                           "description": "These are base components"
                                       }
                                   })



    property bool shouldClose: false


    function save(){
        Plugin.saveToFile(treeModel.getJsonModelRepresentation());
    }



    Plasma2.Dialog {
        id: addDataModelDialog
        property var name: undefined
        buttons: [Row {
                spacing:10
                Button{

                    text: "Cancel"
                    onClicked: {
                        addDataModelDialog.close()
                    }
                    anchors.rightMargin: 10
                }

                Button{
                    enabled: addDataModelDialog.name != undefined
                    text: "Add"
                    onClicked: {
                        let compListItem = list.model.data(list.model.index(list.currentIndex,0));
                        treeModel.insertRow(0,tree.currentIndex,compListItem.schemaPath,addDataModelDialog.name);
                        Plugin.deletePlugin();
                        Plugin.initializePluginFromString(JSON.stringify(treeModel.getJsonModelRepresentation()));
                        addDataModelDialog.close()
                    }
                }}]

        location: Types.Floating


        content: Row {
            spacing: 10
            Text {

                text: "Data Model Name:"
            }
            TextField {
                id:poro
                onTextChanged: addDataModelDialog.name = text
            }
        }


    }

    Rectangle {
        z:200
        visible: closeDialog.status === Plasma2.DialogStatus.Open  || addDataModelDialog.status === Plasma2.DialogStatus.Open
        anchors.fill: parent
        color: "#aacfdbe7"
        MouseArea {
            hoverEnabled: true
            enabled: true
            anchors.fill: parent
        }
    }

    Plasma2.Dialog {
        parent: Qt2.Overlay.overlay
        id: closeDialog
        property var closeEvent;




        buttons: [Row {
                spacing:10
                Button{

                    text: "Exit without save"
                    onClicked: {
                        //window.shouldClose = true;
                        //refresher.running = false;

                        Plugin.deletePlugin();
                        closeDialog.close();
                        isChanged = false;
                        window.hide()
                    }
                    anchors.rightMargin: 10
                }

                Button{

                    anchors.rightMargin: 10
                    text: "Save and Exit"
                    onClicked: {
                        window.shouldClose = true;
                        //refresher.running = false;
                        save()
                        isChanged = false;
                        Plugin.deletePlugin();
                        closeDialog.close()
                        window.hide();
                        plasmoid.action("reset").trigger();
                    }
                }



                Button{
                    Qt2.DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                    anchors.rightMargin: 10
                    text: "Cancel"
                    onClicked: {
                        closeDialog.close();
                        isChanged = false;}
                }}]

        location: Types.Floating


        content:              Text {
            color: Theme.textColor
            text: "There are unsaved changes are you sure you want to exit without saving"
        }


    }


    Qt2.SplitView {
        z:6
        id: split
        handle: Rectangle {
            clip: true

            color:Qt2.SplitHandle.pressed?Theme.viewHoverColor: splitHandleArea.containsMouse?Qt.darker(Theme.viewHoverColor,1.2):Theme.complementaryBackgroundColor
            implicitWidth:10


            MouseArea {
                id:splitHandleArea
                anchors.fill: parent
                hoverEnabled: true
                enabled: true
                preventStealing: true
                onPressed: mouse.accepted = false
            }


        }
        anchors.fill: parent
        Rectangle{
            Qt2.SplitView.minimumWidth: list.contentWidth,tree.contentItem.widt
            color: Theme.viewBackgroundColor
            Qt2.SplitView.preferredWidth:220
            Qt2.SplitView {
                handle: Rectangle {

                    clip: true

                    implicitHeight: 40
                    color:Qt2.SplitHandle.pressed?Theme.viewHoverColor: splitHandleAreaHorizontal.containsMouse?Qt.darker(Theme.viewHoverColor,1.2):Theme.complementaryBackgroundColor



                    MouseArea {
                        id:splitHandleAreaHorizontal
                        anchors.fill: parent
                        hoverEnabled: true
                        enabled: true
                        preventStealing: true
                        onPressed: mouse.accepted = false
                    }


                    Row{
                        spacing: 20
                        anchors.centerIn: parent
                        Button{
                            id:del
                            enabled: selectionModel.currentIndex.valid
                            ColorScope.inherit: false
                            ColorScope.colorGroup: Theme.ButtonColorGroup
                            FallBackIcon {
                                id: iconDel
                                active: false
                                anchors.centerIn: parent
                                height: 20
                                width: 20
                                source: "minus"
                                fallBackSource: "../icons/minus.svg"
                            }

                            onClicked: {
                                tree.model.removeRows(selectionModel.currentIndex.row,1,tree.model.parent(selectionModel.currentIndex));
                                selectionModel.clearCurrentIndex();
                                Plugin.deletePlugin();
                                Plugin.initializePluginFromString(JSON.stringify(treeModel.getJsonModelRepresentation()));
                                web.reload();
                                isChanged = true;
                            }

                            implicitWidth: 40
                            implicitHeight: 25
                        }
                        Button{
                            id: ad;

                            enabled: {
                                let listIndex = list.currentIndex;
                                let treeIndex = selectionModel.currentIndex;
                                let listData;
                                if(listIndex !== -1)
                                 listData = list.model.data(list.model.index(listIndex,0));
                                let treeData = tree.model.data(treeIndex,256);
                                return listIndex !== -1 && (treeIndex.valid)?!treeData.isDataModel() && listData.name !== "Window":listData.name === "Window";
                            }
                            signal schemaChange(var schema, var forData)
                            onClicked: {

                                if(list.currentIndex !== undefined){
                                    var listItem = list.model.data(list.model.index(list.currentIndex,0,undefined));
                                    if(listItem.isDataModel()){
                                        addDataModelDialog.open();
                                        return;
                                    }
                                    if(selectionModel.currentIndex.valid)
                                        tree.model.insertRow(0,selectionModel.currentIndex,listItem.schemaPath);
                                    else
                                        tree.model.insertRow(0,tree.rootIndex,listItem.schemaPath);

                                    Plugin.deletePlugin();
                                    Plugin.initializePluginFromString(JSON.stringify(treeModel.getJsonModelRepresentation()));
                                    isChanged = true;
                                }
                            }
                            FallBackIcon {
                                id: iconExpand
                                active: false
                                anchors.centerIn: parent
                                height: 20
                                width: 20
                                source: "add"
                                fallBackSource: "../icons/add.svg"
                            }
                            implicitWidth: 40
                            implicitHeight: 25
                        }

                    }


                }
                anchors.fill: parent
                orientation: Qt.Vertical

                Rectangle {
                    color: Theme.viewBackgroundColor
                    Qt2.SplitView.preferredHeight: Math.min(list.contentHeight,700)


                    Plasma2.ScrollBar {
                        anchors.right: parent.right

                        //    id:p
                        visible: true
                        implicitWidth: 20
                        flickableItem: list
                        interactive: true
                        stepSize: 10
                        scrollButtonInterval: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 5
                        anchors.topMargin: 5
                        anchors.bottomMargin: 5

                    }
                    ListView{



                        width: parent.width - 35

                        height: parent.height
                        id:list
                        property var longestText: 0

                        ColorScope.colorGroup: Theme.ViewColorGroup




                        //implicitWidth: list.contentWidth
                        //list
                        Qt2.SplitView.preferredHeight: Math.min(contentHeight,700)
                        //Qt2.SplitView.implicitHeight: contentHeight
                        boundsBehavior: Flickable.StopAtBounds
                        //flickableDirection: Flickable.AutoFlickIfNeeded

                        model:ComponentListModel{

                        }

                        keyNavigationWraps: true
                        Keys.enabled: true
                        Keys.onPressed: {if(event.key===Qt.Key_Down){++currentIndex;//console.log(currentIndex)
                            }}
                        Keys.onUpPressed: --currentIndex

                        property var hoveredIndex: value

                        highlight: Plasma2.Highlight {
                            clip: true
                            //anchors.fill: parent
                            //hover: listItemArea.containsMouse

                        }


                        //highlightFollowsCurrentItem: true


                        delegate:  Plasma2.ListItem {
                            clip: true
                            //  id:item



                            visible: model.display.visible
                            id:rect
                            enabled: true
                            height: model.display.visible?30:0
                            //implicitWidth: split.width - 20

                            onClicked: list.currentIndex = index

                            RowLayout {
                                id: row
                                width: list.width
                                //width: split.width
                                //anchors.fill: parent
                                anchors.horizontalCenter: parent
                                Image {
                                    Layout.alignment: Qt.AlignVCenter
                                    sourceSize: Qt.size(20, 20)
                                    source: model.display.iconPath !== ""?model.display.iconPath:"../icons/defaultComponentIcon.svg"
                                }
                                Text {
                                    elide: Text.ElideRight
                                    id:name

                                    Layout.fillWidth: true
                                    //Layout.alignment: Qt.ali
                                    //Layout.fillWidth: true
                                    //width: split.width - dsadas.width
                                    color: Theme.textColor
                                    text: model.display.name
                                }
                            }}


                        section.delegate:Rectangle{
                            height: 30
                            MouseArea {
                                anchors.fill: parent
                                id:area
                                enabled: true
                                hoverEnabled: true
                            }
                            RowLayout{
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                width: list.width
                                FallBackIcon {
                                    id: iconExpan
                                    active: false
                                    width: 20
                                    height: 20
                                    source: "expand"
                                    fallBackSource: "../icons/expand-button.svg"

                                }

                                Text{
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                    id:t
                                    text: section
                                    color: area.containsMouse?Theme.complementaryNegativeTextColor:Theme.complementaryTextColor
                                }
                            }
                        }

                        section.property: "display.section"
                        section.criteria: ViewSection.FullString

                    }

                }

                Rectangle {
                    id:s
                    color:Theme.viewBackgroundColor
                    Plasma2.ScrollBar {
                        anchors.right: s.right
                        z:3
                        //    id:p
                        visible: true
                        implicitWidth: 20
                        flickableItem: tree.flickableItem
                        interactive: true
                        stepSize: 10
                        scrollButtonInterval: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 5
                        anchors.topMargin: 5
                        anchors.bottomMargin: 5
                        height: s.height - 10

                    }

                    Qt1.TreeView{

                        frameVisible: false
                        id:tree
                        width: s.width - 35
                        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                        backgroundVisible: true
                        anchors.fill: parent
                        model: PluginTreeModel { id: treeModel}
                        headerVisible: false
                        Qt1.TableViewColumn{
                            role:"display"
                            width: s.width - 35
                        }

                       selection: ItemSelectionModel {
                        id: selectionModel
                        model: treeModel

                        onCurrentIndexChanged: {
                            if(currentIndex === tree.rootIndex){
                                someObject.formDataChanged({},{});
                            } else {
                            let item = treeModel.data(currentIndex,256);
                            someObject.formDataChanged(item.schemaForm,item.formData);
                            }
                        }
                       }





                        style: Qt1Styles.TreeViewStyle {

                            backgroundColor: Theme.viewBackgroundColor
                            rowDelegate: Rectangle {
                                color: Theme.viewBackgroundColor
                                //property var item: treeModel.data(treeModel.parent(styleData.index),0)
                                height: 30
                                width: tree.parent.parent.width - 35




                            }

    
                            itemDelegate: Text {

                                verticalAlignment: Text.AlignVCenter
                                color: Theme.viewTextColor
                                //id: name
                                text: styleData.value


                                Plasma2.Highlight{
                                    opacity: 0.25
                                    visible: {selectionModel.currentIndex; return selectionModel.isSelected(styleData.index) || treeArea.containsMouse;}
                                    anchors.fill: parent


                                    pressed: {selectionModel.currentIndex; return selectionModel.isSelected(styleData.index)}

                                }
                                MouseArea {
                                    id: treeArea
                                    onPressed: {
                                        console.log(Theme.viewHighlightedTextColor,Theme.viewNegativeTextColor,Theme.viewNeutralTextColor,Theme.viewPositiveTextColor,Theme.viewTextColor);
                                        console.log(selectionModel.isSelected(styleData.index),styleData.selected,"asdasdasdasda");
                                        mouse.accepted = true;
                                        let indexToSelect = selectionModel.isSelected(styleData.index)?tree.rootIndex:styleData.index;
                                        selectionModel.setCurrentIndex(indexToSelect,ItemSelectionModel.ClearAndSelect);
                                        //parent.seleted = selectionModel.isSelected(styleData.index)


                                    }
                                    hoverEnabled: true
                                    anchors.fill: parent
                                }
                            }
                        }
                    }
                }
            }
        }



        Rectangle{
            z:-2
            color: Qt.darker(Theme.backgroundColor,1.2)
            Qt2.SplitView.fillWidth: true

            id:ssd

            ColumnLayout{
                anchors.right: p.left
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.rightMargin: 10
                z:5
                spacing: 10
                //anchors.centerIn: parent

                Timer {
                    interval: 150
                    repeat: true
                    running: true
                    onTriggered: {
                        if(plus.pressed) slider.value += slider.stepSize
                        if(minus.pressed) slider.value -= slider.stepSize
                    }
                }

                RoundButton{
                    id:plus
                    ColorScope.inherit: false
                    ColorScope.colorGroup: Theme.ButtonColorGroup
                    Layout.alignment: Qt.AlignVCenter

                    onClicked: slider.value += slider.stepSize
                    onHoveredChanged: iconPlus.active = !iconPlus.active

                    FallBackIcon {
                        id: iconPlus
                        active: false
                        anchors.centerIn: parent
                        anchors.fill: parent
                        source: "zoom-in"
                        fallBackSource: "../icons/zoom-in.svg"
                    }


                }



                Plasma2.Slider {
                    orientation: Qt.Vertical
                    implicitHeight: 200
                    implicitWidth: minus.width
                    id:slider
                    valueIndicatorText: (slider.value * 100).toString() + "%"
                    value: 1
                    minimumValue :0.1
                    maximumValue:2
                    stepSize: .01


                }
                RoundButton{
                    id:minus


                    ColorScope.inherit: false
                    ColorScope.colorGroup: Theme.ButtonColorGroup
                    Layout.alignment: Qt.AlignVCenter

                    onClicked: slider.value += slider.stepSize
                    onHoveredChanged: iconMinus.active = !iconMinus.active



                    FallBackIcon {
                        id: iconMinus
                        active: false
                        anchors.centerIn: parent
                        anchors.fill: parent
                        source: "zoom-out"
                        fallBackSource: "../icons/zoom-out.svg"
                    }

                }

            }


            Connections {
                target: Plugin
                function onInitialized(s){
                    rep.enabled = true;
                    rep.model = Plugin.numberOfWindows()
                }
            }




            Plasma2.ScrollBar {
                anchors.left: parent.left
                z:20
                //    id:p
                orientation: Qt.Horizontal
                visible: grid.contentWidth > parent.width

                flickableItem: grid
                interactive: true
                stepSize: 10
                scrollButtonInterval: 10
                anchors.leftMargin: 10
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                anchors.bottom: parent.bottom
                anchors.right: parent.right

            }


            Plasma2.ScrollBar {
                z: 20
                id:p
                orientation: Qt.Vertical
                visible: grid.contentHeight > parent.height

                flickableItem: grid
                interactive: true
                stepSize: 10
                scrollButtonInterval: 10

            }


            Flickable {

                boundsMovement: Flickable.StopAtBounds
                id: grid
                width: parent.width
                height: parent.height
                //anchors.centerIn: parent
                contentHeight:  g.height * window.scale
                contentWidth: g.width * window.scale;
                clip: true

                Grid {
                    id:g
                    //transformOrigin: Item.TopLeft



                    columns: 3
                    spacing: 10
                    anchors.centerIn: parent
                    scale: window.scale
                    clip: true
                    Repeater {
                        enabled: false
                        id:rep
                        delegate:  Image {

                            clip: true

                            id: as
                            cache: false
                            property string refreshableSource: "image://livePreview/" + index
                            //sourceSize: Qt.size(348,462)

                            source: refreshableSource
                            function refresh() {
                                source = "";
                                source = Qt.binding(function() { return refreshableSource });
                            }
                            Timer {
                                id:refresher
                                running: window.visible
                                repeat: true
                                interval: 1000
                                onTriggered:{as.source = "";as.refresh()}

                            }

                            //Component.onCompleted: Plugin.initialize.connect(() =>{ window.close(); source="image://livePreview/" + modelData})

                        }

                    }
                }
            }






        }
        QtObject {
            id: someObject

            // ID, under this ID, this object is known on the WebEngineView side.
            WebChannel.id: "backend"

            property string someProperty: "gray"

            signal formDataChanged(var schemaForm, var formData );
            signal styleChanged(var style)
            //onSomeSignal: console.log("sdasqqq")




            function style(){
                console.log(Plugin.stylesheet(),"sdadas");
                return Plugin.stylesheet();
            }

            function setFormData(formData) {
                if(selectionModel.currentIndex.valid){
                    let item = treeModel.data(selectionModel.currentIndex,256);
                    item.formData = formData;
                    Plugin.deletePlugin();
                    console.log(JSON.stringify(treeModel.getJsonModelRepresentation()));
                    Plugin.initializePluginFromString(JSON.stringify(treeModel.getJsonModelRepresentation()));
                    someObject.formDataChanged(item.schemaForm,item.formData);
                    isChanged = true;

                }
            }

            function getTreeCurrentData() {
                if(selectionModel.currentIndex.valid){
                    var item = tree.model.data(selectionModel.currentIndex,0);
                    return {formData:item.formData,schemaForm:item.schemaForm}
                }
                return {formData:{},schemaForm:{}}
            }

        }

        WebEngineView {
            Qt2.SplitView.minimumWidth: 600
            Qt2.SplitView.preferredWidth: 600
            id: web
            url:"../code/jsonForm/build/index.html"
            webChannel.registeredObjects: [someObject]
            onContextMenuRequested: {
                request.accepted = true
            }
        }


        Connections{
            enabled:true
            target: Theme
            function onThemeChanged() {
                someObject.styleChanged(Plugin.stylesheet())
            }
        }



    }
    Component.onCompleted: {Plugin.setHideWindows();Plugin.resetPlugin()}
    onClosing: {
        if(isChanged) {
            close.accepted = false;
            closeDialog.open();
        }
    }
}
