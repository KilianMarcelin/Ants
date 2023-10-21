cmake_minimum_required(VERSION 3.26)
project(Ants)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ants
        main.cpp
        Environment.h
        Environment.cpp
        MathUtils.h
        Rectangle.h
        Renderer.h
        Renderer.cpp
        Timer.h
        Timer.cpp
        Vector2.h
        Agent.h
        Agent.cpp
        Food.h
        Anthill.h
        AntBase.h
        SillyAnt.h
        Pheromone.h
        AntBasePheromone.h
)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(Ants PRIVATE SDL2::SDL2_gfx)
target_link_libraries(Ants
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)