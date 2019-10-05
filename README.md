# Run LittlevGL via PlatformIO

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

In linux just run:

```sh
sudo apt-get install libsdl2-dev
```

Note, this demo still needs care for easy install/build SDL drivers in other
operating systems.


### Install flasher drivers (optional)

If you plan to upload firmware & debug hardware, read notes in PlatformIO
[install docs](http://docs.platformio.org/en/latest/installation.html#troubleshooting).


### Build/Run

1. Clone this repository or download as zip.
2. In vscode, open folder via `File` -> `Open Folder...` menu.
   - If you do it first time - agree, when it suggests to install PlatformIO
     plugin, and wait when PlatformIO then install build tools and package
     dependencies.
3. Build via `Terminal` -> `Run Build Task...` -> `PlatformIO: Build`

If you succeeded with `native` build, you can run it this way:

```sh
./.pio/build/native/program
```

If `native` not yet supported for your OS, you still can do stm32 build,
upload and so on.
