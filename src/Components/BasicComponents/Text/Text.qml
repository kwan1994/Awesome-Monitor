import QtQuick 2.11

Text {
    id: me
    property var colorStates: [{"value":"20","color":"red"}]
    property color defaultColor: "black"

    color: defaultColor;

    Component.onCompleted: {
        me.text = dataModels && dataModels.valueModel && dataModels.valueModel.getValue();
    }

    function getColor(){
        if(colorStates === undefined || colorStates.length === 0) return defaultColor
        for(var i = 0;i < colorStates.length;i++){
            if(colorStates[i].value === me.text && colorStates[i].color){
                return colorStates[i].color;
            }
        }
        return defaultColor;
   }

     Connections {
        target: dataModels.valueModel
        onDataChanged: {
            me.text = value;
            me.color = getColor();
         }
     }
}
