import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AbregeFeur.Triggers 1.0

Rectangle {
    function getCurrentNotes() {
        return notesTriggers.getNotes();
    }

    Colors {
        id: colors
    }

    NotesTriggers {
        id: notesTriggers
    }

    ListModel {
        id: notesThread
    }

    Component.onCompleted: {
        var notes = notesTriggers.getNotes();

        for (var i = 0; i < notes.length; i++) {
            notesThread.append(notes[i]);
        }
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
            model: notesThread

            delegate: Row {
                width: ListView.view.width
                layoutDirection: Qt.LeftToRight

                Rectangle {
                    width: Math.min(parent.width * 0.8, messageText.implicitWidth + 24)
                    height: messageText.implicitHeight + 18
                    radius: 10
                    color: colors.userMessageColor

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
                id: noteInput
                Layout.fillWidth: true
                placeholderText: "Ecrire un message..."
            }

            Button {
                id: addMessageButton
                text: "Envoyer"
                onClicked: {
                    var note = notesTriggers.addNote(noteInput.text);
                    notesThread.append(note);
                    noteInput.text = "";
                }
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
