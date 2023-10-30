<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

function lunar_get_today(): array {}

function lunar_get_todaystring(): string {}

function lunar_get_offset_solardays(int $year, int $month, int $day): int {}

function lunar_get_weekday(int $year, int $month, int $day): int {}

function lunar_get_solar_daysofmonth(int $year, int $month): int {}

function lunar_get_lunar_daysofmonth(int $lyear, int $lmonth): int {}

function lunar_get_solar_daysofyear(int $year): int {}

function lunar_get_lunar_daysofyear(int $lyear): int {}

function lunar_get_leapmonth(int $lyear): int {}

function lunar_get_date(int $days): array {}

function lunar_get_lunardate(int $year, int $month, int $day): array {}

function lunar_get_solardate(int $lyear, int $lmonth, int $lday, bool $isleap = false): array {}

function lunar_get_spring(int $year): array {}

function lunar_get_term_yn(int $year, int $n): int {}
