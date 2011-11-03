import QtQuick 2.0

Item {
    id: plot
    width: 400
    height: 300

    property alias leftScales: leftScales
    property alias rightScales: rightScales
    property alias topScales: topScales
    property alias bottomScales: bottomScales
    property alias plottingArea: plottingArea

    Row {
        id: leftScales
        anchors.top: topScales.bottom
        anchors.bottom: bottomScales.top
        anchors.left: plot.left
        spacing: 0
    }

    Row {
        id: rightScales
        anchors.top: topScales.bottom
        anchors.bottom: bottomScales.top
        anchors.right: plot.right
        spacing: 0
    }

    Column {
        id: topScales
        anchors.left: leftScales.right
        anchors.right: rightScales.left
        anchors.top: plot.top
        spacing: 0
    }

    Column {
        id: bottomScales
        anchors.left: leftScales.right
        anchors.right: rightScales.left
        anchors.bottom: plot.bottom
        spacing: 0
    }

    Item {
        id: plottingArea
        anchors.left: leftScales.right
        anchors.right: rightScales.left
        anchors.top: topScales.bottom
        anchors.bottom: bottomScales.top
    }
}
