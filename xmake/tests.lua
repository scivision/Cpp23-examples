target("tests")
    set_kind("phony")
    on_run(function(_)
        import("core.project.project")
        for _, target in pairs(project.targets()) do
            if not (target:name() == "tests") and target:kind() == "binary" then
                local should_fail = target:values("should_fail") or false
                print("Running test %s", target:name())
                local outdata = os.execv(target:targetfile(), {path.absolute("filesystem/is_symlink.cpp"), path.absolute("$(buildir)/test.lnk")}, {try = true})
                if should_fail then
                    assert(outdata == 1, format(">>>> %s FAILED (%s)", target:name(), outdata))
                else
                    assert(outdata == 0, format(">>>> %s FAILED (%s)", target:name(), outdata))
                end
                print(">>>> PASS")
            end
        end
    end)