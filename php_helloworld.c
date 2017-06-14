// include the PHP API itself
#include <php.h>
#include <regex.h>
// then include the header of your extension
#include "php_helloworld.h"
#include "helpers.c"


#ifdef ZEND_BEGIN_ARG_INFO
ZEND_BEGIN_ARG_INFO_EX(arginfo_php_helloworld, ZEND_SEND_BY_VAL,
                       ZEND_RETURN_VALUE, 1)
ZEND_ARG_INFO(0, test)
ZEND_END_ARG_INFO()
#else
#define arginfo_php_helloworld third_arg_force_ref
#endif


// register our function to the PHP API
// so that PHP knows, which functions are in this module
zend_function_entry php_helloworld_functions[] = {
    PHP_FE(php_helloworld, arginfo_php_helloworld)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry php_helloworld_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_HELLOWORLD_EXTNAME,
    php_helloworld_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_HELLOWORLD_VERSION,
    STANDARD_MODULE_PROPERTIES
};



// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(php_helloworld)

// Finally, we implement our "Hello World" function
// this function will be made available to PHP
// and prints to PHP stdout using printf
PHP_FUNCTION(php_helloworld) {
    char buff[1024];
    char full_filepath[1024];
    char *filename = {0};
    size_t filename_len = 0;
    zend_long pos = 0;
    zval *zndocs = { 0 };
    zval *zcallbacks = { 0 };

    int i;
    int c = 0;
    char **arr = NULL;

    php_stream *stream = { 0 };
    FILE *fp = { 0 };

    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lza/", &filename, &filename_len, &pos, &zndocs,
                                         &zcallbacks)) {
        return;
    }
    sprintf(full_filepath, "%s%s%s%s", filename, "/.git", "/logs", "/HEAD");

    if (NULL == (stream = php_stream_open_wrapper(full_filepath, "rb", IGNORE_URL | REPORT_ERRORS | STREAM_WILL_CAST, NULL))) {
        RETURN_FALSE;
    }

    if (FAILURE == php_stream_cast(stream, PHP_STREAM_AS_STDIO, (void **) &fp, 1)) {
        php_stream_close(stream);
        RETURN_FALSE;
    }

    fseek(fp, 0, SEEK_SET);
    while (!feof(fp))
    {
        memset(buff, 0x00, 1024);
        fscanf(fp, "%[^\n]\n", buff);
    }

    php_printf("String read: %s\n", buff);

    c = split(buff, ' ', &arr);

    char comment[1024];

    for (i = 0; i < c; i++) {

        if(i < 4) {
            comment += arr[i];
        }
        php_printf("string #%d: %s\n", i, arr[i]);
    }
    php_printf("Cooment: %s\n", comment);
}

