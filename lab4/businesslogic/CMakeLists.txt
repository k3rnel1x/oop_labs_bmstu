cmake_minimum_required(VERSION 3.16)
project(laba4 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()
include(CTest)


#setup qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
        io/abstract/IFileReader.h
        core/FacadeResult.h
        core/RendererFacade.h
        core/RendererFacade.cpp
        io/NormalizationParams.h
        io/CsvFileReader.cpp
        io/CsvFileReader.h
        renderer/abstract/ISceneDrawer.h
        math/3DPoint.h
        math/Vertex.h
        math/Figure.cpp
        math/Figure.h
        math/Edge.h
        math/TransformMatrix.cpp
        math/TransformMatrix.h
        math/TransformMatrixBuilder.cpp
        math/TransformMatrixBuilder.h
        renderer/Scene.h
        renderer/abstract/ISceneObject.h
        math/Vertex.cpp
        math/Edge.cpp
        renderer/Scene.cpp
        renderer/QtSceneDrawer.cpp
        renderer/QtSceneDrawer.h
        core/FacadeResult.cpp
        io/ObjFileReader.cpp
        io/ObjFileReader.h
)
add_library(libusinesslogic STATIC ${SOURCES}
        )
target_link_libraries(libusinesslogic PRIVATE Qt6::Widgets)
set_target_properties(libusinesslogic PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# matrixTest
add_executable(matrixTest
        tests/matrixTest.cpp
        math/TransformMatrix.cpp
)
target_link_libraries(matrixTest PRIVATE Qt6::Widgets)
add_test(NAME matrixTest COMMAND matrixTest)

# builderTest
add_executable(builderTest
        tests/builderTest.cpp
        math/TransformMatrixBuilder.cpp
        math/TransformMatrix.cpp
        math/Vertex.cpp
)
target_link_libraries(builderTest PRIVATE Qt6::Widgets)
add_test(NAME builderTest COMMAND builderTest)

# readsceneTest
add_executable(readsceneTest
        tests/readsceneTest.cpp
        math/TransformMatrixBuilder.cpp
        math/TransformMatrix.cpp
        math/Vertex.cpp
        math/Figure.cpp
        renderer/Scene.cpp
        io/CsvFileReader.cpp
        math/Edge.cpp
)
target_link_libraries(readsceneTest PRIVATE Qt6::Widgets)
add_test(NAME readsceneTest COMMAND readsceneTest)

# qtscenedrawerTest
add_executable(qtscenedrawerTest
        tests/qtscenedrawerTest.cpp
        math/TransformMatrixBuilder.cpp
        math/TransformMatrix.cpp
        math/Vertex.cpp
        math/Figure.cpp
        renderer/Scene.cpp
        math/Edge.cpp
        renderer/QtSceneDrawer.cpp
        io/CsvFileReader.cpp
)
target_link_libraries(qtscenedrawerTest PRIVATE Qt6::Widgets)
add_test(NAME qtscenedrawerTest COMMAND ./qtscenedrawerTest)

# rendererfacadeTest
add_executable(rendererfacadeTest
        ${SOURCES}
        core/FacadeResult.cpp
        tests/rendererfacadeTest.cpp
)
target_link_libraries(rendererfacadeTest PRIVATE Qt6::Widgets)
add_test(NAME rendererfacadeTest COMMAND ./rendererfacadeTest)