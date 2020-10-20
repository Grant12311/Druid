workspace("Druid")
    language("C++")
    toolset("gcc")
    configurations({"Debug", "Release"})
    platforms({"LinuxARM"})

    links({"GL"})

    buildoptions({"-std=c++1z", "-Wall", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code"})

    filter("platforms:LinuxARM")
        architecture("ARM")
        system("linux")

    filter("configurations:Debug")
        symbols("On")
        buildoptions({"-pg"})
        linkoptions({"-pg", "-fsanitize=address", "-fsanitize=leak", "-static-libasan"})

    filter("configurations:Release")
        optimize("On")
        flags({"LinkTimeOptimization"})

    project("Druid")
        filename("Druid")
        kind("StaticLib")
        targetdir("bin/%{cfg.platform}/%{cfg.buildcfg}")

        files({"premake5.lua", ".gitignore", "src/*", "include/*"})
