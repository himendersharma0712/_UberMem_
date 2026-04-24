cmake_minimum_required(VERSION 3.16)

project(UberMem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appUberMem
    main.cpp
)

qt_add_qml_module(appUberMem
    URI UberMem
    QML_FILES
        Main.qml
        SOURCES SystemProvider.h
        SOURCES SystemProvider.cpp
        SOURCES processData.h
        SOURCES processModel.h
        SOURCES processModel.cpp
        RESOURCES app.manifest
        RESOURCES resources.rc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appUberMem PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appUberMem
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appUberMem
    PRIVATE Qt6::Quick
)

install(TARGETS appUberMem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(appUberMem
    PRIVATE Qt6::Quick
)

if(WIN32)
    target_link_libraries(appUberMem PRIVATE kernel32 psapi)
endif()

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
endif()
