import QtQuick 2.7

Item {
    id:sorcer1
    objectName:"sorcer1"
    x: 650
    y: 10
    z: 1

    Rectangle {
        width: 60
        height: 60
        color: "transparent"

        AnimatedSprite {
            width: 60
            height: 60
            anchors.centerIn: parent
            source: "/summoner_idle_animation.png"
            frameCount: 7
            frameRate: 4
            frameWidth: 80
            frameHeight: 80
            running: true
            onCurrentFrameChanged: if (currentFrame==frameCount-1) {
                                       source =  "/summoner_idle_animation.png";
                                       loops = AnimatedSprite.Infinite;
                                       frameCount = 7;
                                       sourceChanged();
                                       start();
                                   }
        }

    }

    ParallelAnimation {
            running: false
            NumberAnimation {target: sorcer1; easing.type: Easing.InOutQuart; running: false; property: "x"; duration: 2500;
                onTargetChanged: {
                    if (running) { complete(); restart(); }
                }
            }
            NumberAnimation {target: sorcer1; easing.type: Easing.InOutQuart; running: false; property: "y"; duration: 2500;
                onTargetChanged: {
                    if (running) { complete(); restart(); }
                }
            }

        }

    function hello ()
    {
        visible = false;
        sorcer1.destroy();
        console.log(objectName);

    }
}
