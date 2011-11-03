import QtQuick 2.0
import "." 1.0

Plot {
    id: plot
    width: 400
    height: 300

    Scale {
        id: scaleTop
        parent: plot.topScales
        anchors.left: plot.topScales.left
        anchors.right: plot.topScales.right
        label.text: "log scale"
        baselineThickness: 3
        scaleMap.valueMapper: LogValueMapper {}
        scaleMap.scaleMinimum: 0
        scaleMap.scaleMaximum: 10100
        orientation: "horizontal"
        flip: true
    }

    Scale {
        id: scaleBottom
        parent: plot.bottomScales
        anchors.left: plot.bottomScales.left
        anchors.right: plot.bottomScales.right
        label.text: "linear scale flipped"
        baselineThickness: 3
        scaleMap.valueMapper: ValueMapper {}
        scaleMap.scaleMinimum: -200
        scaleMap.scaleMaximum: 10100
        orientation: "horizontal"
    }

    Scale {
        id: scaleLeft
        parent: plot.leftScales
        anchors.top: plot.leftScales.top
        anchors.bottom: plot.leftScales.bottom
        label.text: "linear scale"
        baselineThickness: 3
        scaleMap.valueMapper: ValueMapper {}
        scaleMap.scaleMinimum: -200
        scaleMap.scaleMaximum: 10100
    }

    Scale {
        id: scaleRight
        parent: plot.rightScales
        anchors.top: plot.rightScales.top
        anchors.bottom: plot.rightScales.bottom
        label.text: "log scale flipped"
        baselineThickness: 3
        scaleMap.valueMapper: LogValueMapper {}
        scaleMap.scaleMinimum: 0
        scaleMap.scaleMaximum: 10100
        flip: true
    }

    Curve {
        parent: plot.plottingArea
        anchors.fill: plot.plottingArea
        xScaleMap: scaleBottom.scaleMap
        yScaleMap: scaleRight.scaleMap
    }

    Curve {
        parent: plot.plottingArea
        anchors.fill: plot.plottingArea
        xScaleMap: scaleTop.scaleMap
        yScaleMap: scaleLeft.scaleMap
    }
}
