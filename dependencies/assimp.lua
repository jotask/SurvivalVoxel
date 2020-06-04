project "assimp"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  systemversion "latest"
  architecture "x86_64"

  targetdir "../build/bin/%{cfg.buildcfg}"
  objdir "../build/obj/%{cfg.buildcfg}"

  disablewarnings {
    "4996",
    "4101",
    "4065",
    "4275",
    "4267"
  }

  defines {
    "ASSIMP_BUILD_NO_C4D_IMPORTER", -- Cinema4D is MSVC only and needs some weird headers to work
    "OPENDDL_STATIC_LIBARY",
  }

  files {
    "assimp/code/**.cpp",
    "assimp/code/**.h",
    "assimp/contrib/irrXML/*.cpp",
    "assimp/contrib/irrXML/*.h",
    "assimp/contrib/unzip/*.c",
    "assimp/contrib/unzip/*.h",
    "assimp/contrib/openddlparser/code/*.cpp",
    "assimp/contrib/poly2tri/poly2tri/**.cc",
    "assimp/contrib/clipper/*.cpp",
    "assimp/contrib/zlib/*.c",
    "assimp/contrib/zlib/*.h"
  }

  includedirs {
    "assimp/config/",
    "assimp/include/",
    "assimp/contrib/irrXML/",
    "assimp/contrib/rapidjson/include/",
    "assimp/contrib/openddlparser/include/",
    "assimp/contrib/unzip/",
    "assimp/contrib/zlib/",
    "assimp/"
  }

  removefiles {
    "assimp/code/Importer/IFC/IFCReaderGen_4.*",
  }

  filter "system:windows"
    systemversion "latest"
    cppdialect "C++17"

    buildoptions { "/bigobj" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

  filter "configurations:Debug"
    defines "ULLR_DEBUG"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines "ULLR_RELEASE"
    runtime "Release"
    optimize "on"

  filter "configurations:Dist"
    defines "ULLR_DIST"
    runtime "Release"
    optimize "on"