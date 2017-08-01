// ExDataStructure.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "logout.h"
#include "define_common.h"

using namespace hukusuke;

/* 100m�̏���o�^ */
void regist_athletes_sprint(list<TR_EVENTS>& list_events) {

	// �� �I��ݒ�.
	TR_ATHLETES ath_bolt;
	ath_bolt.name = "Usain Bolt";
	ath_bolt.record = "9.58";

	TR_ATHLETES ath_gatlin;
	ath_gatlin.name = "Justin Gatlin";
	ath_gatlin.record = "9.74";

	TR_ATHLETES ath_sani;
	ath_sani.name = "Sani Brown";
	ath_sani.record = "10.05";

	// �� ��ږ��ƎQ���҂�o�^
	TR_EVENTS events;
	events.name = "100m";
	events.list_athletes.push_back(ath_bolt);
	events.list_athletes.push_back(ath_gatlin);
	events.list_athletes.push_back(ath_sani);

	// �� ��ڂ֓o�^
	list_events.push_back(events);

	return;
}

/* �}���\���̏���o�^ */
void regist_athletes_marathon(list<TR_EVENTS>& list_events) {

	// �� �I��ݒ�.
	TR_ATHLETES ath_kipruto;
	ath_kipruto.name = "Kipruto";
	ath_kipruto.record = "2:02:57";

	TR_ATHLETES ath_kawauchi;
	ath_kawauchi.name = "Kawauchi";
	ath_kawauchi.record = "2:08:14";

	TR_ATHLETES ath_takaoka;
	ath_takaoka.name = "Takaoka";
	ath_takaoka.record = "2:06:16";

	// �� ��ږ��ƎQ���҂�o�^
	TR_EVENTS events;
	events.name = "42.195km";
	events.list_athletes.push_back(ath_kipruto);
	events.list_athletes.push_back(ath_kawauchi);
	events.list_athletes.push_back(ath_takaoka);

	// �� ��ڂ֓o�^
	list_events.push_back(events);

	return;
}

/* �f�[�^�ő�T�C�Y�̎Z�o */
int get_max_data_size( list<TR_EVENTS> list_events) {

	int max_size = 0;
	max_size += sizeof(list_events.size());	// ��ڐ��̃T�C�Y�����Z.
	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events) 
	{
		max_size += strlen(iter_events->name.c_str()) + 1;		// ��ږ��̃T�C�Y�����Z(NULL�I�[�܂�).
		max_size += sizeof(iter_events->list_athletes.size());	// �Q���Ґ��̃T�C�Y�����Z.
		
		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes) 
		{
			max_size += strlen(iter_athletes->name.c_str()) + 1;	// �Q���҂̖��O�̃T�C�Y�����Z(NULL�I�[�܂�).
			max_size += strlen(iter_athletes->record.c_str()) + 1;	// �L�^�̃T�C�Y�����Z(NULL�I�[�܂�).
		}
	}

	return max_size;
}

/* �������z���1�����z��֕ϊ� */
void convert_multi_to_one_dim(list<TR_EVENTS> list_events, char* binary_data ) {

	int offset = 0;
	int tr_events_size = list_events.size();
	
	// �� ��ڐ���ݒ�.
	memcpy( &binary_data[offset], &tr_events_size, sizeof(tr_events_size)); offset += sizeof(tr_events_size);
	
	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events) 
	{	
		// �� ��ږ���ݒ�.
		memcpy(&binary_data[offset], &iter_events->name[0], strlen(iter_events->name.c_str()) + 1); 
		offset += strlen(iter_events->name.c_str()) + 1;
		
		// �� �Q���Ґ���ݒ�.
		int tr_athletes_size = iter_events->list_athletes.size();
		memcpy(&binary_data[offset], &tr_athletes_size, sizeof(tr_athletes_size)); offset += sizeof(tr_athletes_size);

		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes) 
		{
			// �� �Q���҂̖��O��ݒ�.
			memcpy(&binary_data[offset], &iter_athletes->name[0], strlen(iter_athletes->name.c_str()) + 1);
			offset += strlen(iter_athletes->name.c_str()) + 1;

			// �� �Q���҂̋L�^��ݒ�.
			memcpy(&binary_data[offset], &iter_athletes->record[0], strlen(iter_athletes->record.c_str()) + 1);
			offset += strlen(iter_athletes->record.c_str()) + 1;
		}
	}
}

/* �ꎟ���z��̕\�� */
void display_one_dimensional_array(char* binary_data) {

	int offset = 0;
	int tr_events_size = 0;
	
	memcpy( &tr_events_size, &binary_data[offset], sizeof(tr_events_size));
	offset += sizeof(tr_events_size);

	for (int i = 0; i < tr_events_size; ++i) 
	{
		// �� ��ږ���\��.
		string athletes_type_name;
		athletes_type_name = &binary_data[offset];	// NULL�I�[�܂ŃR�s�[�����.
		offset += strlen(athletes_type_name.c_str()) + 1;
		LOG_OUTPUT(" [%s]", athletes_type_name.c_str());

		int tr_athletes_size =0;
		memcpy(&tr_athletes_size, &binary_data[offset], sizeof(tr_athletes_size));
		offset += sizeof(tr_athletes_size);
		for (int j = 0; j < tr_athletes_size; ++j)
		{
			// �� �Q���Җ��ƎQ���L�^��\��.
			string athletes_name;
			athletes_name = &binary_data[offset];	// NULL�I�[�܂ŃR�s�[�����.
			offset += strlen(athletes_name.c_str()) + 1;

			string athletes_record;
			athletes_record = &binary_data[offset];	// NULL�I�[�܂ŃR�s�[�����.
			offset += strlen(athletes_record.c_str()) + 1;

			LOG_OUTPUT(" + name: %16s, record: %8s", athletes_name.c_str(), athletes_record.c_str());
		}
	}
	return;
}

/* �������z���\��. */
void display_multidimensionall_array(list<TR_EVENTS> list_events) {

	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events)
	{
		// �� ��ږ���\��.
		LOG_OUTPUT(" [%s]", iter_events->name.c_str());

		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes)
		{
			// �� �Q���Җ��ƎQ���L�^��\��.
			LOG_OUTPUT(" + name: %16s, record: %8s", iter_athletes->name.c_str(), iter_athletes->record.c_str());
		}
	}
	return;
}

/* Main�֐� */
int main(void)
{
	LOG_OUTPUT("Start.");
	list<TR_EVENTS>	list_events;			// ���E����̎�ڃ��X�g.
	list_events.clear();

	regist_athletes_sprint(list_events);	// 100m�̏���o�^
	regist_athletes_marathon(list_events);  // �}���\���̏���o�^

	// �� �������z���\��.
	LOG_OUTPUT("+------Multidimensional array-----+");
	display_multidimensionall_array(list_events);
	LOG_OUTPUT("+---------------------------------+");

	// �� �������z���1�����z��֕ϊ�.
	char* binary_data;
	int max_data;
	max_data = get_max_data_size(list_events);	// �������z��̍ő吔���擾.
	
	binary_data = new char[max_data];
	memset(binary_data, 0, max_data);

	convert_multi_to_one_dim(list_events, binary_data);	// �ϊ�.

	// �� 1�����z���\��.
	LOG_OUTPUT("+------One-dimensional array------+");
	display_one_dimensional_array(binary_data);
	LOG_OUTPUT("+---------------------------------+");

	// �� �㏈��.
	if (NULL != binary_data) { delete binary_data; binary_data = NULL; }

	LOG_OUTPUT("Terminate.");
    return 0;
}

