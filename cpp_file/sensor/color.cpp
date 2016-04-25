#include "Comet.h"

I2C colorSensor(p9,p10);
BusOut LED(LED1, LED2, LED3, LED4);

int R,G,B,IR;       //赤，緑,青，赤外
//途中にあるwaitはおそらく最低1秒はほしいかなー
//短いと値取得が不可能だった

//カラーセンサの値を取得する関数
void  get_color_value() {
    char data[8];
    int tmp;
    //start condition
    colorSensor.start();
    //device address
    colorSensor.write(0x54);
    //controll register
    colorSensor.write(0x00);
    //ADC reset enable
    colorSensor.write(0x84);

     //manual timing register 01
     colorSensor.write(0x01);
        
     //値変えれば変わるはず・・・（多分）
     //set manual timing reister 01
     colorSensor.write(0x03);
     //manual timing register 02
     colorSensor.write(0x02);
     //set manual timing register 02
     colorSensor.write(0xC0);
                
    //start condition
    colorSensor.start();
    //device address
    colorSensor.write(0x54);
    //controll register
    colorSensor.write(0x00);
    //ADC reset disable
    colorSensor.write(0x04);
    //stop condition
    colorSensor.stop();
    
    //ここのwait最低何秒だろー？
    wait(1.0);
        
    //start condition
    colorSensor.start();
    //device address
     colorSensor.write(0x54);
    //output databyte set
    colorSensor.write(0x03);
            
    //read sensor
    colorSensor.read(0x55, data, 8);
        
    for(int i=0; i<8; i=i+2){
        tmp = data[i] << 8;  //16bitで出すため8bitシフト
        tmp += data[i+1];
        //printf("%d\t",tmp);  
        if(i== 0){
            R = tmp;
        }else if(i == 2){
            G = tmp;
        }else if(i == 4){
            B = tmp;
        }else {
            IR = tmp;
        }
    }
    //printf(\n);
    colorSensor.stop();
}

//センサで取得した値から何色かを識別する関数
int what_color(){
    get_color_value();
    if(IR > 20){
        //ボールを持っているかの確認
        //printf("\tno_ball\n");
        return NO_BALL;
       
    }
    else{
        if(R > 35 && G < 40 && B < 35){
            //赤色だよー
            //printf("\tred\n");
            return RED;
        }
        else if(R < 30 && G < 35 && B < 38){      //if( R < 50 && G > 30 && B > 50)
            //青色だよー
            //printf("\tblue\n");
            return BLUE;
        }
        //ここの閾値がなんかなー
        else{ //if(R > 50 && G > 50 && B > 20){       // if(R > 90 && G > 100 && B > 40)
            //それ以外は黄色じゃね？
            //printf("\tyello\n");
            return YELLO;
        }
        
    }
}

//色識別の確認用関数
void debug_color(int b_color){
    if(b_color == 0)    //ボールを持っていないときは消灯
        LED = 0;
    else                //ボールを持っているときは対応（？）のLEDを点灯
        LED = 1 << b_color;
}

//busout の使用がよく分からないから用意
void turn_off(){
    LED = 0;
}
