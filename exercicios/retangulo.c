//clear && gcc retangulo.c -lm && ./a.out 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Point2D{
	int x,y;
};
struct Point3D{
	int x,y,z;
};
struct Rectangle{
	struct Point2D UpperLeft, UpperRight, LowerLeft, LowerRight;
};
struct Box{
	struct Point2D FrontUpperLeft, FrontUpperRight, FrontLowerLeft, FrontLowerRight, BackUpperLeft, BackUpperRight, BackLowerLeft, BackLowerRight;
};

double distance2D(struct Point2D *p1, struct Point2D *p2);
double distance3D(struct Point3D *p1, struct Point3D *p2);
// void createBox(struct Point2D,);

void main(){
	struct Rectangle myRectangle;
	printf("Entre com a coordenada do primeiro ponto no formato <x,y> \n");
	scanf("%i,%i", &myRectangle.UpperLeft.x, &myRectangle.UpperLeft.y);
	getchar();
	printf("Entre com a coordenada do segundo ponto no formato <x,y> \n");
	scanf("%i,%i", &myRectangle.LowerRight.x, &myRectangle.LowerRight.y);
	getchar();
	myRectangle.UpperRight.x = myRectangle.UpperLeft.x;
	myRectangle.UpperRight.y = myRectangle.LowerRight.y;
	myRectangle.LowerLeft.x = myRectangle.LowerRight.x;
	myRectangle.LowerLeft.y = myRectangle.UpperLeft.y;
	printf("Os pontos deste retangulo são: \n(%i,%i)\t(%i,%i) \n(%i,%i)\t(%i,%i).\n",
		myRectangle.UpperLeft.x,myRectangle.UpperLeft.y,
		myRectangle.UpperRight.x,myRectangle.UpperRight.y,
		myRectangle.LowerLeft.x,myRectangle.LowerLeft.y,
		myRectangle.LowerRight.x,myRectangle.LowerRight.y);
	printf("O tamanho da estrutura Rectangle: %u\n", sizeof(myRectangle));
	printf("A distancia entre LowerLeft e LowerRight: %lf\n", distance2D(&myRectangle.LowerLeft, &myRectangle.LowerRight));
	printf("A distancia entre LowerLeft e UpperRight: %lf\n", distance2D(&myRectangle.LowerLeft, &myRectangle.UpperRight));
}

// void createBox(){

// }

double distance2D(struct Point2D *p1, struct Point2D *p2){
	return sqrt(pow((*p2).x-(*p1).x,2)+pow((*p2).y-(*p1).y,2));
}

double distance3D(struct Point3D *p1, struct Point3D *p2){
	return sqrt(pow((*p2).x-(*p1).x,2)+pow((*p2).y-(*p1).y,2)+pow((*p2).z-(*p1).z,2));
}