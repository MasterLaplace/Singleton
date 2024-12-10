set_languages("c++20")

set_version("1.0.3")

target("singleton")
    set_kind("library", {headeronly = true})

    add_headerfiles("*.h")
    add_headerfiles("*.hpp")
    add_includedirs(".", {public = true})
