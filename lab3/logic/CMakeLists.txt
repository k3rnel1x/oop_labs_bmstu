qt_add_library(logic STATIC
    facadecalculator.cpp
    deixtralg.cpp
)

target_link_libraries(logic PRIVATE Qt6::Widgets libc++.tbd c++)
target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})