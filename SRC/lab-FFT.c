#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>

 
#define pi 3.141593 // floatС�����6λ
#define NL 256  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=N
    int N=NL;   //FFT����
float Input[NL];//������ź�����
/*
float h[33] = {
   0.000744808099883,0.0008898861356028,-0.002727390076489, 0.002920995444386,
  0.0009645511494193,-0.008002287495031,  0.01133584612049,-0.002751488761016,
   -0.01688113961025,   0.0316509088309, -0.01948352023097, -0.02634617068536,
    0.07974565309008, -0.08470853564896, -0.03245044438095,   0.5650983280183,
     0.5650983280183, -0.03245044438095, -0.08470853564896,  0.07974565309008,
   -0.02634617068536, -0.01948352023097,   0.0316509088309, -0.01688113961025,
  -0.002751488761016,  0.01133584612049,-0.008002287495031,0.0009645511494193,
   0.002920995444386,-0.002727390076489,0.0008898861356028, 0.000744808099883
}; 

float h[32]=
{
  
         0  , -0.00009  ,  0.00042  ,  0.00108  , -0.00224  , -0.00413  ,  0.00704  ,  0.01135,



   -0.01756  , -0.02634  ,  0.03871  ,  0.05650  , -0.08349  , -0.12957  ,  0.23113  ,  0.71720,


    0.71720   , 0.23113  , -0.12957  , -0.08349  ,  0.05650   , 0.03871  , -0.02634  , -0.01756,

  

    0.01135   , 0.00704  , -0.00413  , -0.00224  ,  0.00108   , 0.00042  , -0.00009    ,     0

};  */

//Uint16  SampleTable[NL];
struct Complex		// ���帴���ṹ��
{
   float real,imag;
};
struct Complex Wn;//������ת����
struct Complex Vn;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
struct Complex T;//�����ת������X(k+B)�ĳ˻�

//float Realin[NL]={0};// ���������ʵ��
float output[NL]={0};// �����FFT��ֵ��������ģ��
struct Complex Sample[NL];// ���������ʵ��ת��Ϊ����

struct Complex MUL(struct Complex a,struct Complex b)//���帴��
{
   struct Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

void MYFFT(struct Complex *xin,int N)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   int M=1,Nn=0;// N=2^M
   float B=0; // �����������������ݼ��
   /* ������Ϊ�����½��ľֲ�����*/
   int LH=0,J2=0,N1=0,I,K2=0;
   struct Complex T;
   /*�����ǵ���*/
   LH=N/2; // LH=N/2
   J2=LH;
   N1=N-2;
   for(I=1;I<=N1;I++)
    {
     if(I<J2)
	 {
       T=xin[I];
       xin[I]=xin[J2];
       xin[J2]=T;
	 }
	 K2=LH;
	 while(J2>=K2)
	  {
        J2-=K2;
        K2=K2/2;// K2=K2/2
	  }
	  J2+=K2;
    }	    
   /* ����Ϊ�����M */
   Nn=N;
   while(Nn!=2)// �����N����2Ϊ��������M
   {
     M++;
	 Nn=Nn/2;
   }

   /* �������� */
   for(L=1;L<=M;L++)  // ����
	{
	  B=pow(2,(L-1));
      Vn.real=1;
	  Vn.imag=0;
      Wn.real=cos(pi/B);
      Wn.imag=-sin(pi/B);
	  for(J=0;J<B;J++)   // ����
	   {        
		 for(K=J;K<N;K+=2*B)  // ������������
		  {
            KB=K+B;
            T=MUL(xin[KB],Vn);
            xin[KB].real=xin[K].real-T.real;//ԭַ���㣬�����������ԭ����������
            xin[KB].imag=xin[K].imag-T.imag;
             xin[K].real=xin[K].real+T.real;
             xin[K].imag=xin[K].imag+T.imag;      
		  }
		  Vn=MUL(Wn,Vn);// ��ת�����������൱��ָ����ӣ��õ��Ľ��
		  // ��J*2^��M-L����һ���ģ���Ϊ�ڵ�����������
		 // ����M��L���ǲ���ģ�Ψһ��x�����Ǽ��ڵ�J
		 // ����J����1Ϊ�����ģ���J*W��Ч��W+W+W...J��W���
		}
	 }
}


/*
void FilterDC(struct Complex *ADC,int N)//ȥ�������е�ֱ���ɷ֣�����ֱ���������ܴ�
{
   int i;
   float sum=0;
   for(i=0;i<N;i++)
    { sum+=ADC[i].real;}
   sum=sum/N;
   for(i=0;i<N;i++)
    { ADC[i].real-=sum;}
}*/

/********************************
���ܣ����㸴����ģ
�βΣ�*Sampleָ����Ҫȡģ�ĸ����ṹ��
      NΪȡģ����
	  *output���ȡģ����ֵ������
*********************************/
void ModelComplex(struct Complex *Sample,int N,float *output)
{
   int i;
   for(i=0;i<N;i++)
    {
     output[i]=sqrt(Sample[i].real*Sample[i].real+Sample[i].imag*Sample[i].imag)*2/N;
	}
}

void main(void)
{
   Uint16 i=0;
   InitSysCtrl();
 //  InitXintf16Gpio();
 // InitAdc();
   
   DINT;
   InitPieCtrl();
   IER = 0x0000;
   IFR = 0x0000;
    for(i=0;i<NL;i++) //����һ������г�����Ӷ��ɵķ���
     { 
      Input[i]=sin(2*pi*5*i/(NL-1))+sin(2*pi*i*5*3/(NL-1))/3+sin(2*pi*i*5*5/(NL-1))/5;
	 }
	 for(i=0;i<NL;i++)   //����ʵ���ź�ת��Ϊ����
	  {
         Sample[i].real=Input[i];
		//  Sample[i].real=h[i];
		 Sample[i].imag=0;
	  }
	 MYFFT(Sample,NL);                //FFT
     ModelComplex(Sample,NL,output);  //��ģ
	while(1)
   {       
   //  FilterDC(Sample,NL);
   }
}


//===========================================================================
// No more.
//===========================================================================
