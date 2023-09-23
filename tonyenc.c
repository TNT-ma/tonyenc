/* tonyenc extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_tonyenc.h"
#include "tonyenc_arginfo.h"

#include "core.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ */
PHP_FUNCTION(tonyenc_encode)
{
    zend_string *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &strg) == FAILURE) {
        return;
    }

    /* If encoded */
    if (!memcmp(ZSTR_VAL(strg), tonyenc_header, sizeof(tonyenc_header))) {
        RETURN_FALSE;
    }

    char *t = emalloc(sizeof(tonyenc_header) + ZSTR_LEN(strg));
    memcpy(t, tonyenc_header, sizeof(tonyenc_header));
    if (ZSTR_LEN(strg) > 0) {
        tonyenc_encode(ZSTR_VAL(strg), ZSTR_LEN(strg));
        memcpy(t + sizeof(tonyenc_header), ZSTR_VAL(strg), ZSTR_LEN(strg));
    }

    RETURN_STR(zend_string_init(t, sizeof(tonyenc_header) + ZSTR_LEN(strg), 0));
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tonyenc)
{
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    old_compile_file = zend_compile_file;
    zend_compile_file = cgi_compile_file;
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tonyenc)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */

    zend_compile_file = old_compile_file;

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(tonyenc)
{
#if defined(ZTS) && defined(COMPILE_DL_TONYENC)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tonyenc)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(tonyenc)
{
	    php_info_print_table_start();
        php_info_print_table_header(2, "Tonyenc Support", "enabled");
        php_info_print_table_row(2, "version", PHP_TONYENC_VERSION);
        php_info_print_table_row(2, "author", "Tony");
        php_info_print_table_row(2, "modifier", "DMLF");
        php_info_print_table_row(2, "open sourced by", "veeker.com");
        php_info_print_table_row(2, "homepage", "https://www.lfveeker.com");
        php_info_print_table_end();
}
/* }}} */

/* {{{ tonyenc_module_entry */
zend_module_entry tonyenc_module_entry = {
	STANDARD_MODULE_HEADER,
	"tonyenc",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(tonyenc),
    PHP_MSHUTDOWN(tonyenc),
    NULL,   /* Replace with NULL if there's nothing to do at request start */
    NULL,	/* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(tonyenc),
    PHP_TONYENC_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TONYENC
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(tonyenc)
#endif
