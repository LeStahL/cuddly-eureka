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

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.12.1\\msvc2017_64")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

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
)

add_executable(cuddly-eureka ${CUDDLY_SOURCES})
target_link_libraries(cuddly-eureka Qt5::Widgets Qt5::Gui)

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS ${CMAKE_PREFIX_PATH}\\bin)
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    add_custom_command(TARGET cuddly-eureka COMMAND ${WINDEPLOYQT_EXECUTABLE} "${PROJECT_BINARY_DIR}/Release/")
endif()
