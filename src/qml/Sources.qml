import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Colors {
        id: colors
    }

    color: colors.columnBackgroundColor
    radius: 8

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Text {
            text: "Sources"
            color: colors.brightTextColor
            font.pixelSize: 22
            font.bold: true
            Layout.fillWidth: true
        }

        Rectangle {
            color: colors.columnBorderColor
            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        Button {
            id: addSourceButton
            text: "Ajouter une source"
            Layout.fillWidth: true
            background: Rectangle {
                radius: 6
                color: colors.brightTextColor
            }
            contentItem: Text {
                text: addSourceButton.text
                color: colors.darkTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 8
            model: 3
            delegate: Rectangle {
                width: ListView.view.width
                height: 44
                radius: 6
                color: Qt.darker(colors.columnBackgroundColor, 1.2)
                border.color: colors.columnBorderColor

                Text {
                    anchors.centerIn: parent
                    color: colors.brightTextColor
                    text: "Source placeholder " + (index + 1)
                    font.pixelSize: 14
                }
            }
        }
    }
}
