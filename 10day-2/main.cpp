#include <Novice.h>

const char kWindowTitle[] = "GC2B_04_サワダカズキ";


enum SCENE {
	TITLE,//タイトル画面
	STAGE1,//ゲーム画面
	STAGE2,
	STAGE3,
	GAMECLEAR,//ゲームクリア
	GAMECLEAR2,//STAGE2
	GAMECLEAR3,//STAGE3
	GAMEOVER,//ゲームオーバー
	GAMEOVER2,//STAGE2
};

int sceneNo = TITLE;
//画像読み込み-----------------------------------------------------------
//Map Classに移動する



//ブロックサイズの設定
const int KBlockSize = 32;
int playerPosX = 13 * KBlockSize;
int playerPosY = 672;
int playerR = 32;
int playerSpeed = KBlockSize;

int playerTmpX = 0;
int playerTmpY = 0;
int playerMapX = 0;
int playerMapY = 0;

int caramelMapX = 0;
int caramelMapY = 0;
int caramelTmpX = 0;
int caramelTmpY;

int blockPosX = 32;
int blockPosY = 32;
int blockTmpX = 0;
int blockTmpY = 0;
int blockMapX = 0;
int blockMapY = 0;

//ステージ2
/*int playerPosX = 13 * KBlockSize;
int playerPosY = 320;*/


//タイマー
int goalTimer = 60;//ゴール
int caramelTimer = 200;//カラメル
int deathTimer = 60;//ゲームオーバー
//フラグ-----------
int caramelFlag = 0;

//マップずらすための変数
int mapShift = 200;

