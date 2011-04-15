#pragma once

class CUpan
{
public:
	CUpan(void);
public:
	~CUpan(void);

	BOOL IsEnableDrive(char ch);
	BOOL IsRemoveDrive(char ch);

	int StopAutorun(char ch);
	int KillHide(char ch);
};
