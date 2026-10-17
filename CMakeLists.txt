# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "MainMenu.h" "MainMenu.cpp")
target_link_libraries(CMakeProject1 PRIVATE SFML::Graphics)

add_custom_command(
    TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory #your program runs from inside out/build/..., 
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"   #but your original artwork stays in the source folder. 
        "$<TARGET_FILE_DIR:CMakeProject1>/assets" #This command automatically places a copy beside the built game.
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
