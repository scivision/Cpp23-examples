target("filesep")
    set_kind("binary")
    set_languages("c++17", "clatest")
    add_files("filesep.cpp")

target("canonical_demo")
    set_kind("binary")
    set_languages("c++17", "clatest")
    add_files("canonical_demo.cxx", "canonical.cxx")
    add_headerfiles("canonical_demo.hpp")

local buildir = "$(buildir)"

target("symlink")
    set_kind("binary")
    set_languages("c++17", "clatest")
    add_files("is_symlink.cpp")

    -- on_run(function(target)
        -- print("AAAAAAAAAAAAAAAA", path.join(target:scriptdir(), "is_symlink.cpp"), path.join(path.absolute(buildir), "test.lnk"))
        -- os.runv(target:targetfile(), {path.join(target:scriptdir(), "is_symlink.cpp")}, {path.join(path.absolute(buildir), "test.lnk")})
    -- end)