/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  |  农历扩展函数                                                        |
  +----------------------------------------------------------------------+
  | Author:  陈逸少（jmchxy@gmail.com）                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_jlunar.h"

//农历函数定义
#include "jlunar.h"

//标准库
#include <math.h>
#include <time.h>

/* If you declare any globals in php_jlunar.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(jlunar)
*/

/* True global resources - no need for thread safety here */
static int le_jlunar;

/* {{{ jlunar_functions[]
 *
 * Every user visible function must have an entry in jlunar_functions[].
 */
const zend_function_entry jlunar_functions[] = {
	/* 获取今天的日期和日子字符串 */
	PHP_FE(lunar_get_today,	NULL)
	PHP_FE(lunar_get_todaystring, NULL)
	
	/* 日期和到1900-1-1的天数互换 */
	PHP_FE(lunar_get_date,	NULL)
	PHP_FE(lunar_get_offset_solardays,	NULL)

	/* 公历－农历 互换函数*/
	PHP_FE(lunar_get_lunardate,	NULL)
	PHP_FE(lunar_get_solardate,	NULL)

	/* 某年、 某月 的天数*/
	PHP_FE(lunar_get_solar_daysofmonth,	NULL)
	PHP_FE(lunar_get_lunar_daysofmonth,	NULL)
	PHP_FE(lunar_get_lunar_daysofyear,	NULL)

	/* 春节、24节气、星期数 */
	PHP_FE(lunar_get_spring,	NULL)
	PHP_FE(lunar_get_term_yn,	NULL)
	PHP_FE(lunar_get_weekday,	NULL)
	
	PHP_FE_END	/* Must be the last line in jlunar_functions[] */
};
/* }}} */

/* {{{ jlunar_module_entry
 */
zend_module_entry jlunar_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"jlunar",
	jlunar_functions,
	PHP_MINIT(jlunar),
	PHP_MSHUTDOWN(jlunar),
	PHP_RINIT(jlunar),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(jlunar),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(jlunar),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JLUNAR
