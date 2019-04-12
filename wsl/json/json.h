//#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>

typedef bool BOOL;
typedef uint32_t U32;
typedef struct value JSON;
typedef struct array array;
typedef struct object object;
typedef struct value value;
typedef struct keyvalue keyvalue;

typedef enum json_e
{
    JSON_NONE,
    JSON_BOL,
    JSON_STR,
    JSON_ARR,
    JSON_OBJ,
    JSON_INT,
} json_e;

struct array
{
    value **elems;
    U32 count;
};

struct keyvalue
{
    char *key;
    value *val;
};

struct object
{
    keyvalue *kvs;
    U32 count;
};

struct value
{
    json_e type;
    union {
        int num;
        BOOL bol;
        char *str;
        array arr;
        object obj;
    };
};

// new
extern JSON *json_new(json_e type);          //complete
extern JSON *json_new_val(value *val); //complete

extern JSON *json_new_str(const char *str); //complete
extern JSON *json_new_obj(void);            //complete
extern JSON *json_new_int(const int num);   //complete
extern JSON *json_new_arr(void);            //complete
extern JSON *json_new_bol(const bool bol);  //complete

// delete
extern void json_del(JSON *json); //complete

// setter
extern BOOL json_set_kv(JSON *json, const char *key, const value *val); //complete

extern BOOL json_set_int(JSON *json, const char *key, int val);           //complete
extern BOOL json_set_bool(JSON *json, const char *key, BOOL val);         //complete
extern BOOL json_set_str(JSON *json, const char *key, const char *val);   //complete
extern BOOL json_set_arr(JSON *json, const char *key, const array *val);  //incomplete
extern BOOL json_set_obj(JSON *json, const char *key, const object *val); //incomplete

// getter
extern JSON *json_get_value(const JSON *json, const char *key); //complete
extern JSON *json_get_index(const JSON *json, U32 idx);         //complete

extern int json_get_int(const JSON *json, const char *key, int def);                 //complete
extern BOOL json_get_bool(const JSON *json, const char *key);                        //complete
extern const char *json_get_str(const JSON *json, const char *key, const char *def); //complete
extern const object *json_get_obj(const JSON *json, const char *key);                //incomplete
extern const array *json_get_arr(const JSON *json, const char *key);                 //incomplete

/**
 * add key-value pair for json
 * @param json [in/out]
 * @param key [in]
 * @param val [in]
 * @return false if:
 *   1.the key has already exists,
 *   2.key or val is illegel,
 *   3.fail
 * @return true if success
 */
extern BOOL json_add_kv(JSON *json, const char *key, const value *val); //complete
extern BOOL arr_add_ele(JSON *json, value *val);

extern int json_save(const JSON *json, const char *fname);
extern void direct_output(const JSON *json);
extern void print_tab(const U32 cnt);
extern void json_write(const JSON *json, const U32 depth);

extern int replace_ip(JSON *json);
extern bool match_ip(const char *str);
extern void json_save_exp(JSON *json);