#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"

#pragma comment(lib,"winio.lib")
using namespace std;


int creat_DO(int (&DO_bit)[6])
{
	int temp=0;
  	int i=0;
  	for(i=5;i>0;i--)
   	{
    	temp=(temp+DO_bit[i])*2;
   	}
  	return temp+DO_bit[0];
  }

int creat_DI(int (&DI_bit)[6], int num)
{
  	int i=0;
  	for(i=0;i<6;i++)
   	DI_bit[i]=(num>>i)&0x0001;
  	return 0;
}

void main(void)

{
	unsigned short BASE_ADDRESS = 0xE880;
	int OPort=16;
	int iPort=16;
	


// 初始化WinIO 
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}
//数字量输出

	char c;
	int shutdown= 0;
	int DO_data;
	int DO[6]={0};
	int tmp[6]={0};
	int sounds[7] = {523, 587, 659, 698, 784, 880, 988};

	int i;
	int a;
	int b;
	int d=300;
	int DI_data;
	int DI[6]={0};

	int cnt=0;
	int tmpcnt = cnt;
	int maxcnt = 3;

   while(1)
   {
	   
	   
	DI_data = _inp(BASE_ADDRESS + iPort);
  	creat_DI(DI,DI_data);
  	Sleep(100);
	if (kbhit()){
		c = getch();
		if (c=='\n') {
			for(i=0;i<6;i++) {
				DO[i] = 0;
			}
		}
		shutdown = 1;
	}
	else{
		int mode =0;
		if (DI[5] == 0) mode = 0;
		else if (DI[4] == 0) mode = 1;
		else if (DI[3] == 0) mode = 2;
		tmp[5] = DI[5];
		tmp[4] = DI[4];
		tmp[4] = DI[4];
		
	   if(mode == 0)
		   for (a=0;a<=5;a++)
			{
				DO[a]=1;
				DO_data=creat_DO(DO);
         		_outp(BASE_ADDRESS + OPort, DO_data);
				Beep(sounds[a], d);
				DO[a]=0;
			}
		if(mode == 1)
		   for (a=-2;a<=6;a++)
			{
			   DO[a]=1;
			   DO[a+1]=1;
			   DO[a+2]=1;
			   DO_data=creat_DO(DO);
         		_outp(BASE_ADDRESS + OPort, DO_data);
				switch (a) {
				case -2: 	Beep(sounds[0], d); break;
				case -1:    Beep(sounds[0], d); break;
				case 0: Beep(sounds[1], d); break;
				case 1: Beep(sounds[1], d); break;
				case 2:Beep(sounds[2], d); break;
				case 3:Beep(sounds[2], d); break;
				case 4:Beep(sounds[3], d); break;
				case 5:Beep(sounds[3], d); break;
				case 6:Beep(sounds[4], d); break;
				}
				DO[a]=0;
				DO[a+1]=0;
				DO[a+2]=0;
				Sleep(20);
		   }
		if(mode == 2)
		   for (a=0,b=5;a<=2;a++,b--)
			{
			   DO[a]=1;
			   DO[b]=1;
			   DO_data=creat_DO(DO);
         		_outp(BASE_ADDRESS + OPort, DO_data);
				Beep(sounds[6-a], d);
				DO[a]=0;
				DO[b]=0;
				//Sleep(d);
		   }
		   
	}	
  	DO_data=creat_DO(DO);
  	_outp(BASE_ADDRESS + OPort, DO_data);
	if (tmpcnt != cnt){

		cout<<cnt<<endl;	
		tmpcnt = cnt;
	}
	if (shutdown) break;
   }
	_outp(BASE_ADDRESS + OPort, 0);
    ShutdownWinIo();													//关闭WinIO

}