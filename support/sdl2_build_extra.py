Import("env", "projenv")

for e in [ env, projenv ]:
    # If compiler uses `-m32`, propagate it to linker.
    # Add via script, because `-Wl,-m32` does not work.
    if "-m32" in e['CCFLAGS']:
        e.Append(LINKFLAGS = ["-m32"])

# Override unused "upload" to execute compiled binary
#from SCons.Script import AlwaysBuild
#AlwaysBuild(env.Alias("upload", "$BUILD_DIR/${PROGNAME}", "$BUILD_DIR/${PROGNAME}"))

# Add custom target to explorer
env.AddTarget(
    name = "execute",
    dependencies = "$BUILD_DIR/${PROGNAME}",
    actions = "$BUILD_DIR/${PROGNAME}",
    title = "Execute",
    description = "Build and execute",
    group="General"
)

#print('=====================================')
#print(env.Dump())
