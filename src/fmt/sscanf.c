#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "_internal/sscanf.h"
#include "s21_string.h"

static bool sscanf_init(ts_sscanf **const s);
static bool str_init(ts_sscanf *s, ts_str **str);
static void str_rst(ts_sscanf *s, ts_str *str);
static bool parser(ts_sscanf *s, int *result);
static bool parser_str(ts_sscanf *s, ts_str *str, int *result);
static bool str_is_empty(ts_sscanf *s, ts_str *str, int *result, bool *f_stop);
static bool read_str(ts_sscanf *s, ts_str *str);
static bool st_str_seek_spare(ts_sscanf *s, ts_str *str);
static void st_str_set_state(const ts_sscanf *s, ts_str *str);
static bool st_str_set_data(ts_sscanf *s, ts_str *str);
static bool st_str_check_no_spec(ts_sscanf *s, ts_str *str);
static void str_next(ts_sscanf *s);
static bool is_str_end(char c);
static void rst_format(ts_sscanf *s);
static bool get_format(ts_sscanf *s);
static void check_format_spare(ts_sscanf *s, ts_state_format *f_state);
static bool set_format_str_nospec(ts_sscanf *s, ts_state_format *f_state);
static void add_format_str_nospec(ts_sscanf *s);
static bool set_format_width(ts_sscanf *s, ts_state_format *f_state);
static bool set_format_length(ts_sscanf *s, ts_state_format *f_state);
static bool is_length_opt(ts_sscanf *s);
static bool set_format_spec(ts_sscanf *s, ts_state_format *f_state);
static bool is_specificator(ts_sscanf *s);
static bool check_length_opt(const ts_sscanf *s);
static void set_spec_spare(ts_sscanf *s);
static bool set_data(ts_sscanf *s, ts_str *str);
static void store_opt_c(ts_sscanf *s, ts_str *str);
static bool store_opt_d(ts_sscanf *s, ts_str *str, ts_type t_type);
static void store_int_long(void *p_arg, ts_type t_type, int data,
                           int data_byte_num, bool arg_negative);
static void store_int(void *p_arg, ts_type t_type, int data, int data_byte_num,
                      bool arg_negative);
static bool store_opt_i(ts_sscanf *s, ts_str *str);
static bool store_decimal(ts_sscanf *s, ts_str *str);
static void store_opt_s(ts_sscanf *s, ts_str *str);
static bool store_opt_u(ts_sscanf *s, ts_str *str);
static void store_opt_n(ts_sscanf *s, ts_str *str);

static bool is_spare(char c);
static bool is_percent(char c);
static bool is_digit(char c);

static void mem_free(ts_sscanf *s);

int
s21_sscanf(const char *str, const char *format, ...) {
    int result = -1;
    ts_sscanf *s = NULL;

    if (sscanf_init(&s)) {
        if (format != NULL) {
            s->str = str;
            s->format = format;
            va_start(s->va_args, format);
            parser(s, &result);
            va_end(s->va_args);
        }
        mem_free(s);
    }

    return (result);
}

static bool
sscanf_init(ts_sscanf **const s) {
    *s = (ts_sscanf *)malloc(sizeof(ts_sscanf));
    if (*s != NULL) {
        (*s)->str = NULL;
        (*s)->format = NULL;
        (*s)->p_arg = NULL;
        (*s)->opt_long = OPT_LEN_NULL;
        (*s)->opt = OPT_NULL;
        (*s)->str_nospec = NULL;
        (*s)->str_nospec_cnt = -1;
        (*s)->width = 0;
        (*s)->skip_arg = false;
        (*s)->spare_before_arg = false;
    }

    return (*s != NULL ? true : false);
}

static bool
str_init(ts_sscanf *s, ts_str **str) {
    *str = (ts_str *)malloc(sizeof(ts_str));
    if (*str != NULL) {
        (*str)->start_data = NULL;
        str_rst(s, *str);
    }
    return (*str != NULL ? true : false);
}

static void
str_rst(ts_sscanf *s, ts_str *str) {
    str->state = ST_STR_SEEK_SPARE;
    str->data_byte_num = FIRST_BYTE;
    str->sub_data_start = (char *)s->str;
    str->arg_negative = false;
    str->data_state = ST_NULL;
    str->data_result = false;
}

