#pragma once
#include "stdafx.h"
#include "basic.h"



#pragma warning(disable: 4996)
#define  g_pLogger cLogger::GetInstance()
#define  LoggerEntry cLogger::GetInstance()->EntryPoint(__FILE__,__LINE__,__FUNCTION__)
#define  LoggerLeave cLogger::GetInstance()->LeavePoint(__FILE__,__LINE__,__FUNCTION__)

class cLogger
{
public:
	Singletone(cLogger)

	enum {LOG_WEEK = 0x01,LOG_MONTH = 0x02,LOG_DAY = 0x04,LOG_TIME = 0x08,LOG_YEAR = 0x10};
private:
	FILE *m_fp;
	bool m_IsConsole;
	int  m_IsEntry;
public:
	void CreateLogFile();
	void EntryPoint(std::string FILE,int LINE,std::string FUNC);
	void LeavePoint(std::string FILE, int LINE, std::string FUNC);
	void OnConsole();
	void CloseConsole();
	std::string LocalTime(int MODE);
	
	void ValueLog(std::string FUNC,int LINE,char* dateType,...);
	void AutoTapByEntry();
	void CommentLog(std::string FUNC, std::string CommentLog);
};

//
// 생성  옵션( 콘솔열기 닫기)
// 생성 시기

// 로그 남기기  탬플릿
// 진입점
// 
