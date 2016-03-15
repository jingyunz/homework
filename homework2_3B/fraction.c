#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

int min(int a ,int b)
{
    if(a>b)
        return b;
    else
        return a;
}

//约分
float fconvert(fraction fr1)
{
    return (1.0/fr1.denominator)*fr1.numerator;
}


void reduction(fraction *new)
{
    int i,minnum=min((*new).denominator,(*new).numerator);
    for(i=2; i<minnum; i++)
    {
        while((*new).denominator%i==0 && (*new).numerator%i==0)
        {
            (*new).denominator=(*new).denominator/i;
            (*new).numerator=(*new).numerator/i;
            minnum=minnum/i;
        }
    }

}

//加法
fraction fadd(fraction fr1,fraction fr2)
{
    fraction new;
    new.denominator=fr1.denominator*fr2.denominator;
    new.numerator=fr1.denominator*fr2.numerator+fr2.denominator*fr1.numerator;
    reduction(&new);
    return new;
}
//减法
fraction fminus(fraction fr1,fraction fr2)
{
    fraction new;
    new.denominator=fr1.denominator*fr2.denominator;
    new.numerator=fr2.denominator*fr1.numerator-fr1.denominator*fr2.numerator;
    reduction(&new);
    return new;
}
//乘法
fraction fmultip(fraction fr1,fraction fr2)
{
    fraction new;
    new.denominator=fr1.denominator*fr2.denominator;
    new.numerator=fr1.numerator*fr2.numerator;
    reduction(&new);
    return new;
}
//除法
fraction fdiv(fraction fr1,fraction fr2)
{
    fraction new;
    new.denominator=fr1.denominator*fr2.numerator;
    new.numerator=fr1.numerator*fr2.denominator;
    reduction(&new);
    return new;
}

