#include <stdio.h>
#include "cmp.h"


int main()
{
    int ball[12],cmp2_result,cmp3_result,diff=12,err,i;
    char w=' ';
    FILE *fin=fopen("input.txt","r");
    FILE *fout=fopen("output.txt","w");
    for(i=0; i<12; i++)
    ball[i]=fgetc(fin);
    fclose(fin);
        switch(cmp1(ball))
        {
        case 0:
            cmp2_result=cmp2(ball,0,0,0,&err);
            break;
        case 1:
            cmp2_result=cmp2(ball,0,4,1,&err);
            break;
        case 2:
            cmp2_result=cmp2(ball,4,0,1,&err);
            break;
        default:
            break;
        }

        switch(cmp2_result)
        {
        case 0:
            w='l';
            cmp3_result=cmp3(ball,err,1,w);
            break;
        case 1:
            w='h';
            cmp3_result=cmp3(ball,err,1,w);
            break;
        case 2:
            cmp3_result=cmp3(ball,err,0,w);
            break;
        case 3:
            w='h';
            cmp3_result=cmp3(ball,err,1,w);
            break;
        case 4:
            cmp3_result=cmp3(ball,err,0,w);
            break;
        case 5:
            w='l';
            cmp3_result=cmp3(ball,err,1,w);
            break;
        default:
            break;
        }

        switch(cmp3_result)
        {
        case 0:
            diff=11;
            w='h';
            break;
        case 1:
            if(err)
                diff=3;
            else
                diff=7;
            w='h';
            break;
        case 2:
            diff=err+2;
            break;
        case 3:
            diff=err+1;
            break;
        case 4:
            diff=err;
            break;
        case 5:
            diff=err;
            w='l';
            break;
        default:
            break;
        }

       fputs("the error ball is:",fout);
       fprintf(fout,"%d\n",(diff+1));
       fputs("It is ",fout);
        if(w=='h')
               fputs("heavy\n",fout);
        else
               fputs("light\n",fout);
    fclose(fout);
    return 0;
}
