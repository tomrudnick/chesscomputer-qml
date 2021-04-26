import QtQuick 2.15

import "chessFunctions.js" as ChessFunctions

Item {

    property var id: -1
    property var currentField : null
    property var lastField : null
    property var moveCheck : false
    property alias chessPieceImg : chessPiece.source

    property var pieceWidth : 64
    property var pieceHeight : 64
    property alias pieceNumber : mouseArea.pieceNumber


    Connections {
        target: chesscom
        function onRemovePiece(index, _id) {
            //console.log("I will remove myself: " + index + " my Index: " + currentField.chessIndex);
            if(index === currentField.chessIndex && moveCheck === false && id === _id) {
                console.log("I will remove myself");
                root.visible = false;
                mouseArea.visible = false;
                chessPiece.visible = false;
            }
        }

        function onMoveOk(ok) {
            if(moveCheck === true) {
                console.log("Check if I made a valid move");
                if(ok === false) {
                    mouseArea.parent = lastField;
                    currentField = lastField;
                }
                moveCheck = false;
            }
        }

        function onUiMove(newPos, _id) {
            if(moveCheck === false && id === _id) {
                lastField = currentField
                currentField = boardGrid.rectangles[newPos];
                mouseArea.parent = currentField;
                //If piece is invisble but should move it's probably back alive lol
                if(chessPiece.visible === false) {
                    root.visible = true;
                    chessPiece.visible = true;
                    mouseArea.visible = true;
                }
            }
        }

        function onSetID(newId, rectangle) {
            if(currentField.chessIndex === rectangle) {
                console.log("Setting ID: " + newId);
                id = newId;
            }
        }
    }

    id: root
    width: pieceWidth
    height: pieceHeight

    MouseArea {
        property var pieceNumber
        id: mouseArea
        objectName: "singleChessPiece"
        width: pieceWidth - 20
        height: pieceHeight - 20
        anchors.centerIn: parent



        drag.target: chessPiece;
        Drag.hotSpot.x: width / 2;
        Drag.hotSpot.y: height / 2;

        onReleased: {
            chessPiece.opacity = 1.0
            if(chessPiece.Drag.target === null) {
                if(currentField === null)
                    parent = root
                else
                    parent = currentField
            } else {
                lastField = currentField
                currentField = chessPiece.Drag.target
                parent = currentField
            }


            if(lastField !== null && currentField !== null && lastField !== currentField) {
                moveCheck = true;
                ChessFunctions.toChessMove(lastField.chessIndex, currentField.chessIndex);
                chesscom.moveByUI(lastField.chessIndex, currentField.chessIndex);
            }
        }

        onPressed: {
            chessPiece.opacity = 0.8;
        }


        Component.onCompleted: parent = currentField !== null ? currentField : root;


        Image {
            id: chessPiece
            width: pieceWidth
            height: pieceHeight

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            opacity: 1.0
            mipmap: true
            Drag.keys: ["chessRectangle"]
            Drag.active: mouseArea.drag.active

            states: State {
                when: mouseArea.drag.active
                ParentChange { target: chessPiece; parent: root }
                AnchorChanges {
                    target: chessPiece;
                    anchors.verticalCenter: undefined;
                    anchors.horizontalCenter: undefined
                }
            }
        }
    }
}
