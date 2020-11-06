#pragma once

class Parser
{
private:
	FILE* SrcFile;
	char Token[1024];

public:
	Parser();
	~Parser();
	bool FileOpen(char* Path);
	void FileClose();
	char* GetToken();
	int GetInteger();
	float GetFloat();
	bool IsWhite(IN char c);
	bool IsEqual(IN char* str1, IN char* str2);
	void SkipBlock();
};

