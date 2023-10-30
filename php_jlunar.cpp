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

//------------------------------------------------------
// 返回今天日期的农历日期对象（无参数）
//------------------------------------------------------
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


//------------------------------------------------------
//  计算 公历 year-month-day 到 1900-1-0的天数 
//     参数: 公历的年月日 1900-1-1 ~ 2100-12-31 之间
//     返回:
//         天数, 一个正数值 1900-1-1为 1       
//------------------------------------------------------
/* {{{ function lunar_get_offset_solardays(int $year, int $month, int $day): int  */
/*  计算公历 $year 年 $month 月 $day 日 到 1900-1-1 的天数 */
PHP_FUNCTION(lunar_get_offset_solardays)
{
	//参数值
	long year, month, day;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(year)
		Z_PARAM_LONG(month)
		Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();
	
	//返回计算结果
	RETURN_LONG(cjxGetOffsetSolarDays(year, month, day));
}
/* }}} */


//------------------------------------------------------
//  计算 公历 year-month-day 是 星期几 
//     参数: 公历的年月日 1900-1-1 ~ 2100-12-31 之间
//     返回:
//         星期数，0 - 星期日， 1 - 星期一 ...
//------------------------------------------------------
/* {{{ function lunar_get_weekday(int $year, int $month, int $day): int  */
/*  计算公历 $year 年 $month 月 $day 日 是 星期几 */
PHP_FUNCTION(lunar_get_weekday)
{
	//参数值
	long year, month, day;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(year)
		Z_PARAM_LONG(month)
		Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();
	
	//返回计算结果
	RETURN_LONG(cjxGetWeekday(year, month, day));
}
/* }}} */


//------------------------------------------------------
//  计算 公历 year 年 month 月 的天数 
//     参数: year  - 年， 1900 - 2100
//          month - 月， 1 - 12
//     返回:
//         天数
//------------------------------------------------------
/* {{{ function lunar_get_solar_daysofmonth(int $year, int $month): int  */
/* 计算公历 $year 年 $month 月 的 天数  */
PHP_FUNCTION(lunar_get_solar_daysofmonth)
{
	//接收参数
	long year, month;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(year)
		Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();
	
	//返回结果
	RETURN_LONG(cjxGetSolarMonthDays(year, month));
}
/* }}} */


//------------------------------------------------------
//  计算 农历 lyear 年 lmonth 月 的天数 
//     参数: lyear  - 农历年， 1900 - 2100
//          lmonth - 农历月， 1 - 13
//     返回:
//         天数
//------------------------------------------------------
/* {{{ function lunar_get_lunar_daysofmonth(int $year, int $month): int  */
/* 计算农历 $lyear 年 $lmonth 月 的 天数  */
PHP_FUNCTION(lunar_get_lunar_daysofmonth)
{
	//接收参数
	long lyear, lmonth;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(lyear)
		Z_PARAM_LONG(lmonth)
	ZEND_PARSE_PARAMETERS_END();

	//返回结果
	RETURN_LONG(cjxGetLunarMonthDays(lyear, lmonth));
}
/* }}} */

//------------------------------------------------------
//  计算 公历 year 年  的天数 
//     参数: year  - 农历年， 1900 - 2100
//
//     返回:
//         天数
//------------------------------------------------------
/* {{{ function lunar_get_solar_daysofyear(int $year): int  */
/* 计算农历 $lyear 年 的 天数  */
PHP_FUNCTION(lunar_get_solar_daysofyear)
{
	//接收参数
	long year;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	//返回结果
	RETURN_LONG(cjxGetSolarYearDays(year));
}
/* }}} */


//------------------------------------------------------
//  计算 农历 lyear 年 的 天数
//------------------------------------------------------
/* {{{ function lunar_get_lunar_daysofyear(int $lyear): int  */
/* 计算 农历 lyear 年 的天数  */
PHP_FUNCTION(lunar_get_lunar_daysofyear)
{
	//接收参数
	long lyear;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(lyear)
	ZEND_PARSE_PARAMETERS_END();

	//返回结果
	RETURN_LONG(cjxGetLunaYearDays(lyear));
}
/* }}} */


//------------------------------------------------------
//  计算 农历 lyear 年  闰几月，没有闰月为0
//------------------------------------------------------
/* {{{ function lunar_get_leapmonth(int $lyear): int  */
/* 计算 农历 lyear 年  闰几月，没有闰月为0  */
PHP_FUNCTION(lunar_get_leapmonth)
{
	//接收参数
	long lyear;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(lyear)
	ZEND_PARSE_PARAMETERS_END();

	//返回结果
	RETURN_LONG(cjxLunarLeapMonth(lyear));
}
/* }}} */


