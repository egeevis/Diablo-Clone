cmake_minimum_required(VERSION 3.10)
project(DiabloClone)

set(CMAKE_CXX_STANDARD 17)

# Raylib'i bul
find_package(raylib REQUIRED)

# Eğer find_package çalışmazsa, manuel yol belirtin
# include_directories("D:/raylib/include")
# link_directories("D:/raylib/lib")

add_executable(diablo_game main.cpp)

# Raylib'i link et
target_link_libraries(diablo_game raylib)

# Windows için gerekli kütüphaneler
if(WIN32)
    target_link_libraries(diablo_game opengl32 gdi32 winmm)
endif()