#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>


void drawRoad() {  //roads and line
	int i;
    setcolor(WHITE);
    line(170, 0, 170, getmaxy());  
    line(370, 0, 370, getmaxy());   
    for ( i = 0; i < getmaxy(); i += 40) {
	line(270, i, 270, i + 20); 
    }
}

void drawCar(int x, int y) { //user car
    setcolor(RED);
    rectangle(x, y, x + 50, y + 100); //our car
    setfillstyle(SOLID_FILL, RED);
    floodfill(x + 1, y + 1, RED);     

    // headligts
    setcolor(YELLOW);
    circle(x+12,y,5);
    circle(x+37,y,5);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(x + 15, y, YELLOW);     
    floodfill(x + 35, y, YELLOW);     

}


void drawObstacle(int obsX, int obsY, int rc) {
  
    setcolor(rc);
    rectangle(obsX, obsY, obsX + 50, obsY + 100); //obstacle car body
    setfillstyle(SOLID_FILL, rc);
    floodfill(obsX + 1, obsY + 1, rc);

	//headlight
    setcolor(YELLOW);
    circle(obsX+10,obsY+100,5);
    circle(obsX+40,obsY+100,5);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(obsX + 10, obsY + 100, YELLOW);     
    floodfill(obsX + 40, obsY + 100, YELLOW);     

}

int main() {
    int gd = DETECT, gm;

    int carX = 200, carY = 400; // our car starting position
  
    int obsX1 = 200, obsY1 = 0;   // First obstacle car
    int obsX2 = 300, obsY2 = -200; // Second obstacle car 

    int score = 0;
    char key;
    char scoreStr[20];
    int rc1 = 1;
    int rc2 = 2;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");


    while (1) {
	cleardevice();
	drawRoad();

	drawCar(carX, carY);
	drawObstacle(obsX1, obsY1, rc1);  //R.H.S obstacle car
	drawObstacle(obsX2, obsY2, rc2);  //L.H.S obstacle car

	//******************** incresing speed as score increse  *******************************
	if(score < 5){
	obsY1 += 7;
	obsY2 += 7;
	}
	else if(score >=5 && score < 10)
	{
	obsY1 += 14;
	obsY2 += 14;
	}
	else if(score >=10 && score < 20)
	{
	obsY1 += 19;
	obsY2 += 19;
	}
	else
	{
	obsY1 += 39;
	obsY2 += 39;
	}

     //*************** To decide from which lane upcoming car is coming (randomly) ***********************/

	if (obsY1 > getmaxy()) {  
	    obsY1 = 0; // Reset to starting (upside)
	    srand(time(0));
	    rc1 = (rand() % 10) + 1;
	    obsX1 = (rand() % 2 == 0) ? 200 : 300; // decide right or left lane
	    score++;
	}

	if (obsY2 > getmaxy()) {
	    obsY2 = 0; // Reset to starting (upside)
	    srand(time(0));
	    rc2 = (rand() % 10) + 1;
	    obsX2 = (rand() % 2 == 0) ? 200 : 300; // decide right or left lane
	    score++;
	}

	//***********************  Controlling user car *********************************
	if (kbhit()) {
	    key = getch();
	    if (key == 75 && carX > 200) carX -= 100; //  left
	    if (key == 77 && carX < 300) carX += 100; // right
	}

	//**************************  Collision (GAMEOVER) *********************************** 
	if ((carX == obsX1 && (obsY1 + 100) >= carY) || (carX == obsX2 && (obsY2 + 100) >= carY)) {
	
	    setcolor(RED);
	    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); // Larger text for "Game Over"
	    outtextxy(370, 200, "Game Over!");
	    setcolor(YELLOW);
	    sprintf(scoreStr, "Score: %d", score);	// shows final score
	    outtextxy(370, 230, scoreStr);
	    break;
	}

	//*****************************  Display score ***********************************
	setcolor(YELLOW);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);  // show score at corner during game
	sprintf(scoreStr, "Score: %d", score);
	outtextxy(10, 10, scoreStr);

	delay(75);
    }

    getch();
    closegraph();
    return 0;
}
