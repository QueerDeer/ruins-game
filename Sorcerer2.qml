import QtQuick 2.7

Item {
    id:sorcer2
    objectName:"sorcer2"
    x: 0
    y: 1236
    z: 1

    Rectangle {
        width: 80
        height: 80
        color: "transparent"

        AnimatedSprite {
            width: 80
            height: 80
            anchors.centerIn: parent
            source: "/sorcerer_villain_idle.png"
            frameCount: 11
            frameRate: 5
            frameWidth: 200
            frameHeight: 200
            running: true
            onCurrentFrameChanged: if (currentFrame==frameCount-1) {
                                       source =  "/sorcerer_villain_idle.png";
                                       loops = AnimatedSprite.Infinite;
                                       frameCount = 11;
                                       sourceChanged();
                                       start();
                                   }
        }
    }

    ParallelAnimation {
            running: false
//            NumberAnimation {target: sorcer2; property: "x"; to: 200; duration: 10000}
            NumberAnimation {
                target: sorcer2
                easing.type: Easing.InOutQuad
                running: false
                property: "x"
                duration: 1500
                onTargetChanged: {
                    if (running) { complete(); restart(); }
                }
            }
            NumberAnimation {
                target: sorcer2
                easing.type: Easing.InOutQuad
                running: false
                property: "y"
                duration: 1500
                onTargetChanged: {
                    if (running) { complete(); restart(); }
                }
            }

        }

    function hello ()
    {
        visible = false;
        sorcer2.destroy();
        console.log(objectName);

    }
}
