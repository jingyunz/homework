#include <stdio.h>
#include <stdlib.h>
#include "cup.h"

int times=0;

int main()
{
    cup cup1={8,8};
    cup cup2={5,0};
    cup cup3={3,0};

    FILE *output;

    if((output=fopen("output.txt","w"))==NULL)
    {
        printf("error!\n");
        exit(0);
    }

    cmove(&cup1,&cup2);
  //  fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup2,&cup3);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup3,&cup1);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup2,&cup3);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup1,&cup2);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup2,&cup3);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);
    cmove(&cup3,&cup1);
 //   fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\n",cup1.now,cup2.now,cup3.now);

    fprintf(output,"8ml:%d\n5ml:%d\n3ml:%d\ntimes:%d\n",cup1.now,cup2.now,cup3.now,times);
    fclose(output);
    return 0;
}
