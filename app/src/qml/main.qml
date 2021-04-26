import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0

// Load our plugin from filesystem
import my.plugin.example 1.0
import Qaterial 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Lyzer"
    IconDescription {
        id: iconDes
        width: 400
        height: 100
        color: "red"
    }

    // 'myplugin' C++ class
    MyQuickItem {
        id: pluginItem
        color: iconDes.color
        width: 100
        height: 50
        anchors.centerIn: parent
    }

    Loader {
        id: loader
        source: Qt.resolvedUrl("qrc:/plugin/MyQml.qml")
    }

    Connections {
        target: loader.item
        enabled: loader.status === Loader.Ready
        function onClicked() { MyScript.onClicked(pluginItem) }
    }
}
