#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int size = 15;                          //陣列的大小 
int cheak;								//第二題檢查是否有路徑的變數 
int step;								//計算步數 
int ans3;								//同樣為計算步數(但step的值會受到第二題影響，所以第一題結束時要用ans3來存) 

struct place							//棋盤用的結構 
{
	int road;							//顯示0,1 
	int path;							//紀錄為第幾步 
	int ans1;							//尋找第一題路徑的變數(同時為最短路徑，因為我在找的時候有紀錄步數) 
	int ans3;							//由於ans1會受第二題影響，所以需要ans3來記錄ans1的值 
}chess[15][15];							//棋盤變數 

struct xy								//將二維座標結合成一個變數 
{
	int i;								//放垂直的座標 
	int j;								//放水平的座標 
}s, e, w[500];							//起點變數 終點變數 路徑陣列 

void startGame()						//開始遊戲 
{
	int i,j;
	int temp;							//0和1如果是1:1的話第一題要跑比較久 第二題不好中點 
	
	srand(time(NULL));					//亂數的種子 
	
	for (i = 0; i < size; i++)
		for(j = 0; j < size; j++)
		{
			temp = rand()%3; 			//我讓0和1比是1:2 
			if (temp == 0)
				chess[i][j].road = 1;
			else 
				chess[i][j].road = 0;
		}
			
	s.i = rand()%size;					//設置起點 
	s.j = rand()%size;
	do									//避免起點和終點相同 
	{
		e.i = rand()%size;				//設置終點 
		e.j = rand()%size;
	}
	while(e.i == s.i && e.j == s.j);
	
	chess[s.i][s.j].road = 2;			//將起點終點的路徑改為2 
	chess[e.i][e.j].road = 2;
		
	return;
}

void print()							//列印路徑涵式 
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0l; j < size; j++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
		{
			printf("%d ",chess[i][j].road);
		}
		printf("\n");
	}
	                                             
	return;
}

/* 

		6 5 4 5 6 
		5 4 3 4 5 
		4 3 2 3 4 
		3 2 1 2 3 
		4 3 2 3 4 
		5 4 3 4 5 
		6 5 4 5 6 

	以上為path在路徑都是0的時候所存的值
	每個數字都是一個cont迴圈 

*/ 


