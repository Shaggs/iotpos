cmake_minimum_required(VERSION 3.16)

project(iotpos)

find_package(ECM REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(
  KF5 REQUIRED
  COMPONENTS
    CoreAddons
    Completion
    ConfigWidgets
    Config
    I18n
    KIO
    Notifications
    Plotting
    WidgetsAddons
    XmlGui
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory( src )

add_subdirectory( icons )
add_subdirectory( styles )
add_subdirectory( images )
add_subdirectory( iotstock )
add_subdirectory( database_resources )

# MCH: add_subdirectory( doc )
