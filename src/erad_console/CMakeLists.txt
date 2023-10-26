file(GLOB_RECURSE HEADERS
    *.h
)

file(GLOB_RECURSE SOURCES
    *.cpp
)

add_executable(erad_console ${HEADERS} ${SOURCES})

target_link_libraries(erad_console erad_lib)