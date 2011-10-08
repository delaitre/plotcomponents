import QtQuick 2.0
import "." 1.0

Item {
    width: 400
    height: 300

    Rectangle {
        id: r1
        x: 30
        y: 30
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        width: childrenRect.width
        color: "#B0347853"

        Row {
            spacing: 4
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            Scale {
                label.text: "log scale"
                baselineColor: "yellow"
                baselineThickness: 4
                scaleMap.valueMapper: LogValueMapper {}
                scaleMap.scaleMinimum: 0
                scaleMap.scaleMaximum: 10100
            }

            Scale {
                label.text: "linear scale flipped"
                baselineColor: "yellow"
                baselineThickness: 10
                scaleMap.valueMapper: ValueMapper {}
                scaleMap.scaleMinimum: -200
                scaleMap.scaleMaximum: 10100
                flip: true
            }

            Scale {
                label.text: "linear scale"
                baselineColor: "yellow"
                baselineThickness: 2
                scaleMap.valueMapper: ValueMapper {}
                scaleMap.scaleMinimum: -200
                scaleMap.scaleMaximum: 10100
            }
        }
    }
    Rectangle {
        anchors.top: r1.top
        anchors.left: r1.right
        anchors.right: parent.right
        height: childrenRect.height
        anchors.leftMargin: 40
        anchors.rightMargin: 40
        color: "#B0347853"

        Column {
            spacing: 4
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            Scale {
                label.text: "log scale"
                baselineColor: "yellow"
                baselineThickness: 4
                scaleMap.valueMapper: LogValueMapper {}
                scaleMap.scaleMinimum: 0
                scaleMap.scaleMaximum: 10100
                orientation: "horizontal"
            }

            Scale {
                label.text: "linear scale flipped"
                baselineColor: "yellow"
                baselineThickness: 10
                scaleMap.valueMapper: ValueMapper {}
                scaleMap.scaleMinimum: -200
                scaleMap.scaleMaximum: 10100
                flip: true
                orientation: "horizontal"
            }

            Scale {
                label.text: "linear scale"
                baselineColor: "yellow"
                baselineThickness: 2
                scaleMap.valueMapper: ValueMapper {}
                scaleMap.scaleMinimum: -200
                scaleMap.scaleMaximum: 10100
                orientation: "horizontal"
            }
        }
    }
}
