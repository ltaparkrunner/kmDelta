import QtQuick 2.0
import QtQuick.Dialogs 1.1

MessageDialog {
    id: messageDialog
    title: "May I have your attention, please?"
    text: "Forever"
    onAccepted: {
        console.log("And of course ...")
        Qt.quit()
    }
    Component.onCompleted: visible = true
}
