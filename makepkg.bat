@echo off

g++ main.cpp -o admin.exe
windres app.manifest -O coff -o manifest.res
g++ main.cpp manifest.res -o admin.exe