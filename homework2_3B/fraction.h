

typedef struct fraction
{
    int numerator;
    int denominator;
} fraction;

int min(int a ,int b);

//转至浮点数
float fconvert(fraction fr1);
//约分
void reduction(fraction *new);
//加法
fraction fadd(fraction fr1,fraction fr2);
//减法
fraction fminus(fraction fr1,fraction fr2);
//乘法
fraction fmultip(fraction fr1,fraction fr2);
//除法
fraction fdiv(fraction fr1,fraction fr2);


