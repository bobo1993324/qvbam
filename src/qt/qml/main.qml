import QtQuick 2.0
import QVBA 0.1
Rectangle {
    width: 240
    height: 160
    color: "black"
    ScreenArea {
        id: sa
        anchors.fill: parent
        Connections {
            target: window
            onSDrawScreen: sa.update()
        }
    }
}
