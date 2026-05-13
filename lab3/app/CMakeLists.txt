qt_add_executable(laba4
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_add_ui(laba4 SOURCES mainwindow.ui)

# find_package(QtLiquidGlass)
# target_link_libraries(laba4 PRIVATE QtLiquidGlass::QtLiquidGlass)

target_link_libraries(laba4 PRIVATE logic Qt6::Widgets libc++.tbd Qt6::Core)
target_include_directories(laba4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(laba4 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)