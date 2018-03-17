#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addmember();//회원 추가 함수
void printall();//모든 회원 출력 함수
void search();//회원 검색 함수
void delete();//회원 삭제 함수
void revise();//회원 정보 수정 함수
void save();//회원 정보 저장 함수
void namearr();//회원 이름순 정렬
typedef struct contact//주소록 구조체 선언
{   char name[20];
   char adress[100];
   char phone[20];
   struct contact *next;//링크드리스트
   struct contact *prev;//링크드리스트
}cont;
struct contact *head=NULL,*tail=NULL;//헤드와 테일 선언 및 초기화
int main(void)
{   char select;
   char selsav;
   FILE *fp;
   cont con;
   fp = fopen("save.txt","a");
   fclose(fp);
   fp = fopen("save.txt","rw");
   if(fp == NULL)
      printf("파일을 열지 못했습니다.\n");
   while(fgetc(fp)!=EOF)//원래 feof 함수를 이용하였으나 에러가 발생하여 fgetc로 글자를 하나 읽어오는 것으로 파일의 끝 판단.
   {
      fseek(fp,-1,SEEK_CUR);//fgetc로 인해 한칸 앞으로간 파일포인터 위치를 다시 뒤로 한칸 당김
      if((fscanf(fp,"%s %s %s",&con.name,&con.adress,&con.phone))==EOF)//변수에 데이터 입력과 동시에 만약 빈내용을 가져올시 바로 while문 탈출.
         break;
      cont* tmp = (cont*)malloc(sizeof(cont));//구조체 포인터 tmp선언후 내용을 담을 수 있게 동적할당함.
      memset(tmp,0,sizeof(con));//포인터 주소 0으로 초기화
      strcpy(tmp->name,con.name);
      strcpy(tmp->adress,con.adress);
      strcpy(tmp->phone,con.phone);//con에 있던 내용 tmp로 복사
      if(head == NULL)
         head = tail = tmp;//head안에 내용이 없을시 head=tail이고 복사된 con값 입력
      else
      {
         tail->next = tmp;//기존 tail의 next에 복사된 con값이 들어감
         tmp->prev = tail;//tmp의 prev에 기존 tail의 값이 들어감
         tail = tmp;//결국 tmp가 tail로 바뀜
      }
      if(fgetc(fp)==EOF) //현재 파일 포인터 위치에서 불러온 값이 EOF일시 종료
         break;
      fseek(fp,-1,SEEK_CUR);//fgetc로 이동된 파일 포인터 제자리로 당겨옴
   }
   fclose(fp);
   while(1)
   {
      printf("                               = 매뉴 =                   \n");
      printf("1. 모든 주소록 정보 출력\n");
      printf("2. 회원 등록\n");
      printf("3. 회원 정보 검색\n");
      printf("4. 회원 정보 수정\n");
      printf("5. 회원 삭제\n");
      printf("6. 프로그램 종료\n");
      printf("============================\n");
      printf("선택할 기능을 입력하세요 :");
      scanf(" %c",&select);//가끔씩 실수로 한글입력시 무한루프가 발생해 'c'로 바꿈으로서 해결
      printf("============================\n");
      fflush(stdin);
      switch(select)
      {
         case '1' : printall();
                  break;
         case '2' : addmember();
                  break;
         case '3' : search();
                  break;
         case '4' : revise();
                  break;
         case '5' : delete();
                  break;       
         case '6' : printf("저장하시겠습니까? (Y/N)");//저장 할것인지 묻고 Y,y누를시 저장 
                  scanf(" %s",&selsav);
                  if(selsav=='y'||selsav=='Y')
                     save();
                  exit(1);
         default : printf("잘못된 입력입니다!\n");
                 fflush(stdin);//scanf 입력버퍼 문제로 버퍼 비우기
                 break;
      }
   }
   return 0;
}void printall()
{   namearr();//우선 정보를 이름순으로 배열
   cont* con;//데이터 받아올 포인터 선언
   con = head;//포인터 주소를 head로 함
   int counter=1;
   if(con == NULL)
      printf("불러올 데이터가 없습니다!\n");
   while(con)
   {
      printf("===========================\n");
      printf("#%d\n",counter++);   
      printf("이름 : %s\n",con->name);
      printf("주소 : %s\n",con->adress);
      printf("번호 : %s\n",con->phone);
      con = con->next;
   }
   return;
}void addmember()
{   cont con;//입력받을 변수 선언
   printf("이름 : ");
   scanf(" %s",con.name);
   printf("주소(공백입력불가) : ");
   scanf(" %s",con.adress);
   printf("전화번호(공백입력불가) : ");
   scanf(" %s",con.phone);
   if(head == NULL)
   {
      head = tail = (cont*)malloc(sizeof(cont));
      memset(head,0,sizeof(cont));//만약 head가 비었을시 동적할당 후 0으로 초기화
   }
   else
   {
      cont *con = malloc(sizeof(cont));//con이라는 포인터 선언과 동시에 동적할당 tail->next에 넣기위함.
      memset(con,0,sizeof(cont));//동적할당 후 초기화
      tail->next = con;//tail다음에 새로운 회원을 추가함
      tail = con;//새로운 회원이 결국 tail이 됨
   }
   strcpy(tail->name,con.name);
   strcpy(tail->adress,con.adress);
   strcpy(tail->phone,con.phone);
   printf("\n추가되었습니다.\n");
   printf("============================\n");
}void search()
{   cont* con = head;
   char name[20];
   int check=0;//검색이 완료 됬는지 체크하기 위함
   printf("찾으실 회원의 이름을 입력하세요 : ");
   scanf(" %s",name);
   while(con)
   {
      if(!strcmp(name,con->name))//strcmp가 같을때 0을 리턴하므로 !strcmp로 while실행
      {
         printf("=====================\n");
         printf("이름 : %s\n",con->name);
         printf("주소 : %s\n",con->adress);
         printf("번호 : %s\n",con->phone);
         check=1;
      }
      con = con->next;
   }
   if(check==0)
      printf("검색결과가 없습니다.\n");
}void revise()
{   char name[20];
   cont *con = head;
   int check=0;//위와 같은 이유
   printf("수정할 회원의 이름을 입력하세요 : ");
   scanf(" %s",name);
   while(con)
   {
      if(!strcmp(name,con->name))
      {
         char adress[100];
         char phone[20];
         printf("이름 : ");
         scanf(" %s",name);
         printf("주소 : ");
         scanf(" %s",adress);
         printf("번호 : ");
         scanf(" %s",phone);
         strcpy(con->name,name);
         strcpy(con->adress,adress);
         strcpy(con->phone,phone);//변경내용을 링크드리스트에 저장
         printf("정보가 수정되었습니다.\n");
         check = 1;
         return;
      }
      con = con->next;
   }
   if(check == 0)
      printf("수정할 대상이 없습니다!\n");
}void delete()
{   char name[20];
   cont *con = head;
   printf("수정할 회원의 이름을 입력하세요 : ");
   scanf(" %s",name);//입력버퍼 문제로 %s앞에 띔
   while(con)
   {
      if(!strcmp(name,con->name))
      {
         if(con == head)
         {
            head=head->next;
            if(head)
               head->prev=NULL;
            else
               tail = NULL;
            printf("삭제되었습니다.");
            return;//만약 지우려는 곳의 위치가 head일시 head의 next가 head가 되고 head에 내용이 있을시 head의 prev는 NULL,헤드에 내용이 없을시 head와 tail이 모두 빈 상태이므로 tail과 head는 모두 NULL
         }
         else if(con == tail)
         {
            tail=tail->prev;
            tail->next=NULL;
            printf("삭제되었습니다.");
            return;
         }//con이 tail일 경우 tail의 prev가 tail이 되고 tail의 next를 NULL로 설정하여 링크드리스트에서 제외된다.
         else
         {
            cont* prev_tmp;
            cont* next_tmp;
            prev_tmp=con->prev;
            next_tmp=con->next;
            prev_tmp->next = next_tmp;
            next_tmp->prev = prev_tmp;
            printf("삭제되었습니다.");
            return;//만약 con이 head와 tail의 사이값일경우 con의 prev의 next는 con의 next가 되고 con의 next의 prev는 con의 prev가되어 con이 링크드리스트에서 제외된다.
         }
      }
      con=con->next;
   }
   printf("삭제 대상이 없습니다.\n");
}void save()
{   cont *con = head;
   FILE *fp;
   fp = fopen("save.txt","wt");
   namearr();//저장하기전 이름순으로 배열한다.
   while(con)
   {
      fprintf(fp,"%s %s %s \n", con->name,con->adress,con->phone);
      con=con->next;
   }
   printf("저장되었습니다.\n");
   return;//여태까지의 링크드리스트값을 저장한다.
}void namearr()
{   cont *con1,*con2;
   char tmp_name[20];
   char tmp_adress[100];
   char tmp_phone[20];
   for(con1 = head; con1 != NULL; con1=con1->next)//버블정렬을 이용하였다.
   {
      for(con2 = con1; con2 != NULL && con2->next != NULL; con2=con2->next)
         if(strncmp(con2->name,con2->next->name,10)>0)//strcmp는 문자열의 맨앞글자만을 판단하므로 strncmp로 이름전체를 비교한다.
         {
            strcpy(tmp_name,con2->name);
            strcpy(tmp_adress,con2->adress);
            strcpy(tmp_phone,con2->phone);
            strcpy(con2->name,con2 -> next-> name);
            strcpy(con2->adress,con2->next->adress);
            strcpy(con2->phone,con2->next->phone);
            strcpy(con2->next->name,tmp_name);
            strcpy(con2->next->adress,tmp_adress);
            strcpy(con2->next->phone,tmp_phone);
         }
   }
}
