cmake_minimum_required(VERSION 3.28)
project(tetris-cpp LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp  "header/TetrisBlock.h" "src/TetrisBlock.cpp" "src/TetrisPiece.cpp" "header/TetrisPiece.h" "src/GameArea.cpp" "header/GameArea.h" "header/GameInfo.h" "header/Cell.h" "src/Cell.cpp"     "header/GameUI.h" "src/evh_native.cpp"    "header/TetrisEvents.h" "src/TetrisEvents.cpp" "src/GameUI.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
