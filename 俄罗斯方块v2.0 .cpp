//俄罗斯方块v2.0-21班-2020210557-邹泽光
//v1.0按j开始游戏，左右下移动，上旋转 
/*************************** 
  v1.5预计要增加（已完成用 v 表示） 
	下N块预览          v(N=1) 
	下落预览           v
	空格瞬间下落       v 
****************************/
/*************************** 
  v2.0预计要增加(已完成用 v 表示) 
    块的刷新以7块为一组随机打乱 
	  更改newBlock(int u) 
	开始结束画面
	  初始化面可选择游戏模式与帮助
	  结束画面可重选模式（主要在work里更改） 
    可选择的双人模式                              v
      更改函数为传参便于处理多个游戏(u表示第几个游戏)
      (边更改边用单人验证函数正确性)
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
	  更改work函数以支持双人                      v
****************************/
/********测试代码*********** 
void HideCursor(int n) 
{ 
    CONSOLE_CURSOR_INFO curso
	r_info={1,n};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
} //n default 0


void GotoXy(int x,int y)  //将光标移到（x，y）
{
    HANDLE hout;
    COORD coord;
    coord.X=x;
    coord.Y=y;
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord);
}

测试代码，结果：maxx = 189, maxy = 50
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
1 FOREGROUND_BLUE        表示设置前景色为蓝色，即字体颜色为蓝色。
2  FOREGROUND_GREEN      表示设置前景色为绿色，即字体颜色为绿色。
4  FOREGROUND_RED        表示设置前景色为红色，即字体颜色为红色。
8  FOREGROUND_INTENSITY  表示设置前景色为高亮显示。
16 BACKGROUND_BLUE       表示设置背景色为蓝色。
32 BACKGROUND_GREEN      表示设置背景色为绿色。
64 BACKGROUND_RED        表示设置背景色为红色。
128 BACKGROUND_INTENSITY 表示设置背景色为高亮显示。

getch() // 无回显的读取键盘信息 
getche() // 有回显的读取键盘信息
  while(1)  //测试键值，字母为ascll码 ，方向键为 224 与 上72 下80 左75 右77 
  {
    int a,op;
    a = getch();
    op = getch();
    cout<<a<<" "<<op<<endl;
  }

bool _kbhit() // 有按键按下返回1, 非阻塞函数
_sleep(t)  // 程序停止t毫秒 
 
  for(int j=1;j<=Maxy;j++,cout<<endl)  //测试地图
    for(int i=1;i<=Maxx;i++)
	  cout<<M[i][j]; 

  for(int k=1;k<=7;k++)  //测试七种块四个方向 
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

//函数声明，u表示第几个游戏，v为已实现，vvv为已实现多人模式 
void HideCursor();                 //隐藏光标              vvv
void GotoXy(int x,int y);          //将光标移到（x，y）    vvv
void color(int x);                 //设置颜色              vvv
void get_p_num();                  //获得玩家数量          vvv
void init();                       //初始化                vvv
void drawBgd(int u);               //画背景                vvv
void work();                       //游戏开始！            vvv
void newBlock(int u);              //获得新方块            vvv
int  check(int u,int op);          //检测op操作是否合法    vvv
void move(int u,int op);           //方块移动函数          vvv
void get_final_y(int u);           //获取下落预览块的y     vvv
void clean(int u);                 //消行函数              vvv
void Draw(int u);                  //帧刷新,左上角在X,Y    vvv
//void DrawMap();                  //显示底层地图(测试用)  v
bool is_over(int u);               //判断游戏结束          vvv
void GG(int u,int X,int y);        //游戏结束界面,(X,Y)          
void place(int u,int k,int d,int x,int y); //将方块k的     vvv  d方向放置到地图的(x,y)位置 

//变量声明  
const int Maxx=10,Maxy=20;          //游戏区的地图大小 
int M[5][Maxx+3][Maxy+3];           //Map
int B[8][4][5][5];                  //Blocks ,  
int now_x[5],now_y[5];              //正在移动的方块左上角x,y坐标
int now_k[5],now_d[5];              //正在移动的方块的形状和朝向
int final_y[5];                     //方块最终的落点
int newcube[5][10];                 //下一个方块，用作预览
int X[5]={0,30,100},Y[5]={0,0,0};   //第u张地图的左上角位置(Xu,Yu)
int p_num;                          //玩家数量 

int main()
{
  get_p_num();
  init();
  work();
  return 0;
}

void get_p_num()
{
  cout<<"选完人数后按j(英文小写)开始！！！"<<endl;
  cout<<"P1 wasd 空格是速降"<<endl;
  cout<<"P2 上下左右 0是速降"<<endl; 
  cout<<"一定要全屏！！！！！！！！！！！！"<<endl;
  cout<<"您希望几人游戏(1/2)：";
  do
  {
  	cin>>p_num;
  }while(p_num<1 || p_num>2);
} 

void init()
{
  //绘出七种方块的0方向 
  B[1][0][2][2] = B[1][0][1][2] = B[1][0][2][1] = B[1][0][3][2] = 255; //T 白色 
  B[2][0][2][2] = B[2][0][3][3] = B[2][0][2][3] = B[2][0][2][1] = 239; //L 黄色 
  B[3][0][2][2] = B[3][0][1][3] = B[3][0][2][3] = B[3][0][2][1] = 223; //J 粉色 
  B[4][0][2][2] = B[4][0][1][1] = B[4][0][2][1] = B[4][0][3][2] = 207; //Z 橙色
  B[5][0][2][2] = B[5][0][2][1] = B[5][0][1][2] = B[5][0][3][1] = 191; //S 青色 
  B[6][0][2][2] = B[6][0][1][2] = B[6][0][3][2] = B[6][0][4][2] = 175; //I 绿色 
  B[7][0][2][2] = B[7][0][3][3] = B[7][0][3][2] = B[7][0][2][3] = 159; //O 蓝色 
  
  //TLJZS的其他三个方向
  for(int k=1;k<=5;k++)
    for(int d=1;d<=3;d++)
      for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
        {
          int newi = j, newj = i; //先关于x=y对称 
          newi = 4-newi;  //再关于x=2对称,结合上一个操作等于以(2,2)为中心右转 
		  B[k][d][newi][newj] = B[k][d-1][i][j]; 
		  if(k == 1) 
		    B[7][d][i][j] = B[7][d-1][i][j]; //o块的翻转 
		}
  
  //I的其他三个方向 
  B[6][1][3][1] = B[6][1][3][2] = B[6][1][3][3] = B[6][1][3][4] = 175; //I
  B[6][2][1][3] = B[6][2][2][3] = B[6][2][3][3] = B[6][2][4][3] = 175; //I
  B[6][3][2][1] = B[6][3][2][2] = B[6][3][2][3] = B[6][3][2][4] = 175; //I

  for(int p=1;p<=p_num;p++)
  {
    for(int i=0;i<=Maxx+1;i++) //设置边界墙
      M[p][i][Maxy+1] = 1;  
    for(int j=0;j<=Maxy+1;j++)
      M[p][0][j] = M[p][Maxx+1][j] = 64; //红色 
  }
  
  HideCursor(); //隐藏光标
  for(int p=1;p<=p_num;p++)
    drawBgd(p); //画背景
}

void drawBgd(int u)
{
  for(int j=1;j<=Maxy;j++)
  {
  	int i=0;
    GotoXy(X[u],Y[u]+2*j);
    color(0x0f); //红色
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
    color(0x0f); //红色
	for(int t=1;t<=12;t++)
	  cout<<"|$$|";
	GotoXy(X[u],Y[u]+2*(Maxy+1)+1);
	for(int t=1;t<=12;t++)
	  cout<<"|$$|";
  }
  
  
  GotoXy(X[u]+50,Y[u]+5);
  cout<<"NEXT:";
  
  color(0x0f); //恢复默认颜色 
}

void work()
{ 
  while(true)
  {
    if(getch() == 'j') //如过按下j键，游戏开始
    {
      for(int p=1;p<=p_num;p++)
      { 
        drawBgd(p); //画背景
        newBlock(p);
        newBlock(p); //刷新第一个方块
      } 
	  break;
	}
  }
  
  int num = 4; //每隔num*15ms自然掉落一格
  int cnt[5] = {4,4,4};//计数器，每到0自然下落一格
  while(true)
  { 
  	//读取操作
  	int op = -1;
  	if(_kbhit())
  	{
  	  op = getch();
  	  if(op == 224) //如果是方向键，读第二个有效数字
  	    op = getch();
    }
    
	//GotoXy(60,44);
	//cout<<"cnt= "<<cnt;
    //system("pause");
    
    int u; //该操作操作的地图标号 
    if('a'<=op && op<='z' || op==' ') //如果在字母区就是玩家1 
	  u = 1;
	else if(72<=op && op<=80 || op=='0') //如果在方向键区就是玩家2 
      u = 2;
	else if(op == -1) //如果无操作，就双方都下落 
	  u = 3;
	else
	  op = -1; 
    if(p_num == 1)
	  u = 1; 
    
	//改变地图
	if(op==-1) //如果没有输入隔一段时间尝试自然下落
	{ 
	  for(int p=1;p<=p_num;p++)
	  {
	  	if(cnt[p]>0)
	  	  continue;
	    cnt[p] = num; //重新计数
	    int state = check(p,op);
	  
	    //GotoXy(60,44);
	    //cout<<"cnt= "<<cnt;  测试延时
	  
	    if(state == 1) //如果移动合法
	    {
	  	  move(p,op); //正在移动的方块向下移动
	      cnt[p] = num;
	    }
	    else if(state == 2) //如果下面有支撑 
	    {
	  	  place(p,now_k[p],now_d[p],now_x[p],now_y[p]);//固定方块
	  	
		  //GotoXy(60,45);
          //cout<<"place "<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y; //测试place 
	  	
		  clean(p); //检测并尝试消行
	  	  if(is_over(p))
	  	  {
	  	    //GG(); //Good game 游戏结束 
		    return; 
		  }
   		  newBlock(p); //刷新新的方块
	    }
      }
	}
	if(op != -1) //如果有输入
	{
	  if(op==' ' || op=='0') //如果是快速下降
	  {
	  	get_final_y(u); //获取最终位置 
	  	now_y[u] = final_y[u]; //下降 
	  	place(u,now_k[u],now_d[u],now_x[u],now_y[u]); //方块固定
	  	clean(u); //检测并尝试消行
	  	if(is_over(u))
	  	{
	  	  //GG(); //Good game 游戏结束 
		  return; 
		}
		newBlock(u);//刷新新的方块
	
	  } 
	  get_final_y(u); //获取最终位置
 	  int state = check(u,op);
	  if(state == 1) //变换移动输入合法
	  {
	    move(u,op); //变换移动方块
	    //cnt = num; //重置延时
	  }
	  else if(state == 2)
	  {
	  	place(u,now_k[u],now_d[u],now_x[u],now_y[u]); //隔一段时间方块固定
	  	
		//GotoXy(60,45);
        //cout<<"place "<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y; //测试place 
	  	
	  	clean(u); //检测并尝试消行
	  	if(is_over(u))
	  	{
	  	  //GG(); //Good game 游戏结束 
		  return; 
		}
		newBlock(u);//刷新新的方块
	  }
	}

	//刷新屏幕,并持续一段时间
	//DrawMap();
	for(int p=1;p<=p_num;p++)
	{
	  get_final_y(p); //获取预览块
	  Draw(p);
	  cnt[p]--;
    }
    Sleep(20); //25fps
	//cout<<now_k<<" "<<now_d<<" "<<now_x<<" "<<now_y<<" "<<endl;
	//system("pause");
  } 
}


void newBlock(int u) //生成新方块 
{	
  srand(time(0));
  
  now_x[u] = 4;  //屏幕中间 
  now_y[u] = -2; //刚开始在屏幕外侧   
  now_k[u] = newcube[u][1]; //获取类型 
  now_d[u] = newcube[u][2]; //获取方向 
  
  newcube[u][1] = rand()%7+1; //选取类型
  newcube[u][2] = rand()%4;   //选取方向
  
  
  for(int j=1;j<=4;j++) //打印下一块预览 
  {
  	GotoXy(X[u]+50,Y[u]+6+2*j);
    for(int i=1;i<=4;i++)
    {
      color(B[newcube[u][1]][newcube[u][2]][i][j]);
      cout<<"··";
	}
	GotoXy(X[u]+50,Y[u]+6+2*j+1);
	for(int i=1;i<=4;i++)
    {
      color(B[newcube[u][1]][newcube[u][2]][i][j]);
      cout<<"··"; 
	}
  }
  
  //cout<<"已随机新方块"<<endl; 
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
  if(op==72 || op=='x' || op=='w')  //顺时针转 
    ddd = (ddd+1)%4;
  if(op=='z')  //逆时针转 
    ddd = (ddd+3)%4;
  if(op==75 || op=='a')  //左 
    xxx--;
  if(op==77 || op=='d')  //右 
    xxx++;
  if(op==80 || op==-1 || op=='s')  //下或无命令
    yyy++;
  
  int flag = 1;
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(xxx+i-1>=0 && yyy+j-1>=0 && xxx+i-1<=Maxx+1)
        if(B[now_k[u]][ddd][i][j]>0 && M[u][xxx+i-1][yyy+j-1]>0)
          flag = 0; //移动不合法，与现有方块重合
          
  if(flag)
    return 1;
  
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(now_y[u]+j>=1 && B[now_k[u]][now_d[u]][i][j] && M[u][now_x[u]+i-1][now_y[u]+j])
        return 2; //下面有支撑，可以停止
  
  return 0; //移动不合法 
}

//上72 下80 左75 右77
void move(int u,int op)  //移动转向函数 
{
  if(op==72 || op=='x' || op=='w')  //顺时针转 
    now_d[u] = (now_d[u]+1)%4;
  if(op=='z')  //逆时针转 
    now_d[u] = (now_d[u]+3)%4;
  if(op==75 || op=='a')  //左 
    now_x[u]--;
  if(op==77 || op=='d')  //右 
    now_x[u]++;
  if(op==80 || op==-1 || op=='s')  //下或无命令 
    now_y[u]++;
    
  //get_final_y(); //获取最终位置 
} 

void clean(int u) //消行函数
{
  int p = Maxy;
  for(int j=Maxy;j>=1;j--)
  {
  	int flag = true; //可以消为true 
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
  for(;p>=1;p--)  //其余行置空
    for(int i=1;i<=Maxx;i++)
	    M[u][i][p] = 0;
} 

void place(int u,int k,int d,int x,int y) //将方块k的d方向放置到地图的(x,y)位置
{
  for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++)
      if(1<=x+i-1 && x+i-1<=Maxx && 0<=y+j-1 && y+j-1<=Maxy)
        M[u][x+i-1][y+j-1] += B[k][d][i][j];
  //GotoXy(60,45);
  //cout<<"place "<<k<<" "<<d<<" "<<x<<" "<<y;
} 

bool is_over(int u) //游戏结束返回true 
{
  for(int i=1;i<=Maxx;i++)
    if(M[u][i][0])  //方块超出地图 
      return true;
  return false; 
}

void GG() //游戏结束 
{
  
} 

/*
void DrawMap() //显示底层地图,测试用 
{ 
  color(0x0f);
  for(int j=0;j<=Maxy+1;j++)
  {
  	GotoXy(60,5+j);
    for(int i=0;i<=Maxx+1;i++) 
    {
	  int real = M[i][j];
	  if(now_x<=i && i<=now_x+3 && now_y<=j && j<=now_y+3) //将移动块加入输出中 
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
void Draw(int u) //帧绘制 , 左上角在(X,Y) 
{
  HideCursor();
  
  //绘制移动快，预览块，地图 
  for(int j=1;j<=Maxy;j++)
  {
  	int real[Maxx+5];
    for(int i=1;i<=Maxx;i++) 
    {
	  real[i] = M[u][i][j];
	  if(now_x[u]<=i && i<=now_x[u]+3 && now_y[u]<=j && j<=now_y[u]+3) //将移动块加入输出中 
	    real[i] += B[now_k[u]][now_d[u]][i-now_x[u]+1][j-now_y[u]+1];
	  if(now_x[u]<=i && i<=now_x[u]+3 && final_y[u]<=j && j<=final_y[u]+3 && !real[i]) //把预览块加入输出
	    if(B[now_k[u]][now_d[u]][i-now_x[u]+1][j-final_y[u]+1]) 
	    real[i] += 143; //灰色 
	}
	GotoXy(X[u]+4,Y[u]+2*j);
	for(int i=1;i<=Maxx;i++) 
    {
      if(!real[i])
        color(0x0f);  //默认配色 
      else
        color(real[i]);
      cout<<"··";
	}
	GotoXy(X[u]+4,Y[u]+2*j+1);
	for(int i=1;i<=Maxx;i++) 
    {
      if(!real[i])
        color(0x0f);  //默认配色
      else
        color(real[i]);
      cout<<"··";
	}
  }
  color(0x0f);
}

void HideCursor() //隐藏鼠标 
{
  CONSOLE_CURSOR_INFO cursor_info = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void GotoXy(int x,int y)  //将光标移到（x，y）
{
  HANDLE hout;
  COORD coord;
  coord.X=x;
  coord.Y=y;
  hout=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hout,coord);
}

void color(int x) //更换前景色与背景色 
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
