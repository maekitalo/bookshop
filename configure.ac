AC_INIT([bookshop], [0.1], [tommi@tntnet.org], [http://www.tntnet.org])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_LANG(C++)

AC_CONFIG_HEADERS([src/config.h])
AC_CHECK_HEADER([cxxtools/mutex.h], , AC_MSG_ERROR([cxxtools headers not found]))
AC_CHECK_HEADER([tnt/tntnet.h], , AC_MSG_ERROR([tntnet headers not found]))
AC_CHECK_HEADER([tntdb/connection.h], , AC_MSG_ERROR([tntdb headers not found]))
AC_CHECK_PROGS(ECPPC, [ecppc])
AC_PROG_SED
AX_CHECK_COMPILE_FLAG([-Wall], [CPPFLAGS="$CPPFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-pedantic], [CPPFLAGS="$CPPFLAGS -pedantic"])

AC_OUTPUT([
    Makefile
    src/Makefile
])
