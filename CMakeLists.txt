cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME FlappyBird)
project(${PROJECT_NAME})

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Статическая линковка
add_definitions(-DSFML_STATIC)

# Пути к заголовочным файлам
include_directories(
    inc/
    ext/SFML/include/
)

# Пути к библиотекам
link_directories(ext/SFML/lib/)

# Файлы исходников
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Создаём исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем библиотеки SFML (Debug + Static)
target_link_libraries(${PROJECT_NAME}
    sfml-graphics-s-d
    sfml-window-s-d
    sfml-system-s-d
    sfml-audio-s-d
    opengl32
    freetype
    winmm
    gdi32
    openal32
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
)

# Копируем папку sprites рядом с .exe (в Debug)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)
