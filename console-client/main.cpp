#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <Windows.h>
#include <conio.h> // should be removed.

#include "CamClient.h"

using namespace std;

mutex mtx;
CCamClient* client;


#define MODE_INTRO 0
#define MODE_ACQUI 1
#define MODE_QUIT 3

#define KEY_SP 32 // space(choose)
#define KEY_ESC 27 // esc

thread g_cam_thread;
thread g_key_thread;


// thread func
void OnCamFrame();

// display
int IntroMode();
int AcquisitionMode();
int QuitMode();


int main()
{
	// resize console window 
	system("mode con cols=80 lines=30 | title Console Client");

	int mode = MODE_INTRO;
	bool b_quit = false;
	while (true)
	{
		switch (mode)
		{
		case MODE_INTRO:
			mode = IntroMode();
			break;
		case MODE_ACQUI:
			mode = AcquisitionMode();
			break;
		case MODE_QUIT:
			b_quit = QuitMode();
			break;
		default:
			break;

		}
		
		if (b_quit)
			break;
	}
	

	//g_key_thread.join();
	g_cam_thread.join();

	printf("done.\n");
	system("pause");
	return 0;
}

int QuitMode()
{
	client->StopCamera();
	return true;
}

int AcquisitionMode()
{
	if (client == NULL)
	{
		system("cls");
		client = new CCamClient();
		client->InitCamera();
		client->StartCamera();

		// 1) Using class member function thread  (class func, class constructor, param)
		//cam_thread = thread(&CCamClient::OnCamFrame, client);

		// 2) Using External function thread
		g_cam_thread = thread(OnCamFrame);
	}
	else if (!client->IsCamOpened())
	{
		// Only constructor called status, not init
		client->InitCamera();
		client->StartCamera();

		g_cam_thread = thread(OnCamFrame);
	}
	else if (client->IsCamOpened())
	{
		// Only initialized status, not started
		if (!client->IsCamRunning())
			client->StartCamera();

		// thread is not NULL
	}

	// Wait key
	int next_mode = MODE_ACQUI;

	while (true)
	{
		int key = _getch();
		if (KEY_ESC == key)
		{
			next_mode = MODE_QUIT;
			break;
		}
	}

	return next_mode;
}

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

int IntroMode()
{
	system("cls");
	printf("\n\n\n\n");
	printf("        #####   ###   #   #      #   #  #####  #####  #   #  \n");
	printf("        #      #   #  ## ##      #   #    #    #      #   #  \n");
	printf("        #      #####  # # #       # #     #    #####  # # #  \n");
	printf("        #      #   #  #   #       # #     #    #      ## ##  \n");
	printf("        #####  #   #  #   #        #    #####  #####  #   #  \n");
	printf("\n\n");

	printf("Press SPACEBAR");

	while (true)
	{
		int key = _getch();
		if (KEY_SP == key)
		{
			system("cls");
			break;
		}
	}

	return MODE_ACQUI;
}
