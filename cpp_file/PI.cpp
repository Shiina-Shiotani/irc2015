#include "Comet.h"

//PI制御の計算と出力の関数があるよー(＾◇＾)
//関数名はPIDなのにPI制御なのは突っ込まないで(´･ω･｀)

//右車輪用
PwmOut r_cw(p22);
DigitalOut r_ccw(p12);

//左車輪用
PwmOut l_cw(p23);
DigitalOut l_ccw(p11);

//とりあえず先に宣言しておく
void l_motor(float l_speed, int l_terget_speed);
void r_motor(float r_speed, int r_terget_speed);



void PID(int l_terget, int r_terget){
    float l_speed,r_speed;             //現在の左右のスピード
    float l_hensa,r_hensa;             //左右それぞれの偏差     英語だとよくわからないのでローマ字にした
    float l_output,r_output;           //出力用
    
    //PWMの周期の調性
    r_cw.period(0.00005);
    l_cw.period(0.00005);
    
    //速度の計算
    //割り込み処理の段階で」それぞれの角速度がわかっているので，そこから各車輪の速度を計算している
    l_speed = l_omega * WHEEL_RADIUS;
    r_speed = r_omega * WHEEL_RADIUS;
    
//    printf("%lf\t%lf\n", l_speed, r_speed);
    
    //偏差の取得
    l_hensa = l_speed - l_terget;
    r_hensa = r_speed - r_terget;
  //  printf("%lf\n",l_hensa);
    
    //偏差の蓄積（積分計算）
    l_integral += l_hensa * DELTA_T;
    r_integral += r_hensa * DELTA_T;
    
    //積分上限の設定
    if(l_integral >= 600)    l_integral = 600;
    if(l_integral < -600)    l_integral = -600;
    if(r_integral >= 600)    r_integral = 600;
    if(r_integral < -600)    r_integral = -600;
    
    //出力の計算
    //この段階でデューティー比にしている
    l_output = (PID_L_KP * l_hensa + PID_L_KI * l_integral) / 100;
    r_output = (PID_R_KP * r_hensa + PID_R_KI * r_integral) / 100;
    
//    printf("%lf\t%lf\n", l_output, r_output);
    
    //出力
    l_motor(l_output,l_terget);       
    r_motor(r_output,r_terget);
    wait(DELTA_T);
}

//左モータ出力用関数
//引数は左出力→左目標
void l_motor(float l_speed, int l_terget_speed){
    float L = fabs(l_speed);     //絶対値にするために使用
    if(l_speed >=0 && l_terget_speed >= 0){         //正転だけど目標まで足りない
        l_cw = L;   l_ccw=0;
    }
    else if( l_speed < 0 && l_terget_speed >= 0){   //正転だけど目標を通り過ぎた
        l_cw = L;   l_ccw=1;
    }
    else if( l_speed >= 0 && l_terget_speed < 0){   //逆転だけど目標まで足りない
        l_cw = L;   l_ccw=0;
    }
    else{                                           //逆転だけど目標を通り過ぎた
        l_cw = L;   l_ccw=1;
    }
}
    
//右モータ出力用関数
//引数は右出力→右目標
void r_motor(float r_speed, int r_terget_speed){
    float R = fabs(r_speed);     //絶対値にするために使用
    if(r_speed >=0 && r_terget_speed >= 0){
        r_cw = R;   r_ccw=0;
    }
    else if( r_speed < 0 && r_terget_speed >= 0){
        r_cw = R;   r_ccw=1;
    }
    else if( r_speed >= 0 && r_terget_speed < 0){
        r_cw = R;   r_ccw=0;
    }
    else{
        r_cw = R;   r_ccw=1;
    }
}