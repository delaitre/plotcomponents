import QtQuick 2.0
import "." 1.0

Item {
    width: 400
    height: 300

    Column {
        id: header
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        Text { id: pickerLin; color: "black"; text: "pickerLin" }
        Text { id: pickerLog; color: "black"; text: "pickerLog" }
    }

    Row {
        id: verticalScales
        spacing: 4
        anchors.top: header.bottom
        anchors.bottom: horizontalScales.top
        anchors.left: parent.left

        LinearScale {
            id: verticalScaleLog
            orientation: Qt.Vertical
            scaleMap: ScaleMap {
                valueMapper: LogValueMapper {}
                scaleMinimum: 1
                scaleMaximum: 10100
            }
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 20

            delegate: Rectangle {
                x: -width
                y: tickPosition - height / 2
                width: 8
                height: 2
                color: "black"
                Text { anchors.right: parent.left; anchors.verticalCenter: parent.verticalCenter; text: tickValue }
            }
        }

        LinearScale {
            id: verticalScaleLin
            orientation: Qt.Vertical
            scaleMap: ScaleMap {
                valueMapper: ValueMapper {}
                scaleMinimum: 1
                scaleMaximum: 10100
            }
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 20

            delegate: Rectangle {
                x: -width
                y: tickPosition - height / 2
                width: 8
                height: 2
                color: "black"
                Text { anchors.right: parent.left; anchors.verticalCenter: parent.verticalCenter; text: tickValue }
            }
        }
    }

    Column {
        id: horizontalScales
        spacing: 4
        anchors.left: verticalScales.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        LinearScale {
            id: horizontalScaleLog
            orientation: Qt.Horizontal
            scaleMap: ScaleMap {
                valueMapper: LogValueMapper {}
                scaleMinimum: 1
                scaleMaximum: 10100
            }
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20

            delegate: Rectangle {
                x: tickPosition - width / 2
                y: 0
                width: 2
                height: 8
                color: "black"
                Text { anchors.top: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter; text: tickValue }
            }
        }

        LinearScale {
            id: horizontalScaleLin
            orientation: Qt.Horizontal
            scaleMap: ScaleMap {
                valueMapper: ValueMapper {}
                scaleMinimum: 1
                scaleMaximum: 10100
            }
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20

            delegate: Rectangle {
                x: tickPosition - width / 2
                y: 0
                width: 2
                height: 8
                color: "black"
                Text { anchors.top: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter; text: tickValue }
            }
        }
    }

    Item {
        id: plottingArea
        anchors.left: horizontalScales.left
        anchors.right: horizontalScales.right
        anchors.top: verticalScales.top
        anchors.bottom: verticalScales.bottom

        Curve {
            anchors.fill: parent
            xScaleMap: horizontalScaleLin.scaleMap
            yScaleMap: verticalScaleLog.scaleMap
        }

        Curve {
            anchors.fill: parent
            xScaleMap: horizontalScaleLin.scaleMap
            yScaleMap: verticalScaleLin.scaleMap
        }

        MouseArea {
            id: pickerArea
            anchors.fill: parent
            hoverEnabled: true

            onPositionChanged: {
                var xLin = horizontalScaleLin.scaleMap.mapToScale(mouse.x);
                var yLin = verticalScaleLin.scaleMap.mapToScale(verticalScaleLin.scaleMap.pixelLength - mouse.y);
                pickerLin.text = "lin: (" + xLin + "; " + yLin + ")";

                var xLog = horizontalScaleLog.scaleMap.mapToScale(mouse.x);
                var yLog = verticalScaleLog.scaleMap.mapToScale(verticalScaleLog.scaleMap.pixelLength - mouse.y);
                pickerLog.text = "log: (" + xLog + "; " + yLog + ")";
            }
        }
    }
}
