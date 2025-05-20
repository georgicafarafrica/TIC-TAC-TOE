#include <raylib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BIGBOARD_SIZE 9
#define SMALLBOARD_SIZE 3

typedef struct {
  int value;
}Cell;
// RESETARE PATRAT - POWER-UP 0
// INLOCUIRE - POWER-UP 1
// SCHIMBARE DIRECTIE - POWER-UP 2
typedef struct {
  Cell smallBoard[SMALLBOARD_SIZE][SMALLBOARD_SIZE];
  int winner;
  int values;
}Board;

typedef struct{
  Board squares[SMALLBOARD_SIZE][SMALLBOARD_SIZE];
}BigBoard;

BigBoard tct;
void InitialiseBigBoard(){
  for (int i = 0; i < SMALLBOARD_SIZE;i++)
    for (int j = 0; j < SMALLBOARD_SIZE;j++)
      tct.squares[i][j].values = -1;
    }
void InitialiseSmallBoards(){
  for (int a = 0; a < SMALLBOARD_SIZE; a++){
    for (int b = 0; b < SMALLBOARD_SIZE; b++){
      for (int i = 0; i < SMALLBOARD_SIZE; i++){
	for (int j = 0; j < SMALLBOARD_SIZE; j++)
	  tct.squares[a][b].smallBoard[i][j].value = -1;
      }
    } 
  }
}
/*void DeactivateBoard(){
  for (int i = 0; i < SMALLBOARD_SIZE; i++){
	  for (int j = 0; j < SMALLBOARD_SIZE; j++)
	    tct.squares[i][j].values = -2;
  }
}*/
int player = 1; // 1 pentru X, 0 pentru 0
int CheckOneBoardWinner(){
  for (int a = 0; a < SMALLBOARD_SIZE; a++){
    for (int b = 0; b < SMALLBOARD_SIZE; b++){
      for (int i = 0; i < SMALLBOARD_SIZE; i++){
	if ((tct.squares[a][b].smallBoard[i][0].value) != -1 && (tct.squares[a][b].smallBoard[i][0].value) == (tct.squares[a][b].smallBoard[i][1].value) && (tct.squares[a][b].smallBoard[i][1].value == tct.squares[a][b].smallBoard[i][2].value)){
	  tct.squares[a][b].values = tct.squares[a][b].smallBoard[i][0].value;
	  // DeactivateWinningBoard(a,b);
	}
	if (tct.squares[a][b].smallBoard[0][i].value != -1 && tct.squares[a][b].smallBoard[0][i].value == tct.squares[a][b].smallBoard[1][i].value && tct.squares[a][b].smallBoard[1][i].value == tct.squares[a][b].smallBoard[2][i].value){
	  tct.squares[a][b].values = tct.squares[a][b].smallBoard[0][i].value;
	  // DeactivateWinningBoard(a,b);
	}
	if (tct.squares[a][b].smallBoard[0][0].value != -1 && tct.squares[a][b].smallBoard[0][0].value == tct.squares[a][b].smallBoard[1][1].value && tct.squares[a][b].smallBoard[1][1].value == tct.squares[a][b].smallBoard[2][2].value){
	  tct.squares[a][b].values = tct.squares[a][b].smallBoard[0][0].value;
	  // DeactivateWinningBoard(a,b);
	}
	if (tct.squares[a][b].smallBoard[0][2].value != -1 && tct.squares[a][b].smallBoard[0][2].value == tct.squares[a][b].smallBoard[1][1].value && tct.squares[a][b].smallBoard[1][1].value == tct.squares[a][b].smallBoard[2][0].value){
	  tct.squares[a][b].values = tct.squares[a][b].smallBoard[0][2].value;
	  // DeactivateWinningBoard(a,b);
	}
      }
    }
  }
  return -1;
}

int CheckActualWinner(){
  for (int a = 0; a < SMALLBOARD_SIZE; a++){
	if ((tct.squares[a][0].values) != -1 && (tct.squares[a][0].values) == (tct.squares[a][1].values) && (tct.squares[a][1].values == tct.squares[a][2].values))
	  return tct.squares[a][0].values;
	if (tct.squares[0][a].values != -1 && tct.squares[0][a].values == tct.squares[1][a].values && tct.squares[1][a].values == tct.squares[2][a].values)
	  return tct.squares[0][a].values;
	if (tct.squares[0][0].values != -1 && tct.squares[0][0].values == tct.squares[1][1].values && tct.squares[1][1].values == tct.squares[2][2].values)
	  return tct.squares[0][0].values;
	if (tct.squares[0][2].values != -1 && tct.squares[0][2].values == tct.squares[1][1].values && tct.squares[1][1].values == tct.squares[2][0].values)
	  return tct.squares[0][2].values;
  }
  return -1;
}

