#include <raylib.h>
#include <string.h>
#include <stdio.h>
#define BIGBOARD_SIZE 9
#define SMALLBOARD_SIZE 3
typedef struct {
  int value;
}Cell;

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
void DeactivateWinningBoard(int a, int b){
      for (int i = 0; i < SMALLBOARD_SIZE; i++){
	for (int j = 0; j < SMALLBOARD_SIZE; j++)
	  if (tct.squares[a][b].smallBoard[i][j].value != 0 && tct.squares[a][b].smallBoard[i][j].value != 1)
	    tct.squares[a][b].smallBoard[i][j].value = -2;
  }
}
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

void UpdateFields(int y, int z){
      for (int i = 0; i < SMALLBOARD_SIZE; i ++)
	for (int j = 0; j < SMALLBOARD_SIZE; j++)
	  if (tct.squares[y][z].smallBoard[i][j].value == -2)
	     tct.squares[y][z].smallBoard[i][j].value = -1;
}
void DrawTable(){
  ClearBackground(BLACK);
  for (int i = 1; i < SMALLBOARD_SIZE; i++){
    DrawLineEx((Vector2){i * 300, 0},(Vector2) {i * 300, 900},15, VIOLET);
    DrawLineEx((Vector2){0, i * 300},(Vector2) {900, i * 300},15, VIOLET);
  }
   for (int i = 0; i < SMALLBOARD_SIZE;i++){
     for (int j = 0; j < SMALLBOARD_SIZE; j++){
       DrawLineEx((Vector2){j*300+100,i*300+15},(Vector2){j*300+100,(i+1)*300-15},5, WHITE); // VERTICALA
       DrawLineEx((Vector2){j*300+200,i*300+15},(Vector2){j*300+200,(i+1)*300-15},5, WHITE); // VERTICALA
       DrawLineEx((Vector2){j*300+15,(i*300)+100},(Vector2){(j+1)*300-15,(i*300)+100},5, WHITE);
       DrawLineEx((Vector2){j*300+15,(i*300)+200},(Vector2){(j+1)*300-15,(i*300)+200},5, WHITE);
    }
   }
   for (int a = 0; a < SMALLBOARD_SIZE;a++){
     for (int b = 0; b < SMALLBOARD_SIZE; b++){
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
      if (player == 1)
	player = 0;
      else
	player = 1;
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

int main(){
  int x = 0,y = 0;
  int memorizeX = 0, memorizeY = 0;
  InitWindow(900,900, "TIC-TAC-TOE"); 
  SetWindowPosition(GetScreenWidth(),-GetScreenHeight());
  SetTargetFPS(60);
  InitialiseBigBoard();
  InitialiseSmallBoards();
  while(!WindowShouldClose()){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    	x = GetMouseX() ;
    	y = GetMouseY();
	if (!EmptyCells()){
	  if (x > (memorizeX%3) * 300 && x < ((memorizeX%3) * 300)+300 && y > (memorizeY%3)*300 && y < (memorizeY % 3)*300 + 300 ){
	    MouseControl(x/100,y/100);
	    memorizeX = x/100;
	    memorizeY = y/100;
	  }
	}
	else{
	  MouseControl(x/100,y/100);
	  memorizeX = x/100;
	  memorizeY = y/100;
	}
    }
    BeginDrawing();
    if (!EmptyCells())
	DrawRectangle(((memorizeX)%3)*300,((memorizeY)%3)*300,300,300,LIME);
    DrawTable();
    CheckOneBoardWinner();
    int playerW = CheckActualWinner();
    if (playerW != -1){
      if (playerW == 1)
	DrawText("PLAYER X WON !!!", 220, 250, 40, MAGENTA);
      if (playerW == 0)
	DrawText("PLAYER 0 WON !!!", 220, 250, 40, MAGENTA);
      
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
