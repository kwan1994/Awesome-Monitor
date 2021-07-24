import QtQuick.Controls 2.14
import QtQuick 2.14

ProgressBar {
    id:me
property var control;

    property var colorSteps: [{"value":20,"color":"blue"},{"value":95,"color":"red"},{"value":20,"color":"orange"}]
    property var defaultColor: "black"
    property var dataModels;


    Component.onCompleted: {
        if(background!==null || progress!==null ) me.style = s;
        value = dataModels && dataModels.valueModel && dataModels.valueModel.currentValue;
        from = dataModels && dataModels.minValueModel && dataModels.minValueModel.currentValue;
        to = dataModels && dataModels.maxValueModel && dataModels.maxValueModel.currentValue;
    }

    function getColor(){
        if(colorSteps === undefined || colorSteps.length === 0) return defaultColor
        for(var i = 0;i < colorSteps.length;i++){
            if(colorSteps[i].value === me.value && colorSteps[i].color){
                return colorSteps[i].color;
            }
        }
        return defaultColor;
   }

    Connections {
        target: dataModels.valueModel
        onCurrentValueChanged: {
            me.value = currentValue;

        }
    }

    Connections {
        target: dataModels.minValueModel
        onCurrentValueChanged: {
            me.from = currentValue;
        }
    }

    Connections {
        target: dataModels.maxValueModel
        onCurrentValueChanged: {
            me.to = currentValue;
        }
    }
}
