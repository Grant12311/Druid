workspace "Druid"
    language "C++"
    cppdialect "C++17"
    configurations {"Debug", "Release"}
    platforms {"LinuxX64", "LinuxX86", "LinuxARM", "WindowsARM", "WindowsX86", "WindowsX64"}
    startproject "Name"

    flags {"MultiProcessorCompile"}
    buildoptions {"-pipe", "-Wall"}
    defines {}

    links {}
    includedirs {"%{wks.location}/include/"}

    filter "action:vs*"
        toolset "msc"

    filter "action:not vs*"
        toolset "gcc"
        buildoptions {"-Wextra", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code", "-Wshadow", "-Wconversion", "-Wno-switch", "-Wno-unused-variable"}

    filter "platforms:Linux*"
        system "linux"
    filter "platforms:Windows*"
        system "windows"

    filter "platforms:*ARM"
        architecture "ARM"
    filter "platforms:*X86"
        architecture "x86"
    filter "platforms:*X64"
        architecture "x86_64"

    filter "configurations:Debug"
        symbols "On"
        buildoptions {"-pg", "-fsanitize=address", "-fsanitize=leak", "-static-libasan"}
        linkoptions {"-pg", "-fsanitize=address", "-fsanitize=leak", "-static-libasan"}

    filter "configurations:Release"
        optimize "On"
        defines {"DRUID_DISABLE_GLCALL"}

    include "project.lua"
