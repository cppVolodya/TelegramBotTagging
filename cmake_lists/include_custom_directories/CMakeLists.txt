function(GetSubdirectories result current_directory)
    list(APPEND result ${current_directory})

    file(GLOB_RECURSE subdirectories LIST_DIRECTORIES true "${current_directory}/*")

    foreach(directory ${subdirectories})
        if(IS_DIRECTORY ${directory})
            list(APPEND result ${directory})
        endif()
    endforeach()

    set(${result} PARENT_SCOPE)
endfunction()

GetSubdirectories(HEADER_DIRECTORIES "headers")
GetSubdirectories(SOURCE_DIRECTORIES "sources")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CONFIG_DIRECTORIES_FOR_WINDOWS config/windows/)
endif()

include_directories(${HEADER_DIRECTORIES}
                    ${SOURCE_DIRECTORIES}
                    ${CONFIG_DIRECTORIES_FOR_WINDOWS})
