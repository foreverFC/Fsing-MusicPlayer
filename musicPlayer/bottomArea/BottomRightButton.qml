import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8

Rectangle {
    width: 290
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    color: parent.color

    Button {
        id: songlistButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: songlistButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(currentListRectangle.visible)
                    currentListRectangle.visible = false
                else
                    currentListRectangle.visible = true
            }
        }

        background: Image {
            id:songlistButtonImage
            anchors.fill: parent
            opacity: songlistButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/songlist.png"
        }
    }
    Button {
        id: liricButton
        anchors.right: songlistButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: liricButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:liricButtonnImage
            anchors.fill: parent
            opacity: liricButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/liric.png"
        }
    }

    Button {
        id: orderButton
        anchors.right: liricButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        property int index: 0
        state: "sequence"
        states: [
            State {
                name: "sequence"
                PropertyChanges { target: orderButtonImage
                          source: "qrc:/images/bottomArea/sequence.png" }
            },
            State {
                name: "circle"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/circle.png" }
            },
            State {
                name: "single"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/single.png" }
            },
            State {
                name: "random"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/random.png" }
            }
        ]
        MouseArea{
            id: orderButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                console.log(parent.state)
                if(parent.state === "sequence"){
                    parent.state = "circle"
                    currentPlaylist.playbackMode = Playlist.Loop
                }else if(parent.state === "circle"){
                   parent.state = "single"
                    currentPlaylist.playbackMode = Playlist.CurrentItemInLoop
                }else if(parent.state === "single"){
                    parent.state = "random"
                    currentPlaylist.playbackMode = Playlist.Random
                }else if(parent.state === "random"){
                    parent.state = "sequence"
                    currentPlaylist.playbackMode = Playlist.CurrentItemOnce
                }
            }
        }
        background: Image {
            id:orderButtonImage
            anchors.fill: parent
            opacity: orderButtonMouseArea.containsMouse ? 1.0 : 0.5
        }
    }
    Slider{
        id: voiceSlider
        anchors.right: orderButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 120;
        from:0.0
        to:1.0
        value: mediaPlayer.volume
        onValueChanged: mediaPlayer.volume = value

        handle: Rectangle {
            id:handleRectangle
            visible: sliderMouseArea.containsMouse ? true : false
            x: voiceSlider.value * (voiceSlider.width - voiceSlider.leftPadding
            - voiceSlider.rightPadding)
            y: voiceSlider.topPadding + voiceSlider.availableHeight / 2 - height / 2
            implicitWidth: 14
            implicitHeight: 14
            radius: 13
            border.width: 1;
            border.color: "#E1E1E2";
            Rectangle{
                width: 4;
                height: 4;
                color: "red";
                radius: 13;
                anchors.centerIn: parent;
            }
        }
        Rectangle {
            anchors.left: voiceSlider.left
            anchors.leftMargin: voiceSlider.leftPadding
            anchors.right: handleRectangle.left
            anchors.rightMargin: voiceSlider.rightPadding
            y: voiceSlider.topPadding + voiceSlider.availableHeight / 2 - height / 2
            radius: 13
            height: 4
            color: "red"
        }
        MouseArea{
            id:sliderMouseArea
            anchors.fill: parent;
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: mouse.accepted = false

            acceptedButtons: Qt.LeftButton;
            onReleased: {
                mediaPlayer.volume = (mouse.x  / voiceSlider.width);
            }
            onWheel: wheel.accepted = true;

        }
    }

    Button {
        id: voiceButton
        anchors.right: voiceSlider.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: voiceButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: mediaPlayer.muted ? mediaPlayer.muted = false :
                                     mediaPlayer.muted = true
        }

        background: Image {
            id:voiceButtonImage
            anchors.fill: parent
            opacity: voiceButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/voice.png"
        }
    }
}