ZEND_GET_MODULE(jlunar)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("jlunar.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_jlunar_globals, jlunar_globals)
    STD_PHP_INI_ENTRY("jlunar.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_jlunar_globals, jlunar_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_jlunar_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_jlunar_init_globals(zend_jlunar_globals *jlunar_globals)
{
	jlunar_globals->global_value = 0;
	jlunar_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(jlunar)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(jlunar)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(jlunar)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(jlunar)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(jlunar)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "jlunar support", "enabled");
	php_info_print_table_row(2, "Version", "0.1.0");
	php_info_print_table_row(2, "Author", "jmchxy@gmail.com");
	php_info_print_table_row(2, "encode", "UTF-8");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

/**
 *  下面的函数为模块真正要实现的功能
 *
 */
//把LUNARDATE对象转换到PHP关联数组
void lunar_to_array(zval* new_array, const LUNARDATE*  lunar_date);

// 返回今天日期的字符串（无参数）
PHP_FUNCTION(lunar_get_todaystring)
{
	//设置返回值
	char *strg;
	int  len;
	
    time_t rawtime   = time(NULL);
	struct tm * ptm = gmtime ( &rawtime );

	LUNARDATE lunar_date;
	memset(&lunar_date, 0, sizeof(lunar_date));
	lunar_date.wYear  = ptm->tm_year + 1900;
	lunar_date.wMonth = ptm->tm_mon  + 1;
	lunar_date.wDay   = ptm->tm_mday;
	cjxGetLunarDate(&lunar_date);
	//处理数据
	len = spprintf(&strg, 0, "%d年%d月%d日 农历%s(%s)年%s月%s 星期%s", 
		lunar_date.wYear, lunar_date.wMonth, lunar_date.wDay,
		lunar_date.szYearGanZhi, lunar_date.szYearShengXiao, lunar_date.szLunarMonth, lunar_date.szLunarDay, cjxGetWeekName(lunar_date.wWeekDay));
	
	//返回结果
	RETURN_STRINGL(strg, len, 0);
}

// 返回今天的日期（无参数）
PHP_FUNCTION(lunar_get_today)
{
	//临时变量
	LUNARDATE  lunardate;
	time_t     rawtime;
	struct tm * ptm;
	
	// 返回值使用
	zval*  new_array;			//声明php变量new_array，申请并初始化一个zval容器
	MAKE_STD_ZVAL(new_array);	//设置变量的类型和内容,将名为 "new_array" 变量引入符号表
	array_init(new_array);      //初始化hash表，并赋给数组

	rawtime   = time(NULL);
	ptm = gmtime ( &rawtime );

	memset(&lunardate, 0, sizeof(lunardate));
	lunardate.wYear  = ptm->tm_year + 1900;
	lunardate.wMonth = ptm->tm_mon  + 1;
	lunardate.wDay   = ptm->tm_mday;
	cjxGetLunarDate(&lunardate);
	//使用关联数组
	lunar_to_array(new_array, &lunardate);
	//返回结果
	*return_value = *new_array;	
}

//------------------------------------------------------
//  计算 公历 year-month-day 到 1900-1-0的天数 
//     参数: 公历的年月日 1900-1-1 ~ 2100-12-31 之间
//     返回:
//          天数, 一个正数值 1900-1-1为 1       
//-----------------------------------------------------
PHP_FUNCTION(lunar_get_offset_solardays)
{
	//接收参数
	long year, month, day;
	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 3)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &year,  &month, &day) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetOffsetSolarDays(year, month, day));
}
//-----------------------------------
//获取 距离 1900年1月1日 days 天的日期
//      1900年1月1日为1
//  参数: 距离1900-1-1的天数
//-----------------------------------
PHP_FUNCTION(lunar_get_date)
{
	//接收参数
	long days   = 0;

	//临时变量，计算用
	LUNARDATE  lunar_date;

	// 返回值使用
	zval*  new_array;			//声明php变量new_array，申请并初始化一个zval容器
	MAKE_STD_ZVAL(new_array);	//设置变量的类型和内容,将名为 "new_array" 变量引入符号表
	array_init(new_array);      //初始化hash表，并赋给数组

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 1)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &days) == FAILURE)
	{
		return;
	}
	//计算到农历的时间
	cjxGetDate(days, &lunar_date);
	//----------------------------------------------
	//把结果加入到数组并返回
	//----------------------------------------------
	//使用关联数组
	lunar_to_array(new_array, &lunar_date);

	//返回结果
	*return_value = *new_array;	//此处return_value是返回参数，根据宏定义展开可以看到
}

//-----------------------------------
// 从公历时间转换到农历时间
//   参数：公历年，月，日
//-----------------------------------
PHP_FUNCTION(lunar_get_lunardate)
{
	//接收参数
	long year, month, day;

	//临时变量，计算用
	LUNARDATE  lunar_date;

	// 返回值使用
	zval*  new_array;			//声明php变量new_array，申请并初始化一个zval容器
	MAKE_STD_ZVAL(new_array);	//设置变量的类型和内容,将名为 "new_array" 变量引入符号表
	array_init(new_array);      //初始化hash表，并赋给数组

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 3)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &year,  &month, &day) == FAILURE)
	{
		return;
	}
	//计算到农历的时间
	lunar_date.wYear  = (WORD)year;
	lunar_date.wMonth = (WORD)month;
	lunar_date.wDay   = (WORD)day;
	cjxGetLunarDate(&lunar_date);
	//使用关联数组
	lunar_to_array(new_array, &lunar_date);
	//返回结果
	*return_value = *new_array;
}

