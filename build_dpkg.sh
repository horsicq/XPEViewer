#!/bin/bash -x
export QMAKE_PATH=/usr/bin/qmake

export X_SOURCE_PATH=$PWD
export X_BUILD_NAME=xpeviewer_linux_portable
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/linux.sh

check_file $QMAKE_PATH

if [ -z "$X_ERROR" ]; then
    make_init
    make_build "$X_SOURCE_PATH/xpeviewer_source.pro"
    cd "$X_SOURCE_PATH/gui_source"
    make_translate "gui_source_tr.pro"
    cd "$X_SOURCE_PATH"

    check_file "$X_SOURCE_PATH/build/release/xpeviewer"
    if [ -z "$X_ERROR" ]; then
        create_deb_app_dir xpeviewer
        
        export X_PACKAGENAME='xpeviewer'
        export X_MAINTAINER='hors <horsicq@gmail.com>'
        
        export X_HOMEPAGE='http://ntinfo.biz'
        export X_DESCRIPTION='XPEViewer is a PE file viewer/editor.'
        
        if [ "$X_DEBIAN_VERSION" -ge "11" ]; then
            export X_DEPENDS='libqt5core5a, libqt5svg5, libqt5gui5, libqt5widgets5, libqt5opengl5, libqt5dbus5, libqt5scripttools5, libqt5script5, libqt5network5, libqt5sql5'
        else
            export X_DEPENDS='qt5-default, libqt5core5a, libqt5svg5, libqt5gui5, libqt5widgets5, libqt5opengl5, libqt5dbus5, libqt5scripttools5, libqt5script5, libqt5network5, libqt5sql5'
        fi
        
        create_deb_control $X_SOURCE_PATH/release/$X_BUILD_NAME/DEBIAN/control

        cp -f $X_SOURCE_PATH/build/release/xpeviewer                        $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/bin/
        cp -f $X_SOURCE_PATH/LINUX/xpeviewer.desktop                        $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/applications/
        sed -i "s/#VERSION#/$X_RELEASE_VERSION/"                            $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/applications/xpeviewer.desktop
        cp -Rf $X_SOURCE_PATH/LINUX/hicolor/                                $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/icons/
        cp -Rf $X_SOURCE_PATH/XStyles/qss/                                  $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/
        cp -Rf $X_SOURCE_PATH/XInfoDB/info/                                 $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/
        cp -Rf $X_SOURCE_PATH/Detect-It-Easy/db/                            $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/
		cp -Rf $X_SOURCE_PATH/Detect-It-Easy/db_custom/                     $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/
        cp -Rf $X_SOURCE_PATH/images/                                       $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/
        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/lang/
        cp -f $X_SOURCE_PATH/gui_source/translation/*.qm                    $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/lang/
        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/signatures
        cp -f $X_SOURCE_PATH/signatures/crypto.db                           $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/lib/xpeviewer/signatures/

        make_deb
        mv $X_SOURCE_PATH/release/$X_BUILD_NAME.deb $X_SOURCE_PATH/release/xpeviewer_${X_RELEASE_VERSION}_${X_OS_VERSION}_${X_ARCHITECTURE}.deb
        make_clear
    fi
fi
