#pragma once

class CProcessModule
{
public:
	CProcessModule(void);
public:
	~CProcessModule(void);

	static void GetModule(int Uid,CListCtrl *pList);
};
