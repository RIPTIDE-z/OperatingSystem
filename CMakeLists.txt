cmake_minimum_required(VERSION 3.19)
project(MovingCar LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

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

include(GNUInstallDirs)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS MovingCar
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MovingCar
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
