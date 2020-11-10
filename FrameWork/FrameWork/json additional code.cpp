#include "stdafx.h"

//#include "json export.h"

//object에 rootObject를 넣을 것
JSON_Object * json_Object::object_get_object(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}


	return L_Object;
}

char * json_Object::object_get_pChar(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("json rootobject name : %s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	printf("json rootobject name : %s\n", tmp);
	printf("return char %s\n", json_object_get_string(L_Object, tmp));
	
	return const_cast<char*>(json_object_get_string(L_Object, tmp));
	//return (char*)json_object_get_string(L_Object, tmp); // 가능하지만, 안쓰는걸 권장함
}

const char * json_Object::object_get_const_pChar(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp,128,name);
	
	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	return json_object_get_string(L_Object, tmp);
}

string json_Object::object_get_string(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	return json_object_get_string(L_Object, tmp);
}

JSON_Array  * json_Object::object_get_array(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	return json_object_get_array(L_Object, tmp);
}

//int형 등 다른 형식이 필요하다면 캐스팅해주십쇼
double json_Object::object_get_double(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	// example) "weapon/sword/short_sword/shit_short_sword/";
	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	return json_object_get_number(L_Object, tmp);
}

int json_Object::object_get_boolean(const JSON_Object *rootobject, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp, 128, name);

	for (size_t i = 0, ii = 0; i < strlen(name); i++)
	{
		if ('/' == name[i])
		{
			char L_tmp[128] = { 0 };
			strcpy_s(L_tmp, 128, tmp);
			tmp[i - ii] = '\0';

			if (!is_first)
			{
				L_Object = json_object_get_object(rootobject, tmp);
				is_first++;
			}
			else L_Object = json_object_get_object(L_Object, tmp);
			printf("%s\n", tmp);
			strcpy_s(tmp, 128, &L_tmp[i - ii + 1]);
			ii = i + 1;
		}
	}

	return json_object_get_boolean(L_Object, tmp);
}

D3DXVECTOR3 json_Object::get_D3DXVECTOR3(JSON_Object* rootObject, char* x, char* y, char* z)
{
	return D3DXVECTOR3
	(
		object_get_double(rootObject, x),
		object_get_double(rootObject, y),
		object_get_double(rootObject, z)
	);
}