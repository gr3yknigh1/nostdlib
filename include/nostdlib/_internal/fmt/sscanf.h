#ifndef NOSTDLIB__INTERNAL_SCANF_H_
#define NOSTDLIB__INTERNAL_SCANF_H_

#include <stdarg.h>

#include "nostdlib/types.h"

#define FIRST_BYTE 1
#define S_INFINITY "INFINITY"
#define OCTAL 8
#define HEX 16

typedef enum s_type {
    T_LDOUBLE,
    T_DOUBLE,
    T_FLOAT,
    T_DEC,
    T_UDEC,
    T_OCT,
    T_UOCT,
    T_HEX,
    T_UHEX
} ts_type;

// состояния конечного автомата чтения строки
typedef enum s_state_str {
    ST_STR_SEEK_SPARE,
    ST_STR_GET_CHAR_SPEC,
    ST_STR_GET_CHAR_NOSPEC
} ts_state_str;

// состояния конечного автомата чтения формата
typedef enum s_state_format {
    ST_FORMAT_SPARE,
    ST_FORMAT_PERCENT,
    ST_FORMAT_WIDTH,
    ST_FORMAT_LENGTH,
    ST_FORMAT_SPEC,
    ST_FORMAT_ADD_NOSPEC,
    ST_FORMAT_READY,
} ts_state_format;

// список опций (длина)
typedef enum s_len_opts {
    OPT_LEN_NULL, // 0
    OPT_LEN_h,    // 1
    OPT_LEN_l,    // 2
    OPT_LEN_L     // 3
} ts_len_opts;

// список опций (спецификаторы)
typedef enum s_opts {
    OPT_NULL,  // 0
    OPT_c,     // 1
    OPT_d,     // 2
    OPT_i,     // 3
    OPT_eEfgG, // 4
    OPT_o,     // 5
    OPT_s,     // 6
    OPT_u,     // 7
    OPT_xX,    // 8
    OPT_p,     // 9
    OPT_n,     // 10
} ts_opts;

typedef enum e_data_state {
    ST_NULL,
    ST_FLOAT_BEFORE_DOT,
    ST_DIGITAL_WAIT_DIGIT,
    ST_DIGITAL_DEC,
    ST_DIGITAL_OCT,
    ST_DIGITAL_HEX
} te_data_state;

// структура общая
typedef struct s_sscanf {
    const char *str;    // указатель на строку
    const char *format; // указатель на формат
    void *p_arg;        // указатель на аргумент
    va_list va_args; // структура для получения аргументов
    ts_len_opts opt_long; // длина типа аргумента
    ts_opts opt; // тип аргумента, возвращает парсинг формата
    bool skip_arg;          // флаг, пропуск символов
    const char *str_nospec; // указатель на строковый формат(символы разделители
                            // между данными)
    long int str_nospec_cnt; // общего кол-во символов строкового формата
                             // (разделителя)
    bool spare_before_arg; // разделитель перед флагом
    usize width; // кол-во символов, которые должны быть прочитаны для текущего
                 // формата
} ts_sscanf;

// структура парсинга строки
typedef struct s_str {
    ts_state_str state;
    const char *start_data;
    unsigned int
        data_byte_num; // счетчик кол-ва прочитанных байт значения аргумента
    char *sub_data_start; // начало субстроки аргумента
    // char *sub_data_end;         // ограниечение субстроки аргумента. Для
    // проверки длины
    bool arg_negative; // знак числа (+ или -)
    bool data_result;
    te_data_state data_state;
} ts_str;

#endif // NOSTDLIB__INTERNAL_SCANF_H_
