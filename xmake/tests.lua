target("tests")
    set_kind("phony")
    on_run(function(_)
        import("core.project.project")
        function dump(o)
            if type(o) == 'table' then
               local s = "{ "
               for k,v in pairs(o) do
                  if type(k) ~= 'number' then k = '"'..k..'"' end
                  s = s .. '['..k..'] = ' .. dump(v) .. ','
               end
               return s .. " }"
            else
               return tostring(o)
            end
        end
        for _, target in pairs(project.targets()) do
            if not (target:name() == "tests") and target:kind() == "binary" then
                local should_fail = target:values("should_fail") or false
                local args = (target:name() == "symlink") and {path.absolute(target:targetfile()), path.absolute("build/test.lnk")} or {}
                print("Running test %s %s", target:name(), dump(args))
                local outdata = os.execv(target:targetfile(), args, {try = true})
                if should_fail then
                    assert(outdata == 1, format(">>>> %s FAILED (%s)", target:name(), outdata))
                else
                    assert(outdata == 0, format(">>>> %s FAILED (%s)", target:name(), outdata))
                end
                print(">>>> PASS")
            end
        end
    end)
