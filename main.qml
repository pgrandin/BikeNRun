import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Bike n Run Tracker")

    GridView {
        id: gridView
        y: 0
        anchors.topMargin: 64
        anchors.fill: parent
        model: bikenrun.teams
        delegate: Item {
            x: 5
            height: 50
            Column {
                Rectangle{
                    color: current_lap == 0 ? "white" : (current_lap == target_laps ? "green" : "orange" )
                    border.width: 1

                    border.color: "#ff0000"
                    width: 150
                    height: width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        x: 5
                        text: dossard
                        font.bold: true
                        font.pixelSize: 76
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width

                    }
                    Text {
                        x: 100
                        y: 100
                        text: laps_as_string
                        font.bold: true
                        font.pixelSize: 24
                    }
                    MouseArea {
                        id: mouse_area1
                        z: 1
                        hoverEnabled: false
                        anchors.fill: parent

                        onClicked:{
                            bikenrun.recordLap(index)
                        }
                    }
                }

                spacing: 5
            }
        }
        cellHeight: 160
        cellWidth: 160
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectExisting: true
        onAccepted: {
            bikenrun.handleOpenCSV(fileDialog.fileUrls[0])
            console.log("You chose: " + fileDialog.fileUrls)
            // window.showFullScreen()
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }


    Timer {
        interval: 500; running: false; repeat: true
        id: timer1
        onTriggered: time.text = bikenrun.getElapsedTime()
    }

    Text {
        id: time
        x: 551
        y: 0
        width: 79
        height: 64
        text: qsTr("--:--")
        anchors.right: parent.right
        anchors.rightMargin: 50
        font.pixelSize: 48
    }
    Rectangle {
        id: rectangle
        x: 48
        y: 4
        height: 56
        width: 256
        color: "green"
        border.color: "black"
        border.width: 1
        radius: 10
        Text {
            id: text1
            text: qsTr("START")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 48
        }
        MouseArea {
            id: mouse_area2
            z: 1
            hoverEnabled: false
            anchors.fill: parent

            onClicked:{
                if(timer1.running == false && text1.text == "START") {
                    bikenrun.startTimer()
                    timer1.running=true
                    rectangle.color="red"
                    text1.text="STOP"
                } else {
                    timer1.running=false
                    rectangle.color="orange"
                    text1.text="DONE"
                    saveFileDialog.visible=true
                }
            }
        }
    }
    FileDialog {
        id: saveFileDialog
        title: "Please choose a file to save"
        folder: shortcuts.home
        selectExisting: false
        onAccepted: {
            bikenrun.stopTimer(saveFileDialog.fileUrls[0])
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }
}
