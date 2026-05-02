import QtQuick
import QtQuick.Window

Window {
    id: root

    Colors {
        id: colors
    }

    width: 1080
    height: 720
    title: "AbregeFeur"
    visible: true
    color: colors.backgroundColor

    readonly property real columnWidthRatio: 0.30
    readonly property real columnSpacingRatio: 0.015
    readonly property real columnWidth: width * columnWidthRatio
    readonly property real columnSpacing: width * columnSpacingRatio

    Row {
        anchors.centerIn: parent
        spacing: root.columnSpacing
        width: (root.columnWidth * 3) + (root.columnSpacing * 2)
        height: parent.height * 0.92

        Sources {
            width: root.columnWidth
            height: parent.height
        }

        Notes {
            width: root.columnWidth
            height: parent.height
        }

        Artifacts {
            width: root.columnWidth
            height: parent.height
        }
    }
}
