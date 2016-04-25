#define GLOBAL_INSTANCE
#include "Comet.h"

#define RIGHT true
#define LEFT false

/*
int main(){
    initialize();
    int ball_count = 0;
    
    g_turn(180);
    while(ball_count < 3){
        serch();
        g_turn(0);
        wait(1);
        for(int i = 0; i < 2; i++){
            color = what_color();
        }
    
        Line_Trace(color);
        if(color != NO_BALL){
            Ball_Shoot();
            ball_count++;
        }
        Line_Trace(color);
        
        l_odometry_reset();
        turn(180, FAST);
        g_theta = 0.0;
        
        wait(2);
    }
    while(1){
        stop();
    }
}
*/

//--------------------------------------------------------------------------------------

/*
int main(){     //�{�[���V���[�g�m�F�p    (�{�[���͎蓮�ŃJ�b�v�ɏ悹��)
    initialize();
    
    int ball_count = 0;
//    state = init_state;

    while(ball_count < 15){
        wait(1);
        for(int i = 0; i < 2; i++){
            color = what_color();
        }
    
        Line_Trace(color);
        if(color != NO_BALL){
            Ball_Shoot();
            ball_count++;
        }
        Line_Trace(color);
        
        l_odometry_reset();
        turn(180, FAST);
        g_theta = 0.0;
        
        wait(2);
    }
}
*/

//----------------------------------------------------------------------------------------------------------

/*
int main(){     //�G���A�ړ��m�F�p
    initialize();
    bool area_flag = OFF;
    
    while(1){
        serch();
        color = what_color();
        g_turn(0);
        if(color != 0){
            move_flag = OFF;
            printf("a");
        }
        if(move_flag){
            for(float i = 0; i < 1.5; i+=DELTA_T){
                PID(200, 200);
            }
            PSD_reset();
            area_flag = ON;
            
        }
        else{
            printf("\n");
            turn(180, FAST);
            if(area_flag){
                Line_Trace(1);
            }
        }
    }
}
*/

//-------------------------------------------------------------------------------------------------------------------

/*
int main(){     //Line_Trace �m�F�p   (���ɋȂ���p)
                //Line_Trace �֐��������ς���K�v����
    initialize();
    
    while(1){
        Line_Trace(2);
        wait(0.2);
        turn(180.0,FAST);
        stop();
    }
}
*/

//--------------------------------------------------------------------------------------------------------------------------

/*
int main(){     //�J���[臒l�m�F�p
    initialize();
    
    while(1){
        what_color();
    }
}
*/

//--------------------------------------------------------------------------------------------------------------------------

/*
int main(){
    initialize();
    int mode = 0;       //0:turn, 1:g_turn
    
//    while(1){
        if(mode == 0){
            turn(180, SLOW);
            turn(-180, FAST);
        }else if(mode == 1){
            g_turn(0);
            g_turn(180);
        }
//    }
}
*/

//-----------------------------------------------------------------------------------------------------------------------------

/*
int main(){     //PID�����p
    initialize();
    int l = 50, r = 50;
    
    while(1){
       for(float i = 0; i < 1.0; i+=DELTA_T){
            PID(l, r);
        }
        stop();
        wait(1);
        for(float i = 0; i < 1.0; i+=DELTA_T){
            PID(-l, -r);
        }
        stop();
        wait(1);
        
        l += 50;
        r += 50;
        
        if(l == 450 || r == 450) break;
    }
    
    stop();
}
*/

//-------------------------------------------------------------------------------------------------------------

/*
int main(){     //�T�[�{����m�F�p
    initialize();
    while(1){
        color = what_color();
        printf("%d\n",color);
        wait(1);
        if(color == RED){
            turn(57, FAST);
            wait(1);
        }
        else if(color == YELLO){     //�Ԃ����F��������E��������
            turn(40, FAST);
            wait(1);  
        }
        servo_throw();
        wait(1);
    
        servo_up2();
        wait(1);
        if(color == RED){
            turn(-57, FAST);
            wait(1);
        }
        else if(color == YELLO){     //�Ԃ����F��������E��������
            turn(-40, FAST);
            wait(1);  
        }
    }
//    servo_throw();
//    servo_ready();
//    servo_up();
//    servo_catch();
}
*/

