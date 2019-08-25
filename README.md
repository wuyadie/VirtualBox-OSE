# VirtualBox OSE (Open Source Edition)

## Summary

Oracle VirtualBox Open Source Edition, with custom build toolchain, letting build the solution on any Windows workstation.
Official Oracle source code is optimized for Oracle own infrastructure, which structure is not known, and the process is not documented.

This version allows to compile Virtualbox on Windows 7, 8.1 or any Windows 10. It includes configurations for Virtualbox itself, and Virtualbox Guest Additions for Windows.
Build host should have `x64` architecture.

## Pre-requisites

### Compilers and developer tools

* Windows Software Developer Kit 7.1
* Windows Software Developer Kit 8.1
* Windows Driver Developer Kit 7.1
* Windows Driver Developer Kit 8.0
* Visual Studio 2010 SP1 Professional
* Visual Studio 2013 Update 5 Professional or Ultimate
* ActivePerl 5.26
* ActivePython 2.7
* NASM 2.14
* WiX 3.11
* Cygwin 3.0
* cURL 7.64
* gSOAP 2.8
* MiKTeX 2.9
* DocBook XML DTD 4.5
* DocBook XSL Stylesheets 1.69

### Frameworks and libraries

* Qt 5.6.3
* OpenSSL 1.1.1b
* cURL 7.64
* SDL 1.2
* MinGW 4.5.4
* libvpx 1.7.0
* libopus 1.3

### Tools specific for VirtualBox Guest Additions build

* CDRTools 3.02a
* DIFx 7600.16385.1
* AutoIT 3.3.14
* NSIS 2.51
* NSIS 2.51 Logs Patch

## Compiling Virtualbox OSE under Windows

x64 version of the system is required, Windows 7, 8.0, 8.1 or any Windows 10 are fit for the compilation process.

Use VirtualBox project root as a wolrking directory.

### Set VBOX_VER and other environment variables

```cd /d %~dp0
for /f "tokens=3" %%i in ('findstr /B /R /C:"VBOX_VERSION_MAJOR *=" Version.kmk') do SET VBOX_VER_MJ=%%i
for /f "tokens=3" %%i in ('findstr /B /R /C:"VBOX_VERSION_MINOR *=" Version.kmk') do SET VBOX_VER_MN=%%i
for /f "tokens=3" %%i in ('findstr /B /R /C:"VBOX_VERSION_BUILD *=" Version.kmk') do SET VBOX_VER_BLD=%%i
for /f "tokens=6" %%i in ('findstr /C:"$Rev: " Config.kmk') do SET VBOX_REV=%%i
for /f "tokens=3" %%i in ('findstr /B /C:"VBOX_BUILD_PUBLISHER :=" LocalConfig.kmk') do SET VBOX_VER_PUB=%%i

set VERSION=%VBOX_VER_MJ%.%VBOX_VER_MN%.%VBOX_VER_BLD%%VBOX_VER_PUB%-r%VBOX_REV%
set VBOX_VER_MJ=
set VBOX_VER_MN=
set VBOX_VER_BLD=
set VBOX_VER_PUB=
```

### Set MS Visual C++ valiables

`call C:\WinSDK\7.1\Bin\SetEnv.Cmd /Release /x64 /win7`

### Set target architecture and toolchain binaries

Depend on what's the target architecture you want to compile, run the following for amd64 target

```
set BUILD_TARGET_ARCH=amd64
set PATH=%PATH%;%~dp0kBuild\bin\win.amd64
```

Or this one for x86 target

```
set BUILD_TARGET_ARCH=x86
set PATH=%PATH%;%~dp0kBuild\bin\win.x86
```

### Run configure.vbs script

`cscript configure.vbs --with-DDK=<Windows DDK install path> --with-MinGW-w64=<MinGW x64 libraries path> --with-MinGW32=<MinGW x86 libraries path> --with-libSDL=<SDL libraries path> --with-openssl=<OpenSSL x64 libraries path> --with-openssl32=<OpenSSL x86 libraries path> --with-libcurl=<libCURL x64 libraries path> --with-libcurl32=<libCURL x86 libraries path> --with-Qt5=<Qt root path> --with-libvpx=<libVPX libraries path> --with-libopus=<libopus x64 libraries path> --with-python=<ActivePython 2.7 root path>`

### Set last configuration parameters and build the project

Set last environment variables

`call env.bat`

Run kmake with default target

`kmk`

### Register COM components allowing run and debug Virtualbox.exe

For amd64 target set the following working directory

`cd .\out\win.amd64\release\bin\`

and this directory x86 respectively

`cd .\out\win.x86\release\bin\`

Register Virtualbox Windows COM DLLs

`call comregister.cmd`

Load debug versions of drivers

`call loadall.cmd`

Perform cleanup

`del /q AutoConfig.kmk configure.log env.bat 2>nul`

## Compiling Virtualbox Guest Additions for Windows

Virtualbox Guest Additions for Windows should be compiled on the same host, but in the different directory.

### Differences between Virtualbox.exe and Additions build

Instead of `kmk` command, building the default target, you shoud set special target for building additions

`kmk additions-build`

and one more for packing it into ISO image

`kmk additions-packing`

### Differences in LocalConfig.kmk

You should set the following parameters to your LocalConfig.kmk, if you want to build additions only

```VBOX_ONLY_ADDITIONS := 1
VBOX_WITH_ADDITIONS_PACKING := 1
VBOX_WITHOUT_HARDENING := 1
VBOX_ADDITIONS_WINDOWS_ONLY := 1
```



