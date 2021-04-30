import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0

// Load our plugin from filesystem
import my.plugin.example 1.0
import Qaterial 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Playground"

    GridLayout {
        anchors.fill: parent
        columns: 3

        Text {
            text: Version.readable
        }

//        IconDescription {
//            id: iconDes
//            cache: false
//            source: "qrc:/qt.png"
//            width: 40
//            height: 40
//            color: "red"
//        }

        IconLabelImpl {
            width: 64
            height: width
            iconItem: Image {
                source: "qrc:/qt.png"
            }
        }

        // 'myplugin' C++ class
        MyQuickItem {
            id: pluginItem
//            color: iconDes.color
            width: 100
            height: 50
        }

        MyQml {
            id: myQml
            onClicked: {
                Clipboard.clear()
                MyScript.onClicked(pluginItem)
            }
        }


        Text {
            color: "black"
            text: Clipboard.text ? Clipboard.text : "empty"
        }
    }
    //    Loader {
    //        id: loader
    //        source: Qt.resolvedUrl("qrc:/plugin/MyQml.qml")
    //    }

    //    Connections {
    //        target: loader.item
    //        enabled: loader.status === Loader.Ready
    //        function onClicked() { MyScript.onClicked(pluginItem) }
    //    }
}
