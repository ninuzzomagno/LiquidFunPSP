#include"Liquidi.h"

PSP_MODULE_INFO("Liquidi", 1, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main() {
	App myApp;
	myApp.run();

	return 0;
}