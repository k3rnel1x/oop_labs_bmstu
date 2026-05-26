cmake_minimum_required(VERSION 3.16)
project(laba4 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()
include(CTest)

set(SOURCES
        io/abstract/IFileReader.h
        core/FacadeResult.h
        core/RendererFacade.h
        core/RendererFacade.cpp
        io/NormalizationParams.h
        io/FileReader.cpp
        io/FileReader.h
        core/abstract/ISceneDrawer.h
        math/3DPoint.h
        math/Vertex.h
        math/Figure.cpp
        math/Figure.h
        math/Edge.h
        math/TransformMatrix.cpp
        math/TransformMatrix.h
        math/TransformMatrixBuilder.cpp
        math/TransformMatrixBuilder.h
        core/Scene.h
        core/abstract/ISceneObject.h
        math/Vertex.cpp
        tests/matrixTest.cpp
        tests/builderTest.cpp
        math/Edge.cpp
        core/Scene.cpp
        tests/readsceneTest.cpp
)
add_library(libusinesslogic STATIC ${SOURCES})
set_target_properties(libusinesslogic PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# matrixTest
add_executable(matrixTest
        tests/matrixTest.cpp
        math/TransformMatrix.cpp
)
add_test(NAME matrixTest COMMAND matrixTest)

# builderTest
add_executable(builderTest
        tests/builderTest.cpp
        math/TransformMatrixBuilder.cpp
        math/TransformMatrix.cpp
        math/Vertex.cpp
)
add_test(NAME builderTest COMMAND builderTest)

# readsceneTest
add_executable(readsceneTest
        tests/readsceneTest.cpp
        math/TransformMatrixBuilder.cpp
        math/TransformMatrix.cpp
        math/Vertex.cpp
        math/Figure.cpp
        core/Scene.cpp
        io/FileReader.cpp
        math/Edge.cpp
)
add_test(NAME readsceneTest COMMAND readsceneTest)