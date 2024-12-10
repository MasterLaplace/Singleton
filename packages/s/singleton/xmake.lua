package("singleton")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/MasterLaplace/Singleton")
    set_description("Implementation of a portable singleton in C/CPP following the stb style")
    set_license("MIT")

    set_urls("https://github.com/MasterLaplace/Singleton/archive/refs/tags/$(version).tar.gz",
             "https://github.com/MasterLaplace/Singleton.git")

    add_deps("cmake")

    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))

        import("package.tools.cmake").install(package, configs)
    end)