int walk()								//尋找路徑涵式1 
{
	int i, cont = 0;
	int stemp = 0,						//stemp, etemp, ctemp為控制for迴圈讀取w陣列的值(w為走過的路徑) 
		etemp = 0,
		ctemp = 1;
	w[0] = s;							//將起點放到w[0]的位置 
	chess[s.i][s.j].path = 1;			//將起點的步數設為1(這是為了計算方便，最後會扣回來) 
	
	while(w[cont].i != e.i && w[cont].j != e.j)     //要走到終點才會離開while迴圈 
	{
		cont++;										//每圈步數加一 
		ctemp = 1;									//紀錄該圈又走了幾個點 
		for (i = stemp; i <= etemp; i++)			//讀取同一圈的內容 (stemp, etemp 紀錄每個數字的起點和終點) 
		{
			// 判斷向左 
			if ((chess[w[i].i][w[i].j - 1].road == 0 || chess[w[i].i][w[i].j - 1].road == 2) &&  w[i].j > 0 &&				//((下方路徑為0||下方路徑為終點)&&不能超出邊際&& 
			 	(chess[w[i].i][w[i].j - 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i][w[i].j - 1].path))	// (下方路徑尚未走過||是否路徑比下方短)) 
			{
				w[etemp+ctemp].i = w[i].i;													//將下一個位置記錄在w裡面 
				w[etemp+ctemp].j = w[i].j - 1;
				chess[w[i].i][w[i].j - 1].path = chess[w[i].i][w[i].j].path + 1;			//將此格的步數加1放到下一格裡 
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)						//如果到終點直接結束涵式 
				{
					step = chess[w[i].i][w[i].j].path + 1;									 
					return 0;
				}
				ctemp++;																	 
							
			}
			// 判斷向上 
			if ((chess[w[i].i - 1][w[i].j].road == 0 || chess[w[i].i - 1][w[i].j].road == 2) && w[i].i  > 0 &&
				(chess[w[i].i - 1][w[i].j].path == 0 || chess[w[i].i][w[i].j].path + 1 < (chess[w[i].i - 1][w[i].j].path)) )
			{
				w[etemp+ctemp].i = w[i].i - 1;
				w[etemp+ctemp].j = w[i].j;
				chess[w[i].i - 1][w[i].j].path = chess[w[i].i][w[i].j].path + 1;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 1;
					return 0;
				}
				ctemp++;				
			}
			// 判斷向右 
			if ((chess[w[i].i][w[i].j + 1].road == 0 || chess[w[i].i][w[i].j + 1].road == 2) &&  w[i].j < size-1 && 
				(chess[w[i].i][w[i].j + 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i][w[i].j + 1].path))
			{
				w[etemp+ctemp].i = w[i].i;
				w[etemp+ctemp].j = w[i].j + 1;
				chess[w[i].i][w[i].j + 1].path = chess[w[i].i][w[i].j].path + 1;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 1;
					return 0;
				}
				ctemp++;
							
			}
			// 判斷向下 
			if ((chess[w[i].i + 1][w[i].j].road == 0 || chess[w[i].i + 1][w[i].j].road == 2) && w[i].i < size-1 &&
				(chess[w[i].i + 1][w[i].j].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i + 1][w[i].j].path))
			{
				w[etemp+ctemp].i = w[i].i + 1;
				w[etemp+ctemp].j = w[i].j;
				chess[w[i].i + 1][w[i].j].path = chess[w[i].i][w[i].j].path + 1;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 1;
					return 0;
				}
				ctemp++;
				
			}
			// 判斷向右下 
			if ((chess[w[i].i + 1][w[i].j + 1].road == 0 || chess[w[i].i + 1][w[i].j + 1].road == 2) &&w[i].i < size-1 && w[i].j < size-1 && 
				(chess[w[i].i + 1][w[i].j + 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i + 1][w[i].j + 1].path))
			{
				w[etemp+ctemp].i = w[i].i + 1;
				w[etemp+ctemp].j = w[i].j + 1;
				chess[w[i].i + 1][w[i].j + 1].path = chess[w[i].i][w[i].j].path + 3;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 3;
					return 0;
				}
				ctemp++;
				
			}
			// 判斷向左下 
			if ((chess[w[i].i + 1][w[i].j - 1].road == 0 || chess[w[i].i + 1][w[i].j - 1].road == 2) && w[i].i < size-1 && w[i].j > 0 && 
				(chess[w[i].i + 1][w[i].j - 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i + 1][w[i].j - 1].path))
			{
				w[etemp+ctemp].i = w[i].i + 1;
				w[etemp+ctemp].j = w[i].j - 1;
				chess[w[i].i + 1][w[i].j - 1].path = chess[w[i].i][w[i].j].path + 3;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 3;
					return 0;
				}
				ctemp++;
				
			}
			//  判斷向右上 
			if ((chess[w[i].i - 1][w[i].j + 1].road == 0 || chess[w[i].i - 1][w[i].j + 1].road == 2) && w[i].i > 0 && w[i].j < size-1 &&
				(chess[w[i].i - 1][w[i].j + 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i - 1][w[i].j + 1].path))
			{
				w[etemp+ctemp].i = w[i].i - 1;
				w[etemp+ctemp].j = w[i].j + 1;
				chess[w[i].i - 1][w[i].j + 1].path = chess[w[i].i][w[i].j].path + 3;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 3;
					return 0;
				}
				ctemp++;
				
			}
			// 判斷向左上 
			if ((chess[w[i].i - 1][w[i].j - 1].road == 0 || chess[w[i].i - 1][w[i].j - 1].road == 2) && w[i].i > 0 && w[i].j > 0 && 
				(chess[w[i].i - 1][w[i].j - 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i - 1][w[i].j - 1].path))
			{
				w[etemp+ctemp].i = w[i].i - 1;
				w[etemp+ctemp].j = w[i].j - 1;
				chess[w[i].i - 1][w[i].j - 1].path = chess[w[i].i][w[i].j].path + 3;
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)
				{
					step = chess[w[i].i][w[i].j].path + 3;
					return 0;
				}
				ctemp++;
				
			}		
		
		}
		stemp = etemp + 1;												//控制w讀的地方 從上個結束的下一個開始 
		etemp = stemp + ctemp - 2;										//讀到stemp+ctemp-2為止 
		
	}
	
	printf("\n");

	return 1;
}

