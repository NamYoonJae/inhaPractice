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
	//vector<JSON_Value*> m_rootValue_BOSS; // �ӽ�
	//vector<JSON_Object*> m_rootObject_BOSS; // �ӽ�
	//vector<JSON_Value*> m_rootValue_stage; // �ӽ�
	//vector<JSON_Object*> m_rootObject_stage; // �ӽ�
}

jsonManager::~jsonManager()
{
	Destroy();
}

void jsonManager::Setup()
{
	// ���� UI �ӽ����ϸ� �ҷ���
	// ���� ��� json���� �Ľ��ؼ� object �����ϱ�
	m_rootValue_UI = json_parse_file("data/json/UI index.json");      // JSON ������ �о �Ľ�
	m_rootObject_UI = json_value_get_object(m_rootValue_UI);

	if (!m_rootObject_UI)
		cout << "json ���� �����..." << endl;

	m_rootValue_Setting = json_parse_file("data/json/Game Setting.json");
	m_rootObject_Setting = json_value_get_object(m_rootValue_Setting);;

	if (!m_rootObject_UI)
		cout << "json ���� �����..." << endl;
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

