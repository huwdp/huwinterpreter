#!/bin/bash
cp ../source/build/bin/HuwInterpreter huwcode/bin/huwcode
export VERSION=$(date '+%Y%m%d')
chmod +x linuxdeployqt-continuous-x86_64.AppImage 
./linuxdeployqt-continuous-x86_64.AppImage huwcode/share/applications/huwcode.desktop -appimage -bundle-non-qt-libs -verbose=2
#cp HuwCode-x86_64.AppImage "releases/huwcode$dt.AppImage"
#chmod a+x "releases/huwcode$dt.AppImage"
