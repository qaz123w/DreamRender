#include <iostream>
#include <utils.h>
#include <interface.h>

int main() {
	dream::Interface gui(1800, 1200);
	INFO("[info] AAAAAAAAAAAA");
	ERROR("[error] SSSSSSSSSS");
	WARN("[warning] DDDDDDDDDDDD");
	DEBUG("[debug] ZZZZZZZZZZ");
	gui.Render();

	return 0;
}