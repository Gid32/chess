import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import cpp 1.0



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
            property bool vis: false
            id: img
            source: getImageByType(model.figureType)
            width: 50
            height: 50
            x: getCoordX(model.coords.x)
            y: getCoordY(model.coords.y)
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(mainItem.clickFigure)
                        mainItem.clickFigure.vis = false;
                    mainItem.clickFigure = img;
                    vis = true;
                    model.coords.x = 1;
                }
            }
            property var testM: model.listPosibleTurns
            property var fig: model
            Repeater {
                model: fig.listPosibleTurns
                delegate: Image{
                    x: getCoordTurnX(modelData.x) - img.x
                    y: getCoordTurnY(modelData.y) - img.y
                    source: "qrc:/image/turn"
                    visible: img.vis
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            fig.coords = modelData;
                        }
                    }
                }
            }
        }
    }


    Item {
        anchors.fill: parent
        anchors.margins: 5
        id: mainItem
        property var clickFigure

        Image {
            id: board
            source: "qrc:/image/board"
            width: areaBoard; height: areaBoard;

            Repeater {
                model: chessModel.data
                delegate: figureDelegate
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
    signal saveGame()
    signal leaveGame()

    function loadPlayedGameWindow() {
        stackView.clear();
        stackView.push(playedGameWindow);
    }

    function loadDefaultWindow() {
        stackView.clear();
        stackView.push(defaultWindow);
    }


    function getImageByType(type) {
        switch(type) {
        case Figure.BlackBishop:
            return "qrc:/image/blackBishop";
        case Figure.WhiteBishop:
            return "qrc:/image/whiteBishop";
        case Figure.BlackPawn:
            return "qrc:/image/blackPawn";
        case Figure.WhitePawn:
            return "qrc:/image/whitePawn";
        case Figure.BlackKing:
            return "qrc:/image/blackKing";
        case Figure.WhiteKing:
            return "qrc:/image/whiteKing";
        case Figure.BlackKnight:
            return "qrc:/image/blackKnight";
        case Figure.WhiteKnight:
            return "qrc:/image/whiteKnight";
        case Figure.BlackQueen:
            return "qrc:/image/blackQueen";
        case Figure.WhiteQueen:
            return "qrc:/image/whiteQueen";
        case Figure.BlackRook:
            return "qrc:/image/blackRook";
        case Figure.WhiteRook:
            return "qrc:/image/whiteRook";
        default:
            return "qrc:/image/blackBishop";
        }
    }

    function getCoordX(x) {
        return x*(areaBoard/8)+4;
    }

    function getCoordY(y) {
        return y*(areaBoard/8)+4;
    }

    function getCoordTurnX(x) {
        return x*(areaBoard/8)-4;
    }

    function getCoordTurnY(y) {
        return y*(areaBoard/8)-4;
    }

}
