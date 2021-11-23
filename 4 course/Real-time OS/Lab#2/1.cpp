#include <vingraph.h>
#include <stdlib.h>

int main(){
	ConnectGraph();
	Text (10, 10, "Pixel");
	Pixel (20, 40);
	
	Text (70, 10, "Line");
	Line (70, 50, 130, 90);
	
	Text (140, 10, "Polyline");
	tPoint p1 [] = { {140, 100}, {200, 40}, {200, 100}, {155, 55} };
	Polyline (p1, 4);
	
	Text (210, 10, "Rect");
	Rect (210, 40, 60, 60);
	
	Text (280, 10, "Polygon");
	tPoint p2 [] = { {280, 100}, {310, 40}, {340, 100} };
	Polygon (p2, 3);
	
	Text (385, 10, "Ellipse");
	Ellipse (350, 40, 60, 60);
	Ellipse (420, 50, 60, 40);
	
	Text (490, 10, "Arc");
	//Arc (490, 40, 60, 60, 0, 1800);
	
	Text (560, 10, "Grid");
	Grid (560, 40, 60, 60, 3, 2);
	
	int *im_buf = (int*) malloc (60*60*4);
	for (int i = 0, c = 10; i < 60; i++, c += 0x010304)
	for (int j = 0; j < 60; j++) im_buf [60*i + j] = c;
	Text (630, 10, "Image");
	Image32 (630, 40, 60, 60, im_buf);
	return 0;
}
