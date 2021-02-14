#include "CamClient.h"

CCamClient::CCamClient()
{
	cout << "CCamClient::CCamClient()" << endl;

	m_bCamIsRun = false;
	m_bCamIsOpend = false;
	m_count = 0;
}

CCamClient::~CCamClient()
{
}

void CCamClient::OnCamFrame()
{
	if (!m_bCamIsRun) // pause state
		return;

	cout << "CCamClient::CCamClient()" << endl;
	
	cout << "CCamclient count= " << m_count << endl;
	m_count++;
}

void CCamClient::InitCamera()
{
	cout << "CCamClinet::InitCamera()" << endl;
	m_bCamIsOpend = true;
}

void CCamClient::StartCamera()
{
	cout << "CCamClient::StartCamera()" << endl;
	m_bCamIsRun = true;

}

void CCamClient::PauseCamera()
{
	cout << "CCamClient::PauseCamera()" << endl;
	m_bCamIsRun = false;
}

void CCamClient::StopCamera()
{
	cout << "CCamClient::StopCamera()" << endl;
	
	m_bCamIsRun = false;
}

void CCamClient::ReleaseCamera()
{
	cout << "CCamClient::ReleaseCamera()" << endl;
	m_bCamIsOpend = false;
}

bool CCamClient::IsCamRunning()
{
	return m_bCamIsRun;
}

bool CCamClient::IsCamOpened()
{
	return m_bCamIsOpend;
}

int CCamClient::GetCount()
{
	return m_count;
}
