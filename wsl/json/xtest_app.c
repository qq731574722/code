#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <errno.h>
#include "json.h"
#include "xtest.h"

TEST(test, json_new)
{
	JSON *json = json_new_str("Hello world");
	EXPECT_STREQ("Hello world", json->str);
	json_del(json);

	json = json_new_int(100);
	EXPECT_EQ(100, json->num);
	json_del(json);

	json = json_new_bol(true);
	EXPECT_EQ(true, json->bol);
	json_del(json);

	json = json_new_arr();
	EXPECT_EQ(0, json->arr.count);
	json->arr.elems[0] = json_new_int(100);
	json->arr.count++;
	EXPECT_EQ(100, json_get_index(json, 0)->num);
	EXPECT_EQ(NULL, json_get_index(json, 1));
	JSON *father = json_new_obj();
	json_new_val(json);
	json_add_kv(father, "arr", json);
	json_del(json);

	json = json_new_obj();
	json_add_kv(json, "str", json_new_str("str"));
	EXPECT_STREQ("str", json_get_str(json, "str", ""));
	json_add_kv(father, "obj", json);
	json_del(json);
	json_del(father);

	json_del(json);
}

TEST(test, json_add)
{
	JSON *json = json_new_obj();
	json_add_kv(json, "add_kv", json_new_str("YES"));
	EXPECT_STREQ("YES", json_get_str(json, "add_kv", "NO"));
	EXPECT_STREQ("YES", json_get_str(json, "add_kv", ""));
	EXPECT_STREQ("YES", json_get_str(json, "add_kv", NULL));
	EXPECT_EQ(false, json_add_kv(json, "add_kv", json_new_str("YES")));

	json_add_kv(json, "add_kv_int", json_new_int(100));
	EXPECT_EQ(100, json_get_int(json, "add_kv_int", -1));

	json_add_kv(json, "add_kv_bol", json_new_bol(true));
	EXPECT_EQ(true, json_get_bool(json, "add_kv_bol"));

	json_add_kv(json, "1", json_new_int(1));
	json_add_kv(json, "2", json_new_int(2));
	json_add_kv(json, "3", json_new_int(3));
	json_add_kv(json, "4", json_new_int(4));
	json_add_kv(json, "5", json_new_int(5));

	EXPECT_STREQ("true", json_get_str(json, "add_kv_bol", NULL));
	EXPECT_STREQ("100", json_get_str(json, "add_kv_int", NULL));
	EXPECT_EQ(5, json_get_int(json, "5", -1));

	json_del(json);
}

TEST(test, json_get)
{
	JSON *json = json_new_obj();
	JSON *non = json_new(JSON_NONE);
	EXPECT_EQ(NULL, json_new_val(non));
	EXPECT_EQ(false, json_get_bool(non, "bol"));
	EXPECT_EQ(NULL, json_get_value(non, "val"));
	EXPECT_EQ(NULL, json_get_index(non, 0));
	EXPECT_EQ(-1, json_get_int(non, "int", -1));
	EXPECT_EQ(false, json_add_kv(json, "", json_new_int(1)));
	EXPECT_NE(NULL, json);
	EXPECT_STREQ("World", json_get_str(json, "Hello", "World"));
	EXPECT_EQ(0, json->obj.count);
	EXPECT_NE(NULL, json->obj.kvs);

	//json_get_int

	int cnt = json->obj.count;
	json->obj.kvs[cnt].key = (char *)malloc((strlen("INT_TEST") + 1) * sizeof(char));
	strcpy(json->obj.kvs[cnt].key, "INT_TEST");
	json->obj.kvs[cnt].val = json_new_int(100);
	cnt = ++json->obj.count;
	EXPECT_EQ(100, json_get_int(json, "INT_TEST", -1));
	//json_get_bool
	json->obj.kvs[cnt].key = (char *)malloc((strlen("BOOL_TEST") + 1) * sizeof(char));
	strcpy(json->obj.kvs[cnt].key, "BOOL_TEST");
	value *_val = json_new_bol(true);
	EXPECT_NE(NULL, _val);
	EXPECT_EQ(NULL, json->obj.kvs[cnt].val);
	json->obj.kvs[cnt].val = json_new_bol(true);
	cnt = ++json->obj.count;
	EXPECT_EQ(true, json_get_bool(json, "BOOL_TEST"));
	json_del(json);
}

