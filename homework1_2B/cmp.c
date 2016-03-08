int wsum(int* ball,int pos)
{
    int sum=0,i;
    for(i=0; i<pos; i++)
        sum+=ball[i];
    return sum;
}

int cmp1(int * ball)
{
    if(wsum(ball,4)>wsum(ball+4,4))
        return 1;
    else if(wsum(ball,4)<wsum(ball+4,4))
        return 2;
    else
        return 0;
}

int cmp2(int * ball,int big,int small,char mode,int *err)
{
    if(mode)
    {
        if( (wsum(ball+big,3)+*(ball+small) )> ( *(ball+big+3)+3*ball[11]) )
        {
            *err=big;
            return 3;
        }
        else if( (wsum(ball+big,3)+*(ball+small) ) < ( *(ball+big+3)+3*ball[11]) )
        {
            *err=small;
            return 4;
        }
        else
        {
            *err=small+1;
            return 5;
        }
    }
    else
    {
        if(wsum(ball,3)>wsum(ball+8,3))
        {
            *err=8;
            return 0;
        }
        if(wsum(ball,3)<wsum(ball+8,3))
        {
            *err=8;
            return 1;
        }
        else
        {
            *err=11;
            return 2;
        }
    }

}

int cmp3(int * ball,int err,char mode,char w)
{
    if(mode==0)
    {
        if(ball[err]>ball[1])
            return 0;
        else if(ball[err]<ball[1])
            return 5;
        else
            return 1;
    }
    else
    {
        if(ball[err]==ball[err+1])
            return 2;
        else if((ball[err]>ball[err+1]&&w=='l') || (ball[err]<ball[err+1]&&w=='h'))
            return 3;
        else if((ball[err]<ball[err+1]&&w=='l') || (ball[err]>ball[err+1]&&w=='h'))
            return 4;
    }
}

