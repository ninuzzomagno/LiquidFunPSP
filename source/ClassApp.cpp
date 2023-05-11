#include"Liquidi.h"

App::App() {
	//init oslib
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslSetFramerate(60);
	oslSetBkColor(RGBA(0, 0, 0, 0));
	oslBenchmarkTest(OSL_BENCH_INIT);

	oslShowSplashScreen(1);

	this->command = oslLoadImageFilePNG(const_cast<char*>("resource/texture/command.png"), OSL_IN_RAM || OSL_SWIZZLED, OSL_PF_8888);
	this->pTex = oslLoadImageFilePNG(const_cast<char*>("resource/texture/p0.png"), OSL_IN_VRAM || OSL_SWIZZLED, OSL_PF_8888);
	this->pTex->centerX = RADIUS;
	this->pTex->centerY = RADIUS;
	//Set world
	this->world = new b2World(b2Vec2(0.f, 9.8f));

	this->box.b = new b2Body* [MAX_BOX];
	this->box.max = 0;
	this->box.tex = oslLoadImageFilePNG(const_cast<char*>("resource/texture/box.png"), OSL_IN_VRAM || OSL_SWIZZLED, OSL_PF_8888);
	this->box.tex->centerX = 10;
	this->box.tex->centerY = 10;

	// SET PARTICLE SYSTEMS

	b2ParticleSystemDef psDef;
	psDef.density = 1.f;
	psDef.destroyByAge = false;
	psDef.radius = RADIUS/SCALE_FACTOR;
	
	this->ps = this->world->CreateParticleSystem(&psDef);
}

void App::startDrawing() {
	this->fps.start();
	oslStartDrawing();
	oslClearScreen(0);
	oslReadKeys();
}

void App::endDrawing() {
	this->fps.end();
	this->fps.FPS(460, 0);
	oslEndDrawing();
	oslEndFrame();
	oslSyncFrameEx(1, 8, 1);
}

void App::addWalls() {
	this->walls = new b2Body * [3];

	b2BodyDef bDef;
	b2PolygonShape shape;
	b2FixtureDef fDef;

	bDef.type = b2_staticBody;
	fDef.density = 1.f;

	//LEFT WALL
	
	bDef.position.Set(5.f / SCALE_FACTOR, 136.f / SCALE_FACTOR);

	shape.SetAsBox(5.f / SCALE_FACTOR, 136.f / SCALE_FACTOR);

	fDef.shape = &shape;

	this->walls[0] = this->world->CreateBody(&bDef);
	this->walls[0]->CreateFixture(&fDef);

	//RIGHT WALL

	bDef.position.Set(475.f / SCALE_FACTOR, 136.f / SCALE_FACTOR);

	shape.SetAsBox(5.f / SCALE_FACTOR, 136.f / SCALE_FACTOR);

	fDef.shape = &shape;

	this->walls[1] = this->world->CreateBody(&bDef);
	this->walls[1]->CreateFixture(&fDef);

	// BOTTOM WALL

	bDef.position.Set(240.f / SCALE_FACTOR, 267.f / SCALE_FACTOR);

	shape.SetAsBox(240.f / SCALE_FACTOR, 5.f / SCALE_FACTOR);

	fDef.shape = &shape;

	this->walls[2] = this->world->CreateBody(&bDef);
	this->walls[2]->CreateFixture(&fDef);
}

void App::drawWalls() {
	oslDrawFillRect(0, 0, 10, 272, 0xFF00FF00);
	oslDrawFillRect(470, 0, 480, 272, 0xFF00FF00);
	oslDrawFillRect(0, 262, 480, 272, 0xFF00FF00);
}

void App::addBox(int*p,int i) {
	if (this->box.max < MAX_BOX) {
		b2BodyDef bDef;
		if (i == 0)
			bDef.type = b2_dynamicBody;
		else
			bDef.type = b2_staticBody;
		bDef.position.Set(p[0] / SCALE_FACTOR, p[1] / SCALE_FACTOR);

		b2PolygonShape shape;
		shape.SetAsBox(10.f / SCALE_FACTOR, 10.f / SCALE_FACTOR);

		b2FixtureDef fDef;
		fDef.density = 2.f;
		fDef.shape = &shape;

		this->box.b[this->box.max] = this->world->CreateBody(&bDef);
		this->box.b[this->box.max]->CreateFixture(&fDef);
		this->box.max++;
	}
}

