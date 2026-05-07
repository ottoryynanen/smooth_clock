// Copyright (C) 2026 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import smooth_clock 1.0

Window {
    width: 480
    height: 480
    visible: true
    title: qsTr("Clock")
    color: "black"
    Rectangle {
        id: _background
        color: "white"
        radius: width / 2
        anchors.fill: parent
        Repeater {
            model: 12
            Rectangle {
                x: _background.width / 2
                y: 0
                width: 2
                height: 20
                color: "black"
                antialiasing: true
                transform: [
                    Rotation {
                        origin.x: 0
                        origin.y: _background.height / 2
                        angle: 30.0 * index
                    }
                ]
            }
        }
        Rectangle {
            id: _hourHand
            x: (_background.width - width) / 2
            y: _background.height / 5
            width: 7
            height: 13 * _background.height / 40
            radius: width / 2
            color: "black"
            antialiasing: true
            transform: [
                Rotation {
                    origin.x: _hourHand.width / 2
                    origin.y: (_background.height / 2 - _hourHand.y)
                    angle: _time.hourAngle
                    Behavior on angle {
                        RotationAnimation { duration: 1000; direction: RotationAnimation.Shortest }
                    }
                }
            ]
        }
        Rectangle {
            id: _minuteHand
            x: (_background.width - width) / 2
            y: 5
            width: 3
            height: 11 * _background.height / 20
            radius: width / 2
            color: "black"
            antialiasing: true
            transform: [
                Rotation {
                    origin.x: _minuteHand.width / 2
                    origin.y: (_background.height / 2 - _minuteHand.y)
                    angle: _time.minuteAngle
                    Behavior on angle {
                        RotationAnimation { duration: 1000; direction: RotationAnimation.Shortest }
                    }
                }
            ]
        }
        Rectangle {
            id: _secondHand
            x: (_background.width - width) / 2
            y: 2
            width: 2
            height: 6 * _background.height / 10
            radius: width / 2
            color: "red"
            antialiasing: true
            transform: [
                Rotation {
                    origin.x: _secondHand.width / 2
                    origin.y: (_background.height / 2 - _secondHand.y)
                    angle: _time.secondAngle
                    Behavior on angle {
                        RotationAnimation { duration: 1000; direction: RotationAnimation.Shortest }
                    }
                }
            ]
        }
        Rectangle {
            color: "white"
            width: 2
            height: 2
            anchors.centerIn: parent
        }
    }
    TimeProvider {
        id: _time
    }
}
