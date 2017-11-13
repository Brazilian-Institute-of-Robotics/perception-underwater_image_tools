rock_library(underwater_image_tools
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(underwater_image_tools_bin Main.cpp
    DEPS underwater_image_tools)

