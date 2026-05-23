cmake_minimum_required(VERSION 3.16)
project(laba4 VERSION 0.1 LANGUAGES CXX)

set(SOURCES
        abstract/IFileReader.h
        abstract/IFacadeResult.h
        DrawSurfaceFacade.h
        DrawSurfaceFacade.cpp
        NormalizationParams.h
        FileReader.cpp
        FileReader.h
        abstract/ISceneDrawer.h
)
add_library(libusinesslogic STATIC ${SOURCES})
set_target_properties(libusinesslogic PROPERTIES LINKER_LANGUAGE CXX)