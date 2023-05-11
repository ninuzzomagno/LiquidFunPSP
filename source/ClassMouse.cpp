#include"Liquidi.h"

using namespace Gui;

Mouse::Mouse() {
	this->pos[0] = 240;
	this->pos[1] = 136;
	this->sensivity = 2;
	int lOp[] = { OSL_IN_VRAM | OSL_SWIZZLED,OSL_PF_8888 };
	this->texture = oslLoadImageFilePNG(const_cast<char*>("resource/texture/gui/mouse.png"), OSL_IN_VRAM || OSL_SWIZZLED, OSL_PF_8888);
}

int* Mouse::update() {
	if (osl_pad.held.right && this->pos[0]<480)
		this->pos[0] += this->sensivity;
	else if(osl_pad.held.left && this->pos[0] > 0)
		this->pos[0] -= this->sensivity;

	if (osl_pad.held.down && this->pos[1] < 272)
		this->pos[1] += this->sensivity;
	else if (osl_pad.held.up && this->pos[1]>0)
		this->pos[1] -= this->sensivity;

	return this->pos;
}

void Mouse::draw() {
	oslDrawImageXY(this->texture, this->pos[0], this->pos[1]);
}