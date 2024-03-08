#pragma once

#include <stdlib.h>  
#include <time.h>       
#include <vector>
#include "olcPixelGameEngine.h"
#include "Queue.h"

const int BORDER_WIDTH = 5;

using std::vector;

class Engine : public olc::PixelGameEngine
{
private:
	float fAccumulatedTime = 0.0f;
	float fTargetTime = 1.0f; //default speed of simulation (seconds).

	vector<Queue*> expressQs; //default two express and two regular queue
	vector<Queue*> normalQs;

public:
	Engine()
	{
		sAppName = "Queue-Sim";
	}

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool OnConsoleCommand(const std::string& sText) override;
};