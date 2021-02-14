#ifndef CAMCLIENT_CONSOLE_CAMCLIENT_H_
#define CAMCLIENT_CONSOLE_CAMCLIENT_H_


#include <stdio.h>
#include <iostream>

using namespace std;

class CCamClient
{
public:
	CCamClient();
	~CCamClient();

	// Be static?
	void OnCamFrame();

	void InitCamera();
	void StartCamera();
	void PauseCamera();
	void StopCamera();
	void ReleaseCamera();


	bool IsCamRunning();
	bool IsCamOpened();
	int GetCount();
	

private:
	bool m_bCamIsRun;
	bool m_bCamIsOpend;
	int m_count;
};

#endif //CAMCLIENT_CONSOLE_CAMCLIENT_H_