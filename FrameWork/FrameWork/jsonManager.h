#pragma once

#define g_p_jsonManager jsonManager::GetInstance()

/* ��� ����ü ���
typedef struct json_object_t JSON_Object;
typedef struct json_array_t  JSON_Array;
typedef struct json_value_t  JSON_Value;
 */

class jsonManager
{
	Singletone(jsonManager);
private:
#pragma region File Index
	JSON_Value*		mp_rootValue_Font;
	JSON_Object*	mp_rootObject_Font;

	JSON_Value*		mp_rootValue_HeightMapData;
	JSON_Object*	mp_rootObject_HeightMapData;
	
	JSON_Value*		mp_rootValue_ObjFile;
	JSON_Object*	mp_rootObject_ObjFile;

	JSON_Value*		mp_rootValue_Shader;
	JSON_Object*	mp_rootObject_Shader;
	
	JSON_Value*		mp_rootValue_Sound;
	JSON_Object*	mp_rootObject_Sound;

	JSON_Value*		mp_rootValue_XFile;
	JSON_Object*	mp_rootObject_XFile;

	JSON_Value*		mp_rootValue_UI;
	JSON_Object*	mp_rootObject_UI;
#pragma endregion File Index

	//  �ɷ�ġ, ����, ������ ���µ��� �ҷ����� ������ ������
	//  JSON_Value* mp_rootValue_Charactor;		// �ӽ�
	//  JSON_Object* mp_rootObject_Charactor;	// �ӽ�
	//
	//  JSON_Value* mp_rootValue_Trophy;	// �ӽ�
	//  JSON_Object* mp_rootObject_Trophy;	// �ӽ�
	//
	//  JSON_Value* mp_rootValue_Skill;		// �ӽ�
	//  JSON_Object* mp_rootObject_Skill;	// �ӽ�

	vector<JSON_Value*>		vec_p_rootValue_BOSS; // �ӽ�
	vector<JSON_Object*>	vec_p_rootObject_BOSS; // �ӽ�
	vector<JSON_Value*>		vec_p_rootValue_stage; // �ӽ�
	vector<JSON_Object*>	vec_p_rootObject_stage; // �ӽ�

	// ���� ������ �ҷ����� ������ ������
	JSON_Value*		mp_rootValue_Setting;
	JSON_Object*	mp_rootObject_Setting;

public:
	void Setup();
	void Destroy();

	JSON_Object* get_json_object_UI();
	JSON_Object* get_json_object_Setting();

	// void save_json_UI();
	// void save_json_Setting();
};

