import QtQuick 2.0
import QVBA 0.1
import Ubuntu.Components 0.1
MainView {
    width: units.gu(48)
    height: units.gu(70)
    backgroundColor: "#4E2865"
    PageStack {
        id: pageStack
        Component.onCompleted: {
            push(topPage)
        }
    }

    PlayPage {
        id: playPage
        visible: false
    }
    TopPage{
        id: topPage
        visible: false
    }
}