void find ()															//尋找路徑涵式2 
{
	int i = 0;
	cheak = 0;															//第二題有可能會有走不了，所以需要的變數 
	struct xy temp1 = e;												//用來找回路的變數 
	chess[e.i][e.j].ans1 = 1;
	while(i < 100) 														//迴圈				
	{
		i++;
		if(chess[temp1.i - 1][temp1.j].path + 1 == chess[temp1.i][temp1.j].path)		//如果附近有差1的路徑就將temp1移過去 直到最小1為止 
		{
			chess[temp1.i - 1][temp1.j].ans1 = 1;
			temp1.i --;
			cheak = 99;
		}
		else if(chess[temp1.i + 1][temp1.j].path + 1 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i + 1][temp1.j].ans1 = 1;
			temp1.i ++;
			cheak = 99;
		}
		else if (chess[temp1.i][temp1.j - 1].path + 1 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i][temp1.j - 1].ans1 = 1;
			temp1.j --;
			cheak = 99;
		}
		else if (chess[temp1.i][temp1.j + 1].path + 1 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i][temp1.j + 1].ans1 = 1;
			temp1.j ++;
			cheak = 99;
		}
		else if (chess[temp1.i + 1][temp1.j + 1].path + 3 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i + 1][temp1.j + 1].ans1 = 1;
			temp1.i ++;
			temp1.j++;
			cheak = 99;
		}
		else if (chess[temp1.i + 1][temp1.j - 1].path + 3 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i + 1][temp1.j - 1].ans1 = 1;
			temp1.i ++;
			temp1.j --;
			cheak = 99;
		}
		else if (chess[temp1.i - 1][temp1.j + 1].path + 3 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i - 1][temp1.j + 1].ans1 = 1;
			temp1.i --;
			temp1.j ++;
			cheak = 99;
		}
		else if (chess[temp1.i - 1][temp1.j - 1].path + 3 == chess[temp1.i][temp1.j].path)
		{
			chess[temp1.i - 1][temp1.j - 1].ans1 = 1;
			temp1.i --;
			temp1.j --;
			cheak = 99;
		}
	}
	
	chess[temp1.i][temp1.j].ans1 = 0;     					//會多算一個所以要減掉 
	return;
}

void printa1 ()												//第一題的答案 
{
	int i = 0, j;
	
	find();													//先執行find(); 
	chess[e.i][e.j].ans1 = 2;								//將起點和終點最上記號 
	chess[s.i][s.j].ans1 = 2;
	
	for(i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (chess[i][j].ans1 == 2)
				printf("2 ");
			else if(chess[i][j].ans1 == 1)
				printf("0 ", chess[i][j].path);
			else
				printf("* ");
		}
		printf("\n");
	}
	
	for (i = 0; i < size; i++)										//接下來第二題會動到我不想動的變數，先將他們存起來 
		for (j = 0; j < size; j++)
			chess[i][j].ans3 = chess[i][j].ans1;
	
	ans3 = step;													//同上 
	
	return;
}

