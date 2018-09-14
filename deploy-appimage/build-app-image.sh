#!/bin/bash
make -C ../build-HuwInterpreter-Desktop-Release/
cp ../build-HuwInterpreter-Desktop-Release/HuwInterpreter huwcode/bin/huwcode
./linuxdeployqt-continuous-x86_64.AppImage huwcode/share/applications/huwcode.desktop -appimage -bundle-non-qt-libs -verbose=2
dt=`date '+%Y%m%d'`
cp HuwCode-x86_64.AppImage "releases/huwcode$dt.AppImage"
chmod a+x "releases/huwcode$dt.AppImage"
