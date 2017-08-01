// ExDataStructure.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "logout.h"
#include "define_common.h"

using namespace hukusuke;

/* 100mの情報を登録 */
void regist_athletes_sprint(list<TR_EVENTS>& list_events) {

	// ■ 選手設定.
	TR_ATHLETES ath_bolt;
	ath_bolt.name = "Usain Bolt";
	ath_bolt.record = "9.58";

	TR_ATHLETES ath_gatlin;
	ath_gatlin.name = "Justin Gatlin";
	ath_gatlin.record = "9.74";

	TR_ATHLETES ath_sani;
	ath_sani.name = "Sani Brown";
	ath_sani.record = "10.05";

	// ■ 種目名と参加者を登録
	TR_EVENTS events;
	events.name = "100m";
	events.list_athletes.push_back(ath_bolt);
	events.list_athletes.push_back(ath_gatlin);
	events.list_athletes.push_back(ath_sani);

	// ■ 種目へ登録
	list_events.push_back(events);

	return;
}

/* マラソンの情報を登録 */
void regist_athletes_marathon(list<TR_EVENTS>& list_events) {

	// ■ 選手設定.
	TR_ATHLETES ath_kipruto;
	ath_kipruto.name = "Kipruto";
	ath_kipruto.record = "2:02:57";

	TR_ATHLETES ath_kawauchi;
	ath_kawauchi.name = "Kawauchi";
	ath_kawauchi.record = "2:08:14";

	TR_ATHLETES ath_takaoka;
	ath_takaoka.name = "Takaoka";
	ath_takaoka.record = "2:06:16";

	// ■ 種目名と参加者を登録
	TR_EVENTS events;
	events.name = "42.195km";
	events.list_athletes.push_back(ath_kipruto);
	events.list_athletes.push_back(ath_kawauchi);
	events.list_athletes.push_back(ath_takaoka);

	// ■ 種目へ登録
	list_events.push_back(events);

	return;
}

/* データ最大サイズの算出 */
int get_max_data_size( list<TR_EVENTS> list_events) {

	int max_size = 0;
	max_size += sizeof(list_events.size());	// 種目数のサイズを加算.
	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events) 
	{
		max_size += strlen(iter_events->name.c_str()) + 1;		// 種目名のサイズを加算(NULL終端含む).
		max_size += sizeof(iter_events->list_athletes.size());	// 参加者数のサイズを加算.
		
		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes) 
		{
			max_size += strlen(iter_athletes->name.c_str()) + 1;	// 参加者の名前のサイズを加算(NULL終端含む).
			max_size += strlen(iter_athletes->record.c_str()) + 1;	// 記録のサイズを加算(NULL終端含む).
		}
	}

	return max_size;
}

/* 多次元配列を1次元配列へ変換 */
void convert_multi_to_one_dim(list<TR_EVENTS> list_events, char* binary_data ) {

	int offset = 0;
	int tr_events_size = list_events.size();
	
	// ■ 種目数を設定.
	memcpy( &binary_data[offset], &tr_events_size, sizeof(tr_events_size)); offset += sizeof(tr_events_size);
	
	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events) 
	{	
		// ■ 種目名を設定.
		memcpy(&binary_data[offset], &iter_events->name[0], strlen(iter_events->name.c_str()) + 1); 
		offset += strlen(iter_events->name.c_str()) + 1;
		
		// ■ 参加者数を設定.
		int tr_athletes_size = iter_events->list_athletes.size();
		memcpy(&binary_data[offset], &tr_athletes_size, sizeof(tr_athletes_size)); offset += sizeof(tr_athletes_size);

		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes) 
		{
			// ■ 参加者の名前を設定.
			memcpy(&binary_data[offset], &iter_athletes->name[0], strlen(iter_athletes->name.c_str()) + 1);
			offset += strlen(iter_athletes->name.c_str()) + 1;

			// ■ 参加者の記録を設定.
			memcpy(&binary_data[offset], &iter_athletes->record[0], strlen(iter_athletes->record.c_str()) + 1);
			offset += strlen(iter_athletes->record.c_str()) + 1;
		}
	}
}

/* 一次元配列の表示 */
void display_one_dimensional_array(char* binary_data) {

	int offset = 0;
	int tr_events_size = 0;
	
	memcpy( &tr_events_size, &binary_data[offset], sizeof(tr_events_size));
	offset += sizeof(tr_events_size);

	for (int i = 0; i < tr_events_size; ++i) 
	{
		// ■ 種目名を表示.
		string athletes_type_name;
		athletes_type_name = &binary_data[offset];	// NULL終端までコピーされる.
		offset += strlen(athletes_type_name.c_str()) + 1;
		LOG_OUTPUT(" [%s]", athletes_type_name.c_str());

		int tr_athletes_size =0;
		memcpy(&tr_athletes_size, &binary_data[offset], sizeof(tr_athletes_size));
		offset += sizeof(tr_athletes_size);
		for (int j = 0; j < tr_athletes_size; ++j)
		{
			// ■ 参加者名と参加記録を表示.
			string athletes_name;
			athletes_name = &binary_data[offset];	// NULL終端までコピーされる.
			offset += strlen(athletes_name.c_str()) + 1;

			string athletes_record;
			athletes_record = &binary_data[offset];	// NULL終端までコピーされる.
			offset += strlen(athletes_record.c_str()) + 1;

			LOG_OUTPUT(" + name: %16s, record: %8s", athletes_name.c_str(), athletes_record.c_str());
		}
	}
	return;
}

/* 多次元配列を表示. */
void display_multidimensionall_array(list<TR_EVENTS> list_events) {

	for (list<TR_EVENTS>::iterator iter_events = list_events.begin(); iter_events != list_events.end(); ++iter_events)
	{
		// ■ 種目名を表示.
		LOG_OUTPUT(" [%s]", iter_events->name.c_str());

		for (list<TR_ATHLETES>::iterator iter_athletes = iter_events->list_athletes.begin(); iter_athletes != iter_events->list_athletes.end(); ++iter_athletes)
		{
			// ■ 参加者名と参加記録を表示.
			LOG_OUTPUT(" + name: %16s, record: %8s", iter_athletes->name.c_str(), iter_athletes->record.c_str());
		}
	}
	return;
}

/* Main関数 */
int main(void)
{
	LOG_OUTPUT("Start.");
	list<TR_EVENTS>	list_events;			// 世界陸上の種目リスト.
	list_events.clear();

	regist_athletes_sprint(list_events);	// 100mの情報を登録
	regist_athletes_marathon(list_events);  // マラソンの情報を登録

	// ■ 多次元配列を表示.
	LOG_OUTPUT("+------Multidimensional array-----+");
	display_multidimensionall_array(list_events);
	LOG_OUTPUT("+---------------------------------+");

	// ■ 多次元配列を1次元配列へ変換.
	char* binary_data;
	int max_data;
	max_data = get_max_data_size(list_events);	// 多次元配列の最大数を取得.
	
	binary_data = new char[max_data];
	memset(binary_data, 0, max_data);

	convert_multi_to_one_dim(list_events, binary_data);	// 変換.

	// ■ 1次元配列を表示.
	LOG_OUTPUT("+------One-dimensional array------+");
	display_one_dimensional_array(binary_data);
	LOG_OUTPUT("+---------------------------------+");

	// ■ 後処理.
	if (NULL != binary_data) { delete binary_data; binary_data = NULL; }

	LOG_OUTPUT("Terminate.");
    return 0;
}

