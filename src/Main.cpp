#include <iostream>

#include "Application.h"

int main(int argv, char** argc)
{
    ///Code
   
	/*//States
	bool VR = false;
	// etc, etc, etc...

	//Handle Commandline args
	if (argv >= 2)
	{
		//For now, we are assuming that the argument is telling the Application to use VR
		VR = true;
	}
	else
	{
		std::cout << "Use VR? (1 = yes; 0 = no) ";
		std::cin >> VR;
	}*/

    Application app;

	app.setModeVR(false);

    app.RunLoop();

	system("pause");

    return 0;
}
