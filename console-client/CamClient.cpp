#include "CamClient.h"

CCamClient::CCamClient()
{
	cout << "CCamClient::CCamClient()" << endl;

	m_bCamIsRun = false;
	m_count = 0;
}

CCamClient::~CCamClient()
{
}

void CCamClient::OnCamFrame()
{
	cout << "CCamClient::CCamClient()" << endl;
	
	cout << "CCamclient count= " << m_count << endl;
	m_count++;
}

void CCamClient::InitCamera()
{
	cout << "CCamClinet::InitCamera()" << endl;
	
}

void CCamClient::StartCamera()
{
	cout << "CCamClient::StartCamera()" << endl;
	m_bCamIsRun = true;
}

void CCamClient::StopCamera()
{
	cout << "CCamClient::StopCamera()" << endl;
	m_bCamIsRun = false;
}

void CCamClient::ReleaseCamera()
{
	cout << "CCamClient::ReleaseCamera()" << endl;
}

bool CCamClient::IsCamRunning()
{
	return m_bCamIsRun;
}

int CCamClient::GetCount()
{
	return m_count;
}
