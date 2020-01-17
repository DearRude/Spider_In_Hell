cmake_minimum_required(VERSION 3.15)
project(Spider_In_Hell C)
# Grab the screens
file(GLOB screen_sources "graphic/screens/*.c")
file(GLOB funcsources "gravity.c" "gameFlow.c")

set(CMAKE_C_STANDARD 99)
add_executable(${PROJECT_NAME} main.c ${screen_sources} ${funcsources})
target_link_libraries(Spider_In_Hell m)


target_link_libraries(${PROJECT_NAME} raylib)

file(COPY "graphic/resources/" DESTINATION "graphic/resources/")