//-------------------------------------------------------------------------------------------------------------        

/*
int main(){     //�T������m�F�p
    initialize();
    search(); 
}
*/

//-------------------------------------------------------------------------------------------------------------

///*
int main(){     //��3�񎎑���p
    
    
    float serch_posi = 0.0;
    float move_dis = 0.0;
    state = init_state;
    
    while(1){       //while�J�n
        switch(state){
            case init_state:
                initialize();
                state = free_ball;
                //state = ball_search;
                break;
            
            case free_ball:
                Line_Trace(3);
                turn(85.0, FAST);
                wait(WAIT_DELTA_T);
                servo_throw();
                wait(WAIT_DELTA_T);
                servo_ini();
                wait(WAIT_DELTA_T);
                turn(-85.0,FAST);
                Line_Trace(2);
                state = ball_search;
                break;
                
            case ball_search:
                    
                if(move_flag){
                    while(l_Y <= move_dis)
                        Line_Trace();
                    stop();
                    move_flag = OFF;
                }
                else{
                    if(color != NO_BALL){
                        while(l_Y <= serch_posi)
                            Line_Trace();
                        stop();
                    }
                }
                
                if((l_time+25) > LIMIT && color == NO_BALL){
                    //turn(-1 * serch_data[0][1] + 90, FAST);     //���ʂ�����
                    state = finish;
                    break;
                }
                if(serchRight_flag)
                    search(RIGHT);
                else
                    search(LEFT);
                state = ball_shoot;
                break;
                
            case ball_shoot:
  /*              �����Ȃ��Ƃ��ɂ��悤
                wait(WAIT_DELTA_T);
                if(color != NO_BALL){         //�F�𓾂�ꂽ��
                    if(areaChange_flag)
                        Line_Trace(color + 1);
                    else
                        Line_Trace(color);
                    Ball_Shoot();
                    ball_count++;
                    if(ball_count == B_GOAL || (l_time+25) > LIMIT){
                        state = finish;
                        break;
                    }
                    Line_Trace(color);
                }
                //�ڕW�܂ōs�������̊m�F
                state = ball_search;
                color = NO_BALL;               
                if(move_flag)
                    state = area_move;
                break;
    */        
                //������Ƃ��Ɏg�p
                if(color != NO_BALL){         //�F�𓾂�ꂽ��
                    if(areaChange_flag){
                        if(color == YELLO)
                            Line_Trace(color);
                        else
                            Line_Trace(color + 1);
                        
                    }
                    else{
                        if(color == YELLO)
                            Line_Trace(color - 1);
                        else
                            Line_Trace(color);
                    }
                    
                    Ball_Shoot();
                    ball_count++;
                    if(ball_count == B_GOAL || (l_time+25) > LIMIT){
                        state = finish;
                        break;
                    }
                    if(color == YELLO)
                        Line_Trace(color - 1);
                    else
                        Line_Trace(color);
                }
                
                //�ڕW�܂ōs�������̊m�F
                if(ball_count == B_GOAL){
                    state = finish;
                }else{
                    state = ball_search;
                }
                //color = NO_BALL;               
                if(move_flag)
                    state = area_move; 
                break;
                      
            case area_move:
                move_dis = 200;
                if(serch_posi >= 1200 - move_dis)      //�s���߂��h�~�p
                    move_dis = 0;
                serch_posi += move_dis;
                areaChange_flag = ON;
                serchRight_flag = ON;
                state = ball_search;
                break;
            
            case finish:
                fine(3);
                break;
            
        }//switch�I��
    }//while�I��
}//main�I��
//*/