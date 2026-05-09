import QtQuick

import AbregeFeur.Triggers 1.0

QtObject {
    // Background
    readonly property color backgroundColor: "#000000"
    readonly property color columnBackgroundColor: "#3a3a3a"

    // Text
    readonly property color brightTextColor: "#ffffff"
    readonly property color darkTextColor: "#000000"
    readonly property color primaryTextColor: "#000000"
    readonly property color secondaryTextColor: "#000000"

    // Column
    readonly property color columnBorderColor: "#666666"

    // Notes Chatbox
    readonly property color userMessageColor: "#4e6c8f"
    readonly property color agentMessageColor: "#5a5a5a"

    // Summary Types
    readonly property color markdownSummaryArtifactTypeColor: "#2980b9"

    function colorForArtifactType(value) {
        if (value === ArtifactType.SUMMARY_MARKDOWN) {
            return markdownSummaryArtifactTypeColor;
        }

        return primaryTextColor;
    }
}