static bool
parser(ts_sscanf *s, int *result) {
    ts_str *str = NULL;

    if (str_init(s, &str)) {
        bool f_stop = false;

        str->start_data = s->str;
        do {
            if (get_format(s)) {
                f_stop = parser_str(s, str, result);
            } else {
                // ошибка парсинга формата
                f_stop = true;
                if (*result == -1)
                    *result = 0;
            }
        } while (!is_str_end(*(s->format)) && !f_stop);
        free(str);
    }

    return (true);
}

bool
parser_str(ts_sscanf *s, ts_str *str, int *result) {
    bool f_stop = false;

    if (!str_is_empty(s, str, result, &f_stop)) {
        if (read_str(s, str)) {
            // успешно
            if (s->opt == OPT_n) {
                store_opt_n(s, str);
                if (*result == -1) {
                    *result = 0;
                }
            } else {
                // инкремент результата
                if (!s->skip_arg && s->str_nospec == NULL) {
                    // нет аргумента пропуска и нет неспецификаторов
                    if (*result == -1) {
                        *result = 0;
                    }
                    (*result)++;
                } else if (s->str_nospec != NULL || s->skip_arg) {
                    if (*result == -1) {
                        *result = 0;
                    }
                }
            }
        } else {
            // ошибка по формату или конец строки
            if (s->opt == OPT_n) {
                store_opt_n(s, str);
                if (*result == -1) {
                    *result = 0;
                }
            } else {
                if (is_str_end(*(s->str)) && s->str_nospec_cnt != 0) {
                    // ошибка ввода-вывода
                    if (*result == 0) {
                        *result = -1;
                    }
                } else if (*result == -1) {
                    *result = 0;
                }
                f_stop = true;
            }
        }
    }

    return (f_stop);
}

bool
str_is_empty(ts_sscanf *s, ts_str *str, int *result, bool *f_stop) {
    bool res = false;

    if (is_str_end(*(s->str))) {
        // пустая строка
        res = true;
        if (s->opt == OPT_n) {
            store_opt_n(s, str);
            if (*result == -1)
                *result = 0;
        } else {
            if (*result == 0)
                *result = -1;
            *f_stop = true;
        }
    }

    return (res);
}

bool
read_str(ts_sscanf *s, ts_str *str) {
    str->data_result = false;
    if (!is_str_end(*(s->str))) {
        bool f_stop = false;

        str_rst(s, str);
        while (!is_str_end(*(s->str)) && !f_stop) {
            if (str->state == ST_STR_SEEK_SPARE) {
                f_stop = st_str_seek_spare(s, str);
            } else if (str->state == ST_STR_GET_CHAR_SPEC) {
                f_stop = st_str_set_data(s, str);
            } else if (str->state == ST_STR_GET_CHAR_NOSPEC) {
                f_stop = st_str_check_no_spec(s, str);
            }
            if (is_str_end(*(s->str))) {
                f_stop = true;
            }
        }
    }
    return (str->data_result);
}

bool
st_str_seek_spare(ts_sscanf *s, ts_str *str) {
    bool f_stop = false;

    if (is_spare(*(s->str))) {
        // разделитель
        if (!s->spare_before_arg) {
            // нет разделителя перед аргументом в формате
            if (s->opt == OPT_n) {
                f_stop = true;
                str->data_result = true;
            } else if (s->opt == OPT_c || s->str_nospec != NULL) {
                // нет разделителя, установить состояние
                st_str_set_state(s, str);
            } else {
                str_next(s);
            }

        } else {
            str_next(s);
        }
    } else if (s->opt == OPT_n) {
        // начало подстроки аргумента и флаг n в формате с разделителем
        f_stop = true;
        str->data_result = true;
    } else {
        // начало подстроки аргумента
        str->sub_data_start = (char *)s->str;
        st_str_set_state(s, str);
    }

    return (f_stop);
}

static void
st_str_set_state(const ts_sscanf *s, ts_str *str) {
    if (s->str_nospec == NULL) {
        str->state = ST_STR_GET_CHAR_SPEC;
    } else {
        str->state = ST_STR_GET_CHAR_NOSPEC;
    }
}

