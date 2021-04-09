#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

enum direct { STOP = 0, LEFT, RIGHT, UP, DOWN};

int menu(char key, int game_speed);
void setup(bool &game_over, int &x, int &y, int &width, int &height,int &fruitX, int &fruitY, int &score, char &dir); 
void field(int &game_speed, bool &game_over, int &x, int &y, int &width, int &height,int &fruitX, int &fruitY, int &score, int &nTail, int tailX[100], int tailY[100]);
void input(int &game_speed, char key, char &dir);
void logic(bool &game_over,int &x, int &y, int &width, int &height,int &fruitX, int &fruitY, int &score,char &dir, int &nTail, int tailX[100], int tailY[100]);
void gotoxy(int width, int height);
void SetColor(int text, int background);
void cursorOn();
void cursorOff(); 

int main (){
	int game_speed=1, x, y, width=20, height=20, fruitX, fruitY, score, nTail=0, tailX[100], tailY[100];
	char key, dir;
	bool game_over;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	game_speed=menu(key, game_speed);
	setup(game_over, x,y, width, height,fruitX,fruitY, score,  dir);

	while(!game_over){
		field(game_speed, game_over, x,y, width, height, fruitX,  fruitY,  score, nTail, tailX, tailY);
		gotoxy(height-20,width-20);
		input(game_speed, key,dir);
		logic(game_over, x,y, width, height,  fruitX,  fruitY,  score, dir, nTail, tailX, tailY);
		}
	return 0;
}

void setup(bool &game_over,int &x, int &y, int &width, int &height, int &fruitX, int &fruitY, int &score, char &dir){
	game_over = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	srand(time(0));
	fruitX = rand() % width -1;
	fruitY = rand() % height -1;
	cursorOff();
	score = 0;
} 

void field(int &game_speed, bool &game_over, int &x, int &y, int &width, int &height,int &fruitX, int &fruitY, int &score, int &nTail, int tailX[100], int tailY[100]){

	//================ Difficulty
	if(game_speed==1){
		Sleep(170);
		if(score == 30){
			Sleep(90);
			if(score == 30){
			Sleep(1);
			}
		}
	}
	else if(game_speed==2){
		Sleep(90);
		if(score == 30){
			Sleep(1);
		}
	}
	else if (game_speed==3){
		game_speed=3;
	} 
	//================ Difficulty
	if(game_speed==4) {
		game_over = true;
	}
	
	for(int i=0;i<width+1;i++){
		SetColor(15, 3);
		printf("-"); 
		SetColor(15, 0);
	}
	
	printf("\n"); 
	
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(j == 0 || j == width-1){
				SetColor(15, 3);
				printf("|");
				SetColor(15, 0);
			}
			
				if(i == y && j == x){
					SetColor(15, 2);
					printf("*");
					SetColor(15, 0);
				}	
				else if(i == fruitY && j == fruitX ){
					SetColor(15, 12); 
					printf("F");
					SetColor(15, 0);
				}
				
				else{
					bool tail = false;
					for(int k = 0; k < nTail; k++){
						if(tailX[k] == j && tailY[k] == i){
							tail = true;
							SetColor(15, 10);
							printf("`");
							SetColor(15, 0);
						}
					} 
					if(!tail) 
					printf(" ");
				}
		}
		printf("\n");
	}
	
	for (int i=0;i<width+1;i++){
		SetColor(15, 3);
		printf("-"); 
		SetColor(15, 0);
	}
	
	printf(" "); 
	printf("\nScore:%i", score);
	printf("\nIf Score = 500, you win! =) ");
	printf("\nPress 'X' for Menu\n");
	printf("       UP    - 'W'\n");
	printf("       DOWN  - 'S'\n");
	printf("       LEFT  - 'A'\n");
	printf("       RIGHT - 'D'\n");
	
} //рисование карты

