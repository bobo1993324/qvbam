import QtQuick 2.0
import QVBA 0.1
import Ubuntu.Components 0.1
Page {
    Rectangle {
        anchors {
            top: parent.top
            bottom: buttonBackground.top
        }
        width: parent.width
        color: "black"
        ScreenArea {
            anchors.centerIn: parent
            width: 480
            height: 320
            id: sa
            Connections {
                target: iwindow
                onSDrawScreen: {
                    sa.update()
                }
            }
        }
    }
    Image {
        id: buttonBackground
        width: parent.width
        height: width * 434 / 725
        anchors.bottom: parent.bottom
        source: "img/pad.png"
        //[startx, starty, endx, endy, key]
        property var keyMap: [
            [0.034, 0.086, 0.28, 0.26, Qt.Key_A], // L
            [0.713, 0.086, 0.971, 0.26, Qt.Key_S], // R
            [0.805, 0.574, 0.943, 0.8, Qt.Key_Z], // A
            [0.674, 0.674, 0.815, 0.883, Qt.Key_X], // B
            [0.516, 0.743, 0.604, 0.882, Qt.Key_Return], //START
            [0.406, 0.743, 0.497, 0.882, Qt.Key_Backspace], //SELECT
            [0.125, 0.512, 0.214, 0.626, Qt.Key_Up],
            [0.065, 0.617, 0.128, 0.778, Qt.Key_Left],
            [0.128, 0.765, 0.211, 0.883, Qt.Key_Down],
            [0.214, 0.630, 0.279, 0.774, Qt.Key_Right]
        ]
        property var lastKey;
        MouseArea {
            anchors.fill: parent
            onPressed: {
                var xratio = mouse.x / width;
                var yratio = mouse.y / height;
                for (var i in buttonBackground.keyMap) {
                    if (xratio > buttonBackground.keyMap[i][0] && xratio < buttonBackground.keyMap[i][2]
                            && yratio > buttonBackground.keyMap[i][1] && yratio < buttonBackground.keyMap[i][3]) {
                        iwindow.on_key_press_event(buttonBackground.keyMap[i][4]);
                        buttonBackground.lastKey = buttonBackground.keyMap[i][4];
                    }
                }
            }
            onReleased: {
                iwindow.on_key_release_event(buttonBackground.lastKey);
            }
        }
    }

}
