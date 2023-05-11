#pragma once

#include"liquidfun/Box2D/Box2D.h"
#include"oslib/oslib.h"
#include"FrameRate.h"
#include<string>
#include"math.h"

#define SCALE_FACTOR 50.f

#define RADIUS 4.f

#define MAX_BOX 10

namespace Gui {

	class Widget {
	public:
		virtual void update(int*) {};
		virtual void draw() {};
		virtual void setPosition(b2Vec2 p) {};
		/*inline void focus(bool f, bool s) { this->focused = f; this->selected = s; };
	protected:
		bool focused, selected;*/
	};

	class Mouse : public Widget {
	public:
		Mouse();
		int* update();
		void draw();
	private:
		OSL_IMAGE* texture;
		int pos[2], sensivity;
	};

}

struct ListBox {
	b2Body** b;
	int max;
	OSL_IMAGE* tex;
};

int updateWorld(SceSize, void*);

class App {
public:
	App();
	void run();
private:
	void addBox(int*,int);
	void deleteLastBox();
	void drawBox();

	void addFluid(int*);
	void addParticleGroup(int*);
	void drawFluid();
	void deleteFluid();

	void addWalls();
	void drawWalls();

	void startDrawing();
	void endDrawing();
	b2Body** walls;
	ListBox box;
	FrameRate fps;
	b2World* world;

	b2ParticleSystem* ps;

	OSL_IMAGE* pTex;
	OSL_IMAGE* command;

};

