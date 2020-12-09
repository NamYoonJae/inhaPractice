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
	, mp_rootValue_Setting		(nullptr)
	, mp_rootObject_Setting		(nullptr)
	//, mp_rootValue_Charactor(nullptr)
	//, mp_rootObject_Charactor(nullptr)
	//, mp_rootValue_Trophy(nullptr)
	//, mp_rootObject_Trophy(nullptr)
	//, mp_rootValue_Skill(nullptr)
	//, mp_rootObject_Skill(nullptr)*/
{
	// vector<JSON_Value*> m_rootValue_BOSS;	// 임시
	// vector<JSON_Object*> m_rootObject_BOSS;	// 임시
	// vector<JSON_Value*> m_rootValue_stage;	// 임시
	// vector<JSON_Object*> m_rootObject_stage;	// 임시
}

jsonManager::~jsonManager()
{
	//Destroy();
}

void jsonManager::Setup()
{
	// 모든 json파일 파싱해서 object 객체 생성하기

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

	// Setting
	mp_rootValue_Setting = json_parse_file("data/json/Setting.json");
	mp_rootObject_Setting = json_value_get_object(mp_rootValue_Setting);;
	if (!mp_rootObject_Setting)
		cout << "Setting json 파일 비었음..." << endl;
}

void jsonManager::Destroy()
{
	//json_value_free(mp_rootValue_Charactor);
	//json_value_free(mp_rootValue_Trophy);
	//json_value_free(mp_rootValue_Skill);

	for (size_t i = 0; i < vec_p_rootValue_BOSS.size(); i++)
		if(vec_p_rootValue_BOSS[i])
			json_value_free(vec_p_rootValue_BOSS[i]);
	
	for (size_t i = 0; i < vec_p_rootValue_stage.size(); i++)
		if (vec_p_rootValue_stage[i])
			json_value_free(vec_p_rootValue_stage[i]);
	
	json_value_free(mp_rootValue_Font);
	json_value_free(mp_rootValue_HeightMapData);
	json_value_free(mp_rootValue_ObjFile);
	json_value_free(mp_rootValue_Shader);
	json_value_free(mp_rootValue_Sound);
	json_value_free(mp_rootValue_XFile);
	json_value_free(mp_rootValue_UI);
	json_value_free(mp_rootValue_Setting);
}

JSON_Object* jsonManager::get_json_object_UI()
{
	return mp_rootObject_UI;
}

JSON_Object* jsonManager::get_json_object_Setting()
{
	return mp_rootObject_Setting;
}

