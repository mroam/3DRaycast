#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>
#include "classes.h"

void set(SDL_Renderer*, int, int, uint8_t, uint8_t, uint8_t);
float square(float num);
float dist3D(float x1, float y1, float z1, float x2, float y2, float z2);

int displayWidth = 1000;
int displayHeight = 700;
int frameCount = 0;
int lightX = 0;
int lightY = displayHeight;
int lightZ = displayWidth*4;
bool print;
CRay cRay(0, 0, 0, 0, 0, displayWidth);
Tri testTri(0, 0, displayWidth*2, displayWidth, 0, displayWidth*2, displayWidth/2, displayWidth/2, displayWidth*5/2, 100, 100, 100);
Ball testBall(0, 0, displayWidth*2, displayHeight/2, 0, 255, 100, 100);
Ball lightBall(lightX, lightY, lightZ, displayHeight/10, 255, 0, 0, 255);


CRay castTri(CRay ray, Tri tri){
	float normalX;
	float normalY;
	float normalZ;
	float pointX = ray.x2;
	float pointY = ray.y2;
	float triX1 = tri.x1;
	float triY1 = tri.y1;
	float triX2 = tri.x2;
	float triY2 = tri.y2;
	float triX3 = tri.x3;
	float triY3 = tri.y3;
	if(!(pointY-triY1<(triY2-triY1)*(pointX-triX1)/(triX2-triX1)^triX2<triX1) && !(pointY-triY2<(triY3-triY2)*(pointX-triX2)/(triX3-triX2)^triX3<triX2) && !(pointY-triY3<(triY1-triY3)*(pointX-triX3)/(triX1-triX3)^triX1<triX3)){
		ray.r = tri.r;
		ray.g = tri.g;
		ray.b = tri.b;
		ray.escape = false;
	}
	return ray;
}
CRay castBall(CRay ray, Ball ball, bool isShadow){
	float lineX1 = dist3D(ray.x1, ray.y1, ray.z1, ball.x, ball.y, ball.z);
	float dist1Sq = square(ball.x-ray.x2)+square(ball.y-ray.y2)+square(ball.z-ray.z2);
	float dist2 = dist3D(ray.x2, ray.y2, ray.z2, ray.x1, ray.y1, ray.z1);
	float lineX2 = (dist1Sq-square(dist2)+square(lineX1))/(2*lineX1); //this x and y, along with lineX1 and lineX2, define a ray in a 2D space that will actually be used to calculate the intersection between the original ray and the sphere.  The 2D plane is the plane that intersects the center of the sphere and both points on the 3D ray.
	float lineY2 = sqrt(dist1Sq-square(lineX2));
	//if(print){printf("lineX2:%f, ray z:%f, lineY2:%f\n",lineX2,ray.z2,lineY2);}
	if(/*if ray hits 2D circle (slice of sphere)*/(square((lineX2-lineX1)/lineY2)+1)*ball.radiusSq-lineX1*lineX1>=0){
		if(isShadow){
			//ray.setColor(0, 0, 0, 255);
			ray.r = 0;
			ray.g = 0;
			ray.b = 0;
		}
		else{ray.setColor(ball.r, ball.g, ball.b, ball.a);}
	}
	return ray;
}
CRay castYPlane(CRay ray, float y, int r1, int g1, int b1, int r2, int g2, int b2, int a){
	if(!(ray.y2-ray.y1>0)^(y-ray.y1<0)){
		float planeX = (ray.x2-ray.x1)*(y-ray.y1)/(ray.y2-ray.y1)-ray.x1;
		float planeZ = (ray.z2-ray.z1)*(y-ray.y1)/(ray.y2-ray.y1)-ray.z1;
		ray.x1 = (ray.x2-ray.x1)*(y-ray.y1)/(ray.y2-ray.y1);
		ray.z1 = (ray.z2-ray.z1)*(y-ray.y1)/(ray.y2-ray.y1);
		ray.y1 = y;
		if(/*(int)sqrt(ray.x1*ray.x1+ray.y1*ray.y1+ray.z1*ray.z1)%(int)(displayWidth/2)<displayWidth/4){*/abs((int)planeX)%(int)displayWidth<displayWidth/2^abs((int)planeZ)%(int)displayWidth<displayWidth/2^planeX>0^planeZ>0){ 
			ray.setColor(r1, g1, b1, a);
		}
		else{
			ray.setColor(r2, g2, b2, a);
		}
		ray.escape = false;
	}
	return ray;
}
CRay test2D(CRay ray){
	if(square(ray.x2)+square(ray.y2)<square(displayHeight/2)){
		if(ray.y2<sin(ray.x2*15.7079632679/displayWidth-frameCount*displayWidth/50)*displayHeight/4){
			ray.r = 50;
			ray.g = 200;
			ray.b = 20;
		}
		else{
			ray.r = 200;
			ray.g = 20;
			ray.b = 50;
		}
		ray.escape = false;
	}
	return ray;
}

