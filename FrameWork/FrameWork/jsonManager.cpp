#include "stdafx.h"
#include "jsonManager.h"

jsonManager::jsonManager()
	: mp_rootValue_Font			(nullptr)
	, mp_rootObject_Font		(nullptr)
	, mp_rootValue_HeightMapData(nullptr)
	, mp_rootObject_HeightMapData(nullptr)
	, mp_rootValue_ObjFile		(nullptr)
	, mp_rootObject_ObjFile		(nullptr)
	, mp_rootValue_Shader		(nullptr)
	, mp_rootObject_Shader		(nullptr)
	, mp_rootValue_Sound		(nullptr)
	, mp_rootObject_Sound		(nullptr)
	, mp_rootValue_XFile		(nullptr)
	, mp_rootObject_XFile		(nullptr)
	, mp_rootValue_UI			(nullptr)
	, mp_rootObject_UI			(nullptr)

	, mp_rootValue_Character	(nullptr)
	, mp_rootObject_Character	(nullptr)
	, mp_rootValue_Trophies		(nullptr)
	, mp_rootObject_Trophies	(nullptr)
	, mp_rootValue_Stage_B		(nullptr)
	, mp_rootObject_Stage_B		(nullptr)

	, mp_rootValue_Setting		(nullptr)
	, mp_rootObject_Setting		(nullptr)
	//, mp_rootValue_Trophy(nullptr)
	//, mp_rootObject_Trophy(nullptr)
	//, mp_rootValue_Skill(nullptr)
	//, mp_rootObject_Skill(nullptr)
{

}

jsonManager::~jsonManager()
{
	//Destroy();
}

void jsonManager::Setup()
{
	// 모든 json파일 파싱해서 object 객체 생성하기

#pragma region file index
	// Font
	mp_rootValue_Font = json_parse_file("data/json/index UI.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Font = json_value_get_object(mp_rootValue_Font);
	if (!mp_rootObject_Font)
		cout << "Font json 파일 비었음..." << endl;

	// HeightMapData
	mp_rootValue_HeightMapData = json_parse_file("data/json/index HeightMapData.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_HeightMapData = json_value_get_object(mp_rootValue_HeightMapData);
	if (!mp_rootObject_HeightMapData)
		cout << "HeightMapData json 파일 비었음..." << endl;

	// ObjFile
	mp_rootValue_ObjFile = json_parse_file("data/json/index ObjFile.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_ObjFile = json_value_get_object(mp_rootValue_ObjFile);
	if (!mp_rootObject_ObjFile)
		cout << "ObjFile json 파일 비었음..." << endl;

	// Shader
	mp_rootValue_Shader = json_parse_file("data/json/index Shader.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Shader = json_value_get_object(mp_rootValue_Shader);
	if (!mp_rootObject_Shader)
		cout << "Shader json 파일 비었음..." << endl;

	// Sound
	mp_rootValue_Sound = json_parse_file("data/json/index Sound.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Sound = json_value_get_object(mp_rootValue_Sound);
	if (!mp_rootObject_Sound)
		cout << "Sound json 파일 비었음..." << endl;

	// UI
	mp_rootValue_UI = json_parse_file("data/json/index UI.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_UI = json_value_get_object(mp_rootValue_UI);
	if (!mp_rootObject_UI)
		cout << "UI json 파일 비었음..." << endl;

	// XFile
	mp_rootValue_XFile = json_parse_file("data/json/index XFile.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_XFile = json_value_get_object(mp_rootValue_XFile);
	if (!mp_rootObject_XFile)
		cout << "json 파일 비었음..." << endl;
#pragma endregion file index

	// Character
	mp_rootValue_Character = json_parse_file("data/json/Attribute Chracter.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Character = json_value_get_object(mp_rootValue_Character);
	if (!mp_rootObject_Character)
		cout << "json 파일 비었음..." << endl;

	// Trophies
	mp_rootValue_Trophies = json_parse_file("data/json/Attribute Trophies.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Trophies = json_value_get_object(mp_rootValue_Trophies);
	if (!mp_rootObject_Trophies)
		cout << "json 파일 비었음..." << endl;

	// Stage_B
	mp_rootValue_Stage_B = json_parse_file("data/json/Stage B.json");      // JSON 파일을 읽어서 파싱
	mp_rootObject_Stage_B = json_value_get_object(mp_rootValue_Stage_B);
	if (!mp_rootObject_Stage_B)
		cout << "json 파일 비었음..." << endl;

	// Setting
	mp_rootValue_Setting = json_parse_file("data/json/Setting.json");
	mp_rootObject_Setting = json_value_get_object(mp_rootValue_Setting);;
	if (!mp_rootObject_Setting)
		cout << "Setting json 파일 비었음..." << endl;

	cout << "json 파일 로드 완료" << endl;
}

void jsonManager::Destroy()
{
	//for (size_t i = 0; i < vec_p_rootValue_BOSS.size(); i++)
	//	if(vec_p_rootValue_BOSS[i])
	//		json_value_free(vec_p_rootValue_BOSS[i]);
	//
	//for (size_t i = 0; i < vec_p_rootValue_stage.size(); i++)
	//	if (vec_p_rootValue_stage[i])
	//		json_value_free(vec_p_rootValue_stage[i]);
	
	json_value_free(mp_rootValue_Font);
	json_value_free(mp_rootValue_HeightMapData);
	json_value_free(mp_rootValue_ObjFile);
	json_value_free(mp_rootValue_Shader);
	json_value_free(mp_rootValue_Sound);
	json_value_free(mp_rootValue_XFile);
	json_value_free(mp_rootValue_UI);

	json_value_free(mp_rootValue_Stage_B);
	json_value_free(mp_rootValue_Character);
	json_value_free(mp_rootValue_Trophies);
	
	json_value_free(mp_rootValue_Setting);
}



JSON_Object* jsonManager::get_json_object_UI()
{
	return mp_rootObject_UI;
}

JSON_Object* jsonManager::get_json_object_Character()
{
	return mp_rootObject_Character;
}

JSON_Object* jsonManager::get_json_object_Trophies()
{
	return mp_rootObject_Trophies;
}

JSON_Object* jsonManager::get_json_object_Stage_B()
{
	return mp_rootObject_Stage_B;
}

JSON_Object* jsonManager::get_json_object_Setting()
{
	return mp_rootObject_Setting;
}

JSON_Value* jsonManager::get_json_value_Setting()
{
	return mp_rootValue_Setting;
}

void jsonManager::save_json_Setting()
{
	json_serialize_to_file_pretty(mp_rootValue_Setting, "example.json");
}

