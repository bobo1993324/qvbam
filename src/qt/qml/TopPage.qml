import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
Tabs {
    id: tabs
    property alias configShowSpeed: showSpeedSwitch.checked
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
                        onCheckedChanged: {
                            iwindow.config.mute = !checked
                        }
                    }
                }
                ListItem.Standard {
                    text: "Show speed"
                    control: Switch {
                        id: showSpeedSwitch
                        checked: true
                    }
                }
            }
        }
    }
}
