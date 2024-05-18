import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
      ToolButton {
          onClicked: {
                     buttonAnimation.running = true;
                 }

                 Rectangle {
                     id: animatedRectangle
                     width: 100
                     height: 50
                     color: "blue"
                     anchors.centerIn: parent
                     visible: false
                 }

                 SequentialAnimation {
                     id: buttonAnimation
                     running: false

                     PropertyAnimation {
                         target: animatedRectangle
                         property: "scale"
                         from: 1
                         to: 2
                         duration: 500
                         onRunningChanged: animatedRectangle.visible = running
                     }

                     PropertyAnimation {
                         target: animatedRectangle
                         property: "scale"
                         from: 2
                         to: 1
                         duration: 500
                     }
                 }
      }
}
