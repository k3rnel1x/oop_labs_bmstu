cmake_minimum_required(VERSION 3.16)
project(laba4 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()
include(CTest)

set(SOURCES
        abstract/IFileReader.h
        FacadeResult.h
        DrawSurfaceFacade.h
        DrawSurfaceFacade.cpp
        NormalizationParams.h
        FileReader.cpp
        FileReader.h
        abstract/ISceneDrawer.h
        3DPoint.h
        Vertex.h
        Figure.cpp
        Figure.h
        Edge.h
        TransformMatrix.cpp
        TransformMatrix.h
        TransformMatrixBuilder.cpp
        TransformMatrixBuilder.h
        Scene.h
        abstract/SceneObject.h
        Vertex.cpp
        tests/matrixTest.cpp
        tests/builderTest.cpp
        Edge.cpp
        Scene.cpp
)
add_library(libusinesslogic STATIC ${SOURCES})
set_target_properties(libusinesslogic PROPERTIES LINKER_LANGUAGE CXX)


# matrixTest
add_executable(matrixTest
        tests/matrixTest.cpp
        TransformMatrix.cpp
)
add_test(NAME matrixTest COMMAND matrixTest)

# builderTest
add_executable(builderTest
        tests/builderTest.cpp
        TransformMatrixBuilder.cpp
        TransformMatrix.cpp
        Vertex.cpp
)
add_test(NAME builderTest COMMAND builderTest)