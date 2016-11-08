#include "interpreter.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;
void init(){
	/*����ָ������*/
	strcpy(&(mnemonic[LIT][0]),"LIT");
	strcpy(&(mnemonic[LOD][0]),"LOD");
	strcpy(&(mnemonic[STO][0]),"STO");
	strcpy(&(mnemonic[CAL][0]),"CAL");
	strcpy(&(mnemonic[INT][0]),"INT");
	strcpy(&(mnemonic[JMP][0]),"JMP");
	strcpy(&(mnemonic[JPC][0]),"JPC");
	strcpy(&(mnemonic[ADD][0]),"ADD");
	strcpy(&(mnemonic[SUB][0]),"SUB");
	strcpy(&(mnemonic[MUL][0]),"MUL");
	strcpy(&(mnemonic[DIV][0]),"DIV");
	strcpy(&(mnemonic[RED][0]),"RED");
	strcpy(&(mnemonic[WRT][0]),"WRT");
	strcpy(&(mnemonic[RET][0]),"RET");
}

//���ͳ��򲿷�
int base(int l,int b)
{
	int b1;
	b1=b;
	return b1;
}
//����Ŀ�����
void interpret()
{
	int p,b,t;
	struct instruction i;//ָ��
	int s[stacksize];//ջʽ������
	t=0;//ջ���Ĵ���
	b=0;//��ַ��ַ
	p=0;//ָ����һ��ִ�е�Ŀ�����ĵ�ַ
	s[0]=s[1]=s[2]=0;//������̬������̬�������ص�ַ����Ϊ��
	do
	{
		i=code[p];
		p++;
		switch(i.f)
		{
		case LIT://������ֵȡ��ջ����aΪ����ֵ
			s[t]=i.a;
			t++;
			break;
		case LOD: //������ֵȡ��ջ����aΪ��Ե�ַ��tΪ����           
			s[t]=s[base(i.l,b)+i.a];
			t++;
			break;
		case STO:    //��ջ����������ĳ������Ԫ�У�aΪ��Ե�ַ��tΪ����   
			t--;
			s[base(i.l,b)+i.a]=s[t];
			break;
		case CAL:                  //���ú�����aΪ������ַ
			s[t]=base(i.l,b);        //��ǰ��ַ��ջ
			s[t+1]=b;                  //�����̻�ַ��ջ  DL    (��s[t]һ��)
			s[t+2]=p;                  //��ǰָ���ַ��ջ RA(���ص�ַ)  ���жϳ����Ƿ����ʱ������
			b=t;            //�»�ַ
			p=i.a;
			
			break;
		case INT: //������ջ��Ϊ�����õĹ��̿���a����Ԫ��������
			t=t+i.a;
			break;
		case JMP://��������ת��a��ַ
			p=i.a;
			break;
		case JPC://������ת����ջ��ֵΪ0������ת��a��ַ������˳��ִ��
			t--;
			if(s[t]==0)
			{
				p=i.a;
			}
			break;
		case ADD://��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ
			t--;
			s[t-1]=s[t-1]+s[t];
			break;
		case SUB://��ջ����ȥջ����������ջԪ�أ����ֵ��ջ
			t--;
			s[t-1]=s[t-1]-s[t];
			break;
		case MUL://��ջ������ջ����������ջԪ�أ����ֵ��ջ
			t--;
			s[t-1]=s[t-1]*s[t];
			break;
		case DIV://��ջ������ջ����������ջԪ�أ����ֵ��ջ
			t--;
			if(s[t-1]!=0)
				s[t-1]=s[t-1]/s[t];
			else
				cout<<"input error"<<endl;
			break;
		case RED://�������ж���һ����������ջ��

			cout<<"input:";
			cin>>s[t];
			t++;
			break;
		case WRT://ջ��ֵ�������Ļ������
			cout<<"result:"<<s[t-1]<<endl;  
			fprintf(fa2,"%d\n",s[t-1]);
			t--;
			break;
		case RET://�������ý�����,���ص��õ㲢��ջ
			t=b;     
			p=s[t+2];       //��t�ҵ����ú���ǰ��pֵ     Ҫ���صĵ�ַΪ0ʱ�������
			b=s[t+1];
			break;
		}
	}while(p!=0);
}
//Ŀ��������ִ�У�����
void translate(char *s2,int ll,int aa,int i)  //�����ȡ���ı�����
{
	if(strcmp(s2,"LIT")==0)
	{
		code[i].f=(fct)0;
	}
	else if(strcmp(s2,"LOD")==0)
	{
		code[i].f=(fct)1;
	}
	else if(strcmp(s2,"STO")==0)
	{
		code[i].f=(fct)2;
	}
	else if(strcmp(s2,"CAL")==0)
	{
		code[i].f=(fct)3;
	}
	else if(strcmp(s2,"INT")==0)
	{
		code[i].f=(fct)4;
	}
	else if(strcmp(s2,"JMP")==0)
	{
		code[i].f=(fct)5;
	}
	else if(strcmp(s2,"JPC")==0)
	{
		code[i].f=(fct)6;
	}
	else if(strcmp(s2,"ADD")==0)
	{
		code[i].f=(fct)7;
	}
	else if(strcmp(s2,"SUB")==0)
	{
		code[i].f=(fct)8;
	}
	else if(strcmp(s2,"MUL")==0)
	{
		code[i].f=(fct)9;
	}
	else if(strcmp(s2,"DIV")==0)
	{
		code[i].f=(fct)10;
	}
	else if(strcmp(s2,"RED")==0)
	{
		code[i].f=(fct)11;
	}
	else if(strcmp(s2,"WRT")==0)
	{
		code[i].f=(fct)12;
	}
	else if(strcmp(s2,"RET")==0)
	{
		code[i].f=(fct)13;
	}
	code[i].l=ll;
	code[i].a=aa;
}

//����ִ��
void intercall()
{
	cout<<"c0Ŀ��������ִ�У�"<<endl;
	ifstream in("fa.tmp",ios::in);//�����ļ���
	if(!in)//����ļ������ڣ����ӡ����
	{
		cerr<<"file could not be open";
		return;
	}
	//S2��ָ������
	char s1[10],s2[10];
	//ll����ǲ���
	int ll,aa;
	int i=0;     //��ǰָ��ִ�е����
	while(in>>s1>>s2>>ll>>aa)//���ı�����code����
	{
		translate(s2,ll,aa,i);
		i++;
	}
	interpret();
}
void main(){
				fa2=fopen("fa2.tmp","w");	//�Ƚ�fa2.tmp�ļ�תΪ��״̬
				intercall();    //���ý��ͳ���
			    fclose(fa2);	//�ر�fa2.tmp�ļ�	
}