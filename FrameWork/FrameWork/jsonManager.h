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
	//  능력치, 스탯, 아이템 상태, 스테이지 정보 등
	JSON_Value*		mp_rootValue_Character;
	JSON_Object*	mp_rootObject_Character;

	JSON_Value*		mp_rootValue_Trophies;
	JSON_Object*	mp_rootObject_Trophies;

	JSON_Value*		mp_rootValue_Stage_B;
	JSON_Object*	mp_rootObject_Stage_B;

	// 게임 세팅을 불러오고 저장할 포인터
	JSON_Value*		mp_rootValue_Setting;
	JSON_Object*	mp_rootObject_Setting;

#pragma region File Index
	JSON_Value* mp_rootValue_Font;
	JSON_Object* mp_rootObject_Font;

	JSON_Value* mp_rootValue_HeightMapData;
	JSON_Object* mp_rootObject_HeightMapData;

	JSON_Value* mp_rootValue_ObjFile;
	JSON_Object* mp_rootObject_ObjFile;

	JSON_Value* mp_rootValue_Shader;
	JSON_Object* mp_rootObject_Shader;

	JSON_Value* mp_rootValue_Sound;
	JSON_Object* mp_rootObject_Sound;

	JSON_Value* mp_rootValue_XFile;
	JSON_Object* mp_rootObject_XFile;

	JSON_Value* mp_rootValue_UI;
	JSON_Object* mp_rootObject_UI;
#pragma endregion File Index

public:
	void Setup();
	void Destroy();

#pragma region get json object
	JSON_Object* get_json_object_UI();

	JSON_Object* get_json_object_Character();
	JSON_Object* get_json_object_Trophies();
	JSON_Object* get_json_object_Stage_B();

	JSON_Object* get_json_object_Setting();
	JSON_Value* get_json_value_Setting();

	JSON_Object* get_json_object_Sound();
#pragma endregion get json object

	void save_json_Setting();
};

