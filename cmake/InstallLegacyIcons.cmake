include_guard(GLOBAL)

include(ECMInstallIcons)

function(install_legacy_hicolor_icons)
    file(GLOB legacy_icons CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/hi*.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/hi*.svgz"
    )

    set(generated_icons)
    foreach(icon IN LISTS legacy_icons)
        get_filename_component(icon_filename "${icon}" NAME)
        if(NOT icon_filename MATCHES "^hi([0-9]+|sc)-([^-]+)-(.+)\\.(png|svgz)$")
            message(FATAL_ERROR "Unsupported legacy icon filename: ${icon_filename}")
        endif()

        set(icon_size "${CMAKE_MATCH_1}")
        set(icon_group "${CMAKE_MATCH_2}")
        set(icon_name "${CMAKE_MATCH_3}")
        set(icon_extension "${CMAKE_MATCH_4}")

        if(icon_group STREQUAL "app")
            set(icon_group "apps")
        endif()

        set(generated_icon
            "${CMAKE_CURRENT_BINARY_DIR}/${icon_size}-${icon_group}-${icon_name}.${icon_extension}"
        )
        configure_file("${icon}" "${generated_icon}" COPYONLY)
        list(APPEND generated_icons "${generated_icon}")
    endforeach()

    ecm_install_icons(
        ICONS ${generated_icons}
        DESTINATION ${KDE_INSTALL_ICONDIR}
    )
endfunction()
