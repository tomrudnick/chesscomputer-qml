function createChessBoard(boardGrid) {
    var rectangles = [];
    for(var i = 0; i < 64; i++) {
        console.log("Create component: " + i);
        var component = Qt.createComponent("chessRectangle.qml");
        if(component.status === Component.Ready) {
            var chessRectangleColor = null;
            if(Math.ceil((i + 1) / 8) % 2 == 0) {
                chessRectangleColor = (i + 1) % 2 == 0 ? "white" : "brown"
            } else {
                chessRectangleColor = (i + 1) % 2 == 0 ? "brown" : "white"
            }
            var obj = component.createObject(boardGrid, {"chessIndex": i, "chessRectangleColor" : chessRectangleColor, "z" : 1});
            rectangles.push(obj);
        }
    }
    return rectangles;
    //createChessPieces(boardGrid);
}

function createChessPieces(boardGrid) {

    var dict = {
      '-1' : "black_pawn",
      '-2' : "black_knight",
      '-3' : "black_bishop",
      '-4' : "black_rook",
      '-5' : "black_queen",
      '-6' : "black_king",
      '1' : "white_pawn",
      '2' : "white_knight",
      '3' : "white_bishop",
      '4' : "white_rook",
      '5' : "white_queen",
      '6' : "white_king",
    };

    var chessBoardArr = [-4, -2, -3, -5, -6, -3, -2, -4,
                         -1, -1, -1, -1, -1, -1, -1, -1,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         1, 1, 1, 1, 1, 1, 1, 1,
                         4, 2, 3, 5, 6, 3, 2, 4
                        ]

    console.log("Create Chess Piece")

    for(var i = 0; i < 64; i++) {
        if(chessBoardArr[i] !== 0) {
            var component = Qt.createComponent("chessPiece.qml");
            var chessPieceImg = "images/alpha/" + dict[chessBoardArr[i]];
            if(component.status === Component.Ready) {
                component.createObject(boardGrid, {"z": 5, "currentField" : boardGrid.children[i], "chessPieceImg" : chessPieceImg, "pieceNumber" : chessBoardArr[i]});
            }
        }
    }
    chesscom.chessPiecesCreated();
}


function toChessMove(start, end) {
    var chessColumns = ["A", "B", "C", "D", "E", "F", "G", "H"];
    var xAxisStart = chessColumns[start % 8]
    var yAxisStart = Math.floor((64 - start) / 8) + 1
    var xAxisEnd = chessColumns[end % 8]
    var yAxisEnd = Math.floor((64 - end) / 8) + 1
    console.log("" + xAxisStart + "" + yAxisStart + "-" + xAxisEnd + "" + yAxisEnd);
}
