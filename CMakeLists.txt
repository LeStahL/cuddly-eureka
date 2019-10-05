# cuddly-eureka - Storyboard editor by Team210
# Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.8)

project(cuddly-eureka)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Tell CMake to run qt tools when necessary (For Qt5 GUIs among other things)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the right python interpreter version
find_package(Qt5 COMPONENTS Widgets Gui)

set(CUDDLY_SOURCES
    CuddlyEureka.cpp
    
    ui/MainWindow.cpp
    ui/MainWindow.ui
    ui/MainWindow.qrc
    
    model/Demo.cpp
    model/DemoModel.cpp
    model/Scene.cpp
    model/AddSceneCommand.cpp
    model/RemoveSceneCommand.cpp
    model/DemoValueChangeCommand.cpp
)

add_executable(cuddly-eureka ${CUDDLY_SOURCES})
target_link_libraries(cuddly-eureka Qt5::Widgets Qt5::Gui)

if(WIN32)
    get_filename_component(_qt_bin_dir "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS "${_qt_bin_dir}")
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    add_custom_command(TARGET cuddly-eureka COMMAND ${WINDEPLOYQT_EXECUTABLE} "${PROJECT_BINARY_DIR}")
endif()
