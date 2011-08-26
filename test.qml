import QtQuick 2.0
import "." 1.0

Item {
    width: 400
    height: 300

    Row {
        id: verticalScales
        spacing: 4
        anchors.top: parent.top
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

        Text {
            id: pickerLin
            color: "white"
            text: "pickerLin"

            Rectangle {
                anchors.fill: parent
                color: "black"
                z: -1
            }
        }

        Text {
            id: pickerLog
            color: "white"
            text: "pickerLog"

            Rectangle {
                anchors.fill: parent
                color: "black"
                z: -1
            }
        }

        MouseArea {
            id: pickerArea
            anchors.fill: parent
            hoverEnabled: true

            onPositionChanged: {
                pickerLin.x = mouse.x + 10;
                pickerLin.y = mouse.y;
                var xLin = horizontalScaleLin.scaleMap.mapToScale(mouse.x);
                var yLin = verticalScaleLin.scaleMap.mapToScale(mouse.y);
                pickerLin.text = "lin: (" + xLin + "; " + yLin + ")";

                pickerLog.x = mouse.x + 10;
                pickerLog.y = mouse.y + 15;
                var xLog = horizontalScaleLog.scaleMap.mapToScale(mouse.x);
                var yLog = verticalScaleLog.scaleMap.mapToScale(mouse.y);
                pickerLog.text = "log: (" + xLog + "; " + yLog + ")";
            }
        }
    }
}
