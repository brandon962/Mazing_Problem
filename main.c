#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int size = 15;                          //�}�C���j�p 
int cheak;								//�ĤG�D�ˬd�O�_�����|���ܼ� 
int step;								//�p��B�� 
int ans3;								//�P�ˬ��p��B��(��step���ȷ|����ĤG�D�v�T�A�ҥH�Ĥ@�D�����ɭn��ans3�Ӧs) 

struct place							//�ѽL�Ϊ����c 
{
	int road;							//���0,1 
	int path;							//�������ĴX�B 
	int ans1;							//�M��Ĥ@�D���|���ܼ�(�P�ɬ��̵u���|�A�]���ڦb�䪺�ɭԦ������B��) 
	int ans3;							//�ѩ�ans1�|���ĤG�D�v�T�A�ҥH�ݭnans3�ӰO��ans1���� 
}chess[15][15];							//�ѽL�ܼ� 

struct xy								//�N�G���y�е��X���@���ܼ� 
{
	int i;								//�񫫪����y�� 
	int j;								//��������y�� 
}s, e, w[500];							//�_�I�ܼ� ���I�ܼ� ���|�}�C 

void startGame()						//�}�l�C�� 
{
	int i,j;
	int temp;							//0�M1�p�G�O1:1���ܲĤ@�D�n�]����[ �ĤG�D���n���I 
	
	srand(time(NULL));					//�üƪ��ؤl 
	
	for (i = 0; i < size; i++)
		for(j = 0; j < size; j++)
		{
			temp = rand()%3; 			//����0�M1��O1:2 
			if (temp == 0)
				chess[i][j].road = 1;
			else 
				chess[i][j].road = 0;
		}
			
	s.i = rand()%size;					//�]�m�_�I 
	s.j = rand()%size;
	do									//�קK�_�I�M���I�ۦP 
	{
		e.i = rand()%size;				//�]�m���I 
		e.j = rand()%size;
	}
	while(e.i == s.i && e.j == s.j);
	
	chess[s.i][s.j].road = 2;			//�N�_�I���I�����|�אּ2 
	chess[e.i][e.j].road = 2;
		
	return;
}

void print()							//�C�L���|�[�� 
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

	�H�W��path�b���|���O0���ɭԩҦs����
	�C�ӼƦr���O�@��cont�j�� 

*/ 


