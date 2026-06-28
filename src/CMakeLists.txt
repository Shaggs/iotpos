#MCH: Deshabilitar debug (para alivianar el ejecutable).
#     cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr

set(iotpos_SRCS
   iotpos.cpp
   main.cpp
   iotposview.cpp
   sha1.cc
   hash.cpp
   gaveta.cpp
   inputdialog.cpp
   loginwindow.cpp
   productdelegate.cpp
   misc.cpp
   specialordereditor.cpp
   ../dataAccess/azahar.cpp
   pricechecker.cpp
   ticketpopup.cpp
   ../printing/print-dev.cpp
   ../printing/print-cups.cpp
   ../mibitWidgets/mibitfloatpanel.cpp
   ../mibitWidgets/mibitlineedit.cpp
   ../mibitWidgets/mibittip.cpp
   ../mibitWidgets/mibitpassworddlg.cpp
   ../mibitWidgets/mibitnotifier.cpp
   soselector.cpp
   sostatus.cpp
   resume.cpp
   reservations.cpp
   saleqtydelegate.cpp
   dialogclientdata.cpp
   ../iotstock/src/clienteditor.cpp
   bundlelist.cpp
   kdialogshim.cpp
   localeutils.cpp
   pathutils.cpp
   #printers/sp500.cpp
   BasketPriceCalculationService.cpp
   nouns/BasketEntryPriceSummary.cpp
   nouns/BasketPriceSummary.cpp
   nouns/User.cpp
   nouns/Currency.cpp
 )

#qt4_add_dbus_adaptor(iotpos_SRCS org.kde.iotpos.iotpos.xml iotpos.h iotpos)

qt5_wrap_ui(iotpos_SRCS
  ui/mainview.ui
  ui/prefs_base.ui
  ui/pref_printers.ui
  ui/store_data.ui
  ui/prefs_db.ui
  ui/pref_style.ui
  ui/pref_security.ui
  ui/special_order.ui
  ui/soselector.ui
  ui/sostatus.ui
  ui/resume.ui
  ui/reservations.ui
  ui/checker.ui
  ui/datoscliente.ui
  ../iotstock/src/ui/editclient_widget.ui
  )

kconfig_add_kcfg_files(iotpos_SRCS settings.kcfgc)

add_executable(iotpos ${iotpos_SRCS})

target_link_libraries(iotpos
  KF5::CoreAddons
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

find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

if(NOT GETTEXT_MSGFMT_EXECUTABLE)
    message(STATUS "msgfmt not found; translations will not be installed")
else()
    set(catalogname iotpos)
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

    add_custom_target(iotpos_translations ALL DEPENDS ${GMO_FILES})
endif()

install(TARGETS iotpos DESTINATION ${KDE_INSTALL_BINDIR})

########### install files ###############

install(FILES iotpos.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES iotposui.rc DESTINATION ${KDE_INSTALL_DATADIR}/iotpos)
# With next line... the user needs to read/write the file...
install(FILES iotposrc DESTINATION ${KDE_INSTALL_CONFDIR})
#install( FILES iotposrc        DESTINATION  ${HOME}/.kde/share/config/ )
install(FILES iotpos.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR})
#For KNotifications
install(FILES iotpos.notifyrc DESTINATION ${KDE_INSTALL_DATADIR}/iotpos)
