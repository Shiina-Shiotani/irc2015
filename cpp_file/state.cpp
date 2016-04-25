#include "Comet.h"

DigitalOut L1(LED1),L2(LED2),L3(LED3),L4(LED4);

//全体の初期化の処理
void initialize(){
    l_time = 0.0;                               //時間の初期化
    stop();         wait(1);                    //電源を入れた直後はモータが回転するため止めておく必要あり                   
    servo_ini();                                //サーボの初期姿勢 
    wait(0.5);                              
    r_pulses = 0;   l_pulses = 0;               //パルスの初期化
    serch_data[1][0] = 0.0;
    g_X = g_Y = g_theta = 0.0;                  //オドメトリの初期化
    l_odometry_reset();
    l_theta = 0;                                //ローカル角度の初期化
    serch_data[1][0]= 0.0;                      //0=近い方  1＝今     dis，deg
    ball_count = 0;
    encoder_flag = ON;  switch_encoder();       //エンコーダのフラグON   ＆もう一回パルスの初期(念のため)
    move_flag = OFF;    serchRight_flag = ON;
    areaChange_flag = OFF;                      //エリア移動しないようにする   
}

void fine(int num){//終了させる時の処理
            //パフォーマンスとかかな
    turn(180,FAST);
    if(color != YELLO)
        Line_Trace(4 - color);
    else 
        Line_Trace(5 - color);
    
       
    //何しよう・・・(* _ω_)...
    while(l_Y <= 250)
        PID(200, 200);
    turn(180, FAST);
    wait(0.5);
    servo_performance(num);
    while(1){
        PID(0,0);
    }
}