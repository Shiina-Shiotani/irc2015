#include "Comet.h"

BusIn photo(p5, p6, p7, p8);    //左から順に2進数計算

void Line_Trace(int cross_line_count){
    float limit = 0.2;
    float timer = 0.0;
    int count = 0;
    
    if(cross_line_count != 0){
        for(int i = 0; i < 450; i+=90){
            PID(i, i);
            wait(DELTA_T);
        }
    }
    
    while( count != cross_line_count ){
        
        if(photo == 0 || photo == 1  || photo == 8){    //クロスライン
            if(timer > limit){
                timer = 0.0;
                count++;
                //printf("%d\n",count);
            }
            PID(450, 450);
        }    
        else if(photo == 11)                      //l反応
            PID(70, 450);
        else if(photo == 3 || photo == 7)           //ll, ll+l反応
            PID(50, 450);
        else if(photo == 13)                      //r反応
            PID(450, 10);
        else if(photo == 12 || photo == 14)         //rr, rr+r反応
            PID(450, 10);
        else                                        //その他
            PID(450, 450);
        timer += DELTA_T;
    }
    stop();
    l_odometry_reset();
}

void Line_Trace(){
    if(photo == 7 || photo == 11)                          //l が反応
        PID(100, 350);                       
    else if(photo == 13 || photo == 14)                    //r が反応
        PID(350, 100);
    else                                   //その他は前進
        PID(350, 350);
}