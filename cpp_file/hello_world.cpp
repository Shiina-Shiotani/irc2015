#include "Comet.h"

////////この関数は割り込み処理が外部の関数でも処理できるかのテスト////////
////////実際は使わないので削除推奨///////////////////////////////////
///////ぶっちゃけただのテスト用//////////////////////////////////////

//この関数は成功している
DigitalOut nya(LED1);
Ticker hello_world;

void hello(){
    printf("hello world\n");
    nya = 1 ;
    wait(1);
    printf("The world\n\n");
    nya = 0;   
}

//割り込みの処理をするかどうかの関数
//条件の変数はint型でもOK boolでもOKだった
void switch_hello(){
    if(guhu){
        //ここで割り込み開始
        hello_world.attach(&hello, 3);
    }else{
        //ここで割り込み終了
        hello_world.detach();
        printf("good bye\n");
    }
}