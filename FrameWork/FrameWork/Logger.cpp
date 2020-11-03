#include "stdafx.h"
#include "Logger.h"
#include "basic.h"

cLogger::cLogger()
	: m_IsConsole(true)
	,m_fp(NULL)
{	
}

cLogger::~cLogger()
{
	if(m_fp != NULL)
	{
		// 종료 시기 기입
		std::string szWrite = LocalTime(LOG_WEEK | LOG_MONTH | LOG_DAY | LOG_TIME | LOG_YEAR);
		fprintf(m_fp, "LOG FILE CLOSE %s \n", szWrite.c_str());
		
		fclose(m_fp);
	}

	if(m_IsConsole)
	{
		CloseConsole();
	}
}



void cLogger::CreateLogFile()
{
	bool IsWrite = false;
	
	if(m_fp == nullptr)
	{
		std::string szFileName = 
			LocalTime(LOG_WEEK|LOG_MONTH|LOG_DAY);

		szFileName += std::string(".txt");
		
		fopen_s(&m_fp, &szFileName[0], "r+");

		if(m_fp == NULL)
		{
			fopen_s(&m_fp, &szFileName[0], "w");
			IsWrite = true;
		}
	}

	fseek(m_fp, 0, SEEK_END);

	

	if(IsWrite)
	{
		std::string szWrite = LocalTime(LOG_WEEK | LOG_MONTH | LOG_DAY | LOG_TIME | LOG_YEAR);
		fprintf(m_fp, "LOG CREATE  %s \n", szWrite.c_str());
	}
	else
	{
		fprintf(m_fp, "\n");
		std::string szWrite = LocalTime(LOG_TIME);
		fprintf(m_fp, "LOG FILE OPEN %s \n", szWrite.c_str());
	}
	
}

void cLogger::EntryPoint(std::string FILE, int LINE, std::string FUNC)
{
	AutoTapByEntry();
	if (m_fp)
		fprintf(m_fp, "ETRYPOINT  %s:%d %s \n",FILE.c_str(),LINE,FUNC.c_str());


	if (m_IsConsole)
	{
		std::cout << "ETRYPOINT  " << FILE.c_str() << ":"
			<< LINE << " " << FUNC.c_str() << std::endl;
	}
	++m_IsEntry;
}

void cLogger::LeavePoint(std::string FILE, int LINE, std::string FUNC)
{
	--m_IsEntry;
	if (m_IsEntry < 0)
		m_IsEntry == 0;


	AutoTapByEntry();
	
	if (m_fp)
		fprintf(m_fp, "LEAVEPOINT  %s:%d %s \n", FILE.c_str(), LINE, FUNC.c_str());

	if (m_IsConsole)
	{
		std::cout << "LEAVEPOINT  " << FILE.c_str() << ":"
			<< LINE << " " << FUNC.c_str() <<std::endl;				
	}


}

void cLogger::OnConsole()
{
	if(m_IsConsole == false)
		AllocConsole();
	m_IsConsole = true;
}

void cLogger::CloseConsole()
{
	if(m_IsConsole == true)
		FreeConsole();
	
	m_IsConsole = false;
}


std::string cLogger::LocalTime(int MODE)
{
	using namespace  std;
	auto end = chrono::system_clock::now();
	time_t end_time = chrono::system_clock::to_time_t(end);

	string szTime = ctime(&end_time);


	int nPrevIndex = 0;

	vector<string> List;

	for (int i = 0; i < szTime.size(); i++)
	{
		if(szTime[i] == ' ' || szTime[i] == '\n')
		{
			string T(szTime.begin() + nPrevIndex, szTime.begin() + i);
			nPrevIndex = i;
			if (T.compare(" ") == 0) continue;
			List.push_back(T);
		}
	}

	// 요일 월 날 시간 년
	switch(MODE)
	{
	case LOG_WEEK:
		return List[0];
	case LOG_MONTH:
		return List[1];
	case LOG_DAY:
		return List[2];
	case LOG_TIME:
		return List[3];
	case LOG_YEAR:
		return List[4];
	case LOG_WEEK|LOG_MONTH|LOG_DAY :
		return string(List[0] + List[1] + List[2]);
	case LOG_WEEK | LOG_MONTH | LOG_DAY | LOG_TIME | LOG_YEAR:
		return string(List[0] + List[1] + List[2] + List[3] + List[4]);
	}

}

void cLogger::ValueLog(std::string FUNC,int LINE, char* dateType,...)
{
	AutoTapByEntry();
	int cnt = 0;
	std::string strValue;

	va_list ap;

	va_start(ap, dateType);
	
	while(dateType[cnt] != '\0')
	{
		switch(dateType[cnt])
		{
		case 'f':
			{
				double f = va_arg(ap, double);
				strValue += std::to_string(f);
			}
			break;
		case 'd':
			{
				int i = va_arg(ap, int);
				strValue += std::to_string(i);
			}
			break;
		case 'c':
			strValue += va_arg(ap, char);
			break;
		case 's':
			strValue += va_arg(ap,char*);
			break;
		}

		++cnt;
		strValue += std::string(" / ");
	}

	strValue += std::string("\n");
	va_end(ap);

	if(m_fp)
		fprintf(m_fp, "%s %d Value: %s", FUNC.c_str(),LINE, strValue.c_str());
	
	if (m_IsConsole)
		std::cout << FUNC.c_str() <<" "<<LINE<< " Value: " << strValue.c_str();
}

void cLogger::AutoTapByEntry()
{
	for(int i = 0; i <m_IsEntry; i++)
	{
		fprintf(m_fp, "\t");
		if (m_IsConsole)
			std::cout << "\t";
	}
}

void cLogger::CommentLog(std::string FUNC,std::string CommentLog)
{
	if (m_fp)
		fprintf(m_fp, "CommentMessage: %s,%s", FUNC.c_str(), CommentLog.c_str());
	if (m_IsConsole)
		std::cout << "CommentMessage: " << FUNC.c_str() << 
			"," << CommentLog.c_str() << endl;
	
	return;
}
