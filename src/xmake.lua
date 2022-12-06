target("numbers")
    set_languages("c++latest", "clatest")
    set_kind("binary")
    add_files("numbers.cpp")

target("folding")
    set_languages("c++17", "clatest")
    set_kind("binary")
    add_files("folding.cpp")

target("thread")
    set_languages("c++14", "clatest")
    set_kind("binary")
    add_files("thread_count.cpp")

target("coro")
    set_languages("c++latest", "clatest")
    add_files("coroutine.cpp")