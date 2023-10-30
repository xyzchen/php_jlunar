/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: dc1a30dbc4480720564101e68a74a694bd07d1ff */
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_today, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_todaystring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_offset_solardays, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_lunar_get_weekday arginfo_lunar_get_offset_solardays

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_solar_daysofmonth, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_lunar_daysofmonth, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, lyear, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, lmonth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_solar_daysofyear, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_lunar_daysofyear, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, lyear, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_lunar_get_leapmonth arginfo_lunar_get_lunar_daysofyear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_date, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_lunardate, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_solardate, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, lyear, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, lmonth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, lday, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, isleap, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_spring, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_lunar_get_term_yn, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(lunar_get_today);
ZEND_FUNCTION(lunar_get_todaystring);
ZEND_FUNCTION(lunar_get_offset_solardays);
ZEND_FUNCTION(lunar_get_weekday);
ZEND_FUNCTION(lunar_get_solar_daysofmonth);
ZEND_FUNCTION(lunar_get_lunar_daysofmonth);
ZEND_FUNCTION(lunar_get_solar_daysofyear);
ZEND_FUNCTION(lunar_get_lunar_daysofyear);
ZEND_FUNCTION(lunar_get_leapmonth);
ZEND_FUNCTION(lunar_get_date);
ZEND_FUNCTION(lunar_get_lunardate);
ZEND_FUNCTION(lunar_get_solardate);
ZEND_FUNCTION(lunar_get_spring);
ZEND_FUNCTION(lunar_get_term_yn);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(lunar_get_today, arginfo_lunar_get_today)
	ZEND_FE(lunar_get_todaystring, arginfo_lunar_get_todaystring)
	ZEND_FE(lunar_get_offset_solardays, arginfo_lunar_get_offset_solardays)
	ZEND_FE(lunar_get_weekday, arginfo_lunar_get_weekday)
	ZEND_FE(lunar_get_solar_daysofmonth, arginfo_lunar_get_solar_daysofmonth)
	ZEND_FE(lunar_get_lunar_daysofmonth, arginfo_lunar_get_lunar_daysofmonth)
	ZEND_FE(lunar_get_solar_daysofyear, arginfo_lunar_get_solar_daysofyear)
	ZEND_FE(lunar_get_lunar_daysofyear, arginfo_lunar_get_lunar_daysofyear)
	ZEND_FE(lunar_get_leapmonth, arginfo_lunar_get_leapmonth)
	ZEND_FE(lunar_get_date, arginfo_lunar_get_date)
	ZEND_FE(lunar_get_lunardate, arginfo_lunar_get_lunardate)
	ZEND_FE(lunar_get_solardate, arginfo_lunar_get_solardate)
	ZEND_FE(lunar_get_spring, arginfo_lunar_get_spring)
	ZEND_FE(lunar_get_term_yn, arginfo_lunar_get_term_yn)
	ZEND_FE_END
};
