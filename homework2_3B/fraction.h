

typedef struct fraction
{
    int numerator;
    int denominator;
} fraction;

int min(int a ,int b);

//ת��������
float fconvert(fraction fr1);
//Լ��
void reduction(fraction *new);
//�ӷ�
fraction fadd(fraction fr1,fraction fr2);
//����
fraction fminus(fraction fr1,fraction fr2);
//�˷�
fraction fmultip(fraction fr1,fraction fr2);
//����
fraction fdiv(fraction fr1,fraction fr2);


