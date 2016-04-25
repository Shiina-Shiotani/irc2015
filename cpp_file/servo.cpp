#include "Comet.h"

unsigned char tx1_[13][4]; // 送信用のデータidは13個までOK
Serial servo(p13,p14);

//posは3500～11000までなはず
void set_servo_angle(unsigned char id, int pos){
    servo.baud(115200);
    servo.format(8, Serial::Even,1);
    int i;
    tx1_[id][0] = 0x80 | id;
    tx1_[id][1] = (pos >> 7 & 0x7F);
    tx1_[id][2] = (pos & 0x7F);
    
    for (i = 0; i < 3; i++){
        servo.putc(tx1_[id][i]); // コマンドを１バイトずつ送信する
    }
}

//サーボを一番上に上げてハンドを開く
void servo_ini(){
    set_servo_angle(SERVO_0,SERVO_0_UPWARD);
    wait(WAIT_DELTA_T);
    set_servo_angle(SERVO_1,SERVO_1_OPEN);
}

void servo_throw(){
/*    for(int n = SERVO_0_UPWARD; n < SERVO_0_THROW; n += 8){
        set_servo_angle(SERVO_0,n);
        wait_ms(1.5);
    }
*/
    set_servo_angle(SERVO_0, SERVO_0_THROW);
    wait(WAIT_DELTA_T);
}

//サーボを下げるだけ
void servo_ready(){
    for(int n = SERVO_0_UPWARD; n < SERVO_0_LOWER; n += 5){
        set_servo_angle(SERVO_0,n);
        wait_ms(1.5);
    }
    wait(WAIT_DELTA_T);
}

void servo_up(){
    for(int n = SERVO_0_LOWER; n > SERVO_0_UPWARD; n -= 5){
        set_servo_angle(SERVO_0,n);
        wait_ms(1.5);
    }
    wait(WAIT_DELTA_T);
}

/*
void servo_up2(){
    for(int n = SERVO_0_THROW; n > SERVO_0_UPWARD; n -= 5){
        set_servo_angle(SERVO_0,n);
        wait_ms(1.5);
    }
    wait(0.25);
}
*/

//ボールをキャッチして上にしてポケットにボールを入れるまで
void servo_catch(){
    set_servo_angle(SERVO_1, SERVO_1_CLOSE);
    wait(WAIT_DELTA_T);
    servo_up();
    set_servo_angle(SERVO_1, SERVO_1_OPEN);
    wait(WAIT_DELTA_T);
}

void servo_performance(int ball_count){
    for(int i = 0; i < ball_count; i++){
        set_servo_angle(SERVO_1, SERVO_1_CLOSE);
        wait(0.5);
        set_servo_angle(SERVO_1, SERVO_1_OPEN);
        wait(0.5);
    }
}