static bool
st_str_set_data(ts_sscanf *s, ts_str *str) {
    bool f_stop = false;

    if (s->opt == OPT_c) {
        if (s->width > 0) {
            // задана ширина
            if (str->data_byte_num == (s->width + 1)) {
                // ширина соответствует текущему курсору - 1 или пробел
                // останавливаемся. Позиция курсора на следующем символе
                f_stop = true;
            } else {
                // ширина меньше текущего курсора или нет пробела
                // двигаемся до установленной ширины
                store_opt_c(s, str);
                str_next(s);
                (str->data_byte_num)++;
            }
        } else {
            // сохраняем один символ
            store_opt_c(s, str);
            str_next(s);
            f_stop = true;
        }
    } else if (is_spare(*(s->str))) {
        f_stop = true;
    } else {
        // остальные спецификаторы кроме 'c, n'
        if (str->data_byte_num == (s->width + 1) && s->width > 0) {
            // ширина соответствует текущему курсору - 1
            f_stop = true;
        } else {
            // сохраняем данные, пока не будет разделителя и совпадения по
            // ширине
            if (set_data(s, str)) {
                if (s->width == 0 && s->opt == OPT_c) {
                    f_stop = true;
                }
                str_next(s);
                (str->data_byte_num)++;
            } else {
                // ошибка по формату или стоп, т.к. необходимые данные записаны
                f_stop = true;
            }
        }
    }
    return (f_stop);
}

// символы неспецификаторы
bool
st_str_check_no_spec(ts_sscanf *s, ts_str *str) {
    bool f_stop = false;

    if (*(s->str) != *(s->str_nospec)) {
        // несоответствие неспецификатора символу строки
        f_stop = true;
    } else {
        (s->str_nospec_cnt)--;
        if (s->str_nospec_cnt == 0) {
            // прочитаны все символы не явл. спецификаторами формата
            f_stop = true;
            str->data_result = true;
        }
        str_next(s);
        (s->str_nospec)++;
    }
    return (f_stop);
}

void
str_next(ts_sscanf *s) {
    if (!is_str_end(*(s->str))) {
        (s->str)++;
    }
}

bool
is_str_end(char c) {
    return (c == '\0' ? true : false);
}

void
rst_format(ts_sscanf *s) {
    s->opt_long = OPT_LEN_NULL;
    s->opt = OPT_NULL;
    s->width = 0;
    s->p_arg = NULL;
    s->skip_arg = false;
    s->str_nospec = NULL;
    s->str_nospec_cnt = -1;
    s->spare_before_arg = false;
}

// парсинг строки формата
bool
get_format(ts_sscanf *s) {
    bool result = false;
    if (!is_str_end(*(s->format))) {
        bool f_stop = false;
        ts_state_format f_state = ST_FORMAT_SPARE;

        rst_format(s);
        // перебираем строку формата по одному символу (конечный автомат)
        while (!f_stop) {
            if (f_state == ST_FORMAT_SPARE) {
                check_format_spare(s, &f_state);
            } else if (f_state == ST_FORMAT_ADD_NOSPEC) {
                f_stop = !set_format_str_nospec(s, &f_state);
            } else if (f_state == ST_FORMAT_WIDTH) {
                f_stop = !set_format_width(s, &f_state);
            } else if (f_state == ST_FORMAT_LENGTH) {
                f_stop = !set_format_length(s, &f_state);
            } else if (f_state == ST_FORMAT_SPEC) {
                f_stop = !set_format_spec(s, &f_state);
            }
            if (f_state == ST_FORMAT_READY) {
                result = true;
                f_stop = true;
                if (!s->skip_arg && s->str_nospec == NULL) {
                    s->p_arg = va_arg(s->va_args, void *);
                }
            }
            if (is_str_end(*(s->format))) {
                f_stop = true;
            } else {
                (s->format)++;
            }
        }
        if (s->width >= INT_MAX) {
            s->width = 0;
        }
    }
    return (result);
}

