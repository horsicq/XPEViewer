QT       += core gui widgets

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

!contains(XCONFIG, pewidget) {
    XCONFIG += pewidget
    include(../FormatWidgets/PE/pewidget.pri)
}

!contains(XCONFIG, xoptions) {
    XCONFIG += xoptions
    include(../XOptions/xoptions.pri)
}

win32 {
    RC_ICONS = ../icons/main.ico
    CONFIG -= embed_manifest_exe
    QMAKE_MANIFEST = windows.manifest.xml
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
