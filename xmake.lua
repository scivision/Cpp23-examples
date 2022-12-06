set_xmakever("2.7.3")
set_project("cxx-modules-sandbox")
add_rules("mode.debug", "mode.release")

includes("filesystem/xmake.lua")
includes("modules/xmake.lua")
includes("src/xmake.lua")
includes("xmake/tests.lua")
