cmake_minimum_required(VERSION 3.19)
project(colutius)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/ui/widget.cpp
        src/ui/widget.h
        src/ui/widget.ui
        src/ui/login.cpp
        src/ui/login.h
        src/ui/login.ui
        src/ui/config.cpp
        src/ui/config.h
        src/ui/config.ui
        src/ui/systemTrayIcon.cpp
        src/ui/systemTrayIcon.h
        src/ui/bochatwidget.cpp
        src/ui/bochatwidget.h

        src/irc/client.cpp
        src/irc/client.h
        src/irc/server.cpp
        src/irc/server.h
        src/irc/channel.cpp
        src/irc/channel.h
        src/irc/message.cpp
        src/irc/message.h
        src/irc/fileio.h
        src/irc/fileio.cpp

        resource/resource.qrc
        resource/img/logo.rc
        )

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
