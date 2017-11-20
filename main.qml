import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import ChessLib 1.0



ApplicationWindow {
    visible: true
    width: 640; height: 522;
    minimumHeight: height; maximumHeight: height;
    minimumWidth: width; maximumWidth: width;

    title: qsTr("Chess")

    property int areaBoard: 512

    DefaultWindow {
        id: defaultWindow
    }

    PlayedGameWindow {
        id: playedGameWindow
    }

    Component {
        id: figureDelegate
        Image {
            source: getImageByType(model.figureType,model.figureColor)
            width: 64; height: 64
            x: getPixelCoord(model.coords.x)
            y: getPixelCoord(model.coords.y)

            transform: Rotation {
                origin.x: 64/2; origin.y: 64/2;
                angle: chessModel.player == Figure.Black ? 180 : 0
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(model.figureColor !== chessModel.player)
                        return;
                    chessModel.figure = chessModel.getFigureFromPoint(model.coords);
                    console.log(chessModel.turns);
                }
            }
        }
    }

    Component {
        id: turnDelegate
        Image {
            x: getPixelCoord(modelData.x); y: getPixelCoord(modelData.y)
            source: "qrc:/image/turn"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    chessModel.figure.turn = modelData;
                }
            }
        }
    }


    Item {
        anchors.fill: parent
        anchors.margins: 5
        id: mainItem


        Image {
            id: board
            source: "qrc:/image/board"
            width: areaBoard; height: areaBoard;
            transform: Rotation {
                origin.x: areaBoard/2; origin.y: areaBoard/2;
                angle: chessModel.player == Figure.Black ? 180 : 0
            }

            Repeater {
                id: test
                model: chessModel.data
                delegate: figureDelegate
            }

            Repeater {
                id: turns
                model: chessModel.turns
                delegate: turnDelegate
            }
        }


        StackView {
            id: stackView
            anchors.left: board.right
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 5

        }
    }

    Component.onCompleted: {
        loadDefaultWindow();
    }



    signal startGame()
    signal loadGame()
    signal leaveGame()


    function loadPlayedGameWindow() {
        stackView.clear();
        stackView.push(playedGameWindow);
    }

    function loadDefaultWindow() {
        stackView.clear();
        stackView.push(defaultWindow);
    }


    function getImageByType(type,color) {
        var ret = " ";
        if (color === Figure.Black)
            ret = "Black";
        else
            ret = "White";

        switch(type) {
        case Figure.Pawn:
            return "qrc:/image/Pawn" + ret;
        case Figure.Rook:
            return  "qrc:/image/Rook" + ret;
        case Figure.Knight:
            return  "qrc:/image/Knight" + ret;
        case Figure.Bishop:
            return  "qrc:/image/Bishop" + ret;
        case Figure.Queen:
            return  "qrc:/image/Queen" + ret;
        case Figure.King:
            return  "qrc:/image/King" + ret;
        default:
            return  "qrc:/image/Pawn" + ret;
        }
    }

    function getPixelCoord(logicCoord) {
        return logicCoord*(areaBoard/8);
    }

}
