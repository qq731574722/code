/**
 * json data-structure api
 * @author xiaopeng
 * @time 2019/3/13
 */

#include "json.h"

const int INIT_ARR_SIZE = 4;
const int ARR_EXPAND_TIMES = 2;
//const int BUFF_STR_SIZE=255;
#define BUFF_STR_SIZE 255
#define TAB_SIZE 2

JSON *json_new(json_e type)
{
    JSON *json = (JSON *)calloc(1, sizeof(JSON));
    if (!json)
        return NULL;
    json->type = type;
    return json;
}

JSON *json_new_str(const char *str)
{
    assert(str);
    JSON *json = json_new(JSON_STR);
    if (!json)
        return NULL;
    json->str = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!json->str)
    {
        json_del(json);
        return NULL;
    }
    strcpy(json->str, str);
    return json;
}

JSON *json_new_obj(void)
{
    JSON *json = json_new(JSON_OBJ);
    if (!json)
        return NULL;
    json->obj.kvs = (keyvalue *)malloc(sizeof(keyvalue) * INIT_ARR_SIZE);
    if (!json->obj.kvs)
    {
        json_del(json);
        return NULL;
    }
    return json;
}

JSON *json_new_int(const int num)
{
    JSON *json = json_new(JSON_INT);
    if (!json)
        return NULL;
    json->num = num;
    return json;
}

JSON *json_new_arr(void)
{
    JSON *json = json_new(JSON_ARR);
    if (!json)
        return NULL;
    json->arr.elems = (value **)calloc(sizeof(value *) * INIT_ARR_SIZE, sizeof(value *));
    if (!json->arr.elems)
    {
        json_del(json);
        return NULL;
    }
    json->arr.count = 0;
    return json;
}

JSON *json_new_bol(const bool bol)
{
    JSON *json = json_new(JSON_BOL);
    if (!json)
        return NULL;
    json->bol = bol;
    return json;
}

void json_del(JSON *json)
{
    U32 i;
    assert(json);
    if (!json)
        return;
    switch (json->type)
    {
    case JSON_ARR:
        for (i = 0; i < json->arr.count; i++)
        {
            json_del(json->arr.elems[i]);
        }
        free(json->arr.elems);
        break;

    case JSON_STR:
        if (json->str)
        {
            free(json->str);
            json->str = NULL;
        }
        break;

    case JSON_OBJ:
        for (i = 0; i < json->obj.count; i++)
        {
            if (json->obj.kvs[i].key)
            {
                free(json->obj.kvs[i].key);
                json->obj.kvs[i].key = NULL;
            }
            json_del(json->obj.kvs[i].val);
        }
        free(json->obj.kvs);
        break;
    default:
        break;
    }
    if (json)
    {
        free(json);
        json = NULL;
    }
}

JSON *json_new_val(value *val)
{
    assert(val);
    if (!val || val->type == JSON_NONE)
        return NULL;
    JSON *json = json_new(val->type);
    if (!json)
        return NULL;
    switch (val->type)
    {
    case JSON_INT:
        json->num = val->num;
        break;
    case JSON_BOL:
        json->bol = val->bol;
        break;
    case JSON_STR:
        json->str = (char *)malloc((strlen(val->str) + 1) * sizeof(char));
        if (!json->str)
            return NULL;
        strcpy(json->str, val->str);
        break;
    case JSON_ARR:
        assert(val->arr.count == 0 || val->arr.elems);
        json->arr.elems = val->arr.elems;
        json->arr.count = val->arr.count;
        break;
        /*
    case JSON_OBJ:
        assert(val->obj.count == 0 || val->obj.kvs);
        json->obj.kvs = (keyvalue *)malloc(sizeof(val->obj.kvs) * (val->obj.count));
        if (!json->obj.kvs)
            return NULL;
        for (U32 i = 0; i < val->obj.count; i++)
        {
            json->obj.kvs[i].key = val->obj.kvs[i].key;
            json->obj.kvs[i].val = val->obj.kvs[i].val;
        }
        json->obj.count = val->obj.count;
        break;
    */
    }

    return json;
}

