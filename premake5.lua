workspace("Druid")
    configurations({"Debug", "Release"})
    platforms({"LinuxARM"})

    buildoptions({"-Wall", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code"})

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

    include("project.lua")
