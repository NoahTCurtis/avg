#include <iostream>

#include "application.h"

int main(void)
{
	app = new Application();
	while(app->Loop());
	delete app;
}