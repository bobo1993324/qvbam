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
                        pageStack.push(playPage);
                    }
                }
            }
        }
    }

    Tab {
        id: settingTab
        title: "Settings"
        page: Page {
            Column {
                width: parent.width
                ListItem.Standard {
                    text: "Enable Sound"
                    control: Switch {
                        id: enableSoundSwitch
                        checked: true
                    }
                }
            }
        }
    }
}