BOOL json_set_kv(JSON *json, const char *key, const value *val)
{
    U32 i;
    assert(json);
    assert(key);
    assert(val);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_val(val);
    if (!new_val)
        return false;
    for (i = 0; i < json->obj.count; i++)
    {
        assert(json->obj.kvs[i].key);
        if (!strcmp(json->obj.kvs[i].key, key))
        {
            json_del(json->obj.kvs[i].val);
            json->obj.kvs[i].val = new_val;
            return true;
        }
    }
    return json_add_kv(json, key, val);
}

BOOL json_set_int(JSON *json, const char *key, int val)
{
    assert(json);
    assert(key);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_int(val);
    if (!new_val)
        return false;
    return json_set_kv(json, key, new_val);
}

BOOL json_set_bool(JSON *json, const char *key, BOOL val)
{
    assert(json);
    assert(key);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_bol(val);
    if (!new_val)
        return false;
    return json_set_kv(json, key, new_val);
}

BOOL json_set_str(JSON *json, const char *key, const char *val)
{
    assert(json);
    assert(key);
    assert(val);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_str(val);
    if (!new_val)
        return false;
    return json_set_kv(json, key, new_val);
}

/*
BOOL json_set_arr(JSON *json, const char *key, const array *val)
{
    assert(json);
    assert(key);
    assert(val);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_arr();
    if (!new_val)
        return false;
    new_val->arr.elems = val->elems;
    new_val->arr.count = val->count;
    return json_set_kv(json, key, new_val);
}

BOOL json_set_obj(JSON *json, const char *key, const object *val)
{
    assert(json);
    assert(key);
    assert(val);
    if (json->type != JSON_OBJ || NULL == key || !strcmp(key, ""))
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    value *new_val = json_new_obj();
    if (!new_val)
        return false;
    new_val->obj.kvs = (keyvalue *)malloc(sizeof(keyvalue) * (val->count));
    if (!new_val->obj.kvs)
    {
        json_del(new_val);
        return false;
    }
    memcpy(new_val->obj.kvs, val->kvs, sizeof(keyvalue) * (val->count));
    new_val->obj.count = val->count;
    return true;
}
*/
BOOL json_get_bool(const JSON *json, const char *key)
{
    assert(json);
    if (json->type != JSON_OBJ)
        return false;
    assert(json->obj.count == 0 || json->obj.kvs);
    const JSON *_json = json_get_value(json, key);
    if (!_json || _json->type != JSON_BOL)
        return false;
    return _json->bol;
}

JSON *json_get_value(const JSON *json, const char *key)
{
    U32 i;
    assert(json);
    if (json->type != JSON_OBJ)
        return NULL;
    assert(json->obj.count == 0 || json->obj.kvs);
    for (i = 0; i < json->obj.count; ++i)
    {
        if (strcmp(json->obj.kvs[i].key, key) == 0)
            return json->obj.kvs[i].val;
    }
    return NULL;
}

JSON *json_get_index(const JSON *json, U32 idx)
{
    assert(json);
    if (json->type != JSON_ARR)
        return NULL;
    if (idx >= json->arr.count)
        return NULL;
    return json->arr.elems[idx];
}

int json_get_int(const JSON *json, const char *key, int def)
{
    assert(json);
    if (json->type != JSON_OBJ)
        return def;
    assert(json->obj.count == 0 || json->obj.kvs);
    const JSON *_json = json_get_value(json, key);
    if (!_json || _json->type != JSON_INT)
        return def;
    return _json->num;
}

