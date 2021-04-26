import QtQuick 2.0

DropArea {

    property var chessIndex: 0
    property var chessRectangleColor : "white"

    id: dropZone
    width: 80
    height: 80
    z: 1

    Drag.keys: ["chessRectangle"]


    Rectangle {
        id: dropRectangle
        color: chessRectangleColor

        anchors.fill: parent

        Text {
            text: chessIndex
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
        }

        states: [
            State {
                when: dropZone.containsDrag
                PropertyChanges {
                    target: dropRectangle
                    color: "grey"
                }
            }
        ]
    }
}



