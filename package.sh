#! /bin/bash
mkdir package
cp build/qvbam build/qml manifest.json qvbam.desktop qvbam.json ./package -rf
cd package
click build .
cp *.click ..
cd ..
#rm -rf package

