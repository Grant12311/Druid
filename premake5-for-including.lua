project("Druid")
    language("C++")
    toolset("gcc")
    filename("Druid")
    kind("StaticLib")
    configurations({"Debug", "Release"})
    platforms({"LinuxARM"})

    targetdir("bin/%{cfg.platform}/%{cfg.buildcfg}")

    buildoptions({"-std=c++1z", "-Wall", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code"})

    includedirs({"include"})
    links({"GL"})

    files({"premake5.lua", "premake5-for-including.lua", ".gitignore", "src/**", "include/**"})

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
        defines({"DRUID_DISABLE_GLCALL"})
