import QtQuick 2.0
import QtMultimedia 5.7
import QtQuick.Controls 1.4

Rectangle {
    id:currentListRectangle
    color: "red"
    anchors.right: parent.right
    anchors.bottom: bottomArea.top
    visible: true
    width: 300
    height: 500
    ListView {
        anchors.fill: parent
        model: currentPlaylist
        delegate:Rectangle{
            height: 30
            width: parent.width
            color: currentListRectangle.color
            Text {
                text: client.songInformation(source)
            }
            MouseArea {
                anchors.fill: parent
                onClicked:
                    currentPlaylist.currentIndex = index
            }
        }
    }
}