#!/bin/sh -x
export QMAKE_PATH=$HOME/Qt/5.15.2/clang_64/bin/qmake

export X_SOURCE_PATH=$PWD
export X_BUILD_NAME=xpeviewer_mac_portable
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/mac.sh

check_file $QMAKE_PATH

if [ -z "$X_ERROR" ]; then
    make_init
    make_build "$X_SOURCE_PATH/xpeviewer_source.pro"
    cd "$X_SOURCE_PATH/gui_source"
    make_translate "gui_source_tr.pro" xpeviewer
    cd "$X_SOURCE_PATH"

    check_file "$X_SOURCE_PATH/build/release/XPEViewer.app/Contents/MacOS/XPEViewer"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/XPEViewer.app" "$X_SOURCE_PATH/release/$X_BUILD_NAME"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/XPEViewer.app/Contents/Resources/signatures
        cp -R $X_SOURCE_PATH/signatures/crypto.db            $X_SOURCE_PATH/release/$X_BUILD_NAME/XPEViewer.app/Contents/Resources/signatures
        cp -Rf $X_SOURCE_PATH/XStyles/qss                    $X_SOURCE_PATH/release/$X_BUILD_NAME/XPEViewer.app/Contents/Resources/

        fiximport "$X_SOURCE_PATH/build/release/XPEViewer.app/Contents/MacOS/XPEViewer"

        deploy_qt_library QtWidgets XPEViewer
        deploy_qt_library QtGui XPEViewer
        deploy_qt_library QtCore XPEViewer
        deploy_qt_library QtDBus XPEViewer
        deploy_qt_library QtPrintSupport XPEViewer
        deploy_qt_library QtSvg XPEViewer
        deploy_qt_library QtOpenGL XPEViewer
        deploy_qt_library QtConcurrent XPEViewer

        deploy_qt_plugin platforms libqcocoa XPEViewer
        deploy_qt_plugin platforms libqminimal XPEViewer
        deploy_qt_plugin platforms libqoffscreen XPEViewer

        make_release
        make_clear
    fi
fi