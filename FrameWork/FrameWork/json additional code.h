#pragma once
class json_Fuction;
class json_Pointer;


class json_Fuction
{
private:

public:
	
	static JSON_Object * object_get_object(const JSON_Object *rootobject, const char *name);

#pragma region load
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

class json_Pointer
{
private:
	~json_Pointer()
	{
		json_value_free(g_p_jsonValue);
	}
public:
	JSON_Value * g_p_jsonValue;
	JSON_Object * g_p_jsonRootObject;
	JSON_Object * g_p_jsonSubObject;
	
	json_Pointer(const char * FileDirectory)
	{
		if (!g_p_jsonValue)
		{
			g_p_jsonValue = json_parse_file(FileDirectory);
			g_p_jsonRootObject = json_value_get_object(g_p_jsonValue);
		}
	}
};