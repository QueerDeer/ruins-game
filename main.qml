import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 360
    height: 640
    title: qsTr("Ruin")

    signal qmlChangeField(string msg, string pos)
    signal qmlGenerateField()
    signal qmlStartEngine()
    signal qmlCreateSoldier(string pos)
    signal qmlChangeAnimation(string name, string anim, string pos, string idshka)

    SwipeView {
        id: swipeView
        anchors.fill: parent
        orientation: Qt.Vertical
        interactive:false
        currentIndex: 0

        Page {
            contentHeight: 640
            contentWidth: 720
            Item {
                anchors.centerIn: parent

                Image {
                    id: menush
                    z: 0
                    width: 216
                    height: 263
                    source: "/menu.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                ColumnLayout {
                    x: -73
                    y: -13
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.verticalCenter: parent.verticalCenter
                    width: 148
                    height: 105

                    Button {
                        id: button
                        Layout .fillWidth: true
                        Layout .fillHeight: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        onClicked: {
                            qmlGenerateField();
                            qmlStartEngine();
                            swipeView.interactive = true;
                            timer.running = true;
                        }
                        onPressedChanged: {
                            if( pressed ) {
                                opacity = 0.75
                            }
                            else {
                                opacity = 1
                            }
                        }

                        Timer {
                            id: timer
                            interval: 2000; running: false; repeat: false
                            onTriggered: swipeView.currentIndex = 1
                        }

                        Image {
                            id: but1
                            anchors.fill: parent
                            source: "/but1.png"
                        }
                    }

                    Button {
                        id: button1
                        Layout .fillWidth: true
                        Layout .fillHeight: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        onClicked: dialog.open()
                        onPressedChanged: {
                            if( pressed ) {
                                opacity = 0.75
                            }
                            else {
                                opacity = 1
                            }
                        }

                        Image {
                            id: but2
                            anchors.fill: parent
                            source: "/but2.png"
                        }
                    }
                }
            }

            Dialog {
                id: dialog
                title: qsTr("TEAM")
                modal: true
                width:360
                height:360
                Label {
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height / 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.topMargin: 5
                    anchors.bottomMargin: 5
                    text: "Warren Clark Twitter/ @WoostarsPixels - dark sorcerer, summoning wizard and fallen knight sprites
Jesse M Twitter/ @Jsf23Art - resurrected skeleton warrior sprite
Vendet Forum.HellRoom.ru/ Vendet - diff planescape tiles
Groenendael Twitter/ @ThatGuyWithAx - game development and soundtrack"
                }
            }

        }

        Page {
            id:page
            contentHeight: 640
            contentWidth: 720
            ScrollView {
                anchors.fill: parent
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOff
            Grid {
                id: pagee
                columns: 24
                rows: 44
                spacing: 0

                Repeater {
                    id:mmm
                    objectName: "mmm"
                    model: 1056

                    function changecolor(pos, msg) {
                        //                        mmm.itemAt(pos).color = msg; //Math.floor(Math.random() * (24 + 1)).toString()
                        mmm.itemAt(pos).children[0].source = "/" + msg + ".png"
                        mmm.itemAt(pos).children[0].sourceChanged()
                    }

                    function createsoldier(pos, idshka) {
                        if (pos < 528) {
                            qmlChangeAnimation("sorcer1", "summoner_fly_animation", pos, idshka)
                            var component = Qt.createComponent("Soldier1.qml");
                            component.createObject(pagee, {"x": 30*(pos%24), "y": 30*Math.floor(pos/24)-5, "id":idshka, "objectName":idshka});
                        }
                        else {
                            qmlChangeAnimation("sorcer2", "sorcerer_villain_cast", pos, idshka)
                            var component2 = Qt.createComponent("Soldier2.qml");
                            component2.createObject(pagee, {"x": 30*(pos%24)+5, "y": 30*Math.floor(pos/24), "id":idshka, "objectName":idshka});
                        }
                    }

                    function createtree (pos, idshka) {
                        var component3 = Qt.createComponent("Tree.qml");
                        component3.createObject(pagee, {"x": 30*(pos%24)-10, "y": 30*Math.floor(pos/24)-35, "id":idshka, "objectName":idshka});
                    }

                    function createsorcerers () {
                        var component4 = Qt.createComponent("Sorcerer1.qml");
                        component4.createObject(pagee);
                        var component5 = Qt.createComponent("Sorcerer2.qml");
                        component5.createObject(pagee);
                    }

                    Rectangle {
                        width: 30
                        height: 30
                        color: "black"

                        Image {
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {qmlCreateSoldier(index)}
                        }
                    }

                }

            }
}
        }//page

    }
}
