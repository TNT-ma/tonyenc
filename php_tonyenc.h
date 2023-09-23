/* tonyenc extension for PHP */

#ifndef PHP_TONYENC_H
# define PHP_TONYENC_H

extern zend_module_entry tonyenc_module_entry;
# define phpext_tonyenc_ptr &tonyenc_module_entry

#define PHP_TONYENC_VERSION "1.0.1" /* Replace with version number for your extension */

# if defined(ZTS) && defined(COMPILE_DL_TONYENC)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TONYENC_H */
