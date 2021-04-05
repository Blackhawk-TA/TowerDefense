# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

# Replace "game" with a name for your project (this is used the name of the output)
project(TowerDefense)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE
    src/game.cpp src/game.hpp
    src/objects/enemy.cpp src/objects/enemy.hpp
    src/objects/chest.cpp src/objects/chest.hpp
    src/utils/utils.cpp src/utils/utils.hpp
    src/utils/map.cpp src/utils/map.hpp
    src/handlers/enemies.cpp src/handlers/enemies.hpp
    src/handlers/enemies.cpp src/handlers/enemies.hpp
    src/handlers/chests.cpp src/handlers/chests.hpp
)

# ... and any other files you want in the release here
set(PROJECT_DISTRIBS LICENSE.md README.md)

# Build configuration; approach this with caution!
if (MSVC)
    add_compile_options("/W4" "/wd4244" "/wd4324" "/wd4458" "/wd4100")
else ()
    add_compile_options("-Wall" "-Wextra" "-Wdouble-promotion" "-Wno-unused-parameter")
endif ()

find_package(32BLIT CONFIG REQUIRED PATHS ../32blit-sdk)

blit_executable(${PROJECT_NAME} ${PROJECT_SOURCE})
blit_assets_yaml(${PROJECT_NAME} assets.yml)
blit_metadata(${PROJECT_NAME} metadata.yml)
add_custom_target(flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install(FILES ${PROJECT_DISTRIBS} DESTINATION .)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