void DrawTable(){
  ClearBackground(BLACK);
  for (int i = 1; i < SMALLBOARD_SIZE; i++){
    DrawLineEx((Vector2){i * 300, 0},(Vector2) {i * 300, 900},15, VIOLET);
    DrawLineEx((Vector2){0, i * 300},(Vector2) {900, i * 300},15, VIOLET);
  }
   for (int i = 0; i < SMALLBOARD_SIZE;i++){
     for (int j = 0; j < SMALLBOARD_SIZE; j++){
      if (tct.squares[i][j].values == -1){
       DrawLineEx((Vector2){j*300+100,i*300+15},(Vector2){j*300+100,(i+1)*300-15},5, WHITE); // VERTICALA
       DrawLineEx((Vector2){j*300+200,i*300+15},(Vector2){j*300+200,(i+1)*300-15},5, WHITE); // VERTICALA
       DrawLineEx((Vector2){j*300+15,(i*300)+100},(Vector2){(j+1)*300-15,(i*300)+100},5, WHITE);
       DrawLineEx((Vector2){j*300+15,(i*300)+200},(Vector2){(j+1)*300-15,(i*300)+200},5, WHITE);
      }
      if (tct.squares[i][j].values == 1){
       DrawLineEx ((Vector2){j*300 + 25, i * 300 + 25}, (Vector2){j * 300  + 275, i* 300 + 275},15, GOLD);
	     DrawLineEx ((Vector2){j * 300 + 275,i * 300 + 25},(Vector2){j * 300 + 25, i * 300 + 275},15, GOLD);
      }
      if (tct.squares[i][j].values == 0){
        DrawRing((Vector2){j*300 + 150,i * 300 + 150},120,130,0,360,100,BLUE);
      }
     }
   }
   for (int a = 0; a < SMALLBOARD_SIZE;a++){
     for (int b = 0; b < SMALLBOARD_SIZE; b++){
      if (tct.squares[a][b].values == -1){
       for (int i = 0; i < SMALLBOARD_SIZE; i++){
	 for (int j = 0; j < SMALLBOARD_SIZE; j++){
	   if (tct.squares[a][b].smallBoard[i][j].value == 1){
	     DrawLineEx ((Vector2){b*300 + j * 100 + 15, a * 300 +i * 100 + 15}, (Vector2){b * 300 + j * 100 + 85, a* 300 + i * 100 +85},5, GOLD);
	     DrawLineEx ((Vector2){b * 300 + j * 100 + 85,a * 300 +  i * 100 + 15},(Vector2){b*300 + j * 100 + 15, a * 300 + i * 100 + 85},5, GOLD);
	   }
	   else if (tct.squares[a][b].smallBoard[i][j].value == 0)
	     DrawRing((Vector2){b*300 + j*100+50,a * 300 + i*100+50},35,40,0,360,100,BLUE);
	 }
       }
      }
     }
   }
}

int EmptyCells(){
  for (int a = 0; a < SMALLBOARD_SIZE;a++){
    for (int b = 0; b < SMALLBOARD_SIZE;b++){
      for (int i = 0; i < SMALLBOARD_SIZE; i++){
	for (int j = 0; j < SMALLBOARD_SIZE; j++)
	  if (tct.squares[a][b].smallBoard[i][j].value != -1)
	    return 0;
      }
    }
  }
      return 1;
}

void MouseControl(int x, int y){
       if (x < BIGBOARD_SIZE && y < BIGBOARD_SIZE && tct.squares[y/3][x/3].smallBoard[y%3][x%3].value == -1) {
	 tct.squares[y/3][x/3].smallBoard[y%3][x%3].value = player;
    }
    if((y/3) < 3 && (x/3) < 3){
      if (player == 1)
	player = 0;
      else
	player = 1;
    }
}
int NoMoreCells(){
  for (int a = 0; a < SMALLBOARD_SIZE;a++)
    for (int b = 0; b < SMALLBOARD_SIZE; b++)
      for (int i = 0; i < SMALLBOARD_SIZE;i++)
	      for (int j = 0;j < SMALLBOARD_SIZE;j++)
	  if (tct.squares[a][b].smallBoard[i][j].value == -1)
	    return 0;
  return 1;
}

int IsSquareFull(int x, int y){
  for (int i = 0; i < SMALLBOARD_SIZE;i++)
	      for (int j = 0;j < SMALLBOARD_SIZE;j++)
          if (tct.squares[y%3][x%3].smallBoard[i][j].value == -1)
            return 0;
  return 1;
}

int SquareAvailability(int x, int y){
  if (tct.squares[y][x].values == -1)
    return 1;
  return 0;
}

void Powerup0(int x, int y){// se selecteaza un patrat si se sterge tot din acel patrat// daca acel patrat nu este deja castigat
    for (int i = 0 ; i < SMALLBOARD_SIZE; i++)
      for (int j = 0; j < SMALLBOARD_SIZE; j++)
        tct.squares[y/3][x/3].smallBoard[i][j].value = -1;
}

void YPowerup1(int x, int y){
  int *cell = &tct.squares[y/3][x/3].smallBoard[y%3][x%3].value;
  if (*cell == 1)
    *cell = 0;
}

