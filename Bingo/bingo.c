#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 50 // �����ǿ� �� �� �ִ� ���� �� ���� ū �����Դϴ�.
#define TRUE 1
#define FALSE 0

int main()
{
 int number[MAXNUM][2];
 // �����ǿ� ������ ���ڵ��� ������ �迭�Դϴ�.
 // number[][0]���� 1~MAXNUM�� ���ڰ� ����ǰ�
 // number[][1]���� number[][0]�� ���ڸ� �����ǿ� �質 �Ƚ質 ���θ� ��Ÿ���ϴ�.
 // number[][1]�� TRUE�̸� �����ǿ� ���� ���̰�, FALSE�̸� ���� ������ ���� ���Դϴ�.
 int board[5][5];
 // 5x5 ������
 int tag[25];
 // �������� �� 25ĭ�� ���� ���ڵ��� ���ÿ��θ� ��Ÿ���ϴ�.
 // ����ڰ� ������ ĭ�� TRUE, �׷��� ���� ĭ�� FALSE�� ��Ÿ���ϴ�.
 int n;
 int i,j;
 int bingo=FALSE;
 // ���� �ϼ��Ǿ��� ���θ� ��Ÿ���ϴ�.
 // TRUE�� �ϼ�, FALSE�� �̿ϼ��Դϴ�.

 srand(time(NULL));
 // ���� �߻� �ʱ�ȭ

 // 1~MAXNUM�� ���ڸ� �����մϴ�.
 for(i=0;i<MAXNUM;i++)
 {
  number[i][0]=i+1;
 }

 // �������
 while(!bingo)
 {  
  // ��� ĭ�� ���� �������� ���� ���·� �ʱ�ȭ
  for(i=0;i<25;i++)
  {
   tag[i]=FALSE;
  }

  // ��� ���ڸ� ���� �����ǿ� ���� ���� ���·� �ʱ�ȭ
  for(i=0;i<MAXNUM;i++)
  {
   number[i][1]=FALSE;
  }

  // �������� ����ϴ�
  for(i=0;i<5;i++)
  {
   for(j=0;j<5;j++)
   {
    do
    {
     // 1~MAXNUM������ ���ڸ� �̽��ϴ�.
     n=rand()%MAXNUM;
    }while(number[n][1]==TRUE);
    // �̹� �����ǿ� �����ϴ� ���ڸ� ���� ��� �ٽ� �̽��ϴ�.

    // ���� ���ڸ� �����ǿ� ���ϴ�.
    board[i][j]=number[n][0];
    // �� ���ڰ� �����ǿ� ���� ���� ǥ���մϴ�.
    number[n][1]=TRUE;
   }
  }

  while(1)
  {
   // ȭ�� Ŭ����
   system("cls");
   // �������� ����մϴ�.
   for(i=0;i<5;i++)
   {
    for(j=0;j<5;j++)
    {
     // ������ ���ڴ� ������ ���� ǥ���մϴ�.
     if(tag[i*5+j]==1)
      printf(" (%2d)",board[i][j]);
     // ���� �������� ���� ���ڴ� �׳� ����մϴ�.
     else
      printf("%5d",board[i][j]);
    }
    printf("\n");
   }

   // ���� �ϼ��Ǹ� ������ �����մϴ�.
   if(bingo)
   {
    printf("\nBINGO!!!\n");
    break;
   }

   printf("\n���ڸ� �Է��ϼ���: ");
   scanf("%d",&n);

   // -1�� �ԷµǸ� ���α׷��� �����մϴ�.
   if(n==-1) return 0;

   // ������ ����� ���ڸ� �Է¹����� �ٽ� �Է��ϰ� �մϴ�.
   if(n<1 || n>MAXNUM)
   {
    printf("1~%d ������ ���ڸ� �Է��ϼ���.\n",MAXNUM);
    system("pause");
    continue;
   }

   // �Է¹��� ���ڸ� �����ǿ��� ã���ϴ�.
   for(i=0;i<25;i++)
   {
    if(board[i/5][i%5]==n)
    {
     // i��° ĭ�� ���ڰ� ������ ǥ���մϴ�.
     tag[i]=TRUE;
     // ���ڸ� ã���� �� �̻� Ž������ �ʽ��ϴ�.
     break;
    }
   }
   // ���� �������� ������ Ž���Ͽ��µ� ���ڸ� �߰����� ���ϸ� �ٽ� ���ڸ� �Է¹޽��ϴ�.
   if(i==25)
   {
    printf("%d�� �����ǿ� ���� �����Դϴ�.\n",n);
    system("pause");
    continue;
   }

   // ���� �ϼ��Ǿ����� �˻��մϴ�.
   for(i=0;i<5;i++)
   {
    // ���� �˻�
    // ������ ��� �� ĭ�� index�� 1�� ���̰� ���ϴ�.
    if(tag[i*5]==1 && tag[i*5+1]==1 && tag[i*5+2]==1 && tag[i*5+3]==1 && tag[i*5+4]==1)
    {
     bingo=TRUE;
     // �ϼ��� ���� ã���� ǥ���ϰ� Ž���� �����մϴ�.
     break;
    }

    // ���� �˻�
    // ������ ��� �� ĭ�� index�� 5�� ���̳��ϴ�.
    if(tag[i]==1 && tag[i+5]==1 && tag[i+10]==1 && tag[i+15]==1 && tag[i+20]==1)
    {
     bingo=TRUE;
     break;
    }
   }

   // �밢�� �˻�
   // �밢���� 2���� ���ۿ� �����Ƿ� 2������ ���� ���� Ȯ���մϴ�.
   if(tag[0]==1 && tag[6]==1 && tag[12]==1 && tag[18]==1 && tag[24]==1)
    bingo=TRUE;
   if(tag[4]==1 && tag[8]==1 && tag[12]==1 && tag[16]==1 && tag[20]==1)
    bingo=TRUE;
  }

  printf("continue? (�� 1, �ƴϿ� 2) ");
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
