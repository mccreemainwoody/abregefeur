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
            text: "Artifacts"
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

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 8

            Button {
                id: audioButton
                text: "Audio Summary"
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 6
                    color: colors.audioSummaryArtifactTypeColor
                }
                contentItem: Text {
                    text: audioButton.text
                    color: colors.brightTextColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }
            }

            Button {
                id: visualButton
                text: "Visual Summary"
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 6
                    color: colors.visualSummaryArtifactTypeColor
                }
                contentItem: Text {
                    text: visualButton.text
                    color: colors.brightTextColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }
            }

            Button {
                id: writtenButton
                text: "Written Summary"
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 6
                    color: colors.writtenSummaryTypeColor
                }
                contentItem: Text {
                    text: writtenButton.text
                    color: colors.brightTextColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }
            }
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
                ListElement {
                    artifactType: "Audio Summary"
                }
                ListElement {
                    artifactType: "Written Summary"
                }
            }

            delegate: Rectangle {
                width: ListView.view.width
                height: 44
                radius: 6
                color: Qt.darker(colors.columnBackgroundColor, 1.2)
                border.color: colors.columnBorderColor

                Text {
                    anchors.centerIn: parent
                    text: artifactType
                    color: artifactType === "Audio Summary"
                           ? colors.audioSummaryArtifactTypeColor
                           : artifactType === "Visual Summary"
                             ? colors.visualSummaryArtifactTypeColor
                             : colors.writtenSummaryTypeColor
                    font.pixelSize: 14
                    font.bold: true
                }
            }
        }
    }
}