int map[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,84, 0,84, 0,84, 0,84, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,41, 0, 4, 0,31, 0, 8, 0,23, 0,10, 0,40, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,44, 0, 2, 0, 6, 0,13, 0,16, 0,56, 0,11, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,36, 0,46, 0,15, 0, 3, 0,24, 0,17, 0,48, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int mapFormat[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,84, 0,84, 0,84, 0,84, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,41, 0, 4, 0,31, 0, 8, 0,23, 0,10, 0,40, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,44, 0, 2, 0, 6, 0,13, 0,16, 0,56, 0,11, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,36, 0,46, 0,15, 0, 3, 0,24, 0,17, 0,48, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int map2[22][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,4,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,1,1,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,5,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,1},
{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapFormat2[22][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,4,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,1,1,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,5,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,1},
{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int map3[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,6,0,0,0,0,0,7,0,5,5,7,0,0,0,0,0,0,6,0,0,0,0,1},
{1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1},
{1,1,1,5,5,1,1,1,1,1,5,1,7,1,5,1,1,1,1,1,1,5,5,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,6,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,7,7,0,7,7,0,0,6,0,0,0,6,0,0,7,7,0,7,7,7,7,7,7,1},
{1,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,1},
{1,6,5,5,7,5,5,5,5,0,0,0,0,0,0,0,5,5,5,5,7,5,5,6,6,6,1},
{1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapFormat3[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,6,0,0,0,0,0,7,0,5,5,7,0,0,0,0,0,0,6,0,0,0,0,1},
{1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1},
{1,1,1,5,5,1,1,1,1,1,5,1,7,1,5,1,1,1,1,1,1,5,5,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,6,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,7,7,0,7,7,0,0,6,0,0,0,6,0,0,7,7,0,7,7,7,7,7,7,1},
{1,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,1},
{1,6,5,5,7,5,5,5,5,0,0,0,0,0,0,0,5,5,5,5,7,5,5,6,6,6,1},
{1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


enum HIRAGANA {

	YUKA,//0

	A, I, U, E, O,
	KA, KI, KU, KE, KO,
	SA, SHI, SU, SE, SO,
	TA, CHI, TSU, TE, TO,
	NA, NI, NU, NE, NO,
	HA, HI, FU, HE, HO,
	MA, MI, MU, ME, MO,
	YA, YU, YO,
	RA, RI, RU, RE, RO,
	WA, WO, NN,

	GA, GI, GU, GE, GO,
	ZA, ZI, ZU, ZE, ZO,
	DA, DI, DU, DE, DO,
	BA, BI, BU, BE, BO,
	PA, PI, PU, PE, PO,

	BLOCK1, BLOCK22, BLOCK3, BLOCK4,
	BLOCK5, BLOCK6, BLOCK7, BLOCK8,

	BLOCK,//1
	THORN,//2
	BLOCK2,//3
	GOAL,//4
	SYRUP,//5
	CANDY,//6
	CARAMEL,//7
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
	int mapCountY = sizeof(map) / sizeof(map[0]);

	int mapCountX2 = sizeof(map2[0]) / sizeof(map2[0][0]);
	int mapCountY2 = sizeof(map2) / sizeof(map2[0]);

	int mapCountX3 = sizeof(map3[0]) / sizeof(map3[0][0]);
	int mapCountY3 = sizeof(map3) / sizeof(map3[0]);

	int a = Novice::LoadTexture("./images/a.png");
	int i = Novice::LoadTexture("./images/i.png");
	int u = Novice::LoadTexture("./images/u.png");
	int e = Novice::LoadTexture("./images/e.png");
	int o = Novice::LoadTexture("./images/o.png");

	int ka = Novice::LoadTexture("./images/ka.png");
	int ki = Novice::LoadTexture("./images/ki.png");
	int ku = Novice::LoadTexture("./images/ku.png");
	int ke = Novice::LoadTexture("./images/ke.png");
	int ko = Novice::LoadTexture("./images/ko.png");

	int sa = Novice::LoadTexture("./images/sa.png");
	int shi = Novice::LoadTexture("./images/si.png");
	int su = Novice::LoadTexture("./images/su.png");
	int se = Novice::LoadTexture("./images/se.png");
	int so = Novice::LoadTexture("./images/so.png");

	int ta = Novice::LoadTexture("./images/ta.png");
	int chi = Novice::LoadTexture("./images/ti.png");
	int tsu = Novice::LoadTexture("./images/tu.png");
	int te = Novice::LoadTexture("./images/te.png");
	int to = Novice::LoadTexture("./images/to.png");

	int na = Novice::LoadTexture("./images/na.png");
	int ni = Novice::LoadTexture("./images/ni.png");
	int nu = Novice::LoadTexture("./images/nu.png");
	int ne = Novice::LoadTexture("./images/ne.png");
	int no = Novice::LoadTexture("./images/no.png");

	int ha = Novice::LoadTexture("./images/ha.png");
	int hi = Novice::LoadTexture("./images/hi.png");
	int hu = Novice::LoadTexture("./images/hu.png");
	int he = Novice::LoadTexture("./images/he.png");
	int ho = Novice::LoadTexture("./images/ho.png");

	int ma = Novice::LoadTexture("./images/ma.png");
	int mi = Novice::LoadTexture("./images/mi.png");
	int mu = Novice::LoadTexture("./images/mu.png");
	int me = Novice::LoadTexture("./images/me.png");
	int mo = Novice::LoadTexture("./images/mo.png");

	int ya = Novice::LoadTexture("./images/ya.png");
	int yu = Novice::LoadTexture("./images/yu.png");
	int yo = Novice::LoadTexture("./images/yo.png");

	int ra = Novice::LoadTexture("./images/ra.png");
	int ri = Novice::LoadTexture("./images/ri.png");
	int ru = Novice::LoadTexture("./images/ru.png");
	int re = Novice::LoadTexture("./images/re.png");
	int ro = Novice::LoadTexture("./images/ro.png");

	int wa = Novice::LoadTexture("./images/wa.png");
	int wo = Novice::LoadTexture("./images/wo.png");
	int nn = Novice::LoadTexture("./images/n.png");

	int ga = Novice::LoadTexture("./images/ga.png");
	int gi = Novice::LoadTexture("./images/gi.png");
	int gu = Novice::LoadTexture("./images/gu.png");
	int ge = Novice::LoadTexture("./images/ge.png");
	int go = Novice::LoadTexture("./images/go.png");

	int za = Novice::LoadTexture("./images/za.png");
	int zi = Novice::LoadTexture("./images/zi.png");
	int zu = Novice::LoadTexture("./images/zu.png");
	int ze = Novice::LoadTexture("./images/ze.png");
	int zo = Novice::LoadTexture("./images/zo.png");

	int da = Novice::LoadTexture("./images/da.png");
	int di = Novice::LoadTexture("./images/di.png");
	int du = Novice::LoadTexture("./images/du.png");
	int de = Novice::LoadTexture("./images/de.png");
	int doo = Novice::LoadTexture("./images/do.png");

	int ba = Novice::LoadTexture("./images/ba.png");
	int bi = Novice::LoadTexture("./images/bi.png");
	int bu = Novice::LoadTexture("./images/bu.png");
	int be = Novice::LoadTexture("./images/be.png");
	int bo = Novice::LoadTexture("./images/bo.png");

	int pa = Novice::LoadTexture("./images/pa.png");
	int pi = Novice::LoadTexture("./images/pi.png");
	int pu = Novice::LoadTexture("./images/pu.png");
	int pe = Novice::LoadTexture("./images/pe.png");
	int po = Novice::LoadTexture("./images/po.png");

	int block = Novice::LoadTexture("./images/block.png");
	int goal = Novice::LoadTexture("./images/GOALS.png");
	int player = Novice::LoadTexture("./images/player.png");
	int gameClear = Novice::LoadTexture("./images/GAMECLEAR.png");
	int gameOver = Novice::LoadTexture("./images/GAMEOVERR.png");
	int title = Novice::LoadTexture("./images/TITLE.png");
	int MANUAL = Novice::LoadTexture("./images/MANUALS.png");

	bool isClearFlag = false;
	//int isLife = 3;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			//初期化------------------------------------------------------------
			goalTimer = 60;
			deathTimer = 60;
			playerPosY = 672;
			playerSpeed = KBlockSize;
			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					map[y][x] = mapFormat[y][x];
				}
			}
			//--------------------------------------------------------------------
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = STAGE1;
			}

			break;

		case STAGE1:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 13 * KBlockSize;//プレイヤーの位置
				playerPosY = 672;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY; y++)
				{
					for (int x = 0; x < mapCountX; x++)
					{
						map[y][x] = mapFormat[y][x];
					}
				}
			}



			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I; //ここをUに変える　したも同じ
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
							if (map[1][27] == BLOCK1)
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] == BLOCK1)
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK22)
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK3)
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK4)
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK5)
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK6)
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK7)
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[1][27] = YUKA;
						}
						if (map[1][27] == BLOCK8)
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[1][27] = YUKA;
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK2)
					{
						map[1][27] = BLOCK2;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[1][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[1][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[1][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[1][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[1][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[1][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = I;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = KO;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = SO;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = TA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = CHI;
						playerPosX -= playerSpeed;
					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = NU;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = MA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = YA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = RI;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = RU;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = WA;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = GI;
						playerPosX -= playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = ZO;
						playerPosX -= playerSpeed;
					}
				}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;
					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;
					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}
				//シロップを動かす処理
				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;
					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;
					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;
					}
				}
			}

			//状態変化--------------------------------------------------------------------------------------------------



			//ゴール条件---------------------------------


			// 解答が合ってたらクリアフラグがtrueになる
			if (map[blockMapY][blockMapX] == BLOCK1 && map[blockMapY][blockMapX] == I)
			{
				if (map[blockMapY][blockMapX] == BLOCK22 && map[blockMapY][blockMapX] == NU)
				{
					isClearFlag = true;
				}
			}

			// ステージ遷移　解答のシーンを作る予定
			if (map[playerMapY][playerMapX] == GOAL && isClearFlag == true && keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = STAGE2;
			}

			if (map[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR;
				}
			}

			if (map[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}
			break;

		case STAGE2:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY2; y++)
				{
					for (int x = 0; x < mapCountX2; x++)
					{
						map2[y][x] = mapFormat2[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SYRUP;
						playerPosY -= playerSpeed;
					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SYRUP;
						playerPosX -= playerSpeed;
					}
				}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}

				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SYRUP;
						playerPosX += playerSpeed;
					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosY += playerSpeed;
				}
				//シロップを動かす処理
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SYRUP;
						playerPosY += playerSpeed;
					}
				}
			}

			//状態変化--------------------------------------------------------------------------------------------------
			if (keys[DIK_1] && preKeys[DIK_1] == 0)
			{
				for (int y = 0; y < mapCountY2; y++)
				{
					for (int x = 0; x < mapCountX2; x++)
					{
						if (map2[y][x] == SYRUP)
						{
							map2[y][x] = CANDY;
						}

						else if (map2[y][x] == CANDY)
						{
							map2[y][x] = CARAMEL;
							caramelFlag = 1;
						}

						else if (map2[y][x] == CARAMEL)
						{
							if (caramelTimer <= 0)
							{
								map2[y][x] = YUKA;
								caramelFlag = 0;
							}
							/*if (map2[y][x] = YUKA)
							{
								caramelTimer = 200;
							}*/

							caramelMapX = x;
							caramelMapY = y;

							if (map2[caramelMapY - 1][caramelMapX] == YUKA)//上
							{
								map2[caramelMapY - 1][caramelMapX] = THORN;
							}
							if (map2[caramelMapY + 1][caramelMapX] == YUKA)//下
							{
								map2[caramelMapY + 1][caramelMapX] = THORN;
							}

							if (map2[caramelMapY][caramelMapX - 1] == YUKA)//左
							{
								map2[caramelMapY][caramelMapX - 1] = THORN;
							}
							if (map2[caramelMapY][caramelMapX + 1] == YUKA)//右
							{
								map2[caramelMapY][caramelMapX + 1] = THORN;
							}
						}
					}
				}
			}
			if (caramelFlag == 1)
			{
				caramelTimer--;
			}


			//ゴール条件---------------------------------
			if (map2[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR2;
				}
			}

			if (map2[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}

			break;

		case STAGE3:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY3; y++)
				{
					for (int x = 0; x < mapCountX3; x++)
					{
						map3[y][x] = mapFormat3[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == SYRUP)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SYRUP;
						playerPosY -= playerSpeed;
					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == SYRUP)
				{
					if (map3[playerMapY][playerMapX - 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX - 1] = SYRUP;
						playerPosX -= playerSpeed;
					}
				}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == SYRUP)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SYRUP;
						playerPosX += playerSpeed;
					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosY += playerSpeed;
				}
				//シロップを動かす処理
				if (map3[playerMapY][playerMapX] == SYRUP)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SYRUP;
						playerPosY += playerSpeed;
					}
				}
			}

			//状態変化--------------------------------------------------------------------------------------------------
			if (keys[DIK_1] && preKeys[DIK_1] == 0)
			{
				for (int y = 0; y < mapCountY3; y++)
				{
					for (int x = 0; x < mapCountX3; x++)
					{
						if (map3[y][x] == SYRUP)
						{
							map3[y][x] = CANDY;
						}

						else if (map3[y][x] == CANDY)
						{
							map3[y][x] = CARAMEL;
							caramelFlag = 1;
						}

						else if (map3[y][x] == CARAMEL)
						{
							if (caramelTimer <= 0)
							{
								map3[y][x] = YUKA;
								caramelFlag = 0;
							}
							/*	if (map3[y][x] = YUKA)
								{
									caramelTimer = 200;
								}*/

							caramelMapX = x;
							caramelMapY = y;

							if (map3[caramelMapY - 1][caramelMapX] == YUKA)//上
							{
								map3[caramelMapY - 1][caramelMapX] = THORN;
							}
							if (map3[caramelMapY + 1][caramelMapX] == YUKA)//下
							{
								map3[caramelMapY + 1][caramelMapX] = THORN;
							}

							if (map3[caramelMapY][caramelMapX - 1] == YUKA)//左
							{
								map3[caramelMapY][caramelMapX - 1] = THORN;
							}
							if (map3[caramelMapY][caramelMapX + 1] == YUKA)//右
							{
								map3[caramelMapY][caramelMapX + 1] = THORN;
							}
						}
					}
				}
			}
			if (caramelFlag == 1)
			{
				caramelTimer--;
			}


			//ゴール条件---------------------------------
			if (map3[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR3;
				}
			}

			if (map3[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}

			break;

		case GAMECLEAR:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE2;
			}
			break;

		case GAMECLEAR2:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE3;
			}
			break;

		case GAMECLEAR3:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;


		case GAMEOVER:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			Novice::DrawSprite(0, 0, title, 2, 2, 0, WHITE);
			break;
		case STAGE1:
			//数値見やすく--------------------------------------------------------------
			/*Novice::ScreenPrintf(865, 32, "goalTimer=%d", goalTimer);
			Novice::ScreenPrintf(865, 64, "deathTimer=%d",deathTimer);
			Novice::ScreenPrintf(865, 96, "playerSpeed=%d", playerSpeed);
			Novice::ScreenPrintf(865, 128, "caramelTimer=%d", caramelTimer);*/



			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);

			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					//あ
					if (map[y][x] == A)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, a, 1, 1, 0, WHITE);
					}
					if (map[y][x] == I)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, i, 1, 1, 0, WHITE);
					}
					if (map[y][x] == U)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, u, 1, 1, 0, WHITE);
					}
					if (map[y][x] == E)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, e, 1, 1, 0, WHITE);
					}
					if (map[y][x] == O)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, o, 1, 1, 0, WHITE);
					}

					//か
					if (map[y][x] == KA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ka, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ki, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ku, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ke, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ko, 1, 1, 0, WHITE);
					}

					//さ
					if (map[y][x] == SA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, sa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, shi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, su, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, se, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, so, 1, 1, 0, WHITE);
					}

					//た
					if (map[y][x] == TA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ta, 1, 1, 0, WHITE);
					}
					if (map[y][x] == CHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, chi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TSU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, tsu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, te, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, to, 1, 1, 0, WHITE);
					}

					//な
					if (map[y][x] == NA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, na, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ni, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ne, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, no, 1, 1, 0, WHITE);
					}

					//は
					if (map[y][x] == HA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ha, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == FU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, he, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ho, 1, 1, 0, WHITE);
					}

					//ま
					if (map[y][x] == MA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ma, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ME)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, me, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mo, 1, 1, 0, WHITE);
					}

					//や
					if (map[y][x] == YA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ya, 1, 1, 0, WHITE);
					}
					if (map[y][x] == YU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == YO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yo, 1, 1, 0, WHITE);
					}

					//ら
					if (map[y][x] == RA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ra, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ri, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ru, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, re, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ro, 1, 1, 0, WHITE);
					}

					//わ
					if (map[y][x] == WA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == WO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wo, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nn, 1, 1, 0, WHITE);
					}

					//が
					if (map[y][x] == GA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ga, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ge, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, go, 1, 1, 0, WHITE);
					}

					//ざ
					if (map[y][x] == ZA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, za, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ze, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zo, 1, 1, 0, WHITE);
					}

					//だ
					if (map[y][x] == DA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, da, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, di, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, du, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, de, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, doo, 1, 1, 0, WHITE);
					}

					//ば
					if (map[y][x] == BA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ba, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, be, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bo, 1, 1, 0, WHITE);
					}

					//ぱ
					if (map[y][x] == PA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pe, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, po, 1, 1, 0, WHITE);
					}

					if (map[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BLOCK2)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}
					if (map[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}


				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE2:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY2; y++)
			{
				for (int x = 0; x < mapCountX2; x++)
				{
					if (map2[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map2[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BLOCK2)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}
					if (map2[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}
				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE3:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY3; y++)
			{
				for (int x = 0; x < mapCountX3; x++)
				{
					if (map3[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map3[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}

					if (map3[y][x] == BLOCK2)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}
					if (map3[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}
				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case GAMECLEAR:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR2:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR3:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMEOVER2:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		case GAMEOVER:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}