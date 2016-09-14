import QtQuick 2.3
import QtQuick.Controls 1.4
import CrazzyMad.data 1.0

ApplicationWindow {
    property bool download: false
    width: 500
    height: 150
    visible: true

    TextField {
        id: urlObject
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.topMargin: 10
        width: 480
        height: 40
        text: qsTr("File Url")
    }

    Button {
        id: downloadButton
        text: qsTr("Download")
        width: 100
        height: 35
        onClicked: if(!data.getDownloadStatus())
                       data.download(urlObject.text)
                   else return
        anchors.top: urlObject.bottom
        anchors.right: urlObject.right
        anchors.topMargin: 5
    }

    ProgressBar {
        id: progressDownload
        width: 480
        height: 40
        maximumValue: data.maximumValue
        value: data.value
        anchors.top: downloadButton.bottom
        anchors.right: downloadButton.right
        anchors.topMargin: 5
    }

    Data {
        id: data
    }
}
