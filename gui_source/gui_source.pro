QT       += core gui widgets
QT       += sql

TARGET = xpeviewer

macx {
    TARGET = XPEViewer
}

TEMPLATE = app

CONFIG += c++11

SOURCES += \
        guimainwindow.cpp \
        main_gui.cpp \
        dialogoptions.cpp \
        dialogabout.cpp

HEADERS += \
        dialogoptions.h \
        dialogabout.h \
        guimainwindow.h

FORMS += \
        dialogoptions.ui \
        dialogabout.ui \
        guimainwindow.ui

include(../build.pri)

XCONFIG += use_disasm
XCONFIG += use_extrabuttons
XCONFIG += use_yara

!contains(XCONFIG, pewidget) {
    XCONFIG += pewidget
    include(../FormatWidgets/PE/pewidget.pri)
}

!contains(XCONFIG, xaboutwidget) {
    XCONFIG += xaboutwidget
    include(../XAboutWidget/xaboutwidget.pri)
}

win32 {
    RC_ICONS = ../icons/main.ico
    CONFIG -= embed_manifest_exe
    QMAKE_MANIFEST = windows.manifest.xml
    VERSION = 0.06
    QMAKE_TARGET_COMPANY = NTInfo
    QMAKE_TARGET_PRODUCT = XPEViewer
    QMAKE_TARGET_DESCRIPTION = XPEViewer is a PE file viewer/editor.
    QMAKE_TARGET_COPYRIGHT = horsicq@gmail.com
}
macx {
    ICON = ../icons/main.icns
}

RESOURCES += \
    rsrc.qrc

DISTFILES += \
    ../CMakeLists.txt \
    ../changelog.txt \
    CMakeLists.txt

