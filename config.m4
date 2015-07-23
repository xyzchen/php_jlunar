dnl $Id$
dnl config.m4 for extension jlunar

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(jlunar, for jlunar support,
dnl Make sure that the comment is aligned:
dnl [  --with-jlunar             Include jlunar support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(jlunar, whether to enable jlunar support,
dnl Make sure that the comment is aligned:
[  --enable-jlunar           Enable jlunar support])

if test "$PHP_JLUNAR" != "no"; then
  dnl Write more examples of tests here...
  PHP_REQUIRE_CXX
  AC_LANG_CPLUSPLUS
  PHP_ADD_LIBRARY(stdc++,,JLUNAR_SHARED_LIBADD)
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_JLUNAR"
  dnl # --with-jlunar -> check with-path
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

  dnl # --with-jlunar -> add include path
  dnl PHP_ADD_INCLUDE($JLUNAR_DIR/include)

  dnl # --with-jlunar -> check for lib and symbol presence
  dnl LIBNAME=jlunar # you may want to change this
  dnl LIBSYMBOL=jlunar # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $JLUNAR_DIR/lib, JLUNAR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_JLUNARLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong jlunar lib version or lib not found])
  dnl ],[
  dnl   -L$JLUNAR_DIR/lib -lm
  dnl ])
  dnl
  export CPPFLAGS="$OLD_CPPFLAGS"
  PHP_SUBST(JLUNAR_SHARED_LIBADD)
  AC_DEFINE(HAVE_JLUNAR, 1, [ ])

  PHP_NEW_EXTENSION(jlunar, php_jlunar.c jlunar.cpp jlunarJQ.cpp, $ext_shared)
fi
