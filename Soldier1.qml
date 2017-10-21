import QtQuick 2.7

Item {
    z: 0
    Rectangle {
        width: 30
        height: 30
        color: "transparent"
        opacity: 0

        MouseArea {
            anchors.fill: parent
        }

        AnimatedSprite {
            width: 30
            height: 30
            anchors.centerIn: parent
            source: "/templar_3_idle.png"
            frameCount: 4
            frameRate: 5
            frameWidth: 42
            frameHeight: 42
            running: true
        }

        OpacityAnimator on opacity{
                from: 0;
                to: 1;
                duration: 3000
                running: true
                easing.type: Easing.InCubic
            }
    }

    function hello ()
    {
        visible = false;
        this.destroy();
        console.log(objectName);

    }
}
