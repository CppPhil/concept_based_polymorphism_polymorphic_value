# CMakeList.txt : CMake project for polymorphic_value, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (polymorphic_value_app "main.cpp")

# TODO: Add tests and install targets if needed.
target_link_libraries(
	polymorphic_value_app
	PRIVATE
	polymorphic_value::polymorphic_value)
