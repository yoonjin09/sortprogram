#include <iostream>
#include <stdio.h>
#include <string.h>

#define max 15

using namespace std;


typedef struct{
  int count;
  string content;
} Sort;

void QuickSort(Sort* A[], int start, int end);
void QuickSort4content(Sort* A[], int start, int end);
int Partition(Sort* A[], int start, int end);
int Partition4content(Sort* A[], int start, int end);

int main() {
  FILE *fp;
  fp=fopen("example1.txt","rt");
  char* token;
  char ch[1024];
  Sort* tokenlist[1024];
  Sort* printlist[1024];
  int tokencount=0; //tokenlist가 몇 개있는지 확인
  int confirmtoken=0; //token이 지금 tokenlist에 들어있는지 확인하기 위해 쓰이는 변수
  while (fgets(ch,2048, fp)){
    token=strtok(ch, "-.,[] ");
    
    int alpha=0;
    while(token!= NULL){
      for(int k=0; k<strlen(token); k++){ //소문자를 대문자로 바꾸는 
        if(token[k]>= 'a' && token[k] <= 'z'){ 
          token[k]=token[k]-32;
        }
      }
      if(strlen(token)==1) {
        char K=*token;
        //printf("\nk : %d\n",K-'0');
        alpha=isalpha(K-'0');
        if(K>= 'A' && K<='Z'){
          //printf(" \n이거 : %s\n",token);
          alpha=0;
        }
        else alpha=1;
        //else printf("\n%s",token);
      }
     // int cmp=strcmp(token,"\n");
      //else printf("\n%s",token);
      if(alpha == 0){
        string stringtoken(token);
        for(int a=0; a< tokencount; a++){
          if(tokenlist[a]->content == stringtoken){
            tokenlist[a]->count++;
            printf("\nAgain Debug: %9s %d %d %s",tokenlist[a]->content.c_str(),tokenlist[a]->count,tokencount, token);
          }
          else confirmtoken++;          
        }

        if(confirmtoken == tokencount){
          tokenlist[tokencount]=(Sort*)malloc(sizeof(Sort));
          tokenlist[tokencount]->count=1;
          tokenlist[tokencount]->content=token;
          printf("\nNew22 Debug: %9s %d %d %s",tokenlist[tokencount]->content.c_str(),tokenlist[tokencount]->count,tokencount, token);
          tokencount++;
        }
        confirmtoken=0;
      }
      alpha=0;
      token=strtok(NULL,"-,.[] ");
    }
  }

  QuickSort(tokenlist, 0, tokencount-1);

  printf("\n~~~~~~~~~~\n");
  for(int b=0; b<tokencount;b++){
    printf("%s %d\n",tokenlist[b]->content.c_str(),tokenlist[b]->count);
  }
  /*
  int finalcount=tokencount-1;
  for(int c=0; c<5;c++){
    printlist[c]=(Sort*)malloc(sizeof(Sort));
    printlist[c]=tokenlist[finalcount];
    finalcount--;
  }

  printf("\n~~~~~~~~~~\n");
  for(int b=0; b<5;b++){
    printf("%s %d\n",printlist[b]->content.c_str(),printlist[b]->count);
  }
  */

  for(int b=0; b<tokencount-1;b++){
    int sortcontent=0;
    if(tokenlist[b]->count == tokenlist[b+1]->count){
      for(int B=b+1;B<tokencount;B++){
        if( tokenlist[b]->count == tokenlist[B]->count) sortcontent++;
      }
      QuickSort4content(tokenlist, b, b + sortcontent);
    }
  }


   printf("\n~~~~~~~~~~\n");
  for(int b=0; b<5;b++){
    printf("%s %d\n",tokenlist[b]->content.c_str(),tokenlist[b]->count);
  }

  return 0;
}


int Partition(Sort* A[], int start, int end){
  int pivot = A[end]->count; //pivot을 맨 오른쪽으로 둠
  int i;
  int index = start;
  Sort* templist[100];
  templist[0]=(Sort*)malloc(sizeof(Sort));
  //int temp; //swap을 위해서
  
  for(i=start; i<end; i++){
    if(A[i]->count > pivot){
      templist[0] = A[i];
      A[i]= A[index];
      A[index]= templist[0];
      index++;
    }
  }
  
  templist[0] = A[index];
  A[index]= A[end];
  A[end]=templist[0];
  //free(templist[0]);
  return index;
  
}

int Partition4content(Sort* A[], int start, int end){
  char ch[100];
  strcpy(ch,A[end]->content.c_str());

    //pivot을 맨 오른쪽으로 둠
  int i;
  int index = start;
  
  string temp; //swap을 위해서
  
  for(i=start; i<end; i++){
    char ch1[100];
    strcpy(ch1,A[i]->content.c_str());
    int ch1npivot=strcmp(ch1,ch);
    if( ch1npivot<= 0){
      temp = A[i]->content;
      A[i]->content= A[index]->content;
      A[index]->content= temp;
      index++;
    }
  }
  
  temp = A[index]->content;
  A[index]->content= A[end]->content;
  A[end]->content=temp;
  return index;
  
}

void QuickSort(Sort* A[], int start, int end){
    int index;
    if(start<end){
      index = Partition(A, start, end);
      QuickSort(A, start, index -1);
      QuickSort(A, index+1, end);
    }
    else{
      return ;
    }
}

void QuickSort4content(Sort* A[], int start, int end){
    int index;
    if(start<end){
      index = Partition4content(A, start, end);
      QuickSort4content(A, start, index -1);
      QuickSort4content(A, index+1, end);
    }
    else{
      return ;
    }
}
