import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AbregeFeur.Triggers 1.0

Rectangle {
    property Notes notesContext: null

    Colors {
        id: colors
    }

    ArtifactsTriggers {
        id: artifactsTriggers
    }

    ListModel {
        id: allArtifacts
    }

    Component.onCompleted: {
        let artifacts = artifactsTriggers.getArtifacts();

        for (let i = 0; i < artifacts.length; i++) {
            allArtifacts.append(artifacts[i]);
        }
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
                id: markdownSummaryGenButton
                text: "Markdown Summary"
                readonly property int genType: ArtifactType.SUMMARY_MARKDOWN

                Layout.fillWidth: true

                background: Rectangle {
                    radius: 6
                    color: colors.colorForArtifactType(markdownSummaryGenButton.genType)
                }

                contentItem: Text {
                    text: markdownSummaryGenButton.text
                    color: colors.brightTextColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                }

                onClicked: {
                    if (!notesContext || typeof notesContext.getCurrentNotes !== "function") {
                        console.error("Artifacts: notesContext must provide getCurrentNotes()");
                        return;
                    }

                    const extras = "";

                    const notes = notesContext.getCurrentNotes();

                    const artifact = artifactsTriggers.generateArtifact(
                                         markdownSummaryGenButton.genType,
                                         notes,
                                         extras);

                    allArtifacts.append(artifact);
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
            model: allArtifacts

            delegate: Rectangle {
                width: ListView.view.width
                height: 44
                radius: 6
                color: Qt.darker(colors.columnBackgroundColor, 1.2)
                border.color: colors.columnBorderColor

                Text {
                    anchors.centerIn: parent
                    text: path
                    color: colors.colorForArtifactType(type)
                    font.pixelSize: 14
                    font.bold: true
                }
            }
        }
    }
}
