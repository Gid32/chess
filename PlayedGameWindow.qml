import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

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
        text: qsTr("Save Game")
        anchors.top: leaveGameB.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            saveGame();
        }
    }

}
