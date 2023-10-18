include(GenerateExportHeader)

add_library(erad_lib SHARED erad.cpp)

GENERATE_EXPORT_HEADER(erad_lib)

target_include_directories(erad_lib PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(erad_lib PROPERTIES
        POSITION_INDEPENDENT_CODE 1
)

include(Format)
Format(erad_lib .)