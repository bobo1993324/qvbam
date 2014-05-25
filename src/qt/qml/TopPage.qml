import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
Tabs {
    id: tabs
    Tab {
        id: romTab
        title: "Load Roms"
        page: Page {
            ListView {
                anchors.fill: parent
                model: romsModel.files
                delegate: ListItem.Standard {
                    text: model.modelData
                    onClicked: {
                        iwindow.bLoadRomInQML(model.modelData)
                        pageStack.push(Qt.resolvedUrl("PlayPage.qml"));
                    }
                }
            }
            Label {
                visible: romsModel.files.length == 0
                anchors.bottom: parent.bottom
                text: "Put rom file in ~/.local/share/com.ubuntu.developer\n.bobo1993324.qvbam/roms/"
                wrapMode: TextEdit.WordWrap
            }
        }
    }

    Tab {
        id: settingTab
        title: "Settings"
        page: SettingPage {

        }
    }
}
