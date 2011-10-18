import QtQuick 2.0
import "." 1.0

Item {
    id: scaleContainer
    width: orientation == "vertical" ? childrenRect.width : 0
    height: orientation == "horizontal" ? childrenRect.height : 0

    property alias label: label
    property alias scaleMap: scaleMap
    property alias baselineThickness: baseline.width
    property alias baselineColor: baseline.color
    property alias tickDelegate: scale.delegate
    property bool flip: false
    property string orientation: "vertical"

    Rectangle {
        id: baseline
        anchors.top: orientation == "vertical" ? scale.top : (!flip ? scale.top : undefined)
        anchors.bottom: orientation == "vertical" ? scale.bottom : (flip ? scale.bottom : undefined)
        anchors.left: orientation == "horizontal" ? scale.left : (flip ? scale.left : undefined)
        anchors.right: orientation == "horizontal" ? scale.right : (!flip ? scale.right : undefined)
        width: orientation == "vertical" ? 2 : 0
        height: orientation == "horizontal" ? 2 : 0
        color: "black"
    }

    LinearScale {
        id: scale
        orientation: scaleContainer.orientation == "vertical" ? Qt.Vertical : Qt.Horizontal
        anchors.top: orientation == Qt.Vertical ? parent.top : (flip ? labelContainer.bottom : undefined)
        anchors.bottom: orientation == Qt.Vertical ? parent.bottom : undefined
        anchors.left: orientation == Qt.Horizontal ? parent.left : (!flip ? labelContainer.right : undefined)
        anchors.right: orientation == Qt.Horizontal ? parent.right : undefined
        width: orientation == Qt.Vertical ? childrenRect.width : undefined
        height: orientation == Qt.Horizontal ? childrenRect.height : undefined

        scaleMap: ScaleMap {
            id: scaleMap
            valueMapper: LogValueMapper {}
            scaleMinimum: 1
            scaleMaximum: 10100
        }

        delegate: ValueTick { flip: scaleContainer.flip; orientation: scaleContainer.orientation }
    }

    Item {
        id: labelContainer
        anchors.verticalCenter: scale.orientation == Qt.Vertical ? scale.verticalCenter : undefined
        anchors.horizontalCenter: scale.orientation == Qt.Horizontal ? scale.horizontalCenter : undefined
        anchors.left: (scale.orientation == Qt.Vertical && flip) ? scale.right : undefined
        anchors.top: (scale.orientation == Qt.Horizontal && !flip) ? scale.bottom : undefined
        width: scale.orientation == Qt.Vertical ? label.height : label.width
        height: scale.orientation == Qt.Vertical ? label.width : label.height
        Text {
            id: label
            rotation: scale.orientation == Qt.Horizontal ? 0 : (scaleContainer.flip ? 90 : -90)
            anchors.centerIn: parent
        }
    }
}
