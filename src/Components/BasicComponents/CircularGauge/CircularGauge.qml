import QtQuick 2.0
import QtQuick.Extras 1.4


CircularGauge {
    id:me
    property var colorSteps: [{"value":20,"color":"blue"},{"value":95,"color":"red"},{"value":20,"color":"orange"}]
    property var defaultColor: "black"

    Component.onCompleted: {
        value = dataModels && dataModels.valueModel && dataModels.valueModel.getValue();
        minimumValue = dataModels && dataModels.minValueModel && dataModels.minValueModel.getValue();
        maximumValue = dataModels && dataModels.maxValueModel && dataModels.maxValueModel.getValue();
    }

    function getColor(){
        if(colorStates === undefined) return defaultColor
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
            me.value = value;
            me.color =  me.getColor();
        }
    }

    Connections {
        target: dataMoodels.minValueModel
        onDataChanged: {
            me.minimumValue = value;
        }
    }

    Connections {
        target: dataMoodels.maxValueModel
        onDataChanged: {
            me.maximumValue = value;
        }
    }
}
