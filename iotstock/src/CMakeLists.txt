
set(iotstock_SRCS
   iotstock.cpp
   main.cpp
   iotstockview.cpp
   usersdelegate.cpp
   usereditor.cpp
   clienteditor.cpp
   promoeditor.cpp
   producteditor.cpp
   purchaseeditor.cpp
   offersdelegate.cpp
   subcategoryeditor.cpp
   ../../src/inputdialog.cpp
   ../../src/loginwindow.cpp
   ../../src/misc.cpp
   ../../src/hash.cpp
   ../../src/sha1.cc
   ../../src/productdelegate.cpp
   ../../dataAccess/azahar.cpp
   ../../mibitWidgets/mibitfloatpanel.cpp
   ../../mibitWidgets/mibitlineedit.cpp
   ../../mibitWidgets/mibittip.cpp
   ../../mibitWidgets/mibitnotifier.cpp
   ../../printing/print-dev.cpp
   ../../printing/print-cups.cpp
   ../../src/kdialogshim.cpp
   ../../src/localeutils.cpp
   ../../src/pathutils.cpp
 )

qt5_wrap_ui(iotstock_SRCS
  ui/iotstockview_base.ui
  ui/prefs_base.ui
  ui/prefs_db.ui
  ui/pref_printers.ui
  ui/edituser_widget.ui
  ui/editclient_widget.ui
  ui/editpromo_widget.ui
  ui/producteditor.ui
  ui/purchaseeditor.ui
  ui/subcategoryeditor.ui
  )


kconfig_add_kcfg_files(iotstock_SRCS settings.kcfgc)

add_executable(iotstock ${iotstock_SRCS})

find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

if(NOT GETTEXT_MSGFMT_EXECUTABLE)
    message(STATUS "msgfmt not found; translations will not be installed")
else()
    set(catalogname iotstock)
    file(GLOB PO_FILES CONFIGURE_DEPENDS po/*.po)
    set(GMO_FILES)

    foreach(po_file IN LISTS PO_FILES)
        get_filename_component(lang "${po_file}" NAME_WE)
        set(gmo_file "${CMAKE_CURRENT_BINARY_DIR}/${lang}.gmo")
        add_custom_command(
            OUTPUT "${gmo_file}"
            COMMAND "${GETTEXT_MSGFMT_EXECUTABLE}" -o "${gmo_file}" "${po_file}"
            DEPENDS "${po_file}"
            VERBATIM
        )
        list(APPEND GMO_FILES "${gmo_file}")
        install(
            FILES "${gmo_file}"
            DESTINATION "${KDE_INSTALL_LOCALEDIR}/${lang}/LC_MESSAGES"
            RENAME "${catalogname}.mo"
        )
    endforeach()

    add_custom_target(iotstock_translations ALL DEPENDS ${GMO_FILES})
endif()

target_link_libraries(iotstock
  KF5::CoreAddons
  KF5::Completion
  KF5::ConfigCore
  KF5::ConfigWidgets
  KF5::I18n
  KF5::Notifications
  KF5::Plotting
  KF5::KIOWidgets
  KF5::WidgetsAddons
  KF5::XmlGui
  Qt5::PrintSupport
  Qt5::Sql
  Qt5::Widgets
)

install(TARGETS iotstock DESTINATION ${KDE_INSTALL_BINDIR})

########### install files ###############

install(FILES iotstock.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES iotstockui.rc DESTINATION ${KDE_INSTALL_DATADIR}/iotstock)
install(FILES iotstock.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR})
#For KNotifications
install(FILES iotstock.notifyrc DESTINATION ${KDE_INSTALL_DATADIR}/iotstock)
