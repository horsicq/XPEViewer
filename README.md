[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=NF3FBD3KHMXDN)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/horsicq/XPEViewer.svg)](https://github.com/horsicq/XPEViewer/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/horsicq/XPEViewer/total.svg)](https://github.com/horsicq/XPEViewer/releases)
[![gitlocalized ](https://gitlocalize.com/repo/4736/whole_project/badge.svg)](https://gitlocalize.com/repo/4736/whole_project?utm_source=badge)

PE file viewer/editor for Windows, Linux and MacOS.

* Hex
* Disassembler
* Entropy
* Signature scan

![alt text](https://github.com/horsicq/XPEViewer/blob/master/mascots/xpeviewer.png "Mascot")

![alt text](https://github.com/horsicq/XPEViewer/blob/master/docs/1.png "1")
![alt text](https://github.com/horsicq/XPEViewer/blob/master/docs/2.png "2")
![alt text](https://github.com/horsicq/XPEViewer/blob/master/docs/3.png "3")
![alt text](https://github.com/horsicq/XPEViewer/blob/master/docs/4.png "4")

How to build on Linux(Debian package)
=======

Install packages:

- sudo apt-get install qtbase5-dev -y
- sudo apt-get install qttools5-dev-tools -y
- sudo apt-get install git -y
- sudo apt-get install build-essential -y
- sudo apt-get install qt5-default -y

git clone --recursive https://github.com/horsicq/XPEViewer.git

cd XPEViewer

Run build script: bash -x build_dpkg.sh

Install deb package: sudo dpkg -i release/die_[Version].deb

Run: *xpeviewer [FileName]*

How to build on Linux(Automake)
=======

Qt framework has to be installed on the system.

(Ubuntu)Install Qt Framework: **sudo apt-get install --quiet --assume-yes build-essential qt5-default qtbase5-dev qttools5-dev-tools **

Clone project: git clone --recursive https://github.com/horsicq/XPEViewer.git

- chmod a+x configure
- ./configure
- make
- sudo make install

Run: *xpeviewer [FileName]*

How to build on OSX
=======

Install Qt 5.15.2: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XPEViewer.git

Edit build_mac.sh ( check QMAKE_PATH variable)

Run build script: bash -x build_mac.sh

How to build on Windows(XP)
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XPEViewer.git

Edit build_winxp.bat ( check VSVARS_PATH,  SEVENZIP_PATH, QMAKE_PATH variables)

Run build_winxp.bat

How to build on Windows(7-10)
=======

Install Visual Studio 2019: https://github.com/horsicq/build_tools

Install Qt 5.15.2 for VS2019: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XPEViewer.git

Edit build_win32.bat ( check VSVARS_PATH,  SEVENZIP_PATH, QMAKE_PATH variables)

Edit build_win64.bat ( check VSVARS_PATH,  SEVENZIP_PATH, QMAKE_PATH variables)

Run build_win32.bat

Run build_win64.bat

![alt text](https://github.com/horsicq/XPEViewer/blob/master/mascots/xpeviewer_full.png "Mascot")
