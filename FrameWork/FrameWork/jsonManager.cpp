#include "stdafx.h"
#include "jsonManager.h"

jsonManager::jsonManager()
	: m_rootValue_Charactor(nullptr)
	, m_rootObject_Charactor(nullptr)
	, m_rootValue_Trophy(nullptr)
	, m_rootObject_Trophy(nullptr)
	, m_rootValue_Skill(nullptr)
	, m_rootObject_Skill(nullptr)
	, m_rootValue_UI(nullptr)
	, m_rootObject_UI(nullptr)
	, m_rootValue_Setting(nullptr)
	, m_rootObject_Setting(nullptr)
{
	//vector<JSON_Value*> m_rootValue_BOSS; // 임시
	//vector<JSON_Object*> m_rootObject_BOSS; // 임시
	//vector<JSON_Value*> m_rootValue_stage; // 임시
	//vector<JSON_Object*> m_rootObject_stage; // 임시
}

jsonManager::~jsonManager()
{
	Destroy();
}

void jsonManager::Setup()
{
	// 현재 UI 임시파일만 불러옴
	// 이후 모든 json파일 파싱해서 object 생성하기
	m_rootValue_UI = json_parse_file("data/json/UI index.json");      // JSON 파일을 읽어서 파싱
	m_rootObject_UI = json_value_get_object(m_rootValue_UI);

	if (!m_rootObject_UI)
		cout << "json 파일 비었음..." << endl;

	m_rootValue_Setting = json_parse_file("data/json/Game Setting.json");
	m_rootObject_Setting = json_value_get_object(m_rootValue_Setting);;

	if (!m_rootObject_UI)
		cout << "json 파일 비었음..." << endl;
}

void jsonManager::Destroy()
{
	json_value_free(m_rootValue_Charactor);
	json_value_free(m_rootValue_Trophy);
	json_value_free(m_rootValue_Skill);

	for (size_t i = 0; i < m_rootValue_BOSS.size(); i++)
		if(m_rootValue_BOSS[i])
			json_value_free(m_rootValue_BOSS[i]);
	
	for (size_t i = 0; i < m_rootValue_stage.size(); i++)
		if (m_rootValue_stage[i])
			json_value_free(m_rootValue_stage[i]);
	
	json_value_free(m_rootValue_UI);
	json_value_free(m_rootValue_Setting);
}

JSON_Object* jsonManager::get_json_object_UI()
{
	return m_rootObject_UI;
}

JSON_Object* jsonManager::get_json_object_Setting()
{
	return m_rootObject_Setting;
}

