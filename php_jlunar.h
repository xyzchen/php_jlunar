/* jlunar extension for PHP */

#ifndef PHP_JLUNAR_H
# define PHP_JLUNAR_H

extern zend_module_entry jlunar_module_entry;
# define phpext_jlunar_ptr &jlunar_module_entry

# define PHP_JLUNAR_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_JLUNAR)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_JLUNAR_H */
