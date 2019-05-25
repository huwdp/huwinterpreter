#!/bin/bash
rm *HuwCode*.AppImage
make -C ../build-HuwInterpreter-Desktop-Release/
cp ../build-HuwInterpreter-Desktop-Release/HuwInterpreter huwcode/bin/huwcode
export VERSION=$(date '+%Y%m%d')
./linuxdeployqt-continuous-x86_64.AppImage huwcode/share/applications/huwcode.desktop -appimage -bundle-non-qt-libs -verbose=2
#cp HuwCode-x86_64.AppImage "releases/huwcode$dt.AppImage"
#chmod a+x "releases/huwcode$dt.AppImage"
