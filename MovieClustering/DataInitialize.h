#ifndef DATAINITIALIZE_H
#define DATAINITIALIZE_H
/************************************************************************/
/* K������                                                                     */
/************************************************************************/
#define  K 10
/************************************************************************/
/*  943�������۵ĵ�Ӱ                                                                     */
/************************************************************************/
#define USER_NUMBER 943
#include "Movie.h"
class Data
{
public:
	Data();
	/************************************************************************/
	/* ��ʼ��K������                                                                     */
	/************************************************************************/
	void initKCenters();
	/************************************************************************/
	/* ��ʼ����Ӱ�����ݣ����꣩                                                                     */
	/************************************************************************/
	void initUsers();

	/**
	K������
	*/
	int KCenters[K][MOVIE_NUMBER];
	/************************************************************************/
	/*3706����Ӱ                                                                     */
	/************************************************************************/
	User users[USER_NUMBER];

};
#endif