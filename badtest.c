#include <stdio.h>
#include <strings.h>
int main()
{
    FILE* fin=fopen("decodeME.txt","r");
    //
    char ch;
    int n=0;
    int numbytes;
    //
    int num=28;
    int check;
    int temp;
    char symb;
    int pos=1;
    //
    char arr[10101];
    int j;
    for(j=0;j<num;j++)
    {
        fread(&symb, sizeof(char), 1, fin);
        while(1)
        {
          check=fread(&temp, sizeof(char), 1, fin);
          if( temp=='\n') break;
          if(temp==1)
          {
        pos= 2*pos+1;
          }
          else
          {
        pos=2*pos;
          }
        }
        arr[pos]=symb;
        pos=1;
    }
fclose(fin);
printf("\n");
return 0;
}