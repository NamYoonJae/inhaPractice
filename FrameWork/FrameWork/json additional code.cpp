#include "stdafx.h"

//#include "json export.h"


// ��ȯ���� ������Ʈ�� ����ų ������, name�� ������ "������Ʈ/������Ʈ/������Ʈ/...." �� �ȴ�.

//object�� rootObject�� ���� ��
JSON_Object * Temp_multi_object_get_object(const JSON_Object *object, const char *name)
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
				L_Object = json_object_get_object(object, tmp);
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

//object�� rootObject�� ���� ��
const char * json_multi_object_get_string(const JSON_Object *object, const char *name)
{
	JSON_Object * L_Object = NULL;

	int is_first = 0;
	char tmp[128] = { 0 };
	strcpy_s(tmp,128,name);
	
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
				L_Object = json_object_get_object(object, tmp);
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

//object�� rootObject�� ���� ��
JSON_Array  * json_multi_object_get_array(const JSON_Object *object, const char *name)
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
				L_Object = json_object_get_object(object, tmp);
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

//object�� rootObject�� ���� ��
double Json_multi_object_get_int(const JSON_Object *object, const char *name)
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
				L_Object = json_object_get_object(object, tmp);
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

//object�� rootObject�� ���� ��
int Json_multi_object_get_boolean(const JSON_Object *object, const char *name)
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
				L_Object = json_object_get_object(object, tmp);
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

