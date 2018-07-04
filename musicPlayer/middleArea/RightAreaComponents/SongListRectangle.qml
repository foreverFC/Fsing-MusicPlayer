import QtQuick 2.0

Rectangle {
    anchors.fill: parent;
    property alias source: backImage.source
    property alias playQuantity: playQuantityText.text
    Image {
        id: backImage
        width: 200
        height: 200
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectCrop
        source: "file:///"+applicationDirPath + "/file.jpg"
    }
    Rectangle {
        id:playQuantityRectangle
        x: 370
        anchors.top:backImage.top
        anchors.right: backImage.right
        width:  backImage.height * 0.1
        height:backImage.width * 0.4
        anchors.rightMargin: 30
        anchors.topMargin: -30
        color: parent.color
        rotation:90
        visible:!mouseArea.containsMouse
        gradient: Gradient {
            GradientStop{
                position: 0.0;
                color: Qt.rgba(0,0,0,0.7);

            }
            GradientStop{
                position: 1.0;
                color: Qt.rgba(0,0,0,0);
            }
        }
        Text {
            id: playQuantityText
            x: -5
            color: "#ffffff"
            anchors.top:playQuantityRectangle.top
            anchors.right: playQuantityRectangle.right
            text: qsTr("100")
            anchors.rightMargin: -10
            anchors.topMargin: 28
            rotation: -90
            font.bold: true
            font.pointSize: 16
        }
    }
    MouseArea {
        id:mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            //-----------
        }

    }
    Image {
        id: playImage
        width: 30
        height: 30
        visible: mouseArea.containsMouse
        anchors.bottom: backImage.bottom
        anchors.right: backImage.right
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        source: "../../images/middleArea/play.png"
    }


}