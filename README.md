# Run LittlevGL via PlatformIO

[![Build Status](https://travis-ci.org/lvgl/lv_platformio.svg?branch=master)](https://travis-ci.org/lvgl/lv_platformio)

This demo should help you to organize your project with awesome PlatformIO IDE.

1. It automates installing everything - just open folder with this project in
   [vscode](https://code.visualstudio.com/), and agree to install all it offers.
2. It contains working LittlevGL demo, runnable on PC (via SDL drivers).
3. It has example, how to make multiple build targets. For example:
   - `native` to quickly prototype interfaces on PC
   - other, to build firmware for bare metal


## How to install & use demo

**Important!** `native` build (emulator with SDL2 drivers) was tested in
linux only! But you still can build MCU targets. If anyone interested to
improve other OS support (Windows, macOS) - PR welcome.


### Install Visual Studio Code

https://code.visualstudio.com/ - follow instructions there, if you don't have
vscode yet.


### Install SDL drivers

**Linux (Ubuntu, Debian, ...)**

```sh
sudo apt-get install gcc-multilib g++-multilib libsdl2-dev:i386
```

Note:

- We use 32-bits build for more correct memory stat info. You can
  disable this in `platformio.ini` (see comments inside), and use `libsdl2-dev`
  instead.
- If you have conflicts on `libsdl2-dev:i386` install, remove 64-bits version
  and dependencies first.

**MacOS**

Use [Homebrew](https://brew.sh/):

```sh
brew install sdl2
```

**Windows**

Use [MSYS2](https://www.msys2.org/)

```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2
```

Add the path to your Mingw-w64 `bin` folder to the Windows PATH environment
variable (usually `C:\msys64\mingw64\bin`). See [instruction, 4](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites).


### Install flasher drivers (optional)

If you plan to upload firmware & debug hardware, read notes in PlatformIO
[install docs](http://docs.platformio.org/en/latest/installation.html#troubleshooting).


### Build/Run

1. Clone this repository or download as zip.
2. In vscode, open folder via `File` -> `Open Folder...` menu.
   - If you do it first time - agree, when it suggests to install PlatformIO
     plugin, and wait when PlatformIO then install build tools and package
     dependencies.
3. Build / execute:
   - **Simulator**: `Terminal` -> `Run Task...` -> `PlatformIO: Execute (native)`
   - **Bare metal**: `Terminal` -> `Run Build Task...` -> `PlatformIO: Build (stm32f429_disco)`