//-----------------------------------
//获取 距离 1900年1月1日 days 天的日期
//      1900年1月1日为1
//  参数: 距离1900-1-1的天数
//-----------------------------------
/* {{{ function lunar_get_date(int $days): array */
/* 距离 1900年1月1日 days 天的日期 */
PHP_FUNCTION(lunar_get_date)
{
	//接收参数
	long days;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	//计算到农历的时间
	LUNARDATE  lunar_date;
	cjxGetDate(days, &lunar_date);

	//填充关联数组并返回
	array_init(return_value);
	set_lunar_array(return_value, &lunar_date); //设置数组字段
}
/* }}} */


//-----------------------------------
// 从公历日期转换到农历日期
//   参数：公历年，月，日
//-----------------------------------
/* {{{ function lunar_get_lunardate(int $year, int $month, int $day): array */
/* 从公历年月日获取农历年月日 */
PHP_FUNCTION(lunar_get_lunardate)
{
	//接收参数
	long year, month, day;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(year)
		Z_PARAM_LONG(month)
		Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();
	//计算到农历的时间
	LUNARDATE  lunar_date;
	lunar_date.wYear  = (WORD)year;
	lunar_date.wMonth = (WORD)month;
	lunar_date.wDay   = (WORD)day;
	cjxGetLunarDate(&lunar_date);

	//填充关联数组并返回
	array_init(return_value);
	set_lunar_array(return_value, &lunar_date); //设置数组字段
}
/* }}} */


//-----------------------------------
// 从农历日期转换到公历日期
//   参数：农历年，月，日
//-----------------------------------
/* {{{ function lunar_get_solardate(int $lyear, int $lmonth, int $lday, bool $isleap = false): array */
/* 从农历年月日获取公历年月日 */
PHP_FUNCTION(lunar_get_solardate)
{
	//接收参数
	long lyear, lmonth, lday;
	zend_bool   isleap;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_LONG(lyear)
		Z_PARAM_LONG(lmonth)
		Z_PARAM_LONG(lday)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(isleap)
	ZEND_PARSE_PARAMETERS_END();
	//计算到公历的时间
	LUNARDATE  lunar_date;
	lunar_date.wLunarYear  = (WORD)lyear;
	lunar_date.wLunarMonth = (WORD)lmonth;
	lunar_date.wLunarDay   = (WORD)lday;
	lunar_date.wIsLeapMonth= isleap ? 1 : 0;
	cjxGetSolarDate(&lunar_date);

	//填充关联数组并返回
	array_init(return_value);
	set_lunar_array(return_value, &lunar_date); //设置数组字段
}
/* }}} */


//-----------------------------------
// 返回农历某年春节的日期(月,日)
//   参数：$year - 农历年
//   返回：array(month,day)
//-----------------------------------
/* {{{ lunar_get_spring(int $year): array(month,day) */
/* 从农历年月日获取公历年月日 */
PHP_FUNCTION(lunar_get_spring)
{
	//接收参数
	long year = 1900;

	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	//计算春节日期并返回数组
	array_init(return_value);  	//初始化数组
	//设置数组数值
	add_index_long(return_value, 0, cjxSpringMonth(year));
	add_index_long(return_value, 1, cjxSpringDay(year));
}
/* }}} */


//-----------------------------------------------------
// 24节气结算函数：
//    计算 y 年的第n个节气几号(从0小寒起算)
//       该节气的月份   (int)(n/2+1)
//-----------------------------------------------------
/* {{{ lunar_get_term_yn(int $year, int $n): int */
/* 计算 year 年的第 n 个节气几号(从0小寒起算) */
PHP_FUNCTION(lunar_get_term_yn)
{
	//接收参数
	long year, n;
	//解析参数，第一个表示必须的参数个数，第二个表示最多参数个数
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(year)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	
	//返回结果
	RETURN_LONG(cjxGetTermYN(year, n));
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
	ext_functions,				/* zend_function_entry */
	NULL,						/* PHP_MINIT - Module initialization */
	NULL,						/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(jlunar),			/* PHP_RINIT - Request initialization */
	NULL,						/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(jlunar),			/* PHP_MINFO - Module info */
	PHP_JLUNAR_VERSION,			/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JLUNAR
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(jlunar)
#endif
