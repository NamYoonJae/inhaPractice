#pragma once

#define g_p_jsonManager jsonManager::GetInstance()

/* 사용 구조체 목록
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

	//  능력치, 스탯, 아이템 상태등을 불러오고 저장할 포인터
	//  JSON_Value* mp_rootValue_Charactor;		// 임시
	//  JSON_Object* mp_rootObject_Charactor;	// 임시
	//
	//  JSON_Value* mp_rootValue_Trophy;	// 임시
	//  JSON_Object* mp_rootObject_Trophy;	// 임시
	//
	//  JSON_Value* mp_rootValue_Skill;		// 임시
	//  JSON_Object* mp_rootObject_Skill;	// 임시

	vector<JSON_Value*>		vec_p_rootValue_BOSS; // 임시
	vector<JSON_Object*>	vec_p_rootObject_BOSS; // 임시
	vector<JSON_Value*>		vec_p_rootValue_stage; // 임시
	vector<JSON_Object*>	vec_p_rootObject_stage; // 임시

	// 게임 세팅을 불러오고 저장할 포인터
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

