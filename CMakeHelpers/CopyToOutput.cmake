#########################################################
# Copy local file to output directory of specified target
# Usage:
#   include(CopyToOutput)
#   copy_local_file_to_output_prebuild(target-name settings.xml)
macro (copy_local_file_to_output_prebuild target_name local_file_name)
    add_custom_command(
        TARGET ${target_name} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${local_file_name} $<TARGET_FILE_DIR:${target_name}>)
endmacro()

#########################################################
# Copy file to output directory of specified target
# Usage:
#   include(CopyToOutput)
#   copy_file_to_output_prebuild(target-name ${FullPathToFile}/settings.xml)
macro (copy_file_to_output_prebuild target_name file_name)
    add_custom_command(
        TARGET ${target_name} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_name} $<TARGET_FILE_DIR:${target_name}>)
endmacro()

#########################################################
# Copy local file to output directory of specified target
# Usage:
#   include(CopyToOutput)
#   copy_local_file_to_output_postbuild(target-name settings.xml)
macro (copy_local_file_to_output_postbuild target_name local_file_name)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${local_file_name} $<TARGET_FILE_DIR:${target_name}>)
endmacro()

#########################################################
# Copy file to output directory of specified target
# Usage:
#   include(CopyToOutput)
#   copy_file_to_output_postbuild(target-name ${FullPathToFile}/settings.xml)
macro (copy_file_to_output_postbuild target_name file_name)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_name} $<TARGET_FILE_DIR:${target_name}>)
endmacro()

#########################################################
# Try copy directory to output directory
# Usage:
#   include(CopyToOutput)
#   copy_directory_to_output(target-name ${FullPathToDirectory})
macro (copy_directory_to_output target_name source_directory destination_relative_directory)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${source_directory} $<TARGET_FILE_DIR:${target_name}>/${destination_relative_directory})
endmacro()
