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

    check_file "$X_SOURCE_PATH/build/release/xpeviewer.app/Contents/MacOS/xpeviewer"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/xpeviewer.app" "$X_SOURCE_PATH/release/$X_BUILD_NAME"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/xpeviewer.app/Contents/Resources/signatures
        cp -R $X_SOURCE_PATH/signatures/crypto.db            $X_SOURCE_PATH/release/$X_BUILD_NAME/xpeviewer.app/Contents/Resources/signatures
        cp -Rf $X_SOURCE_PATH/XStyles/qss                    $X_SOURCE_PATH/release/$X_BUILD_NAME/xpeviewer.app/Contents/Resources/

        fiximport "$X_SOURCE_PATH/build/release/xpeviewer.app/Contents/MacOS/xpeviewer"

        deploy_qt_library QtWidgets xpeviewer
        deploy_qt_library QtGui xpeviewer
        deploy_qt_library QtCore xpeviewer
        deploy_qt_library QtDBus xpeviewer
        deploy_qt_library QtPrintSupport xpeviewer
        deploy_qt_library QtSvg xpeviewer
        deploy_qt_library QtOpenGL xpeviewer
        deploy_qt_library QtConcurrent xpeviewer

        deploy_qt_plugin platforms libqcocoa xpeviewer
        deploy_qt_plugin platforms libqminimal xpeviewer
        deploy_qt_plugin platforms libqoffscreen xpeviewer

        make_release
        make_clear
    fi
fi