// пропуск разделителей
void
check_format_spare(ts_sscanf *s, ts_state_format *f_state) {
    if (!is_spare(*(s->format))) {
        if (is_percent(*(s->format))) {
            *f_state = ST_FORMAT_WIDTH;
        } else {
            set_format_str_nospec(s, f_state);
        }
    } else {
        s->spare_before_arg = true;
    }
}

// строковый формат без спецификатора
bool
set_format_str_nospec(ts_sscanf *s, ts_state_format *f_state) {
    bool result = true;

    *f_state = ST_FORMAT_ADD_NOSPEC;
    if (is_percent(*(s->format))) {
        *f_state = ST_FORMAT_READY;
        (s->format)--;
    } else if (is_spare(*(s->format))) {
        *f_state = ST_FORMAT_READY;
        (s->format)--;
    } else if (is_str_end(*(s->format))) {
        if (s->str_nospec_cnt > 0)
            *f_state = ST_FORMAT_READY;
        else {
            result = false;
        }
    } else {
        add_format_str_nospec(s);
    }

    return (result);
}

void
add_format_str_nospec(ts_sscanf *s) {
    if (s->str_nospec == NULL) {
        s->str_nospec = s->format;
        s->str_nospec_cnt = 0;
    }
    (s->str_nospec_cnt)++;
}

bool
set_format_width(ts_sscanf *s, ts_state_format *f_state) {
    bool result = true;

    if (is_digit(*(s->format))) {
        // перед агументом число
        if (s->width <= INT_MAX) {
            s->width = s->width * 10 + (*(s->format) - '0');
        }
    } else if (*(s->format) == '*') {
        if (s->width > 0) {
            result = false;
        } else {
            s->skip_arg = true;
        }
    } else {
        *f_state = ST_FORMAT_LENGTH;
        result = set_format_length(s, f_state);
    }

    return (result);
}

bool
set_format_length(ts_sscanf *s, ts_state_format *f_state) {
    bool result = true;

    if (is_length_opt(s)) {
        *f_state = ST_FORMAT_SPEC;
    } else {
        result = set_format_spec(s, f_state);
    }

    return (result);
}

bool
is_length_opt(ts_sscanf *s) {
    bool result = true;
    char c = *(s->format);

    if (c == 'h') {
        s->opt_long = OPT_LEN_h;
    } else if (c == 'l') {
        s->opt_long = OPT_LEN_l;
    } else if (c == 'L') {
        s->opt_long = OPT_LEN_L;
    } else {
        result = false;
    }

    return (result);
}

bool
set_format_spec(ts_sscanf *s, ts_state_format *f_state) {
    bool result = true;
    // установить спецификатор
    if (is_specificator(s)) {
        // соответствие спецификатору
        *f_state = ST_FORMAT_READY;
        set_spec_spare(
            s); // назначить 'разделитель' спецификаторам (кроме c, n,
                // неспецификаторы), для которых не учитывается разделитель
        if (s->opt_long != OPT_LEN_NULL) {
            result = check_length_opt(
                s); // проверка на соответствие длины опции спецификаторам
        }
    } else if (is_percent(*(s->format))) { // % вместо спецификатора, добавить
                                           // как неспицификатор
        add_format_str_nospec(s);
        s->spare_before_arg =
            true; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!КОСТЫЛЬ???
                  // для '%' не учитывается разделитель в формате
        *f_state = ST_FORMAT_READY;
    } else {
        // добавляем символ как неспецификатор
        result = false;
    }

    return (result);
}

static bool
is_specificator(ts_sscanf *s) {
    // проверка спецификатора
    bool result = true;
    char c = *(s->format);

    if (c == 'c') {
        s->opt = OPT_c;
    } else if (c == 'd') {
        s->opt = OPT_d;
    } else if (c == 'i') {
        s->opt = OPT_i;
    } else if (c == 's') {
        s->opt = OPT_s;
    } else if (c == 'u') {
        s->opt = OPT_u;
    } else if (c == 'n') {
        s->opt = OPT_n;
    } else {
        result = false;
    }

    return (result);
}