int walk()								//�M����|�[��1 
{
	int i, cont = 0;
	int stemp = 0,						//stemp, etemp, ctemp������for�j��Ū��w�}�C����(w�����L�����|) 
		etemp = 0,
		ctemp = 1;
	w[0] = s;							//�N�_�I���w[0]����m 
	chess[s.i][s.j].path = 1;			//�N�_�I���B�Ƴ]��1(�o�O���F�p���K�A�̫�|���^��) 
	
	while(w[cont].i != e.i && w[cont].j != e.j)     //�n������I�~�|���}while�j�� 
	{
		cont++;										//�C��B�ƥ[�@ 
		ctemp = 1;									//�����Ӱ�S���F�X���I 
		for (i = stemp; i <= etemp; i++)			//Ū���P�@�骺���e (stemp, etemp �����C�ӼƦr���_�I�M���I) 
		{
			// �P�_�V�� 
			if ((chess[w[i].i][w[i].j - 1].road == 0 || chess[w[i].i][w[i].j - 1].road == 2) &&  w[i].j > 0 &&				//((�U����|��0||�U����|�����I)&&����W�X���&& 
			 	(chess[w[i].i][w[i].j - 1].path == 0 || chess[w[i].i][w[i].j].path + 1 < chess[w[i].i][w[i].j - 1].path))	// (�U����|�|�����L||�O�_���|��U��u)) 
			{
				w[etemp+ctemp].i = w[i].i;													//�N�U�@�Ӧ�m�O���bw�̭� 
				w[etemp+ctemp].j = w[i].j - 1;
				chess[w[i].i][w[i].j - 1].path = chess[w[i].i][w[i].j].path + 1;			//�N���檺�B�ƥ[1���U�@��� 
				if (w[etemp+ctemp].i == e.i && w[etemp+ctemp].j == e.j)						//�p�G����I���������[�� 
				{
					step = chess[w[i].i][w[i].j].path + 1;									 
					return 0;
				}
				ctemp++;																	 
							
			}
			// �P�_�V�W 
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
			// �P�_�V�k 
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
			// �P�_�V�U 
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
			// �P�_�V�k�U 
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
			// �P�_�V���U 
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
			//  �P�_�V�k�W 
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
			// �P�_�V���W 
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
		stemp = etemp + 1;												//����wŪ���a�� �q�W�ӵ������U�@�Ӷ}�l 
		etemp = stemp + ctemp - 2;										//Ū��stemp+ctemp-2���� 
		
	}
	
	printf("\n");

	return 1;
}

void find ()															//�M����|�[��2 
{
	int i = 0;
	cheak = 0;															//�ĤG�D���i��|�������F�A�ҥH�ݭn���ܼ� 
	struct xy temp1 = e;												//�Ψӧ�^�����ܼ� 
	chess[e.i][e.j].ans1 = 1;
	while(i < 100) 														//�j��				
	{
		i++;
		if(chess[temp1.i - 1][temp1.j].path + 1 == chess[temp1.i][temp1.j].path)		//�p�G���񦳮t1�����|�N�Ntemp1���L�h ����̤p1���� 
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
	
	chess[temp1.i][temp1.j].ans1 = 0;     					//�|�h��@�өҥH�n� 
	return;
}

void printa1 ()												//�Ĥ@�D������ 
{
	int i = 0, j;
	
	find();													//������find(); 
	chess[e.i][e.j].ans1 = 2;								//�N�_�I�M���I�̤W�O�� 
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
	
	for (i = 0; i < size; i++)										//���U�ӲĤG�D�|�ʨ�ڤ��Q�ʪ��ܼơA���N�L�̦s�_�� 
		for (j = 0; j < size; j++)
			chess[i][j].ans3 = chess[i][j].ans1;
	
	ans3 = step;													//�P�W 
	
	return;
}

void printa2 ()
{
	int i, j, t;																	// t�O�ΨӦs��J��m���쥻���|�� 
	int xinput, yinput;																// �ΨӦs��J�ܼ� 
	int bug;
	
	print();																		//��ܭ쥻�ѽL 
	
	printf("Please input two number between 0-14.(EX : 2 3)\n");		

	while(1)																		//�ˬd��J 
	{
    	bug = scanf("%d %d", &xinput,&yinput); 										//��bug����scanf���^�ǭ� 
    	if(bug != 2)																//��J�n�ŦX�榡(�ڪ��i�H�ˬd�X�O�_��int) 
   		{
        	fflush(stdin);		
       		printf("Please input again.(EX : 2 3)\n");
   	 	}
   	 	else if(yinput < 0 || xinput < 0 || yinput > 14 || xinput > 14)				//��J�n�b�d�� 
   	 		printf("Please input again.(EX : 2 3)\n");
   	 	else
        	break;
	}
	
	
	t = chess[yinput][xinput].road;												//�ΨӦs��J�I�쥻���� 
	
	chess[yinput][xinput].road = 3;												
	print();
	for (i = 0; i < 500; i ++)													//�N���L�����|�k�s 
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
	struct xy temp;																//�ΨӼȦs���ܼ� 
	
	temp = e;							
	
	e.i = yinput;																//�N���I�אּ��J�I 
	e.j = xinput;
	chess[yinput][xinput].road = 2;
	//chess[temp.i][temp.j].road = 0;
	
	i = walk();																	//�M��_�I���J�I�����| 
	find();
	
	if (cheak == 0)																//�Y�䤣����|�ШϥΪ̭��s��J�y�� 
	{
		printf("Please input again.(EX : 2 3)\n");					
		e = temp;																//�N�ܼ��٭� 
		chess[yinput][xinput].road = t;
		printa2();
		return;																	//�ѤU���{���X���n�F 
	}
	
	for (i = 0; i < 500; i ++)													//�A���M�Ÿ��| 
	{
		w[i].i = 0;
		w[i].j = 0;
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			chess[i][j].path = 0;
	
	e = temp;																	//�N���I�٭�^���I 
	
	temp = s;
	s.i = yinput;																//�N��J�I�]���_�I 
	s.j = xinput;
	
	i = walk();
	find();
	
	printf("\n");																//�ƪ� 

	if (cheak == 0)																//�Y�䤣����|�ШϥΪ̭��s��J�y��
	{
		printf("Please input again.(EX : 2 3)\n");
		s = temp;																//�N����٭� 
		chess[yinput][xinput].road = t;
		printa2();
		return;																	//�ѤU��������F 
	}
	
	chess[temp.i][temp.j].ans1 = 2;												//���D�حn�D���W�O�� 
	chess[yinput][xinput].ans1 = 3;
	chess[e.i][e.j].ans1 = 2;
	
	for(i = 0; i < size; i++)													//�C�L�X���� 
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
	
	s = temp;																	//�N����٭� 
	chess[yinput][xinput].road = t;
	
	
	return ;
}

void printa3()
{
	print();																	//�L�X��e�ѽL 
	printf("\n");																//�ƪ� 
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
	ans3--;																		//�N��l��1���� 
	printf("The shortest hop is %d.\n", ans3);									//�L�X�̵u���| 
	return;
}

int main(int argc, char *argv[]) 
{
	printf("Enter any key to start.\n");										//�����N��}�l�C�� 
	system("PAUSE");
	
	do																			//�Y�S�����|�N�q���@�ӴѽL 
	{
		printf("Loading...");
		startGame();
	}
	while(walk());
	
	system ("cls");																//�M�ŵe�� 
	print();																	//�L�X��e�ѽL 
	printf("\n");																//�ƪ� 
	
	printf("ans1:\n");										
	printa1();																	//�L�X�Ĥ@�D 
	system("PAUSE");
	system("cls");																//�M�ŵe�� 
	
	printf("ans2:\n");
	printa2();																	//�L�X�ĤG�D 
	system("PAUSE");
	system("cls");
	
	
	printf("ans3:\n");															//�L�X�ĤT�D 
	printa3();
	

	
	
	return 0;
}
