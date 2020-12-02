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
	JSON_Value* m_rootValue_Charactor; // 임시
	JSON_Object* m_rootObject_Charactor; // 임시
	
	JSON_Value* m_rootValue_Trophy; // 임시
	JSON_Object* m_rootObject_Trophy; // 임시
	
	JSON_Value* m_rootValue_Skill; // 임시
	JSON_Object* m_rootObject_Skill; // 임시

	vector<JSON_Value*> m_rootValue_BOSS; // 임시
	vector<JSON_Object*> m_rootObject_BOSS; // 임시
	vector<JSON_Value*> m_rootValue_stage; // 임시
	vector<JSON_Object*> m_rootObject_stage; // 임시

	
	JSON_Value* m_rootValue_UI;
	JSON_Object* m_rootObject_UI;

public:
	void Setup();
	void Destroy();

	JSON_Object* get_json_object_UI();
};

