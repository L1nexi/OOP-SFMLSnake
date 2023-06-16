cmake_minimum_required(VERSION 3.24)
project(Snake)
set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/application)

set(SRC_LIST main.cpp Game.cpp Snake.cpp SnakeNode.cpp Fruit.cpp MenuScreen.cpp Screen.cpp GameScreen.cpp GameOverScreen.cpp OptionScreen.cpp World.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_directories(${PROJECT_NAME} PRIVATE SFML/lib)
target_include_directories(${PROJECT_NAME} PRIVATE SFML/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
