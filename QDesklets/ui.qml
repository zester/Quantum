import Qt 4.7

Rectangle {
  width: 640
  height: 100
  color: "#7b000000"
  radius: 13

  Text {
      color: "#ffffff"
    text: "I'm a Quantum QML Desklet"
    smooth: true
    style: Text.Raised
    font.pointSize: 26
    font.bold: true
    anchors.centerIn: parent
  }
}
