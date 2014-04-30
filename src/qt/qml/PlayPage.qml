import QtQuick 2.0
import QVBA 0.1
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItems
import Ubuntu.Components.Popups 0.1
Page {
    property string slotAction
    Rectangle {
        anchors {
            top: parent.top
            bottom: buttonBackground.top
        }
        width: parent.width
        color: "black"
        ScreenArea {
            anchors.centerIn: parent
            property int scale : Math.min(parent.width / 240, parent.height / 160)
            width: 241 * scale
            height: 160 * scale
            id: sa
            Connections {
                target: iwindow
                onSDrawScreen: {
                    sa.update()
                }
            }
        }
        Label {
            id: speedLabel
            anchors {
                right: parent.right
                top: parent.top
            }
            visible: topPage.configShowSpeed
            text: "Speed: " + iwindow.speed + "%"
        }
        Label {
            anchors {
                right: parent.right
                top: speedLabel.bottom
            }
            visible: topPage.configShowFrameSkip
            text: "Frame Skip: " + iwindow.frameSkip
        }
    }
    Rectangle {
        id: buttonBackground
        width: parent.width
        height: width * 434 / 725
        anchors.bottom: parent.bottom
//        source: "img/pad.png"
        color: "#4E2865"
        //[startx, starty, endx, endy, key]
        property var keyMap: [
            [0.034, 0.086, 0.28, 0.26, Qt.Key_A], // L
            [0.713, 0.086, 0.971, 0.26, Qt.Key_S], // R
            [0.805, 0.574, 0.943, 0.8, Qt.Key_Z], // A
            [0.674, 0.674, 0.815, 0.883, Qt.Key_X], // B
            [0.516, 0.743, 0.604, 0.882, Qt.Key_Return], //START
            [0.406, 0.743, 0.497, 0.882, Qt.Key_Backspace], //SELECT
            [0.14, 0.4, 0.24, 0.55, Qt.Key_Up],
            [0.07, 0.53, 0.138, 0.72, Qt.Key_Left],
            [0.14, 0.71, 0.23, 0.84, Qt.Key_Down],
            [0.23, 0.54, 0.31, 0.72, Qt.Key_Right]
        ]
        property var lastKeyStatus: [false, false, false, false, false, false, false, false, false, false]
        
        MultiPointTouchArea {
            anchors.fill: parent
            onTouchUpdated: {
                for (var i in buttonBackground.lastKeyStatus) {
                    var pressed = false;
                    for (var j in touchPoints) {
                        if (touchPoints[j].x / width > buttonBackground.keyMap[i][0] &&  touchPoints[j].x / width < buttonBackground.keyMap[i][2] && touchPoints[j].y / height > buttonBackground.keyMap[i][1] && touchPoints[j].y / height < buttonBackground.keyMap[i][3])
                            pressed = true;
                    }
                    if (pressed != buttonBackground.lastKeyStatus[i]) {
                        if (pressed) {
                            iwindow.on_key_press_event(buttonBackground.keyMap[i][4]);
                        } else {
                            iwindow.on_key_release_event(buttonBackground.keyMap[i][4]);
                        }
                        buttonBackground.lastKeyStatus[i] = pressed;
                    }
                }
            }
        }
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                console.log(mouse.x / width + " " + mouse.y / height)
//            }
//        }

        Image {
            source: "./img/LButton.png"
            x: buttonBackground.keyMap[0][0] * parent.width
            y: buttonBackground.keyMap[0][1] * parent.height
            width: (buttonBackground.keyMap[0][2] - buttonBackground.keyMap[0][0]) * parent.width
            height: (buttonBackground.keyMap[0][3] - buttonBackground.keyMap[0][1]) * parent.height
        }
        Image {
            source: "./img/RButton.png"
            x: buttonBackground.keyMap[1][0] * parent.width
            y: buttonBackground.keyMap[1][1] * parent.height
            width: (buttonBackground.keyMap[1][2] - buttonBackground.keyMap[1][0]) * parent.width
            height: (buttonBackground.keyMap[1][3] - buttonBackground.keyMap[1][1]) * parent.height
        }
        Image {
            source: "./img/AButton.png"
            x: buttonBackground.keyMap[2][0] * parent.width
            y: buttonBackground.keyMap[2][1] * parent.height
            width: (buttonBackground.keyMap[2][2] - buttonBackground.keyMap[2][0]) * parent.width
            height: (buttonBackground.keyMap[2][3] - buttonBackground.keyMap[2][1]) * parent.height
        }
        Image {
            source: "./img/BButton.png"
            x: buttonBackground.keyMap[3][0] * parent.width
            y: buttonBackground.keyMap[3][1] * parent.height
            width: (buttonBackground.keyMap[3][2] - buttonBackground.keyMap[3][0]) * parent.width
            height: (buttonBackground.keyMap[3][3] - buttonBackground.keyMap[3][1]) * parent.height
        }
        Image {
            source: "./img/circleButton.png"
            x: buttonBackground.keyMap[4][0] * parent.width
            y: buttonBackground.keyMap[4][1] * parent.height
            width: (buttonBackground.keyMap[4][2] - buttonBackground.keyMap[4][0]) * parent.width
            height: (buttonBackground.keyMap[4][3] - buttonBackground.keyMap[4][1]) * parent.height
        }
        Image {
            source: "./img/circleButton.png"
            x: buttonBackground.keyMap[5][0] * parent.width
            y: buttonBackground.keyMap[5][1] * parent.height
            width: (buttonBackground.keyMap[5][2] - buttonBackground.keyMap[5][0]) * parent.width
            height: (buttonBackground.keyMap[5][3] - buttonBackground.keyMap[5][1]) * parent.height
        }
        Image {
            source: "./img/directionButtons.png"
            x: buttonBackground.keyMap[7][0] * parent.width
            y: buttonBackground.keyMap[6][1] * parent.height
            width: (buttonBackground.keyMap[9][2] - buttonBackground.keyMap[7][0]) * parent.width
            height: (buttonBackground.keyMap[8][3] - buttonBackground.keyMap[6][1]) * parent.height
        }
    }
    tools: ToolbarItems {
        back: ToolbarButton {
            action: Action {
                text: "Close"
                iconSource: "./img/close.svg"
                onTriggered: {
                    pageStack.pop();
                    iwindow.vOnFileClose();
                }
            }
        }
        ToolbarButton {
            action: Action {
                text: iwindow.paused ? "Resume" : "Pause"
                iconSource: iwindow.paused ? "./img/media-playback-start.svg" : "./img/media-playback-pause.svg"
                onTriggered: {
                    iwindow.paused = !iwindow.paused;
                }
            }
        }
        ToolbarButton {
            action: Action {
                text: "Save Slot"
                iconSource: "./img/save.svg"
                onTriggered: {
                    slotAction = "save";
                    PopupUtils.open(slotSheet)
                }
            }
        }
        ToolbarButton {
            action: Action {
                text: "Load Slot"
                iconSource: "./img/keyboard-caps.svg"
                onTriggered: {
                    slotAction = "load";
                    PopupUtils.open(slotSheet)
                }
            }
        }
    }
    Component {
        id: slotSheet
        DefaultSheet {
            id: sheet
            title: "Default sheet with done button"
            doneButton: false
            ListView {
                anchors.fill: parent
                model: iwindow.gameSlot
                delegate: ListItems.Standard {
                    text: model.isEmpty ? model.time : "<font color='purple'>" + model.time + "</font>"
                    onClicked: {
                        if (slotAction === "save") {
                            iwindow.vOnSaveGame(model.index + 1);
                        } else if (slotAction === "load") {
                            iwindow.vOnLoadGame(model.index + 1);
                        }
                        PopupUtils.close(sheet);
                    }
                }
            }
        }
    }
}
