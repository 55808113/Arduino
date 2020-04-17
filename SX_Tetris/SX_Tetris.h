/*
* SX_Tetris.h
* 俄罗斯方块类
* Created: 2017-10-10 23:05:39
*  Author: sunxdd
说明：这个是基类。实现的类需要继承这个类
例如：class TetrisGameClass :public SX_TetrisClass
继承方法如下：
drawLogo()
drawBoard()
drawSign
drawNewSign
drawGameOver
drawGameWin
使用例子


*/
#ifndef _SX_TETRIS_h
#define _SX_TETRIS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SX_Fun.h"
#include "SX_Key.h"

struct Jimu
{
	//1110001000000000
	word dat;
	//因为X左移动时可能为负值 x为图形的左边的坐标
	char x;
	//Y为图形的下边的坐标当死时为了显示最后一个。可能为负值
	byte y;
	byte type;
	byte change;
	struct Color color;
};
//一个符号所占的列和行
#define SIGN_ALL    4
//最大的等级
#define MAX_LEVEL    10
//定义了7个图形，每个图形的4个旋转方向的形。所以就是7*4=28个
const byte Block[28][2] = {
	/*
	*   口     口口口   口口
	*   口     口         口      口
	*   口口              口  口口口
	*/
	{ 0x88,0xc0 },{ 0xe8,0x00 },{ 0x62,0x20 },{ 0x02,0xe0 },
	/*
	*   口        口口 口口口
	*   口 口     口       口
	* 口口 口口口 口
	*/
	{ 0x22,0x60 },{ 0x08,0xe0 },{ 0xc8,0x80 },{ 0xe2,0x00 },
	/*
	*   口
	*   口口         口口
	*     口       口口
	*/
	{ 0x8c,0x40 },{ 0x6c,0x00 },{ 0x8c,0x40 },{ 0x6c,0x00 },
	/*
	*   口        口口
	* 口口          口口
	* 口
	*/
	{ 0x4c,0x80 },{ 0xc6,0x00 },{ 0x4c,0x80 },{ 0xc6,0x00 },
	/*
	*          口                口
	*   口     口口   口口口   口口
	* 口口口   口       口       口
	*/
	{ 0x04,0xe0 },{ 0x8c,0x80 },{ 0xe4,0x00 },{ 0x26,0x20 },
	/*口
	* 口
	* 口       口口口口
	* 口
	*/
	{ 0x44,0x44 },{ 0x0f,0x00 },{ 0x44,0x44 },{ 0x0f,0x00 },
	/*
	* 口口
	* 口口
	*/
	{ 0x06,0x60 },{ 0x06,0x60 },{ 0x06,0x60 },{ 0x06,0x60 }
};

class SX_TetrisClass
{
protected:

	/*由子类实现画Logo
	返回：true为进入主界面
	*/
	virtual bool drawLogo();
	/*由子类实现画墙壁，初始化界面

	*/
	virtual void drawBoard();
	/*由子类实现画边框
	x:是坐标x点
	y:是坐标y点
	drawColor:是否去掉上次画的内容：0：去掉。1：是不去掉
	color：颜色
	*/
	virtual void drawSign(int x, int y, bool drawColor = true, struct Color color = { 255,0,0 });
	/*由子类实现画新符号
	x:是坐标x点
	y:是坐标y点
	drawColor:是否去掉上次画的内容：0：去掉。1：是不去掉
	color：颜色
	*/
	virtual void drawNewSign(int x, int y, bool drawColor = true, struct Color color = { 255,0,0 });
	/*由子类实现游戏结束的方法
	
	*/
	virtual void drawGameOver();
	/*由子类实现游戏赢的方法	
	*/
	virtual void drawGameWin(byte score, byte level, bool drawColor = true);
public:
	SX_TetrisClass(byte width = 12, byte height = 21);	
	/*由子类实现游戏初始化方法	
	*/
	void tetrisStart();
	/*由子类实现游戏开始方法	  
	*/
	void tetrisRun();
	//串口设置方向的
	void setKeyBuffer(String keyBuffer);
	//是否显示边框
	void setDrawFrameEnable(bool drawFrameEnable);
	//得到方块游戏的宽度
	byte getWidth();
	//得到方块游戏的高度
	byte getHeight();
private:
	//方块游戏的宽度
	byte _width;
	//方块游戏的高度
	byte _height;
	//积木结构体 _Sign[0]是当前显示的图形 _Sign[1]是下一个要显示的图形
	Jimu _Sign[2];
	//定义共21行，其中num[0]为下墙壁行，num[20]为上墙壁行,每行12格，最左一格为左墙壁列，最右一格为右墙壁列
	//word *_num[19 + 2] = {
	//  0xfff,//第1行，最下面111111111111
	//  0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,
	//  0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,//第2行到第20行共19行
	//  0xfff//第21行，最上面
	//};
	word *_num;
	word _numTopBottom;
	word _numMiddle;	
	
	//所得分数
	byte _Score = 0;
	//当前等级
	byte _Level = 1;
	//外边传的键值
	int _KeyBuffer = 0;
	//是否画边框
	bool _drawFrameEnable = false;
	//是否死亡
	bool _gameOverEnable = false;
	//当前是否有图形
	//boolean _SysSignFlag = false;
	//是否暂停运行
	boolean _pauseFlag = false;
	//等待时间
	unsigned long _DelayTime = millis();
	//画Logo
	void _drawLogo();
	//是否创建新的图形
	//boolean _newSignFlag = false;
	//判断积木图标中方块是否与障碍方块重合
	boolean _checkKnock(struct Jimu sign);
	//判断是否死了
	boolean _checkDead();
	//将积木图标值融入num数据中也即把积木图标固定，无法再下降
	void _fixSign();
	//寻找满格的行并做消除处理最多寻找4个满行并做消除
	void _delFull();
	//随机产生一个积木图标放到预产生区域并显示出来 新符号的位置X和Y
	void _createNewSign();
	//把NewSign的图形设置经SysSign
	void _createSysSign();
	//控制图形移动
	void _controlSign();
	//画显示内容
	void _drawFrame();
	//加分数
	void _addScore();
	//初始化Num
	void _initNum();
	//根据积木图标左下坐标X，Y来画出积木图标
	void _drawSign(struct Jimu sign, bool drawColor = true, bool drawNewSignEnable = false);
	//移动图标
	void _moveSign(struct Jimu &sign, byte key);
	//游戏重新开始
	void _gameInit();
};


#endif


