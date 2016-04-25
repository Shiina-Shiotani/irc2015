#include "Comet.h"

void ball_catch(bool serch_deg);

///*停止用関数
void stop(){
    for(float i = 0.0; i < 0.2; i += DELTA_T){
        l_integral=0;   r_integral=0;
        PID(0,0);
    }
}

//ボール発見用関数
void tansaku(){
    serch_data[1][0] = Get_PSD_low();   serch_data[1][1] = l_theta;
    float high = 66.294 * pow((double)Get_PSD_high(), -1.218);
    
    //条件は後で変えよう
    if(high <= 600){   //high >= 0.24   機能しないから消すかも
        if(serch_data[0][0] < serch_data[1][0] ){   //更新
            serch_data[0][0] = serch_data[1][0];
            serch_data[0][1] = serch_data[1][1];
         }
    }
    //printf("%lf\n", high);
}

///*回転用関数
//角度＆早い方と遅い方の2つのモードを指定する
//引数のdegはどれくらい回転したいかの角度
void turn(float deg, bool mode){
    l_odometry_reset();
    if(mode){       //早い方
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 6.5){   //右回転
                PID(250,-250);
            }       
        }
        else{
            while( ( l_theta - deg ) < -6.5){   //左回転
                PID(-250,250);
            }
        }
    }
    else{       //遅い方あとは同上
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 0.1){   //右回転
                tansaku();
                PID(150,-150);
             }
        }
        else{
            while( ( l_theta - deg ) < -0.1){   //左回転
                tansaku();
                PID(-150,150);
            }
        }
    }
    stop();
}
//*/

/*
//グローバル座標系で回転する関数
//制度がなー(´;ω;｀)
void g_turn(float deg){
    l_odometry_reset();
    if(g_theta > deg ){
        while( ( g_theta - deg ) > 0.1){   //右回転
            PID(200,-200);
        }
    }
    else{
        while( ( g_theta - deg ) < -0.1){   //左回転
            PID(-200,200);
        }
    }
    stop();
}
*/


void search(bool serch_deg){
    PSD_reset();
    if(serch_deg){
        turn(-90, SLOW);
        if(serch_data[0][0] != 0.0)
            ball_catch(serch_deg);
        else{
            serchRight_flag = OFF;
            color = NO_BALL;
            turn(90, FAST);
            l_odometry_reset();
        }
    }
    else{
        turn(90, SLOW);
        if(serch_data[0][0] != 0.0)
            ball_catch(serch_deg);
        else{
            turn(-90, FAST);
            color = NO_BALL;
            
            move_flag = ON;
            l_odometry_reset();
        }
    }
}

void ball_catch(bool serch_deg){
    float serch_dis = 66.294 * pow((double)serch_data[0][0], -1.218);
    l_odometry_reset();
    wait(WAIT_DELTA_T);
    
    if(serch_dis <= 370 ){      //探索エリアの幅的に400(実際は350付近)
        if(serch_deg)
            if(serch_data[0][1] >= -40)
                turn(serch_data[0][1]+92, FAST);    //右側
            else
                turn(serch_data[0][1]+95, FAST);
        else{
            if(serch_data[0][1] <= 40)
                turn(serch_data[0][1]-98, FAST);
            else
                turn(serch_data[0][1]-98, FAST);    //左側
        }
        stop();
        wait(WAIT_DELTA_T);
        if(serch_dis <= 100){
            while(l_Y >= -20)
                PID(-200, -200);
        }
        stop();
        servo_ready();
        
        if(serch_dis <= 200){
            while(l_Y <= serch_dis - 80)     //serch_dis - 80
                PID(200, 200);
        }
/*        else if(serch_dis <= 200){
            while(l_Y <= serch_dis - 60)     //serch_dis - 80
                PID(200, 200);
        }
*/
        else if(serch_dis <= 300){
            while(l_Y <= serch_dis - 90)     //serch_dis - 80
                PID(200, 200);
        }
      
        else{
            while(l_Y <= serch_dis - 80)     //serch_dis - 80
                PID(200, 200);
        }
        stop();
        servo_catch();
        if(serch_dis <=100){
            while(l_Y <=5)
                PID(200,200);
        }else{
            while(l_Y >= 5)
                PID(-200, -200);
        }
        stop();
        wait(0.3);
        color = what_color();
        debug_color(color);                             //色のデバック用
        if(color != NO_BALL){
            if(serch_deg)
                turn(-1 * serch_data[0][1] - 187, FAST);     //後ろを向く(右回転)
            else
                turn(-1 * serch_data[0][1] + 172, FAST);     //後ろを向く(左回転)175
        }
        else{
            if(serch_deg)
                turn(-1 * serch_data[0][1] +5, FAST);
            else
                turn(-1 * serch_data[0][1] +4, FAST);     //正面を向く 2
        }
        wait(WAIT_DELTA_T);
    }
    else{
        if(serch_deg){
            serchRight_flag = OFF;
            turn(90, FAST);
        }
        else{
            turn(-90, FAST);
            move_flag = ON;
        }
        color = NO_BALL;
        l_odometry_reset();
    }
    PSD_reset();
}



/*投げない関数
//回収用関数
void Ball_Shoot(){
    if(color == RED || color == YELLO)
        turn(-80, FAST);
    wait(WAIT_DELTA_T);
    servo_throw();
    wait(WAIT_DELTA_T);
    
    servo_ini();
    wait(WAIT_DELTA_T);
    turn_off();
    if(color == RED || color == YELLO)
        turn(-100, FAST);
    else
        turn(180, FAST);
    wait(WAIT_DELTA_T);
}
*/

//ボールぶん投げる用関数
//使うかは分からない
///*回収用関数
void Ball_Shoot(){
    if(color == RED)     //黄色は青のところから投げるよー
        turn(-80, FAST);  
    else if(color == YELLO)
        turn(40.75, FAST);
    
    wait(WAIT_DELTA_T);
    servo_throw();
    wait(WAIT_DELTA_T);
    
    servo_ini();
    wait(WAIT_DELTA_T);
    turn_off();
    
    if(color == RED)
        turn(-100, FAST);
    else if(color == YELLO)
        turn(139.25, FAST);
    else
        turn(180, FAST);
    wait(0.25);
}
//*/