void input(int &game_speed, char key, char &dir){
	if(_kbhit()) {  //  _kbhit - возвращает значение "истина" если пользлватеь нажал на какую лиьо клав ишу
		switch(_getch())
		{
			case 'a': dir = LEFT; break;
			case 'd': dir = RIGHT; break;
			case 'w': dir = UP; break;
			case 's': dir = DOWN; break;
			case 'x': game_speed=menu(key, game_speed); break;
		}
	}
} // нажати€ пользовател€

void logic(bool &game_over,int &x, int &y, int &width, int &height, int &fruitX, int &fruitY, int &score, char &dir, int &nTail, int tailX[100], int tailY[100]){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev1X, prev1Y;   // переменные в которые мы помещ€ем след елементы
	tailX[0] = x;
	tailY[0] = y;
	for(int i=1; i < nTail; i++){
		prev1X = tailX[i];
		prev1Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev1X;
		prevY = prev1Y;
	}
	switch(dir){
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN: 
		y++;
			break;
	}

	if(x >= width-1){
		x=0;
	}
	else if (x<0){
		x=width-2;
	}
	if(y >= height){
		y=0;
	}
	else if (y<0){
		y=height-1;
	}
	
	
	// ----------------------------------
	for(int i = 0; i < nTail; i++){
		if(tailX[i] == x && tailY[i] == y){
				game_over = true;
				system("cls"); 
				 SetColor(15, 12);
			printf("\n=============\nGAME OVER\n=============");
			SetColor(15, 0); 
		}	
	}
	
	if(x == fruitX && y == fruitY){
		score+=10;
			fruitX = rand() % (width-1) ;
	       	fruitY = rand() % (height-1) ;
	       	for(int i = 0; i < nTail; i++){
	       		if(tailX[i] == fruitX && tailY[i] == fruitY){ // правельна€ проверка)
	       			fruitX = rand() % (width-1) ;
	       			fruitY = rand() % (height-1) ;
				}
			}		
		nTail++;
		
		if(nTail==50){
			system("cls");
			SetColor(15, 12);
			printf("/n");
			printf("     ----- > You Win ! ! ! < -----");
			printf("/n");
			SetColor(15, 0);
			game_over = true;
		}
	}

} // логика игры 

// ==================================================
void gotoxy(int width, int height) {
 HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD coord = { width, height };
 SetConsoleCursorPosition(StdOut, coord);
}

