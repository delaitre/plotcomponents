import QtQuick 2.0

Item {
    anchors.right: (parent && !flip && orientation == "vertical") ? parent.right : undefined
    anchors.left: (parent && flip && orientation == "vertical") ? parent.left : undefined
    anchors.top:  (parent && !flip && orientation == "horizontal") ? parent.top : undefined
    anchors.bottom: (parent && flip && orientation == "horizontal") ? parent.bottom : undefined

    x: orientation == "horizontal" ? tickPosition - width / 2 : 0
    y: orientation == "vertical" ? tickPosition - height / 2 : 0
    width: childrenRect.width
    height: childrenRect.height

    property bool flip: false
    property string orientation: "vertical"

    Rectangle {
        id: tick
        width: orientation == "vertical" ? 8 : 2
        height: orientation == "vertical" ? 2 : 8
        anchors.left: (!flip && orientation == "vertical") ? tickText.right : undefined
        anchors.verticalCenter: orientation == "vertical" ? tickText.verticalCenter : undefined
        anchors.top: (flip && orientation == "horizontal") ? tickText.bottom : undefined
        anchors.horizontalCenter: orientation == "horizontal" ? tickText.horizontalCenter : undefined
        color: "black"
    }
    Text {
        id: tickText
        anchors.left: (flip && orientation == "vertical") ? tick.right : undefined
        anchors.top: (!flip && orientation == "horizontal") ? tick.bottom : undefined
        text: tickValue
        color: "black"
    }
}
