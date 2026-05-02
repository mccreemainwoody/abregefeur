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
            text: "Notes"
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

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 8
            model: ListModel {
                ListElement { content: "Message placeholder utilisateur" }
                ListElement { content: "Message placeholder assistant" }
                ListElement { content: "Nouveau message..." }
            }

            delegate: Row {
                width: ListView.view.width
                layoutDirection: index % 2 === 0 ? Qt.LeftToRight : Qt.RightToLeft

                Rectangle {
                    width: Math.min(parent.width * 0.8, messageText.implicitWidth + 24)
                    height: messageText.implicitHeight + 18
                    radius: 10
                    color: index % 2 === 0 ? colors.userMessageColor : colors.agentMessageColor

                    Text {
                        id: messageText
                        anchors.centerIn: parent
                        text: content
                        color: colors.brightTextColor
                        font.pixelSize: 14
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            TextField {
                Layout.fillWidth: true
                placeholderText: "Ecrire un message..."
            }

            Button {
                id: addMessageButton
                text: "Ajouter"
                background: Rectangle {
                    radius: 6
                    color: colors.brightTextColor
                }
                contentItem: Text {
                    text: addMessageButton.text
                    color: colors.darkTextColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }
            }
        }
    }
}
