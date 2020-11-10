#pragma once

JSON_Object * json_multi_object_get_object(const JSON_Object *object, const char *name);

char * json_multi_object_get_pChar(const JSON_Object *object, const char *name);

const char * json_multi_object_get_const_pChar(const JSON_Object *object, const char *name);

string json_multi_object_get_string(const JSON_Object *object, const char *name);

JSON_Array  * json_multi_object_get_array(const JSON_Object *object, const char *name);

double json_multi_object_get_double(const JSON_Object *object, const char *name);

int json_multi_object_get_boolean(const JSON_Object *object, const char *name);


D3DXVECTOR3 json_get_D3DXVECTOR3(JSON_Object* rootObject, char* x, char* y, char* z);
