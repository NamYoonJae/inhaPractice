#pragma once
#include <vector>
#include <string>
#include <assert.h> //예외처리 할 때 경고문 사용하기 위해 사용
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <map>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstdarg>
#include<process.h>
#include <thread>
#include <random>
#include <iostream>
#include <conio.h>
using namespace std;

struct ST_PC_VERTEX
{
	D3DXVECTOR3  p;
	D3DCOLOR	 c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

#define MatrixIdentity D3DXMATRIXA16(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)

template <typename T>
T GenerateRandomNum(T minRange, T maxRange)
{
	srand(time(NULL));

	random_device rd;
	mt19937_64 gen(rd());
	uniform_real_distribution<> randNum(minRange, maxRange);

	return randNum(gen);
}