//-----------------------------------
// 从农历时间转换到公历时间
//   参数：农历年，月，日，是否闰月
//-----------------------------------
PHP_FUNCTION(lunar_get_solardate)
{
	//接收参数
	long year, month, day, isleap=0;

	//临时变量，计算用
	LUNARDATE  lunar_date;

	// 返回值使用
	zval*  new_array;			//声明php变量new_array，申请并初始化一个zval容器
	MAKE_STD_ZVAL(new_array);	//设置变量的类型和内容,将名为 "new_array" 变量引入符号表
	array_init(new_array);      //初始化hash表，并赋给数组

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() < 3)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if(ZEND_NUM_ARGS() == 3)
	{
		if (zend_parse_parameters(3 TSRMLS_CC, "lll", &year,  &month, &day) == FAILURE)
		{
			return;
		}
	}
	else //第四个可选参数
	{
		if (zend_parse_parameters(4 TSRMLS_CC, "llll", &year,  &month, &day, &isleap) == FAILURE)
		{
			return;
		}
	}
	
	//计算到农历的时间
	lunar_date.wLunarYear  = (WORD)year;
	lunar_date.wLunarMonth = (WORD)month;
	lunar_date.wLunarDay   = (WORD)day;
	lunar_date.wIsLeapMonth= (WORD)isleap;
	cjxGetSolarDate(&lunar_date);
	//使用关联数组
	lunar_to_array(new_array, &lunar_date);
	//返回结果
	*return_value = *new_array;
}
//-------------------------------------
// 返回指定年/月/日的星期数，0为星期日
//-------------------------------------
PHP_FUNCTION(lunar_get_weekday)
{
	//接收参数
	long year, month, day;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 3)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &year,  &month, &day) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetWeekday(year, month, day));
}

// 计算公历某月的天数(参数，年/月)
PHP_FUNCTION(lunar_get_solar_daysofmonth)
{
	//接收参数
	long year, month;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 2)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &year,  &month) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetSolarMonthDays(year, month));
}

// 计算农历某月的天数(参数，年/月)
PHP_FUNCTION(lunar_get_lunar_daysofmonth)
{
	//接收参数
	long year, month;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 2)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &year,  &month) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetLunarMonthDays(year, month));
}

// 计算农历某年的天数(参数，年)
PHP_FUNCTION(lunar_get_lunar_daysofyear)
{
	//接收参数
	long year;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 1)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &year) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetLunaYearDays(year));
}

// 计算农历某年闰几月，没有闰月为0
PHP_FUNCTION(lunar_get_leapmonth)
{
	//接收参数
	long year;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 1)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &year) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxLunarLeapMonth(year));
}
//-----------------------------------------------------
// 24节气结算函数：
//    计算 y 年的第n个节气几号(从0小寒起算)
//       该节气的月份   (int)(n/2+1)
//-----------------------------------------------------
PHP_FUNCTION(lunar_get_term_yn)
{
	//接收参数
	long year, n;

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 2)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &year,  &n) == FAILURE)
	{
		return;
	}
	//返回结果
	RETURN_LONG(cjxGetTermYN(year, n));
}
//-----------------------------------
// 返回农历某年春节的日期(月,日)
//   参数：农历年
//   返回：array(month,day)
//-----------------------------------
PHP_FUNCTION(lunar_get_spring)
{
	//接收参数
	long year = 1900;

	// 返回值使用
	zval*  new_array;			//声明php变量new_array，申请并初始化一个zval容器
	MAKE_STD_ZVAL(new_array);	//设置变量的类型和内容,将名为 "new_array" 变量引入符号表
	array_init(new_array);      //初始化hash表，并赋给数组

	//检查参数，抛出异常
	if(ZEND_NUM_ARGS() != 1)
	{
		WRONG_PARAM_COUNT;
	}	
	//解析参数
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &year) == FAILURE)
	{
		return;
	}
	//计算春节日期并返回数组
	add_index_long(new_array, 0, cjxSpringMonth(year));
    add_index_long(new_array, 1, cjxSpringDay(year));
	//返回结果
	*return_value = *new_array;
}

/////////////////////////////////////////////////////////////////////
//定义一个帮助函数，
//把LUNARDATE对象转换成PHP关联数组
void lunar_to_array(zval* new_array, const LUNARDATE*  lunar_date)
{
	//公历：年，月，日，星期
	add_assoc_long(new_array, "year", lunar_date->wYear);
    add_assoc_long(new_array, "month", lunar_date->wMonth);
	add_assoc_long(new_array, "day",    lunar_date->wDay);
	add_assoc_long(new_array, "weekday", lunar_date->wWeekDay);
	//农历年月日，是否闰月
	add_assoc_long(new_array, "lunar_year", lunar_date->wLunarYear);
	add_assoc_long(new_array, "lunar_month", lunar_date->wLunarMonth);
	add_assoc_long(new_array, "lunar_day", lunar_date->wLunarDay);
	add_assoc_long(new_array, "lunar_isleap", lunar_date->wIsLeapMonth);
}
/* }}} */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
