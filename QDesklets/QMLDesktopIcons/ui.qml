import Qt 4.7

Rectangle {
    id: rectangle2
  width: 300
  height: 200
  color: "#64000000"
  radius: 5
  border.color: "#000000"
  z: 0
  rotation: 0

  MouseArea {
      id: mouse_area1
      x: 33
      y: 61
      width: 74
      height: 83

      Text {
          id: text1
          x: 19
          y: 66
          color: "#ffffff"
          text: "Home"
          font.pixelSize: 12
      }

      Image {
          id: image1
          x: 6
          y: 5
          width: 62
          height: 61
          source: "images/folder-black.png"
      }
  }

  Text {
      id: text2
      y: 14
      color: "#ffffff"
      text: "Desktop"
      anchors.left: parent.left
      anchors.leftMargin: 14
      font.bold: true
      font.pixelSize: 15
  }

  Rectangle {
      id: rectangle1
      x: 199
      y: -150
      width: 2
      height: parent.width - 10
      anchors.horizontalCenterOffset: 0
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenterOffset: -50
      anchors.verticalCenter: parent.verticalCenter
      rotation: -90
      gradient: Gradient {
          GradientStop {
              position: 0
              color: "#00000000"
          }

          GradientStop {
              position: 0.68
              color: "#64000000"
          }
      }
  }
}
