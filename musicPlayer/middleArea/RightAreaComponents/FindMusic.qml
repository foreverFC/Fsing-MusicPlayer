import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.2
import  "../../songList"

Rectangle {
    property int index: 0
    property var interfaceParamter : client.getinterface()

    Connections {
        target: mainWindow
        onLeftButtonPressed:{
            findMusicstackView.pop(findMusicPage)
        listmodel1.clear()
        }
    }

    StackView {
        id: findMusicstackView
        anchors.fill: parent
        visible: true
        initialItem: findMusicPage
        Component {
            id: findMusicPage
            ColumnLayout{
                id: layout
                spacing: 6
                RowLayout{

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(50)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[6]
                            songlistId: interfaceParamter[0]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(60)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[16]
                            songlistId: interfaceParamter[10]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(70)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[26]
                            songlistId: interfaceParamter[20]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(80)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[36]
                            songlistId: interfaceParamter[30]
                        }
                    }
                }
                RowLayout{

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(50)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[46]
                            songlistId: interfaceParamter[40]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(60)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[56]
                            songlistId: interfaceParamter[50]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(70)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[66]
                            songlistId: interfaceParamter[60]
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.minimumWidth: 200
                        Layout.maximumHeight: 300
                        Layout.maximumWidth: 300
                        Layout.minimumHeight: 200
                        SongListRectangle{
                            playQuantity: String(80)
                            source: "file:///"+applicationDirPath + "/" + interfaceParamter[76]
                            songlistId: interfaceParamter[70]
                        }
                    }
                }
            }
        }
        Component {
            id:songListPage
            SongList {
                id: songlist
                width: parent.width
                height: parent.height
                model: listmodel1
                userImg: "qrc:/images/logo.jpg"
                username: "zhy"
                createTime: "2018-09-01"
                Component.onCompleted: {
                    var songListInformation = client.getSongListInformation()
                    console.log(songListInformation)
                    listname = songListInformation[1]
                    listImg = "file:///"+applicationDirPath + "/" + songListInformation[6]
                    label = songListInformation[4]
                    briefInfo = songListInformation[5]
                    username = songListInformation[2]

            }
            }
        }
    }

    ListModel {
        id:listmodel1
    }

    function appendSong(){
        var list = client.getSongList()
        var count = client.getSongListCount()
        for(var i = 0;i< count;++i){

        listmodel1.append(
            {
                     "album" : list[i*8 +3],
                     "id" : list[i*8],
                     "name" : list[i*8 +1],
                     "playQuantity" : list[i*8 +5],
                     "singer" : list[i*8 +2],
                     "source" : list[i*8 +4]
             }

            )
        }
    }
}




