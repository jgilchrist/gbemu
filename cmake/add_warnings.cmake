function(add_warnings)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(extra_warn
        -Weverything
        -Wno-extra-semi-stmt
        -Wno-weak-vtables
        -Wno-exit-time-destructors
        -Wno-gnu-zero-variadic-macro-arguments
        -Wno-global-constructors
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
    )
    else()
    set(extra_warn
        -Wno-variadic-macros
        -Wno-unknown-pragmas
        -Wno-unused-variable
    )
    endif()

    set(all_warn
        ${extra_warn}
        -Wall
        -Wextra
        -Wpedantic
        -Wno-padded
        -Wno-format-nonliteral
        -Wno-unused-parameter
    )

    # FIXME: Temporarily silenced during development
    list(APPEND all_warn -Wno-sign-conversion)

    # FIXME: Temporarily silence warnings during development
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND all_warn -Wno-missing-noreturn)
    else()
    list(APPEND all_warn -Wno-return-type)
    endif()

    add_definitions(${all_warn})
endfunction()