void App::deleteLastBox() {
	if (this->box.max > 0) {
		this->box.max--;
		this->world->DestroyBody(this->box.b[this->box.max]);
	}
}

void App::drawBox() {
	b2Vec2 pos;
	for (int i = 0; i < this->box.max;i++) {
		pos = this->box.b[i]->GetPosition();
		oslDrawImageXY(this->box.tex, pos.x * SCALE_FACTOR, pos.y * SCALE_FACTOR);
	}
}

void App::addFluid(int* p) {
	b2ParticleDef pDef;
	pDef.position.Set(p[0] / SCALE_FACTOR, p[1] / SCALE_FACTOR);
	pDef.color.Set(b2Color(0.f, 0.f, 1.f));
	this->ps->CreateParticle(pDef);
}

void App::drawFluid() {
	b2Vec2*p;
	p = this->ps->GetPositionBuffer();
	for (int y = 0; y < this->ps->GetParticleCount(); y++)
		oslDrawImageXY(pTex, p[y].x * SCALE_FACTOR, p[y].y * SCALE_FACTOR);
}

void App::deleteFluid() {
	this->ps->DestroyOldestParticle(0, false);
}

void App::addParticleGroup(int*p) {
	if (rand() % 2 == 0) {
		b2PolygonShape shape;
		shape.SetAsBox(50.f / SCALE_FACTOR, 50.f / SCALE_FACTOR);
		b2ParticleGroupDef pgDef;
		pgDef.position.Set(p[0] / SCALE_FACTOR, p[1] / SCALE_FACTOR);
		pgDef.shape = &shape;
		this->ps->CreateParticleGroup(pgDef);
	}
	else {
		b2CircleShape shape;
		shape.m_radius = 50.f / SCALE_FACTOR;
		b2ParticleGroupDef pgDef;
		pgDef.position.Set(p[0] / SCALE_FACTOR, p[1] / SCALE_FACTOR);
		pgDef.shape = &shape;
		this->ps->CreateParticleGroup(pgDef);
	}
}

int updateWorld(SceSize size, void* data) {
	b2World* d = (b2World*)data;
	while (true) {
		d->Step(1.f / 60.f, 0, 0, 1);
	}
}

void App::run() {

	this->addWalls();

	Gui::Mouse mouse;
	int* pm;

	bool pause = true;
	/*int threadID = sceKernelCreateThread("render", updateWorld, 0x500, 0x10000, THREAD_ATTR_VFPU, NULL);

	sceKernelStartThread(threadID, sizeof(b2World), this->world);*/

	while (true) {
		this->startDrawing();

		if (osl_pad.pressed.start)
			pause = !pause;

		if (!pause) {
			this->world->Step(1.f / 60.f, 3, 2, 1);
			if (osl_pad.held.L)
				this->addFluid(pm);
			else if (osl_pad.pressed.R)
				this->addParticleGroup(pm);
			else if (osl_pad.held.circle)
				this->deleteFluid();
			else if (osl_pad.pressed.cross)
				this->addBox(pm,0);
			else if (osl_pad.pressed.square)
				this->addBox(pm,1);
			else if (osl_pad.pressed.triangle)
				this->deleteLastBox();

			pm = mouse.update();

			this->drawWalls();
			this->drawBox();
			this->drawFluid();

			mouse.draw();

			oslDrawStringf(15, 0, "Total particles : %i", this->ps->GetParticleCount());
			oslDrawStringf(15, 15, "Total group : %i", this->ps->GetParticleGroupCount());
			oslDrawStringf(15, 30, "Particle radius : %i", int(RADIUS));
		}
		else {
			oslDrawImageXY(this->command, 0, 0);
		}
		this->endDrawing();
	}
}