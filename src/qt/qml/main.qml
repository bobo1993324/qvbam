import QtQuick 2.0
import QVBA 0.1
import Ubuntu.Components 0.1
MainView {
    width: units.gu(48)
    height: units.gu(70)
    PageStack {
        id: pageStack
        PlayPage {
            id: playPage
        }
        Component.onCompleted: push(playPage)
    }
}
