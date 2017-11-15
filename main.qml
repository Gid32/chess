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
            source: getImageByType(model.figureType,model.figureColor)
            width: 64
            height: 64
            x: getCoordX(model.coords.x)
            y: getCoordY(model.coords.y)
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(mainItem.clickFigure)
                        mainItem.clickFigure.vis = false;
                    mainItem.clickFigure = img;
                    vis = true;
                    //model.coords.x = 1;
                }
            }
            property var testM: model.listPosibleTurns
            property var fig: model
            Repeater {
                model: fig.listPosibleTurns
                delegate: Image{
                    x: getCoordX(modelData.x) - img.x
                    y: getCoordY(modelData.y) - img.y
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


    function getImageByType(type,color) {
        var ret = " ";

        if (color === Figure.Black) ret = "Black";
        else ret = "White";

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

    function getCoordX(x) {
        return x*(areaBoard/8);//+4;
    }

    function getCoordY(y) {
        return y*(areaBoard/8);//+4;
    }

}
