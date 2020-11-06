#include "stdafx.h"
#include "Parser.h"

Parser::Parser()
	:SrcFile(nullptr)
{
}

Parser::~Parser()
{
}

bool Parser::FileOpen(char* Path)
{
	if (fopen_s(&SrcFile, Path, "rb") == 0)
		return true;
	else
		return false;
}

void Parser::FileClose()
{
	if (SrcFile != nullptr)
		fclose(SrcFile);
}

char* Parser::GetToken()
{
	int ReadCnt = 0;
	bool IsQuote = false;


	while(true)
	{
		char c = fgetc(SrcFile);
		if (feof(SrcFile)) break;

		if(c == '\"')
		{
			if (IsQuote) break;

			IsQuote = true;
			continue;
		}

		if(!IsQuote && IsWhite(c))
		{
			if(ReadCnt == 0) continue;

			break;
		}

		Token[ReadCnt++] = c;
	}

	if (ReadCnt == 0) return nullptr;

	Token[ReadCnt] = '\0';
	return Token;
}

int Parser::GetInteger()
{
	return atoi(GetToken());
}

float Parser::GetFloat()
{
	return static_cast<float>(atof(GetToken()));
}

bool Parser::IsWhite(char c)
{
	return c < 33;
}

bool Parser::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0;
}

void Parser::SkipBlock()
{
	int Level = 0;

	do
	{
		char* token = GetToken();

		if (IsEqual(token, "{")) Level++;
		else if (IsEqual(token, "}")) Level--;
		
	} while (Level > 0);
}
