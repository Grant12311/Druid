project "Druid"
    language "C++"
    cppdialect "C++17"
    filename "Druid"
    kind "StaticLib"
    targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"

    includedirs {"include", "vendor/glad/include/"}
    links {"GL"}

    files {"premake5.lua", "project.lua", ".gitignore", "src/**", "include/**"}
