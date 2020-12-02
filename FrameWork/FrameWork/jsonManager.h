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
	JSON_Value* m_rootValue_Charactor; // �ӽ�
	JSON_Object* m_rootObject_Charactor; // �ӽ�
	
	JSON_Value* m_rootValue_Trophy; // �ӽ�
	JSON_Object* m_rootObject_Trophy; // �ӽ�
	
	JSON_Value* m_rootValue_Skill; // �ӽ�
	JSON_Object* m_rootObject_Skill; // �ӽ�

	vector<JSON_Value*> m_rootValue_BOSS; // �ӽ�
	vector<JSON_Object*> m_rootObject_BOSS; // �ӽ�
	vector<JSON_Value*> m_rootValue_stage; // �ӽ�
	vector<JSON_Object*> m_rootObject_stage; // �ӽ�

	
	JSON_Value* m_rootValue_UI;
	JSON_Object* m_rootObject_UI;

public:
	void Setup();
	void Destroy();

	JSON_Object* get_json_object_UI();
};

