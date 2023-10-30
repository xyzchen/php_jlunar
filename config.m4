dnl config.m4 for extension jlunar

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([jlunar],
dnl   [for jlunar support],
dnl   [AS_HELP_STRING([--with-jlunar],
dnl     [Include jlunar support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([jlunar],
  [whether to enable jlunar support],
  [AS_HELP_STRING([--enable-jlunar],
    [Enable jlunar support])],
  [no])

if test "$PHP_JLUNAR" != "no"; then
  dnl Write more examples of tests here...
  PHP_REQUIRE_CXX
  AC_LANG_CPLUSPLUS
  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, JLUNAR_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jlunar -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/jlunar.h"  # you most likely want to change this
  dnl if test -r $PHP_JLUNAR/$SEARCH_FOR; then # path given as parameter
  dnl   JLUNAR_DIR=$PHP_JLUNAR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for jlunar files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       JLUNAR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$JLUNAR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the jlunar distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jlunar -> add include path
  dnl PHP_ADD_INCLUDE($JLUNAR_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jlunar -> check for lib and symbol presence
  dnl LIBNAME=JLUNAR # you may want to change this
  dnl LIBSYMBOL=JLUNAR # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_JLUNAR_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your jlunar library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $JLUNAR_DIR/$PHP_LIBDIR, JLUNAR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_JLUNAR_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your jlunar library.])
  dnl ],[
  dnl   -L$JLUNAR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(JLUNAR_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_JLUNAR, 1, [ Have jlunar support ])

  PHP_NEW_EXTENSION(jlunar, php_jlunar.cpp jlunar.cpp jlunarJQ.cpp, $ext_shared)
fi
