#pragma once
#include"oslib/oslib.h"

class FrameRate {
public:
	FrameRate();
	void start();
	void end();
	void FPS(int, int);
private:
	int last;
	int fps;
	int current;
};