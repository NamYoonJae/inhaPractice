#pragma once

class json_Object
{
	
public:
#pragma region load
	static JSON_Object * object_get_object(const JSON_Object *rootobject, const char *name);

	static char * object_get_pChar(const JSON_Object *rootobject, const char *name);

	static const char * object_get_const_pChar(const JSON_Object *rootobject, const char *name);

	static string object_get_string(const JSON_Object *rootobject, const char *name);

	static JSON_Array  * object_get_array(const JSON_Object *rootobject, const char *name);

	static double object_get_double(const JSON_Object *rootobject, const char *name);

	static int object_get_boolean(const JSON_Object *rootobject, const char *name);

	static D3DXVECTOR3 get_D3DXVECTOR3(JSON_Object* rootObject, char* x, char* y, char* z);
#pragma load

#pragma region save

	// TODO 채워넣기
	
	
#pragma save
};

