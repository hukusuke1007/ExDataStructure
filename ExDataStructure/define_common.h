#pragma once
#include <string>
#include <list>
using namespace std;

/* 参加者 */
struct TR_ATHLETES{
	string name;	// 参加名
	string record;	// 参加記録
};

/* 種目 */
struct TR_EVENTS {
	string name;						// 種目名
	list<TR_ATHLETES> list_athletes;	// 参加者のリスト.
};