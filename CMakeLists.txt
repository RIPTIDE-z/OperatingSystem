cmake_minimum_required(VERSION 3.19)
project(MovingCar LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
# 开启 RCC
set(CMAKE_AUTORCC ON)

qt_add_executable(MovingCar
    WIN32 MACOSX_BUNDLE
    main.cpp
    movingcar.cpp
    movingcar.h
    movingcar.ui
    resources.qrc
)

target_link_libraries(MovingCar
    PRIVATE
        Qt::Core
        Qt::Widgets
)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)