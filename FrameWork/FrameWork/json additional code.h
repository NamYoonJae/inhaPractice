#pragma once

JSON_Object * json_multi_object_get_object(const JSON_Object *object, const char *name);

double json_multi_object_get_int(const JSON_Object *object, const char *name);

const char * json_multi_object_get_string(const JSON_Object *object, const char *name);

JSON_Array  * json_multi_object_get_array(const JSON_Object *object, const char *name);
