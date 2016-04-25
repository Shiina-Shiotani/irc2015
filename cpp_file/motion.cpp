#include "Comet.h"

void ball_catch(bool serch_deg);

///*��~�p�֐�
void stop(){
    for(float i = 0.0; i < 0.2; i += DELTA_T){
        l_integral=0;   r_integral=0;
        PID(0,0);
    }
}

//�{�[�������p�֐�
void tansaku(){
    serch_data[1][0] = Get_PSD_low();   serch_data[1][1] = l_theta;
    float high = 66.294 * pow((double)Get_PSD_high(), -1.218);
    
    //�����͌�ŕς��悤
    if(high <= 600){   //high >= 0.24   �@�\���Ȃ������������
        if(serch_data[0][0] < serch_data[1][0] ){   //�X�V
            serch_data[0][0] = serch_data[1][0];
            serch_data[0][1] = serch_data[1][1];
         }
    }
    //printf("%lf\n", high);
}

///*��]�p�֐�
//�p�x���������ƒx������2�̃��[�h���w�肷��
//������deg�͂ǂꂭ�炢��]���������̊p�x
void turn(float deg, bool mode){
    l_odometry_reset();
    if(mode){       //������
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 6.5){   //�E��]
                PID(250,-250);
            }       
        }
        else{
            while( ( l_theta - deg ) < -6.5){   //����]
                PID(-250,250);
            }
        }
    }
    else{       //�x�������Ƃ͓���
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 0.1){   //�E��]
                tansaku();
                PID(150,-150);
             }
        }
        else{
            while( ( l_theta - deg ) < -0.1){   //����]
                tansaku();
                PID(-150,150);
            }
        }
    }
    stop();
}
//*/

/*
//�O���[�o�����W�n�ŉ�]����֐�
//���x���ȁ[(�L;��;�M)
void g_turn(float deg){
    l_odometry_reset();
    if(g_theta > deg ){
        while( ( g_theta - deg ) > 0.1){   //�E��]
            PID(200,-200);
        }
    }
    else{
        while( ( g_theta - deg ) < -0.1){   //����]
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
    
    if(serch_dis <= 370 ){      //�T���G���A�̕��I��400(���ۂ�350�t��)
        if(serch_deg)
            if(serch_data[0][1] >= -40)
                turn(serch_data[0][1]+92, FAST);    //�E��
            else
                turn(serch_data[0][1]+95, FAST);
        else{
            if(serch_data[0][1] <= 40)
                turn(serch_data[0][1]-98, FAST);
            else
                turn(serch_data[0][1]-98, FAST);    //����
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
        debug_color(color);                             //�F�̃f�o�b�N�p
        if(color != NO_BALL){
            if(serch_deg)
                turn(-1 * serch_data[0][1] - 187, FAST);     //��������(�E��])
            else
                turn(-1 * serch_data[0][1] + 172, FAST);     //��������(����])175
        }
        else{
            if(serch_deg)
                turn(-1 * serch_data[0][1] +5, FAST);
            else
                turn(-1 * serch_data[0][1] +4, FAST);     //���ʂ����� 2
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



/*�����Ȃ��֐�
//����p�֐�
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

//�{�[���Ԃ񓊂���p�֐�
//�g�����͕�����Ȃ�
///*����p�֐�
void Ball_Shoot(){
    if(color == RED)     //���F�͐̂Ƃ��납�瓊�����[
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