import QtQuick 2.0

Image {
    property int index: -1
    source: "/Image_Index_" + index + ".png"
    width: parent.width / dimensions
    height: parent.height / dimensions
}