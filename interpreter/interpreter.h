#include<iostream>
#include<fstream>
#include<stdio.h>

struct instruction
{
	enum fct f;
	int l;//����
	int a;//��ַ
};
#define norw 8      //�ؼ��ֵĸ���  word����
#define al 10
#define txmax 100    //���ֱ�����
#define nmax 14
#define cxmax 200
#define levmax 3
#define amax 2047   //��ַ�Ͻ�
#define stacksize 500

//ö�����ͣ�ö�ٱ����г������п��ܳ��ֵ�ֵ
enum fct
{
	LIT,  LOD,  STO,
	CAL,  INT,  JMP,
	JPC,  ADD,  SUB,
	MUL,  DIV,  RED,
	WRT,  RET,
};
//������ָ�����Ƶĵ�һλ
#define fctnum 14
//ָ������
instruction code[100];
char mnemonic[fctnum][5];   //���������ָ������
//���ָ������tmp�ļ�
FILE *fa;
//�����д��fa2.tmp�ļ���
FILE *fa2;

//����Ŀ�����
void interpret();   
//���ͳ��򲿷�
int base(int l,int b);
//Ŀ��������ִ�У�����
void translate(char *s2,int ll,int aa,int i); 
//����ִ��
void intercall();