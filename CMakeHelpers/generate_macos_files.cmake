include (CMakeParseArguments)

set (GenerateXCodeFilesCurrentDir ${CMAKE_CURRENT_LIST_DIR})

#SET_TARGET_PROPERTIES( ${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PLIST_TEMPLATE}
#set_target_properties(mac-updater
#   PROPERTIES
#   MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
#   )