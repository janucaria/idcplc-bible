import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

// SQLite driver
import QtQuick.LocalStorage 2.0

import ActionProvider 0.1

ApplicationWindow {
    property var db;
    property var categories;
    property var mdl;

    id: mainWindow
    visible: true
    color: "white"
    title: "kodew"
    width: 900
    height: 600
    minimumWidth: 800
    minimumHeight: 600

    // Main screen terbagi 3 panel:  Category browser | Snippet browser | Code viewer
    SplitView {
        id: splitView

        anchors.fill: parent
        orientation: Qt.Horizontal

        handleDelegate: Rectangle {
            width: 1
            color: "#3D4451"
        }

        CategoryBrowser {
            id: categoryBrowser
        }

        SnippetBrowser {
            id: snippetBrowser
        }

        CodeViewer {
            id: codeViewer
        }

    } // SplitView

    // View untuk input snippet.
    AddSnippetView {
        id: addSnippetView
    }
}