void SetColor(int text, int background)
{
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//SetColor(15, 0); стандартне значенн€
// ==================================================
void cursorOff(){
  
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;
GetConsoleCursorInfo(handle,&structCursorInfo);
structCursorInfo.bVisible = FALSE;
SetConsoleCursorInfo( handle, &structCursorInfo );
}
/*
void cursorOn(){
  
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;
GetConsoleCursorInfo(handle,&structCursorInfo);
structCursorInfo.bVisible = TRUE;
SetConsoleCursorInfo( handle, &structCursorInfo );
}
*/ 

int menu(char key, int game_speed)
{
	cursorOff();	
	do{

	if(game_speed>=5){
		game_speed=1;
	}
	if(game_speed<1){
		game_speed=5;
	} 
	if(key==115){
		game_speed++;
	}
	if(key==119){
		game_speed--; 
	} 
	switch (game_speed)
	{
		case 1 : 
		system("cls"); 
			printf("\n");
	printf("\n");
	printf("      **      *        *           *          *    *  ********   \n");
	printf("    *     *   **       *          * *         *   *   *          \n");
	printf("    *     *   * *      *         *   *        *  *    *          \n");
	printf("     *        *  *     *        *     *       * *     *          \n");
	printf("      *       *   *    *       *********      **      *          \n");
	printf("       *      *    *   *      *         *     * *     ******     \n");
	printf("        *     *     *  *     *           *    *  *    *          \n");
	printf("    *     *   *      * *    *             *   *   *   *          \n");
	printf("    *     *   *       **   *               *  *    *  *          \n");
	printf("      **      *        *  *                 * *     * ********   \n");
	printf("\n");
	printf("\n");
	printf("       Select the difficulty level   \n");
	printf("             -> Easy                          \n");
	printf("                Medium                        \n");
	printf("                Hard                          \n");
	printf("                Exit                          \n");
	printf("\n");
	printf("       UP    - 'W'\n");
	printf("       DOWN  - 'S'\n");
	printf("       LEFT  - 'A'\n");
	printf("       RIGHT - 'D'\n");
	key=getch();
	break;
	
	// --------------------------------------------------------
	
	case 2 : 
	system("cls"); 
			printf("\n");
	printf("\n");
	printf("      **      *        *           *          *    *  ********   \n");
	printf("    *     *   **       *          * *         *   *   *          \n");
	printf("    *     *   * *      *         *   *        *  *    *          \n");
	printf("     *        *  *     *        *     *       * *     *          \n");
	printf("      *       *   *    *       *********      **      *          \n");
	printf("       *      *    *   *      *         *     * *     ******     \n");
	printf("        *     *     *  *     *           *    *  *    *          \n");
	printf("    *     *   *      * *    *             *   *   *   *          \n");
	printf("    *     *   *       **   *               *  *    *  *          \n");
	printf("      **      *        *  *                 * *     * ********   \n");
	printf("\n");
	printf("\n");
	printf("       Select the difficulty level   \n");
	printf("                Easy                          \n");
	printf("             -> Medium                        \n");
	printf("                Hard                          \n");
	printf("                Exit                          \n");
	printf("\n");
	printf("       UP    - 'W'\n");
	printf("       DOWN  - 'S'\n");
	printf("       LEFT  - 'A'\n");
	printf("       RIGHT - 'D'\n");
	key=getch();
	
	break;
	// --------------------------------------------------------
	
	case 3: 
	system("cls"); 
			printf("\n");
	printf("\n");
	printf("      **      *        *           *          *    *  ********   \n");
	printf("    *     *   **       *          * *         *   *   *          \n");
	printf("    *     *   * *      *         *   *        *  *    *          \n");
	printf("     *        *  *     *        *     *       * *     *          \n");
	printf("      *       *   *    *       *********      **      *          \n");
	printf("       *      *    *   *      *         *     * *     ******     \n");
	printf("        *     *     *  *     *           *    *  *    *          \n");
	printf("    *     *   *      * *    *             *   *   *   *          \n");
	printf("    *     *   *       **   *               *  *    *  *          \n");
	printf("      **      *        *  *                 * *     * ********   \n");
	printf("\n");
	printf("\n");
	printf("       Select the difficulty level   \n");
	printf("                Easy                          \n");
	printf("                Medium                        \n");
	printf("             -> Hard                          \n");
	printf("                Exit                          \n");
	printf("\n");
	printf("       UP    - 'W'\n");
	printf("       DOWN  - 'S'\n");
	printf("       LEFT  - 'A'\n");
	printf("       RIGHT - 'D'\n");
	key=getch();
	
	break;
	// --------------------------------------------------------
	
		case 4: 
	system("cls"); 
			printf("\n");
	printf("\n");
	printf("      **      *        *           *          *    *  ********   \n");
	printf("    *     *   **       *          * *         *   *   *          \n");
	printf("    *     *   * *      *         *   *        *  *    *          \n");
	printf("     *        *  *     *        *     *       * *     *          \n");
	printf("      *       *   *    *       *********      **      *          \n");
	printf("       *      *    *   *      *         *     * *     ******     \n");
	printf("        *     *     *  *     *           *    *  *    *          \n");
	printf("    *     *   *      * *    *             *   *   *   *          \n");
	printf("    *     *   *       **   *               *  *    *  *          \n");
	printf("      **      *        *  *                 * *     * ********   \n");
	printf("\n");
	printf("\n");
	printf("       Select the difficulty level   \n");
	printf("                Easy                          \n");
	printf("                Medium                        \n");
	printf("                Hard                          \n");
	printf("             -> Exit                          \n");
	printf("\n");
	printf("       UP    - 'W'\n");
	printf("       DOWN  - 'S'\n");
	printf("       LEFT  - 'A'\n");
	printf("       RIGHT - 'D'\n");
	key=getch();
	
	break;
		
	}
}while(key!=13);
system("cls"); 
return game_speed;
}
