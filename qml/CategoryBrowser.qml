import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import idcplc.kodew 0.1

// Category browser
Rectangle {
    id: categoryBrowser
    property alias browser : browser

    color: "#323844"
    width: 170
    height: parent.height

    // Category label
    Label {
        y: 10
        height: 15
        text: "Categories"
        verticalAlignment: Text.AlignVCenter
        color: "lightgray"
        anchors.leftMargin: 10
        anchors.left: parent.left
        anchors.rightMargin: 10
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
        model: CategoryEntryModel{}

        delegate: Component {
            Item {
                width: parent.width
                height: 30

                // Category image
                Image {
                    source: "qrc:/res/folder.png"
                    y: 8
                    height: 15
                    width: 15
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                }

                // Category name
                Label {
                    y: 5
                    height: 20
                    text: model.display;
                    verticalAlignment: Text.AlignVCenter
                    color: "lightgray"
                    anchors.leftMargin: 42
                    anchors.left: parent.left
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                }

                MouseArea {
                    id: itemMouseArea
                    anchors.fill: parent

                    // On select item with mouse click
                    onClicked: {
                        browser.focus = true;
                        browser.currentIndex = index;
                        
                        snippetBrowser.browser.model.category = model.display;
                    }
                }
            }
        } // delegate
    } // ListView
} // Category browser
