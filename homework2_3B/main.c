#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

int main()
{
    FILE *input,*output;
    fraction fr1,fr2,result;
    float resultf1,resultf2;
    if( (input=fopen("input.txt","r"))==NULL || (output=fopen("output.txt","w"))==NULL )
    {
        printf("error!\n");
        exit(0);
    }
    fscanf(input,"%d/%d %d/%d",&fr1.numerator,&fr1.denominator,&fr2.numerator,&fr2.denominator);
    fclose(input);

    resultf1=fconvert(fr1);
    resultf2=fconvert(fr2);
    fprintf(output,"�����������%f %f\n",resultf1,resultf2);
    result=fdiv(fr1,fr2);
    fprintf(output,"���������%d/%d\n",result.numerator,result.denominator);
    result=fmultip(fr1,fr2);
    fprintf(output,"�˷������%d/%d\n",result.numerator,result.denominator);
    result=fminus(fr1,fr2);
    fprintf(output,"���������%d/%d\n",result.numerator,result.denominator);
    result=fadd(fr1,fr2);
    fprintf(output,"�ӷ������%d/%d\n",result.numerator,result.denominator);

    fclose(output);
    return 0;
}
