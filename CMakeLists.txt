# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

if(EXISTS ${32BLIT_DIR}/32blit-pico/sdk_import.cmake)
    include(${32BLIT_DIR}/32blit-pico/sdk_import.cmake)
endif()

# Replace "game" with a name for your project (this is used the name of the output)
project(TowerDefense)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE
    src/game.cpp src/game.hpp
    src/logic-objects/builder.cpp src/logic-objects/builder.hpp
    src/logic-objects/credits.cpp src/logic-objects/credits.hpp
    src/game-objects/chest.cpp src/game-objects/chest.hpp
    src/game-objects/enemies/enemy.cpp src/game-objects/enemies/enemy.hpp
    src/game-objects/enemies/medium_enemy.cpp src/game-objects/enemies/medium_enemy.hpp
    src/game-objects/enemies/hard_enemy.cpp src/game-objects/enemies/hard_enemy.hpp
    src/game-objects/turret.cpp src/game-objects/turret.hpp
    src/utils/map.cpp src/utils/map.hpp
    src/utils/ui_overlay.cpp src/utils/ui_overlay.hpp
    src/utils/utils.cpp src/utils/utils.hpp
    src/handlers/chest_handler.cpp src/handlers/chest_handler.hpp
    src/handlers/enemy_handler.cpp src/handlers/enemy_handler.hpp
    src/handlers/turret_handler.cpp src/handlers/turret_handler.hpp
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
target_compile_definitions(${PROJECT_NAME} PRIVATE ALLOW_HIRES=0)
add_custom_target(flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install(FILES ${PROJECT_DISTRIBS} DESTINATION .)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
