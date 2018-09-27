/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
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
  |  农历扩展函数                                                          |
  +----------------------------------------------------------------------+
  | Author:  陈逸少（jmchxy@gmail.com）                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_JLUNAR_H
#define PHP_JLUNAR_H

extern zend_module_entry jlunar_module_entry;
#define phpext_jlunar_ptr &jlunar_module_entry

#ifdef PHP_WIN32
#	define PHP_JLUNAR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_JLUNAR_API __attribute__ ((visibility("default")))
#else
#	define PHP_JLUNAR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(jlunar);
PHP_MSHUTDOWN_FUNCTION(jlunar);
PHP_RINIT_FUNCTION(jlunar);
PHP_RSHUTDOWN_FUNCTION(jlunar);
PHP_MINFO_FUNCTION(jlunar);

//=============================================
//  功能函数
//=============================================
// 返回今天的日期（无参数）
PHP_FUNCTION(lunar_get_today);
// 返回今天的日期的字符串（无参数）
PHP_FUNCTION(lunar_get_todaystring);
// 返回指定年/月/日的星期数，0为星期日
PHP_FUNCTION(lunar_get_weekday);
// 计算公历某月的天数(参数，年/月)
PHP_FUNCTION(lunar_get_solar_daysofmonth);
// 计算农历某月的天数(参数，农历年/月)
PHP_FUNCTION(lunar_get_lunar_daysofmonth);
// 计算农历某年的天数(参数，农历年)
PHP_FUNCTION(lunar_get_lunar_daysofyear);
// 计算农历某年闰几月，没有闰月为0
PHP_FUNCTION(lunar_get_leapmonth);
//------------------------------------------------------
//  计算 公历 year-month-day 到 1900-1-0的天数 
//     参数: 公历的年月日 1900-1-1 ~ 2100-12-31 之间
//     返回:
//          天数, 一个正数值 1900-1-1为 1       
//-----------------------------------------------------
PHP_FUNCTION(lunar_get_offset_solardays);
//-----------------------------------
//获取 距离 1900年1月1日 days 天的日期
//      1900年1月1日为1
//  参数: 距离1900-1-1的天数
//-----------------------------------
PHP_FUNCTION(lunar_get_date);
//-----------------------------------
// 从公历时间转换到农历时间
//   参数：公历年，月，日
//-----------------------------------
PHP_FUNCTION(lunar_get_lunardate);
//-----------------------------------
// 从农历时间转换到公历时间
//   参数：农历年，月，日，是否闰月
//-----------------------------------
PHP_FUNCTION(lunar_get_solardate);
//-----------------------------------
// 返回农历某年春节的日期(月,日)
//   参数：农历年
//   返回：array(month,day)
//-----------------------------------
PHP_FUNCTION(lunar_get_spring);
//-----------------------------------------------------
// 24节气结算函数：
//    计算 y 年的第n个节气几号(从0小寒起算)
//       该节气的月份   (int)(n/2+1)
//-----------------------------------------------------
PHP_FUNCTION(lunar_get_term_yn);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(jlunar)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(jlunar)
*/

/* In every utility function you add that needs to use variables 
   in php_jlunar_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as JLUNAR_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define JLUNAR_G(v) TSRMG(jlunar_globals_id, zend_jlunar_globals *, v)
#else
#define JLUNAR_G(v) (jlunar_globals.v)
#endif

#endif	/* PHP_JLUNAR_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
