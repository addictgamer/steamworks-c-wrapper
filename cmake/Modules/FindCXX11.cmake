# - Finds if the compiler has C++11 support
# This module can be used to detect compiler flags for using C++11, and checks
# a small subset of the language.
#
# The following variables are set:
#   CXX11_FLAGS - flags to add to the CXX compiler for C++11 support
#   CXX11_FOUND - true if the compiler supports C++11
#

include(CheckCXXSourceCompiles)
include(FindPackageHandleStandardArgs)

set(CXX11_FLAG_CANDIDATES
    #Microsoft Visual Studio, and everything that automatically accepts C++11 (placed in first position in case user defines C++11 flags)
    " "
    #gcc, intel, clang
    "-std=c++11"
    "-std=c++0x"
    #Intel windows
    "/Qstd=c++0x"
    #Clang on OSX
    "-std=c++11 -stdlib=libc++"
    )

set(CXX11_TEST_SOURCE
"
#include <array>

class Matrix
{
public:
    Matrix(int a, int b, int c, int d)
        : data {a, b, c, d}
    {}

    Matrix() : Matrix(1, 0, 1, 0) {} // Test constructor delegation
    const static char dtype_test = 'n'; // For decltype testing

private:
    int data[4];
};

int main()
{
    int n[] {4,7,6,1,2}; // Test array initialiser list
    Matrix mat; // Test delegated constructor
    char a = decltype(mat)::dtype_test; // Test decltype
    return 0;
}
")

message(STATUS "Checking for necessary C++11 support")

foreach(FLAG ${CXX11_FLAG_CANDIDATES})
    set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${FLAG}")
    unset(CXX11_FLAG_DETECTED CACHE)
    message(STATUS "Trying C++11 flag = [${FLAG}]")
    check_cxx_source_compiles("${CXX11_TEST_SOURCE}" CXX11_FLAG_DETECTED)
    set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
    if(CXX11_FLAG_DETECTED)
        set(CXX11_FLAGS_INTERNAL "${FLAG}")
        break()
    endif(CXX11_FLAG_DETECTED)
endforeach(FLAG ${CXX11_FLAG_CANDIDATES})

set(CXX11_FLAGS "${CXX11_FLAGS_INTERNAL}")

find_package_handle_standard_args(CXX11 DEFAULT_MSG CXX11_FLAGS)
mark_as_advanced(CXX11_FLAGS)
