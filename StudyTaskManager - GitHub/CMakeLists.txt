cmake_minimum_required(VERSION 3.19)
project(StudyTaskManager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(StudyTaskManager
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui


    task.h
    taskmanager.h
    taskmanager.cpp
    icons.qrc





)

# Compile icons.qrc
qt_add_resources(ICONS_RESOURCES icons.qrc)
target_sources(StudyTaskManager PRIVATE ${ICONS_RESOURCES})

target_link_libraries(StudyTaskManager
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS StudyTaskManager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET StudyTaskManager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
