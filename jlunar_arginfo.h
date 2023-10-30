/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: dc1a30dbc4480720564101e68a74a694bd07d1ff */
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_today, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_todaystring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(lunar_get_today);
ZEND_FUNCTION(lunar_get_todaystring);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(lunar_get_today, arginfo_lunar_get_today)
	ZEND_FE(lunar_get_todaystring, arginfo_lunar_get_todaystring)
	ZEND_FE_END
};
