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


#define MODE_MAIN 0
#define MODE_MENU 1
#define MODE_LOG  2
#define MODE_QUIT 3

#define KEY_W_UP 119
#define KEY_S_DW 115

#define KEY_SP 32 // space(choose)
#define KEY_ESC 27 // esc


//#define KEY_Q 113 // Cam stop
//#define KEY_I 105 // Show current cam param summary
//#define KEY_S 115 // Save current cam param as XML.
//#define KEY_D 100 // Set to default cam param.
//#define KEY_H 104 // Show command key information.

thread g_cam_thread;
thread g_key_thread;


// thread func
void OnCamFrame();
void OnKey(int curmode);

// choose key
void GoToXY(int x, int y);

// display
int DispMain();
int DispMenuMode();
int DispLogMode();

int main()
{

	// resize console window 
	system("mode con cols=80 lines=30 | title Console Client");

	int mode = MODE_MAIN;
	bool b_quit = false;
	while (true)
	{
		switch (mode)
		{
		case MODE_MAIN:
			mode = DispMain();
			break;
		case MODE_LOG:
			mode = DispLogMode();
			break;
		case MODE_MENU:
			mode = DispMenuMode();
			break;
		case MODE_QUIT:
			b_quit = true;
			break;
		default:
			break;

		}
		
		if (b_quit)
			break;
	}
	
	

	// key event on logmode.
	g_key_thread = thread(OnKey, MODE_LOG);

	g_cam_thread.join();
	g_key_thread.join();

	system("pause");
	return 0;
}


int DispLogMode()
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

	while (true)
	{
		int key = _getch();
		if (KEY_ESC == key)
		{
			
			return MODE_MENU;
		}
	}

	return 100;
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

void OnKey(int curmode)
{
	// On camera running(log mode)

	while (true)
	{
		int key = _getch();
		//cout << key << endl;

		if (curmode == MODE_MAIN)
		{
			if (KEY_SP == key)
			{
				DispLogMode();
			}
		}
		else if (curmode == MODE_LOG)
		{
			if (KEY_ESC == key)
			{
				// go to menu mode
				client->PauseCamera();
				DispMenuMode();
			}
		}
		else if (curmode == MODE_MENU)
		{
			if (KEY_ESC == key)
			{
				// go to log mode
				client->StartCamera();
				DispLogMode();
			}
		}
		

	}
}

void GoToXY(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int DispMenuMode()
{
	int x = 2;
	int y = 1;

	system("cls");

	GoToXY(x,y);
	printf("> Save capture image (.bmp)");
	GoToXY(x-2, y+1);
	printf("Stop camera");
	GoToXY(x-2, y+2);
	printf("Display current setting summary");
	GoToXY(x-2, y+3);
	printf("Control exposure");
	GoToXY(x-2, y+4);
	printf("Control gain");
	GoToXY(x-2, y+5);
	printf("Set to default setting");

	while (true)
	{
		int key = _getch();
		
		if (KEY_W_UP == key)
		{
			if (y > 1)
				GoToXY(x - 2, y);
			{
				printf(" ");
				GoToXY(x - 2, --y);
				printf(">");
			}
		}
		else if (KEY_S_DW == key)
		{
			if (y < 6)
			{
				GoToXY(x - 2, y);
				printf(" ");
				GoToXY(x - 2, ++y);
				printf(">");
			}
		}
		else if (KEY_SP == key)
		{
			return y - 1; // 0=capture, 1=setting summary
		}

	}


}

int DispMain()
{
	system("cls");
	printf("\n\n\n\n");
	printf("        #####   ###   #   #      #   #  #####  #####  #   #  \n");
	printf("        #      #   #  ## ##      #   #    #    #      #   #  \n");
	printf("        #      #####  # # #       # #     #    #####  # # #  \n");
	printf("        #      #   #  #   #       # #     #    #      ## ##  \n");
	printf("        #####  #   #  #   #        #    #####  #####  #   #  \n");
	printf("\n\n");

	printf("> start");

	while (true)
	{
		int key = _getch();
		if (KEY_SP == key)
		{
			system("cls");
			break;
		}
	}

	return MODE_LOG;
}




