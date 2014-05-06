#include "Traces.h"
#include "MatrixVibroSound.h"
#include "ofAppGlutWindow.h"
#include "FaceWalrus.h"
#include<conio.h>


//--------------------------------------------------------------
int main(){
	// create a window
	ofAppGlutWindow window; 


	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);

	cout << "Please select which app you would like to run" << endl << endl;
	cout << "0: traces " << endl 
		<< "1: MatrixVibroSound" << endl 
		<< "2: FaceWalrus" << endl 
		<< endl << "             ";

	int c;
	// c = getch();
	c = '2';

	cout << endl << endl;
	
	switch (c) {
	case '0': 
		ofRunApp(new Traces());
		break;

	case '1':		
		ofRunApp (new MatrixVibroSound());
		break;

	case '2':
		ofRunApp (new FaceWalrus());
		break;

	case '3':
		break;

	default:
		break;
	}

	cout << endl << endl;
}
