import QtQuick 2.7

Item {
    z: 0
    Rectangle {
        width: 20
        height: 20
        color: "transparent"
        opacity: 0

        MouseArea {
            anchors.fill: parent
        }

        AnimatedSprite {
            width: 15
            height: 20
            anchors.centerIn: parent
            source: "/Skeleton_Idle.png"
            frameCount: 11
            frameRate: 9
            frameWidth: 24
            frameHeight: 32
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
