# Run LittlevGL via PlatfomIO

This demo should help you to organize your project with awesome PlatfomIO IDE.

1. It automates installing everything - just open folder with this project in
   [vscode](https://code.visualstudio.com/), and agree to install all it offers.
2. It contains working LittlevGL demo, runnable on PC (via SDL drivers).
3. It has example, how to make multiple build targets. For example:
   - `native` to quickly prototype interfaces on PC
   - other, to build firmware for bare metal

## How to install & use demo

### Install vscode

https://code.visualstudio.com/ - follow instructions there, if you don't have
vscode yet.


### Install SDL drivers

This drivers required if you plan to use PC builds and run code without
hardware.

In linux just run:

```sh
sudo apt-get install libsdl2-dev
```

Or read about other possibilities at https://docs.littlevgl.com/en/html/get-started/pc-simulator.html#install-sdl-2.


### Build & run demo

1. Clone this repo or download as zip.
2. In vsccode, open folder via `File` -> `Open Folder...` menu.
   - If you do it first time - agree, when it suggests to install PlatformIO
     plugin, and whait when PlatformIO then install build tools and package
     dependencies.
3. Build via `Terminal` -> `Run Build Task...` -> `PlatformIO: Build`

Then you may run demo as

```sh
./.pio/build/native/program
```
