project "Druid"
    language "C++"
    cppdialect "C++17"
    filename "Druid" 
    kind "StaticLib"
    targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"

    includedirs {"include"}
    links {"GL"}

    files {"premake5.lua", "premake5-for-including.lua", ".gitignore", "src/**", "include/**"}
