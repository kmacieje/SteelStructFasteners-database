cmake_minimum_required(VERSION 3.5)

project(SteelStructFastenersTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

set(TEST_SOURCES
    Test.cpp
    ../src/mainwindow.cpp
    ../src/fasteners.cpp
    ../src/fastenerscollector.cpp
)

add_executable(SteelStructFastenersTests
    ${TEST_SOURCES}
)

target_include_directories(SteelStructFastenersTests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(SteelStructFastenersTests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

add_test(NAME SteelStructFastenersTests COMMAND SteelStructFastenersTests)
add_custom_target(run_test SteelStructFastenersTests)

