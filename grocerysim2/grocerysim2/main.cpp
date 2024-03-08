#include "Engine.h"

int main()
{
	Engine main;
	if (main.Construct(356, 340, 2, 2))
		main.Start();

	return 0;
}