static bool
check_length_opt(const ts_sscanf *s) {
    // проверка определителя для спецификатора
    bool result = false;

    if (s->opt_long == OPT_LEN_h &&
        (s->opt == OPT_i || s->opt == OPT_d || s->opt == OPT_u ||
         s->opt == OPT_o || s->opt == OPT_xX)) {
        result = true;
    } else if (s->opt_long == OPT_LEN_l &&
               (s->opt == OPT_i || s->opt == OPT_d || s->opt == OPT_u ||
                s->opt == OPT_o || s->opt == OPT_xX || s->opt == OPT_c ||
                s->opt == OPT_s)) {
        result = true;
    } else if (s->opt_long == OPT_LEN_L && s->opt == OPT_eEfgG) {
        result = true;
    }

    return (result);
}

static void
set_spec_spare(ts_sscanf *s) {
    // установка зависимостей спецификатора от разделителя
    if (s->opt != OPT_c && s->opt != OPT_n) {
        s->spare_before_arg = true;
    }
}

static bool
set_data(ts_sscanf *s, ts_str *str) {
    bool result = true;

    if (s->opt == OPT_d) {
        result = store_opt_d(s, str, T_DEC);
    } else if (s->opt == OPT_i) {
        result = store_opt_i(s, str);
    } else if (s->opt == OPT_s) {
        store_opt_s(s, str);
    } else if (s->opt == OPT_u) {
        result = store_opt_u(s, str);
    }
    return (result);
}

static void
store_opt_c(ts_sscanf *s, ts_str *str) {
    str->data_result = true;
    // запись в аргумент однобайтового символа
    if (!s->skip_arg) {
        // нет пропуска, сохраняем каждый символ как в описании, в
        // инкрементированный указатель
        *((char *)s->p_arg) = *(s->str);
        s->p_arg = ((char *)s->p_arg) + 1;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // FIXME: Arithmetic on a pointer to void is a GNU extension
    }
}

static bool
store_opt_d(ts_sscanf *s, ts_str *str, ts_type t_type) {
    bool result = true;

    if (*(s->str) == '+') {
        if (str->data_byte_num == FIRST_BYTE) {
            str->arg_negative = false;
        } else {
            result = false;
        }
    } else if (*(s->str) == '-') {
        if (str->data_byte_num == FIRST_BYTE) {
            str->arg_negative = true;
        } else {
            result = false;
        }
    } else if (is_digit(*(s->str))) { // if (LOG) printf("\tstore_opt_d->is
                                      // digit->p_arg=%d\n", *((int*)s->p_arg));
        if (!s->skip_arg) {
            int i = *(s->str) - '0';
            if (s->opt_long == OPT_LEN_l) { // ld
                store_int_long(s->p_arg, t_type, i, str->data_byte_num,
                               str->arg_negative);
            } else { // d
                store_int(s->p_arg, t_type, i, str->data_byte_num,
                          str->arg_negative);
            }
        }
        str->data_result = true;
    } else {
        result = false;
    }
    return (result);
}

static void
store_int_long(void *p_arg, ts_type t_type, int data, int data_byte_num,
               bool arg_negative) {
    if (t_type == T_DEC) {
        if (data_byte_num == FIRST_BYTE) {
            *((long int *)p_arg) = 0;
        }
        *((long int *)p_arg) = *((long int *)p_arg) * 10;
        for (int ii = 0; ii < data; ii++) {
            (*((long int *)p_arg))++;
        }
        if (arg_negative) {
            *((long int *)p_arg) = -*((long int *)p_arg);
        }
    } else if (t_type == T_UDEC) {
        if (data_byte_num == FIRST_BYTE) {
            *((unsigned long int *)p_arg) = 0;
        }
        *((unsigned long int *)p_arg) = *((unsigned long int *)p_arg) * 10;
        for (int ii = 0; ii < data; ii++) {
            (*((unsigned long int *)p_arg))++;
        }
        if (arg_negative) {
            *((unsigned long int *)p_arg) = -*((unsigned long int *)p_arg);
        }
    }
}

