set_project("Singleton")
set_languages("c++20")

set_version("1.0.2")

target("Singleton")
    set_kind("library", {headeronly = true})

    add_headerfiles("*.h")
    add_headerfiles("*.hpp")
    add_includedirs(".", {public = true})
