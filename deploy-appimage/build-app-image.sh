#!/bin/bash
make -C ../build-HuwInterpreter-Desktop-Release/
cp ../build-HuwInterpreter-Desktop-Release/HuwInterpreter huwcode/bin/huwcode
./linuxdeployqt-continuous-x86_64.AppImage huwcode/share/applications/huwcode.desktop -bundle-non-qt-libs
dt=`date '+%d%m%Y%H%M%S'`
cp AppRun "releases/huwcode$dt.AppImage"