const char *json_get_str(const JSON *json, const char *key, const char *def)
{
    static char str[BUFF_STR_SIZE];
    assert(json);
    if (json->type != JSON_OBJ)
        return def;
    assert(json->obj.count == 0 || json->obj.kvs);
    const JSON *_json = json_get_value(json, key);
    if (!_json)
        return def;
    switch (_json->type)
    {
    case JSON_STR:
        return _json->str;
    case JSON_INT:
        sprintf(str, "%d", _json->num);
        return str;
    case JSON_BOL:
        return _json->bol ? "true" : "false";
    default:
        return def;
    }
    return def;
}

BOOL json_add_kv(JSON *json, const char *key, const value *val)
{
    assert(json);
    assert(key);
    assert(val);
    if (json_get_value(json, key) != NULL) // key already exists
        return false;
    // if key or val is illegal
    if (NULL == key || NULL == val || !strcmp(key, ""))
        return false;

    // get current allocated count
    U32 cnt = json->obj.count;
    U32 allocated_cnt = INIT_ARR_SIZE;
    while (allocated_cnt < cnt)
        allocated_cnt *= ARR_EXPAND_TIMES;

    // old memeory area has been run out
    // expand to a new area
    if (allocated_cnt == cnt)
    {
        keyvalue *new_area =
            (keyvalue *)malloc(sizeof(keyvalue) * allocated_cnt * ARR_EXPAND_TIMES);
        if (!new_area)
            return false;
        // copy from old area
        for (U32 i = 0; i < cnt; i++)
        {
            new_area[i].key = json->obj.kvs[i].key;
            new_area[i].val = json->obj.kvs[i].val;
        }
        free(json->obj.kvs);
        json->obj.kvs = new_area;
    }
    json->obj.kvs[cnt].key =
        (char *)malloc((strlen(key) + 1) * sizeof(char));
    if (json->obj.kvs[cnt].key == NULL)
    {
        return false;
    }
    strcpy(json->obj.kvs[cnt].key, key);
    json->obj.kvs[cnt].val = val;
    json->obj.count++;
    return true;
    return false;
}

BOOL arr_add_ele(JSON *json, value *val)
{

    assert(json);
    assert(val);
    if (json->type != JSON_ARR)
        return false;
    // get current allocated count
    U32 cnt = json->arr.count;
    U32 allocated_cnt = INIT_ARR_SIZE;
    while (allocated_cnt < cnt)
        allocated_cnt *= ARR_EXPAND_TIMES;

    // old memeory area has been run out
    // expand to a new area
    if (cnt == allocated_cnt)
    {
        value **new_area =
            (value **)realloc(json->arr.elems, sizeof(value *) * cnt * ARR_EXPAND_TIMES);
        if (!new_area)
        {
            return false;
        }
        json->arr.elems = new_area;
    }
    json->arr.elems[cnt] = val;
    json->arr.count++;
    return true;
}

int json_save(const JSON *json, const char *fname)
{
    FILE *file = freopen(fname, "w", stdout);
    //printf("file name:%s\n",fname);
    json_write(json, 0);
    fclose(file);
    return 0;
}

void json_write(const JSON *json, const U32 depth)
{
    assert(json);
    switch (json->type)
    {
    // this 3 type of json can be direct print
    case JSON_STR:
        assert(json->str);
    case JSON_BOL:
    case JSON_INT:
        print_tab(depth);
        direct_output(json);
        break;

    case JSON_ARR:
        assert(json->arr.elems);
        for (U32 i = 0; i < json->arr.count; i++)
        {
            int type = json->arr.elems[i]->type;
            if (type == JSON_ARR || type == JSON_OBJ)
            {
                json_write(json->arr.elems[i], depth + 1);
            }
            else
            {
                print_tab(depth);
                printf("- ");
                direct_output(json->arr.elems[i]);
            }
        }
        break;
    case JSON_OBJ:
        assert(json->obj.kvs);
        for (U32 i = 0; i < json->obj.count; i++)
        {
            print_tab(depth);
            printf("%s:", json->obj.kvs[i].key);
            int type = json->obj.kvs[i].val->type;
            if (type == JSON_ARR || type == JSON_OBJ)
            {
                printf("\n");
                json_write(json->obj.kvs[i].val, depth + 1);
            }
            else
            {
                printf(" ");
                direct_output(json->obj.kvs[i].val);
            }
        }
        break;
        
    }
}

