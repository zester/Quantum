import Qt 4.7

Rectangle {
  width: 200
  height: 200
  color: "#00000000"
  radius: 0
  rotation: 38

  Text {
      x: 55
      y: 165
      color: "#ffffff"
    text: "Todo List"
    anchors.verticalCenterOffset: 77
    anchors.horizontalCenterOffset: -1
    smooth: true
    style: Text.Raised
    font.pointSize: 15
    font.bold: false
    anchors.centerIn: parent
  }

  Image {
      id: image1
      x: 29
      y: 16
      width: 142
      height: 149
      smooth: true
      source: "images/sticky-note.png"

      Text {
          id: text1
          x: 17
          y: 22
          width: 109
          height: 100
          text: "1. Feed the dog   2. Take out trash   3. Make dinner"
          wrapMode: Text.WordWrap
          font.pixelSize: 11
      }
  }
}
