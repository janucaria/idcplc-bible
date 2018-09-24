import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

// SQLite driver
import QtQuick.LocalStorage 2.0

import ActionProvider 0.1

import idcplc.kodew 0.1

// Snippet browser
// Container untuk button add snippet dan listview
// Minimal width 200, maximal width 400, default width 250 (@geger009)
Rectangle {
    id: snippetBrowser
    property alias browser : browser
    property alias txtSearch : txtSearch

    color: "#323844"
    width: 250
    height: parent.height
    Layout.minimumWidth: 100
    Layout.maximumWidth: 400

    // Search bar
    Rectangle {
        color: "transparent"
        width: parent.width
        height: 30

        // Magnifier button
        Button {
            iconSource: "qrc:/res/magnifying_glass.png"
            width: 30
            height: parent.height
            anchors.leftMargin: 10
            anchors.left: parent.left
            style: ButtonStyle {
                background: Rectangle {
                    color: "transparent"
                }
            }
        }

        // Search text field
        TextField {
            id: txtSearch
            placeholderText: qsTr("Search...")
            height: parent.height
            anchors.leftMargin: 40
            anchors.left: parent.left
            anchors.rightMargin: 40
            anchors.right: parent.right
            style: TextFieldStyle {
                placeholderTextColor: "darkGray"
                textColor: "white"
                background: Rectangle {
                    color: "transparent"
                }
            }
        }

        // Plus button
        Button {
            id: btnAddSnippet
            objectName: "btnAddSnippet"
            iconSource: "qrc:/res/plus.png"
            width: 30
            height: parent.height
            anchors.rightMargin: 10
            anchors.right: parent.right
            style: ButtonStyle {
                background: Rectangle {
                    color: "transparent"
                }
            }
            onClicked:
            {
                addSnippetView.visible = true
            }
        }
    }

    // Separator
    Rectangle {
        color: "#3D4451"
        x: 0
        y: 30
        height: 1
        anchors.left: parent.left
        anchors.right: parent.right
    }

    // View untuk menampilkan daftar snippets (panel kiri).
    ListView {
        id: browser
        x: 0
        width: 250
        anchors.top: parent.top
        anchors.topMargin: 31
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        flickableDirection: Flickable.HorizontalFlick
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right
        highlight: Rectangle {
            color: "#2B303B"
        }
        focus: true
        
        model: SnippetEntryModel {}

        delegate: Component {
            Item {
                width: parent.width
                height: 60

                // Title label
                Label {
                    y: 10
                    height: 15
                    text: model.title
                    verticalAlignment: Text.AlignVCenter
                    color: "lightgray"
                    anchors.leftMargin: 10
                    anchors.left: parent.left
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                }

                // Platform label
                Label {
                    y: 35
                    height: 15
                    text: "Linux"
                    verticalAlignment: Text.AlignVCenter
                    color: "#929A97"
                    anchors.leftMargin: 10
                    anchors.left: parent.left
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                }

                // Datetime label
                Label {
                    y: 35
                    height: 15
                    text: "10:45"
                    verticalAlignment: Text.AlignVCenter
                    color: "#929A97"
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                }

                // Separator
                Rectangle {
                    color: "#3D4451"
                    y: 59
                    height: 1
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                MouseArea {
                    id: itemMouseArea
                    anchors.fill: parent

                    // On select item with mouse click
                    onClicked: {
                        browser.focus = true;
                        browser.currentIndex = index;
                        ActionProvider.displaySnippetById(codeViewer, model.xid);
                    }
                }
            }
        } // delegate

        // Navigate snippet using key up.
        Keys.onUpPressed: {
            if (count > 0 && currentIndex > 0)
            {
                currentIndex--;
                var mdlIdx = model.index(currentIndex, 0);
                var xid = model.data(mdlIdx, SnippetEntryModel.IdRole);
                ActionProvider.displaySnippetById(codeViewer, xid);
            }
        }

        // Navigate snippet using key down.
        Keys.onDownPressed: {
            if (currentIndex < (count-1))
            {
                currentIndex++;
                var mdlIdx = model.index(currentIndex, 0);
                var xid = model.data(mdlIdx, SnippetEntryModel.IdRole);
                ActionProvider.displaySnippetById(codeViewer, xid);
            }
        }

        Keys.onReturnPressed: {
            var mdlIdx = model.index(currentIndex, 0);
            var xid = model.data(mdlIdx, SnippetEntryModel.IdRole);
            ActionProvider.editSnippetForm(addSnippetView, xid);
        }
    } // ListView
} // Snippet browser
