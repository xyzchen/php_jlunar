/* jlunar extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_jlunar.h"
#include "jlunar_arginfo.h"

//农历函数定义
#include "jlunar.h"

//标准库
#include <math.h>
#include <time.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/////////////////////////////////////////////////////////////////////
//--------------------------------------------------------
//  帮助函数，
//    把LUNARDATE对象转换成PHP关联数组
//-------------------------------------------------------
static zend_result set_lunar_array(zval* return_value, const LUNARDATE* lunar_date)
{
	if(lunar_date == NULL)
	{
		RETVAL_NULL();
		return FAILURE;
	}
	//公历：年，月，日，星期
	add_assoc_long(return_value, "year", lunar_date->wYear);
	add_assoc_long(return_value, "month", lunar_date->wMonth);
	add_assoc_long(return_value, "day",    lunar_date->wDay);
	add_assoc_long(return_value, "weekday", lunar_date->wWeekDay);
	//农历年月日，是否闰月
	add_assoc_long(return_value, "lunar_year", lunar_date->wLunarYear);
	add_assoc_long(return_value, "lunar_month", lunar_date->wLunarMonth);
	add_assoc_long(return_value, "lunar_day", lunar_date->wLunarDay);
	add_assoc_long(return_value, "lunar_isleap", lunar_date->wIsLeapMonth);
	//返回
	return SUCCESS;
}

//////////////////////////////////////////////////////////
/**
 *  下面的函数为模块真正要实现的功能
 *
 */

/* {{{ function lunar_get_today(): array */
/* 返回今天的日期（无参数） */
PHP_FUNCTION(lunar_get_today)
{
	//无参数要处理
	ZEND_PARSE_PARAMETERS_NONE();

	//获取当前日期
	time_t rawtime  = time(NULL);
	struct tm * ptm = gmtime ( &rawtime );

	//转换成农历格式
	LUNARDATE  lunardate;
	memset(&lunardate, 0, sizeof(lunardate));
	lunardate.wYear  = ptm->tm_year + 1900;
	lunardate.wMonth = ptm->tm_mon  + 1;
	lunardate.wDay   = ptm->tm_mday;
	cjxGetLunarDate(&lunardate);

	//填充关联数组并返回
	array_init(return_value);
	set_lunar_array(return_value, &lunardate); //设置数组字段
}
/* }}} */

//------------------------------------------------------
// 返回今天日期的字符串（无参数）
//------------------------------------------------------
/* {{{ function lunar_get_todaystring(): string  */
/*  返回今天日期的字符串（无参数） */
PHP_FUNCTION(lunar_get_todaystring)
{
	//无参数要处理
	ZEND_PARSE_PARAMETERS_NONE();

	//获取当前时间
	time_t rawtime  = time(NULL);
	struct tm * ptm = gmtime( &rawtime );

	//转换成农历时间
	LUNARDATE lunar_date;
	memset(&lunar_date, 0, sizeof(lunar_date));
	lunar_date.wYear  = ptm->tm_year + 1900;
	lunar_date.wMonth = ptm->tm_mon  + 1;
	lunar_date.wDay   = ptm->tm_mday;
	cjxGetLunarDate(&lunar_date);

	//处理成php数据返回
	zend_string * retstr = strpprintf(0,
		"%d年%d月%d日 农历%s(%s)年%s月%s 星期%s", 
		lunar_date.wYear, lunar_date.wMonth, lunar_date.wDay,
		lunar_date.szYearGanZhi, lunar_date.szYearShengXiao, 
		lunar_date.szLunarMonth, lunar_date.szLunarDay, 
		cjxGetWeekName(lunar_date.wWeekDay));

	//返回结果
	RETURN_STR(retstr);
}
/* }}} */


//////////////////////////////////////////////////////////
/**
 *  下面为PHP框架
 */
/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(jlunar)
{
#if defined(ZTS) && defined(COMPILE_DL_JLUNAR)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(jlunar)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "jlunar support", "enabled");
	php_info_print_table_row(2, "Version", "0.1.0");
	php_info_print_table_row(2, "Author", "jmchxy@gmail.com");
	php_info_print_table_row(2, "encode", "UTF-8");
	php_info_print_table_end();
}
/* }}} */

/* {{{ jlunar_module_entry */
zend_module_entry jlunar_module_entry = {
	STANDARD_MODULE_HEADER,
	"jlunar",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(jlunar),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(jlunar),			/* PHP_MINFO - Module info */
	PHP_JLUNAR_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JLUNAR
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(jlunar)
#endif
