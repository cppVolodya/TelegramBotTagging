add_executable(telegram_bot_tagging ${PROGRAM_FILES})
target_link_libraries(telegram_bot_tagging PRIVATE ${TARGET_LIBRARIES})
target_link_options(telegram_bot_tagging PRIVATE ${LINKER_OPTIONS})
