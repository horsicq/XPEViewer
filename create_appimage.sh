#!/bin/bash -x
export X_SOURCE_PATH=$PWD
export X_RELEASE_VERSION=$(cat "release_version.txt")
export VERSION=$X_RELEASE_VERSION

source build_tools/linux.sh

create_image_app_dir xpeviewer

cp -f $X_SOURCE_PATH/build/release/xpeviewer                        $X_SOURCE_PATH/release/appDir/usr/bin/
cp -f $X_SOURCE_PATH/DEBIAN/xpeviewer.desktop                       $X_SOURCE_PATH/release/appDir/usr/share/applications/
sed -i "s/#VERSION#/1.0/"                                           $X_SOURCE_PATH/release/appDir/usr/share/applications/xpeviewer.desktop
cp -Rf $X_SOURCE_PATH/DEBIAN/hicolor/                               $X_SOURCE_PATH/release/appDir/usr/share/icons/
cp -Rf $X_SOURCE_PATH/XStyles/qss/                                  $X_SOURCE_PATH/release/appDir/usr/lib/xpeviewer/
mkdir -p $X_SOURCE_PATH/release/appDir/usr/lib/xpeviewer/signatures
cp -f $X_SOURCE_PATH/signatures/crypto.db                           $X_SOURCE_PATH/release/appDir/usr/lib/xpeviewer/signatures/

cd $X_SOURCE_PATH/release

linuxdeployqt $X_SOURCE_PATH/release/appDir/usr/share/applications/xpeviewer.desktop -appimage -always-overwrite
#mv *.AppImage xpeviewer_${X_RELEASE_VERSION}.AppImage

cd $X_SOURCE_PATH

rm -Rf $X_SOURCE_PATH/release/appDir