CRay setCRay(CRay ray, float x1, float y1, float z1, float x2, float y2, float z2){
	ray.x1 = x1;
	ray.y1 = y1;
	ray.z1 = z1;
	ray.x2 = x2;
	ray.y2 = y2;
	ray.z2 = z2;
	ray.r = 0;
	ray.g = 0;
	ray.b = 0;
	ray.a = 255;
	ray.escape = true;
	return ray;
}

void renderPixel(SDL_Renderer *renderer, int x, int y){
	print = x==0 && y==3;
	cRay = setCRay(cRay, frameCount*displayWidth/50, 0, 0, x+frameCount*displayWidth/50, y, displayWidth);
	lightY = displayHeight*(-frameCount-50)/100;
	if(x==-displayWidth/2 && y==-displayHeight/2){
		lightBall.x = lightX;
		lightBall.y = lightY;
		lightBall.z = lightZ;
	}
	//cRay = castTri(cRay, testTri);
	cRay = castBall(cRay, lightBall, false);
	cRay = castBall(cRay, testBall, false);
	if(cRay.escape){cRay = castYPlane(cRay, -displayWidth/*frameCount*displayWidth/50-displayWidth*/, 0, 0, 0, 150, 0, 150, 255);}
	cRay.x2 = lightX;
	cRay.y2 = lightY;
	cRay.z2 = lightZ;
	if(!cRay.escape){cRay = castBall(cRay, testBall, true);}
	/*if(x==0 && y==0 && frameCount==2){
		lightBall.x = cRay.x1;
		lightBall.y = cRay.y1;
		lightBall.z = cRay.z1;
	}*/
	if(cRay.escape){cRay.setColor(150, 200, 255, 255);}
	set(renderer, x+displayWidth/2, y+displayHeight/2, cRay.r, cRay.g, cRay.b);
}

void draw(SDL_Renderer *renderer){
	for(int x = 0; x<displayWidth; x ++){
		for(int y = 0; y<displayHeight; y ++){
			renderPixel(renderer, x-displayWidth/2, y-displayHeight/2);
		}
	}
}



int main(int argc, char* args[]){
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	printf("width: %i, ", DM.w);
	printf("height: %i\n", DM.h);
	//displayWidth = DM.w;
	//displayHeight = DM.h;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialize.  SDL_Error: %s\n", SDL_GetError());
	}
	else{
		window = SDL_CreateWindow("3D Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
		if(window==NULL){
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			while(frameCount<100){
				draw(renderer);
				SDL_RenderPresent(renderer);
				frameCount ++;
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Done\n");
	return 0;
}

void set(SDL_Renderer *renderer, int x, int y, uint8_t r, uint8_t g, uint8_t b){
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
}
float square(float num){
	return num*num;
}
float dist3D(float x1, float y1, float z1, float x2, float y2, float z2){
	return sqrt(square(x2-x1)+square(y2-y1)+square(z2-z1));
}
