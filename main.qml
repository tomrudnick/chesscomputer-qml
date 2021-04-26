import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import "chessFunctions.js" as ChessFunctions

Window {

    id: root
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")


    Column {
        id: chessRowIndex
        spacing: 1
        //anchors.leftMargin: 10
        Repeater {
            model: 8

            Rectangle {
                width: 32
                height: 80

                Text {
                    text: getIndex(index)
                    anchors.centerIn: parent
                    font.pixelSize: 20
                }

                function getIndex(index) {
                    var chessRows = ["8", "7", "6", "5", "4", "3", "2", "1"];
                    return chessRows[index];
                }


            }
        }
    }

    Rectangle {
        z : 1
        id: board
        property var borderWidth: 5
        border.color: "brown"
        border.width: borderWidth
        width: 80 * 8 + borderWidth * 2
        height : 80 * 8 + borderWidth * 2
        anchors.left: chessRowIndex.right
        Grid {
            property var rectangles: []
            id: boardGrid
            rows: 8
            columns: 8
            anchors.centerIn: parent
            Component.onCompleted: {
                rectangles = ChessFunctions.createChessBoard(boardGrid);
                console.log(rectangles.length);
                ChessFunctions.createChessPieces(boardGrid);
            }
        }


        Row {
            anchors.top: board.bottom
            Repeater {
                model: 8

                Rectangle {
                    width: 80
                    height: 32

                    Text {
                        text: getText(index)
                        anchors.centerIn: parent
                        font.pixelSize: 20
                    }
                    function getText(index) {
                        console.log(index)
                        var chessColumns = ["A", "B", "C", "D", "E", "F", "G", "H"];
                        return chessColumns[index];
                    }
                }
            }
        }

    }

    Column {
        anchors.left: board.right
        Button {
            text: "undo"
            onClicked: chesscom.undo()
        }
    }




}
