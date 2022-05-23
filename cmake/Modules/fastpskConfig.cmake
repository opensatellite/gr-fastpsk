INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_FASTPSK fastpsk)

FIND_PATH(
    FASTPSK_INCLUDE_DIRS
    NAMES fastpsk/api.h
    HINTS $ENV{FASTPSK_DIR}/include
        ${PC_FASTPSK_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    FASTPSK_LIBRARIES
    NAMES gnuradio-fastpsk
    HINTS $ENV{FASTPSK_DIR}/lib
        ${PC_FASTPSK_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FASTPSK DEFAULT_MSG FASTPSK_LIBRARIES FASTPSK_INCLUDE_DIRS)
MARK_AS_ADVANCED(FASTPSK_LIBRARIES FASTPSK_INCLUDE_DIRS)

