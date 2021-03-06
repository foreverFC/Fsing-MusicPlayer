import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    width: 270
    height: parent.height
    anchors.left: bottomLeftButton.right
    anchors.right: bottomRightButton.left
    color: parent.color

    Text {
        id: totalTime
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: change(mediaPlayer.duration)
    }
    Text {
        id: currentTime
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: change(mediaPlayer.position)
    }
    Slider {
        id: positionSlider
        anchors.left: currentTime.right
        anchors.right: totalTime.left
        anchors.verticalCenter: parent.verticalCenter
        from: 0.0
        to: 1.0
        value: mediaPlayer.position / mediaPlayer.duration

        handle: Rectangle {
            id: handleRectangle
            visible: true
            x: positionSlider.value * (positionSlider.width - positionSlider.leftPadding
                                       - positionSlider.rightPadding)
            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            implicitWidth: 14
            implicitHeight: 14
            radius: 13
            border.width: 1
            border.color: "#E1E1E2"
            Rectangle {
                width: 4
                height: 4
                color: "red"
                radius: 13
                anchors.centerIn: parent
            }
        }
        Rectangle {
            anchors.left: positionSlider.left
            anchors.leftMargin: positionSlider.leftPadding
            anchors.right: handleRectangle.left
            anchors.rightMargin: positionSlider.rightPadding

            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            radius: 13
            height: 4
            color: "red"
        }
        MouseArea{
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton;
            onReleased: {
                mediaPlayer.seek(Math.round(mouse.x / parent.width * mediaPlayer.duration));
            }
            onWheel: wheel.accepted = true;

        }
    }
    function change(value){
        var s = Math.round(value / 1000);
        var m = Math.round(s / 60);
        s = s % 60;
        var mm = "0" + m;
        if(m > 9)
            mm = "%1".arg(m);
        var ss = "0" + s;
        if(s > 9)
            ss = "%1".arg(s);
        return mm + ":" + ss;
    }
}
