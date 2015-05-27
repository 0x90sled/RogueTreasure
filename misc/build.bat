@echo off
mkdir ..\build
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall" x64
pushd ..\build
cl ..\source\rogue_treasure.cc
popd