import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
Page {
    title: "Settings"
    Column {
        width: parent.width
        //sound doesn't work yet
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
                checked: settings.configShowSpeed
                onCheckedChanged: {
                    settings.configShowSpeed = checked;
                }
            }
        }
        ListItem.Standard {
            text: "Show frame skip"
            control: Switch {
                checked: settings.configShowFrameSkip
                onCheckedChanged: {
                    settings.configShowFrameSkip = checked;
                }
            }
        }
    }
}
