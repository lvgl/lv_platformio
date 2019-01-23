# Run LittelvGL in on PC using PlatfomIO

This repository contains a PlatformIO project to test LittelvGL on your PC. 

### Install SDL

The [SDL library](https://www.libsdl.org/) need to installed to run the project. You will find a step-by-step GUI about the installation [here](https://docs.littlevgl.com/#PC-simulator)
(It's super easy on Linux but sometimes tricky on Windows and OSX.)

### Open the project
I assume that you already have a working PlatformIO environment with Visual Studio Code.
1. Clone this repo with `git clone https://github.com/littlevgl/pc_simulator_sdl_platformio.git` anywhere you want or [download it as zip from GitHub](https://github.com/littlevgl/pc_simulator_sdl_platformio/archive/master.zip).
2. In Visual Studio Code click **File/Add folder to workspace** and browse the **lv_pio_sdl** folder in the cloned or downloaded project

### Build and run
3. Click the pipe icon on the left bottom corner to build the project. 
4. Run the compiled file from the terminal of Visual Studio Code: `./.pioenvs/native/program`




