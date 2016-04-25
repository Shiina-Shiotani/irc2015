#include "mbed.h"
#include "robo_para.h"  //ロボットのパラメータ
#include "define.h"     //その他変数用

//詳しくはread_me.txt参照
#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "function.h"           //関数宣言