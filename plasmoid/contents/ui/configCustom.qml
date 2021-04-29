import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import org.kde.kirigami 2.9 as Kirigami
import Qt.labs.platform 1.1


Item {
    
    ColorAnimation {
        from: "white"
        to: "black"
        duration: 200
        //property:
    }
    Kirigami.FormLayout {
        Repeater{
            id:repeat
            delegate: Row{
                Kirigami.FormData.label: modelData+":"
                bottomPadding: 10
                TextField {
                    width: 500
                    text: settings.value(modelData)
                    onTextChanged: settings.setValue(modelData,text);
                }}
        }
    }

    Component.onCompleted:{
        var xhr = new XMLHttpRequest;
        xhr.open("GET", StandardPaths.locate(StandardPaths.ConfigLocation,"AwesomeMonitor",StandardPaths.LocateFile).toString().substring(7));
        console.log("dasd",StandardPaths.locate(StandardPaths.ConfigLocation,"AwesomeMonitor",StandardPaths.LocateFile).toString().substring(7))
        xhr.onreadystatechange = function() {
            console.log("asdas",xhr.readyState)
            if (xhr.readyState === XMLHttpRequest.DONE) {
                var response = xhr.responseText;
                var regex = /\[.*\]/
                var splitted = xhr.responseText.split(/\[.*\]/).filter(value=> value !== "");
                var categories = xhr.responseText.match(/\[.*\]/g);
                console.log(splitted,categories)
                var index = 0;
                for(index;index<categories.length;index++){
                    if(categories[index].includes("Custom")) break;
                }

                var categoryLines = splitted[index].split(/\r?\n/).filter(line => line !== "").map(line => line.match(/.*=/)[0].slice(0,-1));
                repeat.model = categoryLines;
                for(var s in categoryLines){
                    console.log(settings.value(categoryLines[s],s));
                }
                console.log(categoryLines);
            }
        };
        xhr.send();}
}
