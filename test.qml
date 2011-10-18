import QtQuick 2.0
import "." 1.0

Item {
    id: plot
    width: 400
    height: 300

    Scale {
        id: scaleTop
        anchors.top: plot.top
        anchors.left: scaleLeft.right
        anchors.right: scaleRight.left
        label.text: "log scale"
        baselineColor: "yellow"
        baselineThickness: 4
        scaleMap.valueMapper: LogValueMapper {}
        scaleMap.scaleMinimum: 0
        scaleMap.scaleMaximum: 10100
        orientation: "horizontal"
        flip: true
    }

    Scale {
        id: scaleBottom
        anchors.bottom: plot.bottom
        anchors.left: scaleLeft.right
        anchors.right: scaleRight.left
        label.text: "linear scale flipped"
        baselineColor: "yellow"
        baselineThickness: 10
        scaleMap.valueMapper: ValueMapper {}
        scaleMap.scaleMinimum: -200
        scaleMap.scaleMaximum: 10100
        orientation: "horizontal"
    }

    Scale {
        id: scaleLeft
        anchors.left: plot.left
        anchors.top: scaleTop.bottom
        anchors.bottom: scaleBottom.top
        label.text: "log scale"
        baselineColor: "yellow"
        baselineThickness: 4
        scaleMap.valueMapper: ValueMapper {}
        scaleMap.scaleMinimum: -200
        scaleMap.scaleMaximum: 10100
    }

    Scale {
        id: scaleRight
        anchors.right: plot.right
        anchors.top: scaleTop.bottom
        anchors.bottom: scaleBottom.top
        label.text: "linear scale flipped"
        baselineColor: "yellow"
        baselineThickness: 10
        scaleMap.valueMapper: LogValueMapper {}
        scaleMap.scaleMinimum: 0
        scaleMap.scaleMaximum: 10100
        flip: true
    }

    Curve {
        anchors.left: scaleBottom.left
        anchors.right: scaleBottom.right
        anchors.top: scaleRight.top
        anchors.bottom: scaleRight.bottom
        xScaleMap: scaleBottom.scaleMap
        yScaleMap: scaleRight.scaleMap
    }

    Curve {
        anchors.left: scaleTop.left
        anchors.right: scaleTop.right
        anchors.top: scaleLeft.top
        anchors.bottom: scaleLeft.bottom
        xScaleMap: scaleTop.scaleMap
        yScaleMap: scaleLeft.scaleMap
    }
}