static void
store_int(void *p_arg, ts_type t_type, int data, int data_byte_num,
          bool arg_negative) {
    if (t_type == T_DEC) {
        if (data_byte_num == FIRST_BYTE) {
            *((int *)p_arg) = 0;
        }
        *((int *)p_arg) = *((int *)p_arg) * 10;
        for (int ii = 0; ii < data; ii++) {
            (*((int *)p_arg))++;
        }
        if (arg_negative) {
            *((int *)p_arg) = -*((int *)p_arg);
        }
    } else if (t_type == T_UDEC) {
        if (data_byte_num == FIRST_BYTE) {
            *((unsigned int *)p_arg) = 0;
        }
        *((unsigned int *)p_arg) = *((unsigned int *)p_arg) * 10;
        for (int ii = 0; ii < data; ii++) {
            (*((unsigned int *)p_arg))++;
        }
        if (arg_negative) {
            *((unsigned int *)p_arg) = -*((unsigned int *)p_arg);
        }
    }
}

static bool
store_opt_i(ts_sscanf *s, ts_str *str) {
    bool result = true;

    if (str->data_byte_num == FIRST_BYTE) {
        // назначить состояние
        if (*(s->str) == '+' && str->data_state == ST_NULL) {
            str->data_state = ST_DIGITAL_WAIT_DIGIT;
            str->data_byte_num =
                FIRST_BYTE - 1; // сбросить для повторного прохода
            str->arg_negative = false;
        } else if (*(s->str) == '-' && str->data_state == ST_NULL) {
            str->data_state = ST_DIGITAL_WAIT_DIGIT;
            str->data_byte_num =
                FIRST_BYTE - 1; // сбросить для повторного прохода
            str->arg_negative = true;
        } else if (*(s->str) == '0') {
            // после +/- или вместо, первый 0. Далее ожидается только octal,
            // hex.
            result = store_decimal(s, str); // store first zero
            str->data_result = true;
        } else if (is_digit(*(s->str))) {
            // после +/- или вместо, первая цифра, не 0
            str->data_state = ST_DIGITAL_DEC;
            result = store_decimal(s, str);
            str->data_result = true;
        } else {
            result = false;
        }

    } else if (str->data_state == ST_DIGITAL_DEC) {
        result = store_decimal(s, str);
    } else {
        result = false;
    }

    return (result);
}

static bool
store_decimal(ts_sscanf *s, ts_str *str) {
    bool result = true;

    result = store_opt_d(s, str, T_DEC);

    return (result);
}

static bool
store_opt_u(ts_sscanf *s, ts_str *str) {
    bool result = true;

    result = store_opt_d(s, str, T_UDEC);

    return (result);
}

static void
store_opt_s(ts_sscanf *s, ts_str *str) {
    str->data_result = true;
    if (s->opt_long == OPT_LEN_l) {
        // запись в аргумент многобайтового символа
        if (!s->skip_arg) {
            wchar_t *tmp = s->p_arg;
            size_t cnt = mbstowcs(
                tmp, str->sub_data_start,
                str->data_byte_num); // Преобразует строку многобайтовых
                                     // символов в строку широких символов
            if (cnt) {
                tmp += str->data_byte_num;
                *tmp = '\0';
            }
        }
        int byte_cnt = mblen(
            (s->str), MB_CUR_MAX); // определение длины многобайтового символа
        for (int i = 1; i < byte_cnt; i++) {
            str_next(s);
        }
    } else {
        // запись в аргумент однобайтового символа
        if (!s->skip_arg) {
            *((char *)s->p_arg) = (*(s->str));
            s->p_arg = ((char *)s->p_arg) + 1;
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            // FIXME: Arithmetic on a pointer to void is a GNU extension
            *((char *)(s->p_arg)) = '\0';
        }
    }
}

static void
store_opt_n(ts_sscanf *s, ts_str *str) {
    str->data_result = true;
    if (!s->skip_arg) {
        *((int *)(s->p_arg)) = s->str - str->start_data;
    }
}

static bool
is_spare(char c) {
    return (c == 32 || c == '\t' || c == '\n' ? true : false);
}

static bool
is_percent(char c) {
    return (c == '%' ? true : false);
}

static bool
is_digit(char c) {
    return (c >= '0' && c <= '9' ? true : false);
}

static void
mem_free(ts_sscanf *s) {
    if (s != NULL) {
        free(s);
    }
}
