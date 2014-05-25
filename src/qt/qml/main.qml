import QtQuick 2.0
import QVBA 0.1
import Ubuntu.Components 0.1
MainView {
    width: units.gu(48)
    height: units.gu(70)
    backgroundColor: "#4E2865"
    automaticOrientation: true
    PageStack {
        id: pageStack
        Component.onCompleted: {
            push(Qt.resolvedUrl("TopPage.qml"))
        }
    }

    Settings {
        id: settings
    }

    PlayPage {
        id: playPage
        visible: false
    }
    focus: true
    Keys.onPressed: {
        iwindow.on_key_press_event(event.key);
    }
    Keys.onReleased: {
        iwindow.on_key_release_event(event.key);
    }
    Connections {
        target: Qt.application
        onActiveChanged: {
            if (Qt.application.active) {
                iwindow.paused = false;
            } else {
                iwindow.paused = true;
            }
        }
    }
}
