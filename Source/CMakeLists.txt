cmake_minimum_required (VERSION 3.7)
#set(PROJECT_NAME="Simple2D")

project("HibikiOrigins")

set(TEMP MainMenuState.cpp GameStateMachine.cp PlayState.cpp MenuButton.cpp PauseState.cpp 
AnimatedGraphic.cpp GameOverState.cpp StateParser.cpp Level.cpp TileLayer.cpp 
LevelParser.cpp GlobalVariables.cpp ObjectLayer.cpp)

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_mixer SDL2_image SDL2_net SDL2_gfx zlib)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} Main.cpp Game.cpp TextureManager.cpp InputHandler.cpp
SDLGameObject.cpp Player.cpp Enemy.cpp GameObjectFactory.cpp

tinyXml/tinyxml.cpp tinyXml/tinystr.cpp tinyXml/tinyxmlerror.cpp tinyXml/tinyxmlparser.cpp tinyXml/tinyxml.h
tinyXml/tinystr.h base64/base64.cpp icon.rc)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})