void direct_output(const JSON *json)
{
    assert(json);
    switch (json->type)
    {
    case JSON_BOL:
        printf("%s\n", json->bol ? "true" : "false");
        break;
    case JSON_STR:
        assert(json->str);
        printf("%s\n", json->str);
        break;
    case JSON_INT:
        printf("%d\n", json->num);
        break;
    default:
        return;
    }
}

void print_tab(const U32 cnt)
{
    for (U32 i = 0; i < cnt * TAB_SIZE; i++)
        printf(" ");
}

int replace_ip(JSON *json)
{
    assert(json);
    static JSON *root;
    if (!root)
        root = json;
    static JSON *new_ips;
    if (!new_ips)
    {
        new_ips = json_new_arr();
        char buf[BUFF_STR_SIZE];
        FILE *file = fopen("replace_ip.txt", "r");
        while (fgets(buf, sizeof(buf), file))
        {
            int i;
            while (buf[i] != '\n')
                i++;
            buf[i] = '\0';
            //printf("%d\n",strlen(buf));
            puts(buf);
            arr_add_ele(new_ips, json_new_str(buf));
        }
        fclose(file);
    }
    switch (json->type)
    {
    case JSON_STR:
        //printf("JSON_STR\n");
        if (match_ip(json->str))
        {
            printf("matched\n");
            char *old_ip = (char *)malloc(sizeof(json->str));
            if (!old_ip)
            {
                json_del(new_ips);
                return -1;
            }
            strcpy(old_ip, json->str);
            for (U32 i = 0; i < new_ips->arr.count; i++)
            {
                char *new_ip = (char *)malloc(sizeof(new_ips->arr.elems[i]->str));
                if (!new_ip)
                {
                    json_del(new_ips);
                    free(old_ip);
                    return -1;
                }
                strcpy(new_ip, new_ips->arr.elems[i]->str);
                free(json->str);
                json->str = new_ip;
                json_save_exp(root);
            }
            free(json->str);
            json->str = old_ip;
        }
        else
        {
            printf("not match\n");
        }

        break;
    case JSON_ARR:
        for (U32 i = 0; i < json->arr.count; i++)
        {
            replace_ip(json->arr.elems[i]);
        }
        break;
    case JSON_OBJ:
        for (U32 i = 0; i < json->obj.count; i++)
        {
            //printf("%s: %s\n", json->obj.kvs[i].key, json->obj.kvs[i].val->str);
            replace_ip(json->obj.kvs[i].val);
        }
        break;
    default:
        break;
    }
    if (json == root)
    {
        json_del(root);
        json_del(new_ips);
        new_ips = NULL;
        root = NULL;
    }
    return 0;
}

bool match_ip(const char *str)
{
    int status, i;
    int cflags = REG_EXTENDED;
    regmatch_t pmatch[1];
    const U32 nmatch = 1;
    regex_t reg;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]).){3}(25[0-5]|2[0-5][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$";
    //	const char *pattern="^((25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d).){3}(25[0-5]|2[0-5]\\d|[01]?\\d?\\d)$";
    regcomp(&reg, pattern, cflags);
    status = regexec(&reg, str, nmatch, pmatch, 0);
    regfree(&reg);
    if (status == REG_NOMATCH)
        return false;
    else if (status == 0)
        return true;
}

void json_save_exp(JSON *json)
{
    assert(json);
    static int file_cnt = 0;
    char file_name[BUFF_STR_SIZE];
    sprintf(file_name, "exp%d.yaml", file_cnt++);
    json_save(json, file_name);
}