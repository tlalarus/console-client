#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <Windows.h>
#include <conio.h>

#include "CamClient.h"

using namespace std;

mutex mtx;
CCamClient* client;

#define KEY_C 99

void OnCamFrame()
{
	while(client->IsCamRunning())
	{
		mtx.lock();

		client->OnCamFrame();
		this_thread::sleep_for(chrono::duration<int>(1));
		
		mtx.unlock();
	}
}

void OnKey()
{
	while (true)
	{
		int key = _getch();
		//cout << key << endl;

		if (key == KEY_C)
		{
			mtx.lock();
			client->StopCamera();
			mtx.unlock();
			break;
		}
	}
}

int main()
{
	client = new CCamClient();
	client->InitCamera();

	client->StartCamera();

	thread cam_thread;
	cout << "Create thread for acquisition" << endl;

	// 1) Using class member function thread  (class func, class constructor, param)
	//cam_thread = thread(&CCamClient::OnCamFrame, client);

	// 2) Using External function thread
	cam_thread = thread(OnCamFrame);

	thread key_thread = thread(OnKey);

	cam_thread.join();
	key_thread.join();

	system("pause");
	return 0;
}