void printa2 ()
{
	int i, j, t;																	// t是用來存輸入位置的原本路徑值 
	int xinput, yinput;																// 用來存輸入變數 
	int bug;
	
	print();																		//顯示原本棋盤 
	
	printf("Please input two number between 0-14.(EX : 2 3)\n");		

	while(1)																		//檢查輸入 
	{
    	bug = scanf("%d %d", &xinput,&yinput); 										//用bug接收scanf的回傳值 
    	if(bug != 2)																//輸入要符合格式(我的可以檢查出是否為int) 
   		{
        	fflush(stdin);		
       		printf("Please input again.(EX : 2 3)\n");
   	 	}
   	 	else if(yinput < 0 || xinput < 0 || yinput > 14 || xinput > 14)				//輸入要在範圍內 
   	 		printf("Please input again.(EX : 2 3)\n");
   	 	else
        	break;
	}
	
	
	t = chess[yinput][xinput].road;												//用來存輸入點原本的值 
	
	chess[yinput][xinput].road = 3;												
	print();
	for (i = 0; i < 500; i ++)													//將走過的路徑歸零 
	{
		w[i].i = 0;
		w[i].j = 0;
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			chess[i][j].path = 0;
			chess[i][j].ans1 = 0;
		}
	}
	struct xy temp;																//用來暫存的變數 
	
	temp = e;							
	
	e.i = yinput;																//將終點改為輸入點 
	e.j = xinput;
	chess[yinput][xinput].road = 2;
	//chess[temp.i][temp.j].road = 0;
	
	i = walk();																	//尋找起點到輸入點的路徑 
	find();
	
	if (cheak == 0)																//若找不到路徑請使用者重新輸入座標 
	{
		printf("Please input again.(EX : 2 3)\n");					
		e = temp;																//將變數還原 
		chess[yinput][xinput].road = t;
		printa2();
		return;																	//剩下的程式碼不要了 
	}
	
	for (i = 0; i < 500; i ++)													//再次清空路徑 
	{
		w[i].i = 0;
		w[i].j = 0;
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			chess[i][j].path = 0;
	
	e = temp;																	//將終點還原回終點 
	
	temp = s;
	s.i = yinput;																//將輸入點設為起點 
	s.j = xinput;
	
	i = walk();
	find();
	
	printf("\n");																//排版 

	if (cheak == 0)																//若找不到路徑請使用者重新輸入座標
	{
		printf("Please input again.(EX : 2 3)\n");
		s = temp;																//將資料還原 
		chess[yinput][xinput].road = t;
		printa2();
		return;																	//剩下的不執行了 
	}
	
	chess[temp.i][temp.j].ans1 = 2;												//案題目要求做上記號 
	chess[yinput][xinput].ans1 = 3;
	chess[e.i][e.j].ans1 = 2;
	
	for(i = 0; i < size; i++)													//列印出答案 
	{
		for (j = 0; j < size; j++)
		{
			if (chess[i][j].ans1 == 2)
				printf("2 ");
			else if(chess[i][j].ans1 == 3)
				printf("3 ");
			else if(chess[i][j].ans1 == 1)
				printf("0 ");
			else
				printf("* ");
		}
		printf("\n");
	}
	
	s = temp;																	//將資料還原 
	chess[yinput][xinput].road = t;
	
	
	return ;
}

void printa3()
{
	print();																	//印出當前棋盤 
	printf("\n");																//排版 
	int i,j;
	for(i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (chess[i][j].ans3 == 2)
				printf("2 ");
			else if(chess[i][j].ans3 == 3)
				printf("3 ");
			else if(chess[i][j].ans3 == 1)
				printf("0 ");
			else
				printf("* ");
		}
		printf("\n");
	}
	ans3--;																		//將初始的1扣掉 
	printf("The shortest hop is %d.\n", ans3);									//印出最短路徑 
	return;
}

int main(int argc, char *argv[]) 
{
	printf("Enter any key to start.\n");										//按任意鍵開始遊戲 
	system("PAUSE");
	
	do																			//若沒有路徑就從做一個棋盤 
	{
		printf("Loading...");
		startGame();
	}
	while(walk());
	
	system ("cls");																//清空畫面 
	print();																	//印出當前棋盤 
	printf("\n");																//排版 
	
	printf("ans1:\n");										
	printa1();																	//印出第一題 
	system("PAUSE");
	system("cls");																//清空畫面 
	
	printf("ans2:\n");
	printa2();																	//印出第二題 
	system("PAUSE");
	system("cls");
	
	
	printf("ans3:\n");															//印出第三題 
	printa3();
	

	
	
	return 0;
}
