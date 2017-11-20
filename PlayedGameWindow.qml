import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import ChessLib 1.0

Item {
    Button {
        id: leaveGameB
        text: qsTr("Leave Game")
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            leaveGame();
        }
    }

    Button {
        id: saveGameB
        text: qsTr("Save Game")
        anchors.top: leaveGameB.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            chessModel.saveLog();
        }
    }

    Label {
        id: turnUser
        anchors.top: saveGameB.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text:chessModel.player === Figure.Black ? "Turn black" : "Turn white"
    }

    ListView {
        anchors.top: turnUser.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: chessModel.log
        delegate:
            Label {
                text: index+1 + ") " + chessModel.log[index]
            }
    }

}
