cmake_minimum_required(VERSION 3.16)

project(iotpos)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(
  KF5 REQUIRED
  COMPONENTS
    CoreAddons
    ConfigWidgets
    ConfigCore
    I18n
    KIO
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
