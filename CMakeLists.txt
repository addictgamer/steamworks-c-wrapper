cmake_minimum_required(VERSION 3.1)
project(steamworks_cwrapper)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (BIT_32)
	MESSAGE("COMPILING 32 BIT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -m32")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_DEBUG} -m32")
endif()

set (Windows 0)
if (WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-exceptions")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-exceptions")
	set(Windows 1)
elseif (APPLE)
	#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pg -O3 -ffast-math -funroll-loops -malign-double -fstrict-aliasing -mwindows")
	#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math -funroll-loops -malign-double -fstrict-aliasing -mwindows")
else()
	#Linux
endif ()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fPIC -lrt -lstdc++ -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fPIC -lrt -lstdc++ -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CXX11_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CXX11_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${CXX11_FLAGS}")
message("------------------------")
message("Building with flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("------------------------")

configure_file("${PROJECT_SOURCE_DIR}/src/Config.h.in" "${PROJECT_SOURCE_DIR}/src/Config.h")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")

find_package(STEAMWORKS REQUIRED)
include_directories(${STEAMWORKS_INCLUDE_DIR})

add_subdirectory(src)

add_library(steamworks_cwrapper ${LIBRARY_SOURCES})
if (Windows)
	#Because CMake in Windows acts like a drugged hippie that plays with fire potatos instead of compiling code. Ugh.
	find_package(CXX11 REQUIRED)
else ()
	#Seriously. Why isn't this working under Windows? Twice has a user reported it don't work.
	target_compile_features(steamworks_cwrapper PRIVATE cxx_range_for)
endif ()

target_link_libraries(steamworks_cwrapper ${STEAMWORKS_LIBRARY})

install(TARGETS steamworks_cwrapper
	ARCHIVE DESTINATION lib COMPONENT Development
)

foreach (HEADER ${LIBRARY_HEADERS})
	string(REPLACE "${PROJECT_SOURCE_DIR}/src/" "" HEADER ${HEADER})
	get_filename_component(HEADER_DIR "${HEADER}" PATH) # Ugly hack because CMake can't currently install headers while preserving directory structure <I think>
	get_filename_component(HEADER_NAME "${HEADER}" NAME)
	install(FILES "src/${HEADER}" DESTINATION "include/steamworks_cwrapper/${HEADER_DIR}")
endforeach ()