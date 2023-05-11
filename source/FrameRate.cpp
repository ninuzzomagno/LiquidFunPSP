#include"FrameRate.h"

FrameRate::FrameRate() {
	this->last = 0;
	this->fps = 0;
	this->current = 0;
}

void FrameRate::start() {
	oslBenchmarkTest(OSL_BENCH_START);
}

void FrameRate::end() {
	oslBenchmarkTest(OSL_BENCH_END);
	this->current = oslBenchmarkTest(OSL_BENCH_GET);
	if (this->current != this->last) {
		this->fps = 1 / (this->current - last);
	}
	else
		this->fps = 60;
	this->last = this->current;

	if (this->fps > 60)
		this->fps = 60;
	else if (this->fps < 0)
		this->fps = 0;
}

void FrameRate::FPS(int x, int y) {
	oslDrawStringf(x, y, "%i", this->fps);
}