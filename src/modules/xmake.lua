if is_plat("windows") then
    target("hello_mod")
        set_kind("binary")
        set_languages("c++latest", "clatest")
        add_files("msvc_core.cpp")
        set_values("msvc.modules.stdifcdir", true)
        set_policy("build.c++.modules", true) -- because no .mpp / .ixx / mxx / .cppm
end

target("math_mod")
    set_kind("binary")
    set_languages("c++latest", "clatest")
    add_files("math.cpp", "math.ixx")
