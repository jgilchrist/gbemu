function(add_sources)
    foreach(source ${ARGN})
        if(NOT IS_ABSOLUTE "${source}")
            set(source "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        endif()

        set_property(
            GLOBAL APPEND PROPERTY
            "ALL_SRC_FILES"
            "${source}"
        )
    endforeach()
endfunction()

function(declare_library binary_name subdirectory)
    add_subdirectory(${subdirectory})

    get_property(sources GLOBAL PROPERTY ALL_SRC_FILES)
    add_library("${binary_name}" STATIC "${sources}")

    set_property(
        GLOBAL PROPERTY
        "ALL_SRC_FILES"
        ""
    )
endfunction()

function(declare_executable binary_name subdirectory)
    add_subdirectory(${subdirectory})

    get_property(sources GLOBAL PROPERTY ALL_SRC_FILES)
    add_executable("${binary_name}" "${sources}")

    set_property(
        GLOBAL PROPERTY
        "ALL_SRC_FILES"
        ""
    )
endfunction()
