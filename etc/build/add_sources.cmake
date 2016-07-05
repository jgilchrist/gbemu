function(add_sources)
    foreach(source ${ARGN})
        if(NOT IS_ABSOLUTE "${source}")
            set(source "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        endif()

        set_property(
            GLOBAL APPEND PROPERTY
            "EMULATOR_SRCS"
            "${source}"
        )
    endforeach()
endfunction()

function(declare_executable binary_name)
    get_property(sources GLOBAL PROPERTY EMULATOR_SRCS)
    add_executable("${binary_name}" "${sources}")
endfunction()
