project "Bullet3"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    files {
        "bullet3/src/Bullet3Collision/**.cpp",
        "bullet3/src/Bullet3Collision/**.h",

        "bullet3/src/Bullet3Common/**.cpp",
        "bullet3/src/Bullet3Common/**.h",

        "bullet3/src/Bullet3Dynamics/**.cpp",
        "bullet3/src/Bullet3Dynamics/**.h",
        
        "bullet3/src/Bullet3Geometry/**.cpp",
        "bullet3/src/Bullet3Geometry/**.h",
        
        "bullet3/src/Bullet3Serialize/**.cpp",
        "bullet3/src/Bullet3Serialize/**.h",
        
        "bullet3/src/BulletCollision/**.cpp",
        "bullet3/src/BulletCollision/**.h",
        
        "bullet3/src/BulletDynamics/**.cpp",
        "bullet3/src/BulletDynamics/**.h",
        
        "bullet3/src/BulletInverseDynamics/**.cpp",
        "bullet3/src/BulletInverseDynamics/**.h",
        
        "bullet3/src/BulletSoftBody/**.cpp",
        "bullet3/src/BulletSoftBody/**.h",
        
        "bullet3/src/LinearMath/**.cpp",
        "bullet3/src/LinearMath/**.h"
    }

    includedirs {
        "bullet3/src"
    }

    filter { "system:windows" }
        links { "OpenGL32" }

    filter { "system:not windows" }
        links { "GL" }

    filter "action:vs*"
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "action:not vs*"
        language "C"
        buildoptions { "-Wall" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"

    filter "system:macosx"
        defines { "GL_SILENCE_DEPRECATION" }