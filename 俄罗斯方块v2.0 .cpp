//����˹����v2.0-21��-2020210557-�����
//v1.0��j��ʼ��Ϸ���������ƶ�������ת 
/*************************** 
  v1.5Ԥ��Ҫ���ӣ�������� v ��ʾ�� 
	��N��Ԥ��          v(N=1) 
	����Ԥ��           v
	�ո�˲������       v 
****************************/
/*************************** 
  v2.0Ԥ��Ҫ����(������� v ��ʾ) 
    ���ˢ����7��Ϊһ��������� 
	  ����newBlock(int u) 
	��ʼ��������
	  ��ʼ�����ѡ����Ϸģʽ�����
	  �����������ѡģʽ����Ҫ��work����ģ� 
    ��ѡ���˫��ģʽ                              v
      ���ĺ���Ϊ���α��ڴ�������Ϸ(u��ʾ�ڼ�����Ϸ)
      (�߸��ı��õ�����֤������ȷ��)
        now_k[3]...                               v
		final_y[3];                               v
		M[3][Maxx+3][Maxy+3];                     v
		newcube[3][10];                           v
		map_x[3],map_y[3];                        v
		newBlock(int u);                          v
		check(int u,int op);                      v
		move(int u,int op);                       v
		get_final_y(int u);                       v
		clean(int u);                             v
		Draw(int u,int X,int Y);                  v
		is_over(int u);                           v
		GG(int u,int X,int y);                    
		place(int u,int k,int d,int x,int y);     v
	  ����work������֧��˫��                      v
****************************/
/********���Դ���*********** 
void HideCursor(int n) 
{ 
    CONSOLE_CURSOR_INFO curso
	r_info={1,n};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
} //n default 0


void GotoXy(int x,int y)  //������Ƶ���x��y��
{
    HANDLE hout;
    COORD coord;
    coord.X=x;
    coord.Y=y;
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord);
}

���Դ��룬�����maxx = 189, maxy = 50
int i;
for(i=0;i<=188;i++)
{
  GotoXy(i,10);
  cout<<1;
}
cout<<i;

void color(int x)  
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
1 FOREGROUND_BLUE        ��ʾ����ǰ��ɫΪ��ɫ����������ɫΪ��ɫ��
2  FOREGROUND_GREEN      ��ʾ����ǰ��ɫΪ��ɫ����������ɫΪ��ɫ��
4  FOREGROUND_RED        ��ʾ����ǰ��ɫΪ��ɫ����������ɫΪ��ɫ��
8  FOREGROUND_INTENSITY  ��ʾ����ǰ��ɫΪ������ʾ��
16 BACKGROUND_BLUE       ��ʾ���ñ���ɫΪ��ɫ��
32 BACKGROUND_GREEN      ��ʾ���ñ���ɫΪ��ɫ��
64 BACKGROUND_RED        ��ʾ���ñ���ɫΪ��ɫ��
128 BACKGROUND_INTENSITY ��ʾ���ñ���ɫΪ������ʾ��

getch() // �޻��ԵĶ�ȡ������Ϣ 
getche() // �л��ԵĶ�ȡ������Ϣ
  while(1)  //���Լ�ֵ����ĸΪascll�� �������Ϊ 224 �� ��72 ��80 ��75 ��77 
  {
    int a,op;
    a = getch();
    op = getch();
    cout<<a<<" "<<op<<endl;
  }

bool _kbhit() // �а������·���1, ����������
_sleep(t)  // ����ֹͣt���� 
 
  for(int j=1;j<=Maxy;j++,cout<<endl)  //���Ե�ͼ
    for(int i=1;i<=Maxx;i++)
	  cout<<M[i][j]; 

  for(int k=1;k<=7;k++)  //�������ֿ��ĸ����� 
    for(int d=0;d<=3;d++)
    {
      color(0x0f);
      GotoXy(0,0);
      cout<<"K = "<<k<<"  d = "<<d<<endl;
      place(k,d,5,5);
      Draw();
      _sleep(1000);
	}
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdlib.h> 
#include <windows.h>
#include <conio.h>
using namespace std;

//����������u��ʾ�ڼ�����Ϸ��vΪ��ʵ�֣�vvvΪ��ʵ�ֶ���ģʽ 
void HideCursor();                 //���ع��              vvv
void GotoXy(int x,int y);          //������Ƶ���x��y��    vvv
void color(int x);                 //������ɫ              vvv
void get_p_num();                  //����������          vvv
void init();                       //��ʼ��                vvv
void drawBgd(int u);               //������                vvv
void work();                       //��Ϸ��ʼ��            vvv
void newBlock(int u);              //����·���            vvv
int  check(int u,int op);          //���op�����Ƿ�Ϸ�    vvv
void move(int u,int op);           //�����ƶ�����          vvv
void get_final_y(int u);           //��ȡ����Ԥ�����y     vvv
void clean(int u);                 //���к���              vvv
void Draw(int u);                  //֡ˢ��,���Ͻ���X,Y    vvv
//void DrawMap();                  //��ʾ�ײ��ͼ(������)  v
bool is_over(int u);               //�ж���Ϸ����          vvv
void GG(int u,int X,int y);        //��Ϸ��������,(X,Y)          
void place(int u,int k,int d,int x,int y); //������k��     vvv  d������õ���ͼ��(x,y)λ�� 

//��������  
const int Maxx=10,Maxy=20;          //��Ϸ���ĵ�ͼ��С 
int M[5][Maxx+3][Maxy+3];           //Map
int B[8][4][5][5];                  //Blocks ,  
int now_x[5],now_y[5];              //�����ƶ��ķ������Ͻ�x,y����
int now_k[5],now_d[5];              //�����ƶ��ķ������״�ͳ���
int final_y[5];                     //�������յ����
int newcube[5][10];                 //��һ�����飬����Ԥ��
int X[5]={0,30,100},Y[5]={0,0,0};   //��u�ŵ�ͼ�����Ͻ�λ��(Xu,Yu)
int p_num;                          //������� 

int main()
{
  get_p_num();
  init();
  work();
  return 0;
}

void get_p_num()
{
  cout<<"ѡ��������j(Ӣ��Сд)��ʼ������"<<endl;
  cout<<"P1 wasd �ո����ٽ�"<<endl;
  cout<<"P2 �������� 0���ٽ�"<<endl; 
  cout<<"һ��Ҫȫ��������������������������"<<endl;
  cout<<"��ϣ��������Ϸ(1/2)��";
  do
  {
  	cin>>p_num;
  }while(p_num<1 || p_num>2);
} 

void init()
{
  //������ַ����0���� 
  B[1][0][2][2] = B[1][0][1][2] = B[1][0][2][1] = B[1][0][3][2] = 255; //T ��ɫ 
  B[2][0][2][2] = B[2][0][3][3] = B[2][0][2][3] = B[2][0][2][1] = 239; //L ��ɫ 
  B[3][0][2][2] = B[3][0][1][3] = B[3][0][2][3] = B[3][0][2][1] = 223; //J ��ɫ 
  B[4][0][2][2] = B[4][0][1][1] = B[4][0][2][1] = B[4][0][3][2] = 207; //Z ��ɫ
  B[5][0][2][2] = B[5][0][2][1] = B[5][0][1][2] = B[5][0][3][1] = 191; //S ��ɫ 
  B[6][0][2][2] = B[6][0][1][2] = B[6][0][3][2] = B[6][0][4][2] = 175; //I ��ɫ 
  B[7][0][2][2] = B[7][0][3][3] = B[7][0][3][2] = B[7][0][2][3] = 159; //O ��ɫ 
  
  //TLJZS��������������
  for(int k=1;k<=5;k++)
    for(int d=1;d<=3;d++)
      for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
        {
          int newi = j, newj = i; //�ȹ���x=y�Գ� 
          newi = 4-newi;  //�ٹ���x=2�Գ�,�����һ������������(2,2)Ϊ������ת 
		  B[k][d][newi][newj] = B[k][d-1][i][j]; 
		  if(k == 1) 
		    B[7][d][i][j] = B[7][d-1][i][j]; //o��ķ�ת 
		}
  
  //I�������������� 
  B[6][1][3][1] = B[6][1][3][2] = B[6][1][3][3] = B[6][1][3][4] = 175; //I
  B[6][2][1][3] = B[6][2][2][3] = B[6][2][3][3] = B[6][2][4][3] = 175; //I
  B[6][3][2][1] = B[6][3][2][2] = B[6][3][2][3] = B[6][3][2][4] = 175; //I

  for(int p=1;p<=p_num;p++)
  {
    for(int i=0;i<=Maxx+1;i++) //���ñ߽�ǽ
      M[p][i][Maxy+1] = 1;  
    for(int j=0;j<=Maxy+1;j++)
      M[p][0][j] = M[p][Maxx+1][j] = 64; //��ɫ 
  }
  
  HideCursor(); //���ع��
  for(int p=1;p<=p_num;p++)
    drawBgd(p); //������
}

void drawBgd(int u)
{
  for(int j=1;j<=Maxy;j++)
  {
  	int i=0;
    GotoXy(X[u],Y[u]+2*j);
    color(0x0f); //��ɫ
	cout<<"||||";
	GotoXy(X[u],Y[u]+2*j+1);
	cout<<"||||";
	GotoXy(X[u]+44,Y[u]+2*j);
	cout<<"||||";
	GotoXy(X[u]+44,Y[u]+2*j+1);
	cout<<"||||";
  }
  
  for(int i=0;i<=Maxx+1;i++)
  {
  	GotoXy(X[u],Y[u]+2*(Maxy+1));
    color(0x0f); //��ɫ
	for(int t=1;t<=12;t++)
	  cout<<"|$$|";
	GotoXy(X[u],Y[u]+2*(Maxy+1)+1);
	for(int t=1;t<=12;t++)
	  cout<<"|$$|";
  }
  
  
  GotoXy(X[u]+50,Y[u]+5);
  cout<<"NEXT:";
  
  color(0x0f); //�ָ�Ĭ����ɫ 
}

void work()
{ 
  while(true)
  {
    if(getch() == 'j') //�������j������Ϸ��ʼ
    {
      for(int p=1;p<=p_num;p++)
      { 
        drawBgd(p); //������
        newBlock(p);
        newBlock(p); //ˢ�µ�һ������
      } 
	  break;
	}
  }
  
  int num = 4; //ÿ��num*15ms��Ȼ����һ��
  int cnt[5] = {4,4,4};//��������ÿ��0��Ȼ����һ��
  while(true)
  { 
  	//��ȡ����
  	int op = -1;
  	if(_kbhit())
  	{
  	  op = getch();
  	  if(op == 224) //����Ƿ���������ڶ�����Ч����
  	    op = getch();
    }
    
	//GotoXy(60,44);
	//cout<<"cnt= "<<cnt;
    //system("pause");
    
    int u; //�ò��������ĵ�ͼ��� 
    if('a'<=op && op<='z' || op==' ') //�������ĸ���������1 
	  u = 1;
	else if(72<=op && op<=80 || op=='0') //����ڷ�������������2 
      u = 2;
	else if(op == -1) //����޲�������˫�������� 
	  u = 3;
	else
	  op = -1; 
    if(p_num == 1)
	  u = 1; 
    
	//�ı��ͼ
	if(op==-1) //���û�������һ��ʱ�䳢����Ȼ����
	{ 
	  for(int p=1;p<=p_num;p++)
	  {
	  	if(cnt[p]>0)
	  	  continue;
	    cnt[p] = num; //���¼���
	    int state = check(p,op);
	  
	    //GotoXy(60,44);
	    //cout<<"cnt= "<<cnt;  ������ʱ
	  
	    if(state == 1) //����ƶ��Ϸ�
	    {
	  	  move(p,op); //�����ƶ��ķ��������ƶ�
	      cnt[p] = num;
	    }
	    else if(state == 2) //���������֧�� 
	    {
	  	  place(p,now_k[p],now_d[p],now_x[p],now_y[p]);//�̶�����
	  	
		  //GotoXy(60,45);
          //cout<<"place "<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y; //����place 
	  	
		  clean(p); //��Ⲣ��������
	  	  if(is_over(p))
	  	  {
	  	    //GG(); //Good game ��Ϸ���� 
		    return; 
		  }
   		  newBlock(p); //ˢ���µķ���
	    }
      }
	}
	if(op != -1) //���������
	{
	  if(op==' ' || op=='0') //����ǿ����½�
	  {
	  	get_final_y(u); //��ȡ����λ�� 
	  	now_y[u] = final_y[u]; //�½� 
	  	place(u,now_k[u],now_d[u],now_x[u],now_y[u]); //����̶�
	  	clean(u); //��Ⲣ��������
	  	if(is_over(u))
	  	{
	  	  //GG(); //Good game ��Ϸ���� 
		  return; 
		}
		newBlock(u);//ˢ���µķ���
	
	  } 
	  get_final_y(u); //��ȡ����λ��
 	  int state = check(u,op);
	  if(state == 1) //�任�ƶ�����Ϸ�
	  {
	    move(u,op); //�任�ƶ�����
	    //cnt = num; //������ʱ
	  }
	  else if(state == 2)
	  {
	  	place(u,now_k[u],now_d[u],now_x[u],now_y[u]); //��һ��ʱ�䷽��̶�
	  	
		//GotoXy(60,45);
        //cout<<"place "<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y; //����place 
	  	
	  	clean(u); //��Ⲣ��������
	  	if(is_over(u))
	  	{
	  	  //GG(); //Good game ��Ϸ���� 
		  return; 
		}
		newBlock(u);//ˢ���µķ���
	  }
	}

	//ˢ����Ļ,������һ��ʱ��
	//DrawMap();
	for(int p=1;p<=p_num;p++)
	{
	  get_final_y(p); //��ȡԤ����
	  Draw(p);
	  cnt[p]--;
    }
    Sleep(20); //25fps
	//cout<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y<<" "<<endl;
	//system("pause");
  } 
}


void newBlock(int u) //�����·��� 
{	
  srand(time(0));
  
  now_x[u] = 4;  //��Ļ�м� 
  now_y[u] = -2; //�տ�ʼ����Ļ���   
  now_k[u] = newcube[u][1]; //��ȡ���� 
  now_d[u] = newcube[u][2]; //��ȡ���� 
  
  newcube[u][1] = rand()%7+1; //ѡȡ����
  newcube[u][2] = rand()%4;   //ѡȡ����
  
  
  for(int j=1;j<=4;j++) //��ӡ��һ��Ԥ�� 
  {
  	GotoXy(X[u]+50,Y[u]+6+2*j);
    for(int i=1;i<=4;i++)
    {
      color(B[newcube[u][1]][newcube[u][2]][i][j]);
      cout<<"����";
	}
	GotoXy(X[u]+50,Y[u]+6+2*j+1);
	for(int i=1;i<=4;i++)
    {
      color(B[newcube[u][1]][newcube[u][2]][i][j]);
      cout<<"����"; 
	}
  }
  
  //cout<<"������·���"<<endl; 
  //system("pause");
}


void get_final_y(int u)
{
  final_y[u] = now_y[u];
  int yyy = final_y[u]+1;
  
  while(1)
  {
  	int flag = true;
    for(int i=1;i<=4 && flag;i++)
      for(int j=1;j<=4 && flag;j++)
        if(M[u][now_x[u]+i-1][yyy+j-1] && B[now_k[u]][now_d[u]][i][j])
          flag = false;
    if(flag)
      final_y[u] = yyy++;
    else
      break;
  }
  
  //GotoXy(60,10);
  //cout<<"final_y = "<<final_y[u]<<endl;
  
}

int check(int u,int op)
{  
  int ddd = now_d[u];
  int xxx = now_x[u];
  int yyy = now_y[u];
  if(op==72 || op=='x' || op=='w')  //˳ʱ��ת 
    ddd = (ddd+1)%4;
  if(op=='z')  //��ʱ��ת 
    ddd = (ddd+3)%4;
  if(op==75 || op=='a')  //�� 
    xxx--;
  if(op==77 || op=='d')  //�� 
    xxx++;
  if(op==80 || op==-1 || op=='s')  //�»�������
    yyy++;
  
  int flag = 1;
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(xxx+i-1>=0 && yyy+j-1>=0 && xxx+i-1<=Maxx+1)
        if(B[now_k[u]][ddd][i][j]>0 && M[u][xxx+i-1][yyy+j-1]>0)
          flag = 0; //�ƶ����Ϸ��������з����غ�
          
  if(flag)
    return 1;
  
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(now_y[u]+j>=1 && B[now_k[u]][now_d[u]][i][j] && M[u][now_x[u]+i-1][now_y[u]+j])
        return 2; //������֧�ţ�����ֹͣ
  
  return 0; //�ƶ����Ϸ� 
}

//��72 ��80 ��75 ��77
void move(int u,int op)  //�ƶ�ת���� 
{
  if(op==72 || op=='x' || op=='w')  //˳ʱ��ת 
    now_d[u] = (now_d[u]+1)%4;
  if(op=='z')  //��ʱ��ת 
    now_d[u] = (now_d[u]+3)%4;
  if(op==75 || op=='a')  //�� 
    now_x[u]--;
  if(op==77 || op=='d')  //�� 
    now_x[u]++;
  if(op==80 || op==-1 || op=='s')  //�»������� 
    now_y[u]++;
    
  //get_final_y(); //��ȡ����λ�� 
} 

void clean(int u) //���к���
{
  int p = Maxy;
  for(int j=Maxy;j>=1;j--)
  {
  	int flag = true; //������Ϊtrue 
    for(int i=1;i<=Maxx;i++)
      if(M[u][i][j] == 0)
      {
        flag = false;
        for(int i=1;i<=Maxx;i++)
	      M[u][i][p] = M[u][i][j];
	    p--;
        break;
	  }
  }
  for(;p>=1;p--)  //�������ÿ�
    for(int i=1;i<=Maxx;i++)
	    M[u][i][p] = 0;
} 

void place(int u,int k,int d,int x,int y) //������k��d������õ���ͼ��(x,y)λ��
{
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(1<=x+i-1 && x+i-1<=Maxx && 0<=y+j-1 && y+j-1<=Maxy)
        M[u][x+i-1][y+j-1] += B[k][d][i][j];
  //GotoXy(60,45);
  //cout<<"place "<<k<<" "<<d<<" "<<x<<" "<<y;
} 

bool is_over(int u) //��Ϸ��������true 
{
  for(int i=1;i<=Maxx;i++)
    if(M[u][i][0])  //���鳬����ͼ 
      return true;
  return false; 
}

void GG() //��Ϸ���� 
{
  
} 

/*
void DrawMap() //��ʾ�ײ��ͼ,������ 
{ 
  color(0x0f);
  for(int j=0;j<=Maxy+1;j++)
  {
  	GotoXy(60,5+j);
    for(int i=0;i<=Maxx+1;i++) 
    {
	  int real = M[i][j];
	  if(now_x<=i && i<=now_x+3 && now_y<=j && j<=now_y+3) //���ƶ����������� 
	    real += B[now_k][now_d][i-now_x+1][j-now_y+1];
      if(real)
	    cout<<1;
	  else
	    cout<<' ';
	}
	
	GotoXy(100,5+j);
	for(int i=0;i<=Maxx+1;i++) 
      if(M[i][j])
	    cout<<1;
	  else
	    cout<<' ';
  }
}
*/
void Draw(int u) //֡���� , ���Ͻ���(X,Y) 
{
  HideCursor();
  
  //�����ƶ��죬Ԥ���飬��ͼ 
  for(int j=1;j<=Maxy;j++)
  {
  	int real[Maxx+5];
    for(int i=1;i<=Maxx;i++) 
    {
	  real[i] = M[u][i][j];
	  if(now_x[u]<=i && i<=now_x[u]+3 && now_y[u]<=j && j<=now_y[u]+3) //���ƶ����������� 
	    real[i] += B[now_k[u]][now_d[u]][i-now_x[u]+1][j-now_y[u]+1];
	  if(now_x[u]<=i && i<=now_x[u]+3 && final_y[u]<=j && j<=final_y[u]+3 && !real[i]) //��Ԥ����������
	    if(B[now_k[u]][now_d[u]][i-now_x[u]+1][j-final_y[u]+1]) 
	    real[i] += 143; //��ɫ 
	}
	GotoXy(X[u]+4,Y[u]+2*j);
	for(int i=1;i<=Maxx;i++) 
    {
      if(!real[i])
        color(0x0f);  //Ĭ����ɫ 
      else
        color(real[i]);
      cout<<"����";
	}
	GotoXy(X[u]+4,Y[u]+2*j+1);
	for(int i=1;i<=Maxx;i++) 
    {
      if(!real[i])
        color(0x0f);  //Ĭ����ɫ
      else
        color(real[i]);
      cout<<"����";
	}
  }
  color(0x0f);
}

void HideCursor() //������� 
{
  CONSOLE_CURSOR_INFO cursor_info = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void GotoXy(int x,int y)  //������Ƶ���x��y��
{
  HANDLE hout;
  COORD coord;
  coord.X=x;
  coord.Y=y;
  hout=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hout,coord);
}

void color(int x) //����ǰ��ɫ�뱳��ɫ 
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
