import QtQuick 2.0

Item {
    property var tilesByIndex: []
    property list<Tile> tiles
    id: root

    //This function performs reeaaaally bad since it renews ALL tiles everytime
    //TODO optimize optimize optimize
    onTilesByIndexChanged: {
        tiles = []

        for (var i = 0; i < tilesByIndex.length; i++) {
            let component = Qt.createComponent("Tile.qml")
            let newTile = component.createObject(root, {
                                                     "index": tilesByIndex[i],
                                                     height: root.height/dimensions,
                                                     width: root.width/dimensions
                                                 })
            tiles.push(newTile)
        }
        console.log("New Tile Length: " + tiles.length + "tilesByindex Length: "
                    + tilesByIndex.length)
    }

    Component.onCompleted: handler.drawGrid(dimensions)

    //This is the Connection to the grid InitFunction
    //The GridView is initialized in the correct way
    Connections {
        target: handler
        function onGridInit(dimensions) {
            for (var x = 0; x < (dimensions * dimensions); x++) {
                tilesByIndex.push(-1)
            }
            tileGrid.rows = dimensions
            tileGrid.columns = dimensions
            tilesByIndexChanged()
        }
    }
    //This is the Connection to the drawTile Function of handler
    //In the function the Tiles are drawn on the canvas
    //Function chooses what tile to draw depending on the index passt in the
    //Emitted signal
    Connections {
        target: handler
        function onDrawTile(posIndex, newTileIndex) {
            console.log("Hello Draw Tile")

            tilesByIndex[posIndex] = newTileIndex
            tilesByIndexChanged()
        }
    }
    //Click anywhere to start Algorithm
    MouseArea {
        anchors.fill: parent
        onClicked: {
            this.visible = false
            handler.startCollapsing()
        }
    }

    Grid {
        id: tileGrid
        anchors.fill: parent
        children: tiles
    }
}
