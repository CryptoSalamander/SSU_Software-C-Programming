#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 50 // 빙고판에 쓸 수 있는 숫자 중 가장 큰 숫자입니다.
#define TRUE 1
#define FALSE 0

int main()
{
 int number[MAXNUM][2];
 // 빙고판에 써지는 숫자들을 저장할 배열입니다.
 // number[][0]에는 1~MAXNUM의 숫자가 저장되고
 // number[][1]에는 number[][0]의 숫자를 빙고판에 썼나 안썼나 여부를 나타냅니다.
 // number[][1]가 TRUE이면 빙고판에 써진 것이고, FALSE이면 아직 써지지 않은 것입니다.
 int board[5][5];
 // 5x5 빙고판
 int tag[25];
 // 빙고판의 총 25칸에 써진 숫자들의 선택여부를 나타냅니다.
 // 사용자가 선택한 칸은 TRUE, 그렇지 않은 칸은 FALSE로 나타냅니다.
 int n;
 int i,j;
 int bingo=FALSE;
 // 빙고가 완성되었나 여부를 나타냅니다.
 // TRUE는 완성, FALSE는 미완성입니다.

 srand(time(NULL));
 // 난수 발생 초기화

 // 1~MAXNUM의 숫자를 저장합니다.
 for(i=0;i<MAXNUM;i++)
 {
  number[i][0]=i+1;
 }

 // 빙고게임
 while(!bingo)
 {  
  // 모든 칸을 아직 선택하지 않은 상태로 초기화
  for(i=0;i<25;i++)
  {
   tag[i]=FALSE;
  }

  // 모든 숫자를 아직 빙고판에 쓰지 않은 상태로 초기화
  for(i=0;i<MAXNUM;i++)
  {
   number[i][1]=FALSE;
  }

  // 빙고판을 만듭니다
  for(i=0;i<5;i++)
  {
   for(j=0;j<5;j++)
   {
    do
    {
     // 1~MAXNUM까지의 숫자를 뽑습니다.
     n=rand()%MAXNUM;
    }while(number[n][1]==TRUE);
    // 이미 빙고판에 존재하는 숫자를 뽑은 경우 다시 뽑습니다.

    // 뽑은 숫자를 빙고판에 씁니다.
    board[i][j]=number[n][0];
    // 고른 숫자가 빙고판에 써진 것을 표시합니다.
    number[n][1]=TRUE;
   }
  }

  while(1)
  {
   // 화면 클리어
   system("cls");
   // 빙고판을 출력합니다.
   for(i=0;i<5;i++)
   {
    for(j=0;j<5;j++)
    {
     // 선택한 숫자는 선택한 것을 표시합니다.
     if(tag[i*5+j]==1)
      printf(" (%2d)",board[i][j]);
     // 아직 선택하지 않은 숫자는 그냥 출력합니다.
     else
      printf("%5d",board[i][j]);
    }
    printf("\n");
   }

   // 빙고가 완성되면 게임을 종료합니다.
   if(bingo)
   {
    printf("\nBINGO!!!\n");
    break;
   }

   printf("\n숫자를 입력하세요: ");
   scanf("%d",&n);

   // -1이 입력되면 프로그램을 종료합니다.
   if(n==-1) return 0;

   // 범위를 벗어나는 숫자를 입력받으면 다시 입력하게 합니다.
   if(n<1 || n>MAXNUM)
   {
    printf("1~%d 사이의 숫자만 입력하세요.\n",MAXNUM);
    system("pause");
    continue;
   }

   // 입력받은 숫자를 빙고판에서 찾습니다.
   for(i=0;i<25;i++)
   {
    if(board[i/5][i%5]==n)
    {
     // i번째 칸에 숫자가 있음을 표시합니다.
     tag[i]=TRUE;
     // 숫자를 찾으면 더 이상 탐색하지 않습니다.
     break;
    }
   }
   // 만약 빙고판을 끝까지 탐색하였는데 숫자를 발견하지 못하면 다시 숫자를 입력받습니다.
   if(i==25)
   {
    printf("%d는 빙고판에 없는 숫자입니다.\n",n);
    system("pause");
    continue;
   }

   // 빙고가 완성되었는지 검사합니다.
   for(i=0;i<5;i++)
   {
    // 가로 검사
    // 가로의 경우 각 칸의 index가 1씩 차이가 납니다.
    if(tag[i*5]==1 && tag[i*5+1]==1 && tag[i*5+2]==1 && tag[i*5+3]==1 && tag[i*5+4]==1)
    {
     bingo=TRUE;
     // 완성된 줄을 찾으면 표시하고 탐색을 종료합니다.
     break;
    }

    // 세로 검사
    // 세로의 경우 각 칸의 index가 5씩 차이납니다.
    if(tag[i]==1 && tag[i+5]==1 && tag[i+10]==1 && tag[i+15]==1 && tag[i+20]==1)
    {
     bingo=TRUE;
     break;
    }
   }

   // 대각선 검사
   // 대각선은 2가지 경우밖에 없으므로 2가지를 각각 직접 확인합니다.
   if(tag[0]==1 && tag[6]==1 && tag[12]==1 && tag[18]==1 && tag[24]==1)
    bingo=TRUE;
   if(tag[4]==1 && tag[8]==1 && tag[12]==1 && tag[16]==1 && tag[20]==1)
    bingo=TRUE;
  }

  printf("continue? (예 1, 아니오 2) ");
  scanf("%d",&n);

  switch(n)
  {
  case 1:
   bingo=FALSE;
   break;
  case 2:
   return 0;
  default:
   break;
  }
 }
}
