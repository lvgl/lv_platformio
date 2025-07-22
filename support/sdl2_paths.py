Import("env")
import sys
import os
import glob

if sys.platform.startswith("darwin"):
    #sdl_include_path = !find /opt/homebrew/Cellar/sdl2 -name "include" | sed "s/^/-I /"
    sdl_include = glob.glob("/opt/homebrew/Cellar/sdl2/*/include", recursive=True)
    if sdl_include:
        print(f"Found Homebrew SDL include path: {sdl_include[0]}")
        env.Append(
            CPPPATH=sdl_include[0]
        )
    sdl_lib = glob.glob("/opt/homebrew/Cellar/sdl2/**/libSDL2.a", recursive=True)
    if sdl_lib:
        print(f"Found Homebrew SDL lib path: {sdl_lib[0]}")
        env.Append(
            LIBPATH=os.path.dirname(sdl_lib[0])
        )

elif sys.platform.startswith("win"):
    msys_root = "C:\\msys64\\mingw64"
    sdl_include = os.path.join(msys_root, "include")
    sdl_lib = os.path.join(msys_root, "lib")
    if os.path.exists(sdl_include):
        print(f"Found MSYS2 SDL include path: {sdl_include}")
        env.Append(CPPPATH=[sdl_include])
    libSDL = os.path.join(sdl_lib, "libSDL2.a")
    if os.path.exists(libSDL):
        print(f"Found MSYS2 SDL lib path: {libSDL}")
        env.Append(LIBPATH=[sdl_lib], LIBS=["SDL2"])    
    
#breakpoint()
    
#print('NewENV=====================================')
#print(env.Dump())
#print('DefaultENV=====================================')
#print(DefaultEnvironment().Dump())