TEST(arr, add)
{
	JSON *json = json_new_obj();
	JSON *arr = json_new_arr();
	EXPECT_EQ(true, arr_add_ele(arr, json_new_str("ele1")));
	EXPECT_EQ(true, arr_add_ele(arr, json_new_int(2)));
	EXPECT_EQ(true, arr_add_ele(arr, json_new_bol(true)));
	arr_add_ele(arr, json_new_int(4));
	arr_add_ele(arr, json_new_int(5));
	arr_add_ele(arr, json_new_int(6));

	json_add_kv(json, "arr", json_new_val(arr));
	EXPECT_STREQ("ele1", json_get_index(arr, 0)->str);
	EXPECT_EQ(2, json_get_index(arr, 1)->num);
	EXPECT_EQ(true, json_get_index(arr, 2)->bol);
	EXPECT_EQ(6, json_get_index(arr, 5)->num);

	json_del(json);
}

TEST(test, json_set)
{
	JSON *json = json_new_obj();
	json_add_kv(json, "int", json_new_str("hello"));
	json_set_int(json, "int", 2);
	EXPECT_EQ(2, json_get_int(json, "int", -1));
	EXPECT_EQ(false, json_set_int(json, "", -1));
	json_set_bool(json, "bool", true);
	EXPECT_EQ(true, json_get_bool(json, "bool"));
	EXPECT_EQ(false, json_set_bool(json, "", true));
	json_set_str(json, "str", "str");
	EXPECT_STREQ("str", json_get_str(json, "str", ""));
	EXPECT_EQ(false, json_set_str(json, "", "str"));
	json_set_str(json, "str", "another str");
	EXPECT_STREQ("another str", json_get_str(json, "str", ""));
	json_del(json);
	json = json_new(JSON_STR);
	json_set_kv(json, "key", json_new_str("val"));
	json_del(json);
}

/*
"house:\n"
"  family:\n"
"    name: Doe\n"
"    parents:\n"
"      - John\n"
"      - Jane\n"
"    children:\n"
"      - Paul\n"
"      - Mark\n"
"      - Simone\n"
"  address:\n"
"    number: 34\n"
"    street: Main Street\n"
"    city: Nowheretown\n"
"    zipcode: 12345\n";
*/
TEST(test, json_save)
{
	json_save(json_new_str("Hello world"), "test.yaml");
	JSON *root = json_new_obj();
	JSON *house = json_new_obj();
	JSON *family = json_new_obj();
	json_add_kv(family, "name", json_new_str("Doe"));
	JSON *parents = json_new_arr();
	arr_add_ele(parents, json_new_str("John"));
	EXPECT_EQ(true, arr_add_ele(parents, json_new_str("Jane")));
	json_add_kv(family, "parents", parents);
	EXPECT_STREQ("John", json_get_index(parents, 0)->str);

	JSON *children = json_new_arr();
	arr_add_ele(children, json_new_str("Pual"));
	arr_add_ele(children, json_new_str("Mark"));
	arr_add_ele(children, json_new_str("Simone"));
	EXPECT_EQ(true, arr_add_ele(parents, children));
	json_add_kv(family, "children", children);

	JSON *address = json_new_obj();
	json_add_kv(address, "number", json_new_int(34));
	json_add_kv(address, "street", json_new_str("Main Street"));
	json_add_kv(address, "city", json_new_str("Nowheretow"));
	json_add_kv(address, "zipcode", json_new_int(12345));
	json_add_kv(address, "reality", json_new_bol("true"));

	EXPECT_EQ(true, json_add_kv(house, "family", family));
	json_add_kv(house, "address", address);
	json_add_kv(root, "house", house);

	EXPECT_EQ(0, json_save(root, "test.yaml"));

	json_del(root);
}

// "ldap":{
// 	"basic":{
// 		"ip":"200.200.3.61",
// 		"port":389,
// 		"timeout":10,
// 		"basedn":"/dns/www"
// 	}
// }
TEST(replace_ip, str)
{
	JSON *root = json_new_obj();
	JSON *ldap = json_new_obj();
	JSON *basic = json_new_obj();
	json_add_kv(basic,"ip",json_new_str("200.200.3.61"));
	json_add_kv(basic,"port",json_new_int(389));
	json_add_kv(basic,"ip_2",json_new_str("256.0.0.1"));
	json_add_kv(ldap,"basic",basic);
	JSON *basedn = json_new_arr();
	arr_add_ele(basedn,json_new_str("200.200.3.61"));
	arr_add_ele(basedn,json_new_str("256.0.0.1"));
	json_add_kv(ldap,"arr",basedn);
	json_add_kv(root,"ladap",ldap);
	replace_ip(root);
	//EXPECT_EQ(true,match_ip("113.87.161.146"));
	json_del(root);
}

int main(int argc, char **argv)
{
	return xtest_start_test(argc, argv);
}