void XPowerup1(int x, int y){
  int *cell = &tct.squares[y/3][x/3].smallBoard[y%3][x%3].value;
  if (*cell == 0)
    *cell = 1;
}

void ResetGame(){
  InitialiseBigBoard();
  InitialiseSmallBoards();
  player = 1;
}

int main(){
  srand(time(NULL));
  int x = 0,y = 0;
  int memorizeX = 0, memorizeY = 0;
  int playerW = -1;
  int powerUp = 0;
  int rand_int = -1, randA = 0;
  int PmemorizeX = 0, PmemorizeY = 0;
  InitWindow(1400,900, "TIC-TAC-TOE"); 
  SetWindowPosition(GetScreenWidth()-600,-GetScreenHeight());
  SetTargetFPS(60);
  InitialiseBigBoard();
  InitialiseSmallBoards();
  while(!WindowShouldClose()){
    if (player == 1 && playerW == -1 && powerUp == 0)
      DrawText("X turn :",910,50,40,WHITE);
    if (player == 0 && playerW == -1 && powerUp == 0)
      DrawText("0 turn :",910,50,40,WHITE);
    if (powerUp == 1 && playerW == -1 && rand_int == 0)
      DrawText("Clear a square : ",910,50,40,WHITE);
    if (powerUp == 1 && playerW == -1 && rand_int == 1)
      DrawText("Swap one opponent move: ",900,50,40,WHITE);
    if (powerUp == 1 && playerW == -1 && rand_int == 2){
      DrawText("Select a small square: ",910,50,40,WHITE);
      DrawText("so your opponent can play: ",910,80,40,WHITE);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    	x = GetMouseX() ;
    	y = GetMouseY();
	CheckOneBoardWinner();
	if ( powerUp == 0 && !EmptyCells() && SquareAvailability(memorizeX%3,memorizeY%3) && !IsSquareFull(memorizeX,memorizeY)){
	  if (x > (memorizeX%3) * 300 && x < ((memorizeX%3) * 300)+300 && y > (memorizeY%3)*300 && y < ((memorizeY % 3)*300 + 300)){
	    MouseControl(x/100,y/100);
	    memorizeX = x/100;
	    memorizeY = y/100;
      randA = 0;
	  }
	}
	else if (powerUp == 0){
	  MouseControl(x/100,y/100);
	  memorizeX = x/100;
	  memorizeY = y/100;
	  }
  }
  CheckOneBoardWinner();
  BeginDrawing();
  if (!SquareAvailability(memorizeX/3,memorizeY/3)){
    powerUp = 1;
    if (!randA){
      rand_int = rand() % 3;
      randA = 1;
    }
    if (rand_int == 0){
      if (x/100 < 9 && y/100 < 9 && SquareAvailability(x/300,y/300)){
        Powerup0(x/100,y/100);
        powerUp = 0;
        //randA = 0;
    }
  }
    else if (rand_int == 1){
          if (x/100 < 9 && y/100 < 9 && SquareAvailability(x/300,y/300) && tct.squares[y/3][x/3].smallBoard[y%3][x%3].value != -1){
            if (player == 0)
              XPowerup1(x/100, y/100);
            if (player == 1)
              YPowerup1(x/100,y/100);
            powerUp = 0;
            //randA = 0;
            }
      }
    else if (rand_int == 2){
      if (x/100 < 9 && y/100 < 9 && SquareAvailability(x/300,y/300)){
        DrawRectangle((x/300)*300,(y/300)*300,300,300,LIME);
        memorizeX = x/300;
        memorizeY = y/300;
        powerUp = 0;
        //randA = 0;
      }
    }
  }
    if (powerUp == 0 && playerW == -1 && !EmptyCells() && SquareAvailability(memorizeX%3,memorizeY%3) && !IsSquareFull(memorizeX,memorizeY)) //&& SquareAvailability(x/100,y/100))//  && (tct.squares[(y/100)%3][(x/100)%3].values == -1))
	    DrawRectangle(((memorizeX)%3)*300,((memorizeY)%3)*300,300,300,LIME);
    else{
      if (playerW == -1 && powerUp == 0){
        DrawText("You can play wherever", 910, 150,40,WHITE);
        DrawText("you want", 910, 190, 40 , WHITE);
      }
    }
    DrawTable();
    DrawRectangle(900,800,500,100, GRAY);
    DrawText("RESTART",915,800,100, YELLOW);
    playerW = CheckActualWinner();
    if (playerW != -1){
      if (playerW == 1)
	      DrawText("PLAYER X WON !!!", 910, 190, 60, GREEN);
      if (playerW == 0)
	      DrawText("PLAYER 0 WON !!!", 910, 190, 60, GREEN);
      
    }
  if (NoMoreCells())
    DrawText("REMIZA !!!", 910, 190, 60, YELLOW);
  if (x > 900 && y > 800){
    ResetGame();
    powerUp = 0;
  }
  EndDrawing();
  }
  CloseWindow();
  return 0;
}
