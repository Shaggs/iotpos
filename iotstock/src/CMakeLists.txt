
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


include(KConfigAddKcfgFiles)
kconfig_add_kcfg_files(iotstock_SRCS settings.kcfgc)

add_executable(iotstock ${iotstock_SRCS})

FIND_PROGRAM(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

IF(NOT GETTEXT_MSGFMT_EXECUTABLE)
        MESSAGE(
"------
                 NOTE: msgfmt not found. Translations will *not* be installed
------")
ELSE(NOT GETTEXT_MSGFMT_EXECUTABLE)

        SET(catalogname iotstock)

        ADD_CUSTOM_TARGET(translations ALL)

        FILE(GLOB PO_FILES po/*.po)

        FOREACH(_poFile ${PO_FILES})
                GET_FILENAME_COMPONENT(_lang ${_poFile} NAME_WE)
                SET(_gmoFile ${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo)
                ADD_CUSTOM_COMMAND(TARGET translations
                        COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${_gmoFile} ${_poFile}
                        DEPENDS ${_poFile})
                INSTALL(FILES ${_gmoFile} DESTINATION ${KDE_INSTALL_LOCALEDIR}/${_lang}/LC_MESSAGES/ RENAME ${catalogname}.mo)
        ENDFOREACH(_poFile ${PO_FILES})

ENDIF(NOT GETTEXT_MSGFMT_EXECUTABLE)

target_link_libraries(iotstock
  KF5::CoreAddons
  KF5::ConfigWidgets
  KF5::I18n
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
