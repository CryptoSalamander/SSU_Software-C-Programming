#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 9
#define T 3
#define BT 40
int input_cmd(void);
int make_sudoku(void);
int input_sudoku(void);
int main(void)
{
	char i;
	make_sudoku();
	return 0;
}
int input_cmd(void)
{
	char i,j,k;

	printf("Input Commands:");
	scanf(" %c",&i);
	switch(i)
	{
		case 'n':
		case 'N':	  
			system("clear");
			make_sudoku();
			input_cmd();
			break;
		case 'q':
		case 'Q':
			printf("스도쿠를 종료합니다.");
			exit(1);
			break;  
		case 'h':
		case 'H':
			printf("숫자 1 숫자2 숫자3 : 숫자1 행 숫자2 열을 숫자3으로 한다.\n");
			printf("A : 현재 스도쿠 문제를 처음부터 다시 시작한다.\n");
			printf("I : 스도쿠 문제를 입력받는다. \n");
			printf("Q : 스도쿠 프로그램을 종료한다. \n");
			printf("U : 마지막으로 실행한 명령을 취소한다.\n");
			printf("H : 명령어 도움말 출력\n");
			printf("V : 스도쿠 조건이 맞는지 검증한다.\n");
			printf("R : 게임 랭킹을 출력한다.\n");
			printf("N : 새로운 게임을 시작한다.\n");
			input_cmd();
	}
	return i;
}
int make_sudoku(void)
{
	int i,j,k,n1,n2,n3,n4,count,tmpj[BT],tmpk[BT],i2,answer[N][N],ion,x1,x2,x3;
	int tmp[T][T];
	int undoj[5];
	int undok[5];
	int undotmp[5];
	int undoi=0;
	int undocount=0;
	static int i3=0;
	int i4=0;
	int sudoku[N][N]={1,2,3,4,5,6,7,8,9};	
	srand(time(NULL));
	int p1[T][T]={1,2,3,4,5,6,7,8,9};
    static int rank[1000];
    static time_t start,end,diff,ex1,ex2;

	for(i=0 ; i < 100 ; i++)
	{	
		n1 = rand() % 3;
		n2 = rand() % 3;
		n3 = rand() % 3;
		n4 = rand() % 3;
		tmp[n1][n2]=p1[n1][n2];
		p1[n1][n2]=p1[n3][n4];
		p1[n3][n4]=tmp[n1][n2];
	}
	for(i=0;i<=2;i++)
		for(j=0;j<=2;j++)
			sudoku[i][j]=p1[i][j];//첫번째 3x3칸
	for(i=0;i<=2;i++)
		for(j=3;j<=5;j++)
		{
			if(i==2)
				sudoku[i][j]=p1[i-2][j-3];
			else
				sudoku[i][j]=p1[i+1][j-3];	
		}//두번째 3x3칸
	for(i=0;i<=2;i++)
		for(j=6;j<=8;j++)
		{
			if(i==0)
				sudoku[i][j]=p1[i+2][j-6];
			else
				sudoku[i][j]=p1[i-1][j-6];
	    }//3번째 3x3칸
	for(i=3;i<=5;i++)
		for(j=0;j<=2;j++)
		{
			if(j==2)
				sudoku[i][j]=p1[i-3][j-2];
			else
				sudoku[i][j]=p1[i-3][j+1];
		}//4번째 3x3칸
	for(i=3;i<=5;i++)
		for(j=3;j<=5;j++)
		{
			if(i==5&&j!=5)
				sudoku[i][j]=p1[i-5][j-2];
			else if(j==5&&i!=5)
				sudoku[i][j]=p1[i-2][j-5];
			else if(i==5&&j==5)
				sudoku[i][j]=p1[i-5][j-5];
			else
				sudoku[i][j]=p1[i-2][j-2];
		}//5번째 3x3칸
	for(i=3;i<=5;i++)
		for(j=6;j<=8;j++)
		{
			if(j==8&&i!=3)
				sudoku[i][j]=p1[i-4][j-8];
			else if(i==3&&j!=8)
				sudoku[i][j]=p1[i-1][j-5];
			else if(i==3&&j==8)
				sudoku[i][j]=p1[i-1][j-8];
			else
				sudoku[i][j]=p1[i-4][j-5];
		}//6번째 3x3칸
	for(i=6;i<=8;i++)
		for(j=0;j<=2;j++)
		{
			if(j==0)
				sudoku[i][j]=p1[i-6][j+2];
			else
				sudoku[i][j]=p1[i-6][j-1];
		}//7번째 3x3칸
	for(i=6;i<=8;i++)
		for(j=3;j<=5;j++)
		{
			if(i==8&&j!=3)
				sudoku[i][j]=p1[i-8][j-4];
			else if(i!=8&&j==3)
				sudoku[i][j]=p1[i-5][j-1];
			else if(i==8&&j==3)
				sudoku[i][j]=p1[i-8][j-1];
			else
				sudoku[i][j]=p1[i-5][j-4];
		}//8번쨰 3x3칸
	for(i=6;i<=8;i++)
		for(j=6;j<=8;j++)
		{
			if(i==6&&j==6)
				sudoku[i][j]=p1[i-4][j-4];
			else if(i==6&&j!=6)
				sudoku[i][j]=p1[i-4][j-7];
			else if(i!=6&&j==6)
				sudoku[i][j]=p1[i-7][j-4];
			else
				sudoku[i][j]=p1[i-7][j-7];

		}
	for(i=0;i<=8;i++)
		for(j=0;j<=8;j++)
			answer[i][j]=sudoku[i][j]+'0';
	count=0;
	for(i4=0;i4<=999;i4++)
		if(rank[i4]==0)
			rank[i4]=10000;
	while(count<1)
	{ 
		j=rand() % 9;
		k=rand() % 9;
		tmpj[count]=j;
		tmpk[count]=k;
		if(sudoku[j][k]!=0)
			count++;
		sudoku[j][k]=0;
	}
	for(j=0; j < 9; j++)
	{
		for(k = 0; k < 9; k++)
		{
			switch(sudoku[j][k])  
			{
				case 0:
					sudoku[j][k]='.';
					break;
				case 1:
					sudoku[j][k]='1';
					break;
				case 2:
					sudoku[j][k]='2';
					break;
				case 3:
					sudoku[j][k]='3';		 
					break;
				case 4:
					sudoku[j][k]='4';
					break;
				case 5:
					sudoku[j][k]='5';
					break;
				case 6:
					sudoku[j][k]='6';
					break;
				case 7:
					sudoku[j][k]='7';
					break;
				case 8:
					sudoku[j][k]='8';
					break;
				case 9:
					sudoku[j][k]='9';
					break;
			}	
		}
	}		
	do
	{
		printf("   1 2 3    4 5 6    7 8 9 \n");
		printf(" ┏━━━━━━━━┯━━━━━━━┯━━━━━━━┓\n");
		printf("1┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[0][0],sudoku[0][1],sudoku[0][2],sudoku[0][3],sudoku[0][4],sudoku[0][5],sudoku[0][6],sudoku[0] [7],sudoku[0] [8]);   
		printf("2┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[1] [0],sudoku[1] [1],sudoku[1] [2],sudoku[1] [3],sudoku[1] [4],sudoku[1] [5],sudoku[1] [6],sudoku[1] [7],sudoku[1] [8]);
		printf("3┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[2] [0],sudoku[2] [1],sudoku[2] [2],sudoku[2] [3],sudoku[2] [4],sudoku[2] [5],sudoku[2] [6],sudoku[2] [7],sudoku[2] [8]);
		printf(" ┣━━━━━━━━╋━━━━━━━╋━━━━━━━┫\n");
		printf("4┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[3] [0],sudoku[3] [1],sudoku[3] [2],sudoku[3] [3],sudoku[3] [4],sudoku[3] [5],sudoku[3] [6],sudoku[3] [7],sudoku[3] [8]);
		printf("5┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[4] [0],sudoku[4] [1],sudoku[4] [2],sudoku[4] [3],sudoku[4] [4],sudoku[4] [5],sudoku[4] [6],sudoku[4] [7],sudoku[4] [8]);
		printf("6┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[5] [0],sudoku[5] [1],sudoku[5] [2],sudoku[5] [3],sudoku[5] [4],sudoku[5] [5],sudoku[5] [6],sudoku[5] [7],sudoku[5] [8]);
		printf(" ┣━━━━━━━━╋━━━━━━━╋━━━━━━━┫\n");
		printf("7┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[6] [0],sudoku[6] [1],sudoku[6] [2],sudoku[6] [3],sudoku[6] [4],sudoku[6] [5],sudoku[6] [6],sudoku[6] [7],sudoku[6] [8]); 
		printf("8┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[7] [0],sudoku[7] [1],sudoku[7] [2],sudoku[7] [3],sudoku[7] [4],sudoku[7] [5],sudoku[7] [6],sudoku[7] [7],sudoku[7] [8]);
		printf("9┃ %c %c %c  ┃ %c %c %c ┃ %c %c %c ┃\n",sudoku[8] [0],sudoku[8] [1],sudoku[8] [2],sudoku[8] [3],sudoku[8] [4],sudoku[8] [5],sudoku[8] [6],sudoku[8] [7],sudoku[8] [8]);
		printf(" ┗━━━━━━━━┻━━━━━━━┻━━━━━━━┛\n");
		start=time(NULL);
		i=input_cmd();
		int m;
		int k;
			if(i=='i'||i=='I')
			{
				ion=1;
				for(i2=0;i2<=8;i2++)
					for(m=0;m<=8;m++)
					{
						scanf(" %c",&k);
		 				sudoku[i2][m]=k;
						
					}
			}
		if(i=='a'||i=='A')
		{
			for(i2=0;i2<40;i2++)
				sudoku[tmpj[i2]][tmpk[i2]]='.';
			system("clear");
		}
	    else if(i=='r' || i=='R')
	    {
			int f;
			system("clear");
			for(f=0;f<5;f++)
			{
				if(rank[f]==10000)
					printf("%d위 : 기록없음\n",f+1);
				else
		    		printf("%d위 : %d초\n",f+1,rank[f]);
			}	    
			
  		 }

		else if(i=='v'||i=='V')
		{
				system("clear");
				while(1)
				{
					for(i4=0;i4<=8;i4++)
					{
						for(i2=0;i2<=8;i2++)
						{
							if(sudoku[i4][i2]=='.')
							{
								printf("(%d,%d)가 잘못됬습니다. \n",i4+1,i2+1);
								x1=1;
								break;
							}
						}
						if(x1==1)
							break;
					}
					if(x1==1)
						break;
				for(i4=0;i4<=8;i4++)
				{
					for(i2=0;i2<=8;i2++)
					{	
						for(i3=i2+1;i3<=8;i3++)
							{
								if(sudoku[i4][i3]==sudoku[i4][i2])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x1=1;
								break;
							}
							}
						if(x1==1)
							break;
					}
					if(x1==1)
						break;
				}
				if(x1==1)
					break;
				for(i4=0;i4<=8;i4++)
				{
					for(i2=0;i2<=8;i2++)
					{	
						for(i3=i2+1;i3<=8;i3++)
							{
								if(sudoku[i3][i4]==sudoku[i2][i4])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i2+1,i4+1);
								x2=1;
								break;
							}
							}
						if(x2==1)
							break;
					}
					if(x2==1)
						break;
				}
					if(x2==1)
						break;
				for(i4=0;i4<=2;i4++)
				{
					for(i2=0;i2<=2;i2++)
					{
						for(i3=i2+1;i3<=2;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=0;i4<=2;i4++)
				{
					for(i2=3;i2<=5;i2++)
					{
						for(i3=i2+1;i3<=5;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=0;i4<=2;i4++)
				{
					for(i2=6;i2<=8;i2++)
					{
						for(i3=i2+1;i3<=8;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=3;i4<=5;i4++)
				{
					for(i2=0;i2<=2;i2++)
					{
						for(i3=i2+1;i3<=2;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=3;i4<=5;i4++)
				{
					for(i2=3;i2<=5;i2++)
					{
						for(i3=i2+1;i3<=5;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=3;i4<=5;i4++)
				{
					for(i2=6;i2<=8;i2++)
					{
						for(i3=i2+1;i3<=8;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				
				}
				if(x3==1)
					break;
				for(i4=6;i4<=8;i4++)
				{
					for(i2=0;i2<=2;i2++)
					{
						for(i3=i2+1;i3<=2;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=6;i4<=8;i4++)
				{
					for(i2=3;i2<=5;i2++)
					{
						for(i3=i2+1;i3<=5;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
				}
				if(x3==1)
					break;
				for(i4=6;i4<=8;i4++)
				{
					for(i2=6;i2<=8;i2++)
					{
						for(i3=i2+1;i3<=8;i3++)
						{
							if(sudoku[i4][i2]==sudoku[i4][i3])
							{
								printf("(%d,%d)가 잘못 됬습니다.\n",i4+1,i2+1);
								x3=1;
								break;
							}
						}
						if(x3==1)
							break;
					}
					if(x3==1)
					{
						break;
					}	
					
				}
				break;
				}	
				x1=0;
				x2=0;
				x3=0;
		}
		else if(i=='u'||i=='U')
		{
			if(undocount>4)
				printf("Undo는 5번만 가능합니다.\n");					
			else
			{	
			sudoku[undoj[undocount]][undok[undocount]]=undotmp[undocount];
			undocount++;
			system("clear");
			}
			
		}

		else
	{			


				
				undotmp[4]=undotmp[3];
				undotmp[3]=undotmp[2];
				undotmp[2]=undotmp[1];
				undotmp[1]=undotmp[0];
				undoj[4]=undoj[3];
				undok[4]=undok[3];
				undoj[3]=undoj[2];
				undok[3]=undok[2];
				undoj[2]=undoj[1];
				undok[2]=undok[1];
				undoj[1]=undoj[0];
				undok[1]=undok[0];
				scanf(" %c %c",&j,&k);

				for(i2=0;i2<=40;i2++)
				{
					if((i-'0'-1)==tmpj[i2]&&(j-'0'-1)==tmpk[i2])
				{
					undotmp[0]=sudoku[i-'0'-1][j-'0'-1];
					sudoku[i-'0'-1][j-'0'-1]=k;
					system("clear");
					undoj[0]=i-'0'-1;
					undok[0]=j-'0'-1;
				}
					
				}
	}
			int y=0;
			for(i2=0;i2<=8;i2++)
			{
				for(j=0;j<=8;j++)
				{
					if(answer[i2][j]!=sudoku[i2][j])
					{
						y=1;
						break;
					}
				}	
				if(y==1)
					break;
			}
			if(y==0)
			{
				printf("축하합니다!!!");
				end=time(NULL);
				diff=end-start;
				ex1=diff/60;
				ex2=diff%60;
				printf("%d분 %d초 입니다\n",ex1,ex2);
			
				rank[i3]=diff;
				i3++;
		 		int a,s,d;
		 		for(a=0; a<5; a++)
		    		{
				for(s=4; s>=a; s--)
				     if(rank[s-1]>rank[s])
				        {
				               d=rank[s-1];
				               rank[s-1]=rank[s];
				               rank[s] = d;
						}
					}
				
				printf("다시 하려면 1을 종료하려면  0을 입력하세요: ");
				scanf("%d",&i2);
				if(i2==1)
				{
				 	system("clear");
					main();
				}
				else if(i2=='0')
				   return 0;
			}

			int z=0;
				for(i2=0;i2<=8;i2++)
				{
					for(j=0;j<=8;j++)
					{
						if(sudoku[i2][j]=='.')
						{
							z=1;
							break;
						}
					}
					if(z==1)
						break;
				}
			
				if(z==0)
				{
					if(ion!=1)
					if(y!=0)
					printf("아쉽지만 틀렸습니다..\n");
				}

}
		while(1);
	}



