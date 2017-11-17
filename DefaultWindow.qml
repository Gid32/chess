import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3


Item {

    Button {
        id: startGameB
        text: qsTr("Start Game")
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            startGame();
        }
    }

    Button {
        text: qsTr("Load Game")
        anchors.top: startGameB.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            chessModel.loadLog();
        }
    }


}
