#pragma once
#include <string>
#include <list>
using namespace std;

/* �Q���� */
struct TR_ATHLETES{
	string name;	// �Q����
	string record;	// �Q���L�^
};

/* ��� */
struct TR_EVENTS {
	string name;						// ��ږ�
	list<TR_ATHLETES> list_athletes;	// �Q���҂̃��X�g.
};