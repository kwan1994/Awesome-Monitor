import QtQuick.Controls 1.4
import QtQuick 2.1

ProgressBar {
    id:me
    property var colorSteps: [{"value":20,"color":"blue"},{"value":95,"color":"red"},{"value":20,"color":"orange"}]
    property var defaultColor: "black"

    Component.onCompleted: {
        value = dataModels && dataModels.valueModel && dataModels.valueModel.currentValue;
        minimumValue = dataModels && dataModels.minValueModel && dataModels.minValueModel.currentValue;
        maximumValue = dataModels && dataModels.maxValueModel && dataModels.maxValueModel.currentValue;
    }

    function getColor(){
        if(colorStates === undefined || colorStates.length === 0) return defaultColor
        for(var i = 0;i < colorStates.length;i++){
            if(colorStates[i].value === me.value && colorStates[i].color){
                return colorStates[i].color;
            }
        }
        return defaultColor;
   }

    Connections {
        target: dataMoodels.valueModel
        onDataChanged: {
            me.value = currentValue;
            me.color =  me.getColor();
        }
    }

    Connections {
        target: dataMoodels.minValueModel
        onDataChanged: {
            me.minimumValue = currentValue;
        }
    }

    Connections {
        target: dataMoodels.maxValueModel
        onDataChanged: {
            me.maximumValue = currentValue;
        }
    }
}
