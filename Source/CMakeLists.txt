cmake_minimum_required (VERSION 3.7)

project("HibikiOrigins")

set(MAIN Main.cpp GameController.cpp GlobalVariables.cpp)

set(FACTORIES Factories/GameObjectFactory.cpp)

set(GAME_OBJECTS GameObjects/DynamicGameObject.cpp GameObjects/Player.cpp GameObjects/Enemy.cpp
    GameObjects/MenuButton.cpp GameObjects/AnimatedGraphic.cpp GameObjects/CollisionGameObject.cpp
    GameObjects/Collider.cpp GameObjects/StaticGameObject.cpp)

set(LEVELS Levels/Level.cpp Levels/TileLayer.cpp Levels/LevelParser.cpp)

set(LIBS Libs/tinyXml/tinyxml2.cpp
         Libs/base64/base64.cpp)

set(MANAGERS Managers/TextureManager.cpp Managers/InputManager.cpp)

set(STATES States/StateParser.cpp States/MainMenuState.cpp States/GameStateMachine.cpp 
    States/PlayState.cpp States/PauseState.cpp States/GameOverState.cpp)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_mixer SDL2_image SDL2_net SDL2_gfx zlib)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
add_executable(${PROJECT_NAME}  ${MAIN} ${FACTORIES} ${GAME_OBJECTS} ${LEVELS} ${LIBS} ${MANAGERS} ${STATES} icon.rc)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
