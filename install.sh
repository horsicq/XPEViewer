#!/bin/bash -x
export X_SOURCE_PATH=$PWD

cp -f $X_SOURCE_PATH/build/release/xpeviewer                        /usr/bin/
cp -f $X_SOURCE_PATH/DEBIAN/xpeviewer.desktop                       /usr/share/applications/
cp -Rf $X_SOURCE_PATH/DEBIAN/hicolor/                               /usr/share/icons/
cp -Rf $X_SOURCE_PATH/XStyles/qss/                                  /usr/lib/xpeviewer/
mkdir -p  /usr/lib/translation/lang
cp -f $X_SOURCE_PATH/gui_source/translation/*.qm                    /usr/lib/xpeviewer/lang/
mkdir -p  /usr/lib/xpeviewer/signatures
cp -f $X_SOURCE_PATH/signatures/crypto.db                           /usr/lib/xpeviewer/signatures/
