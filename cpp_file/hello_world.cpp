#include "Comet.h"

////////���̊֐��͊��荞�ݏ������O���̊֐��ł������ł��邩�̃e�X�g////////
////////���ۂ͎g��Ȃ��̂ō폜����///////////////////////////////////
///////�Ԃ����Ⴏ�����̃e�X�g�p//////////////////////////////////////

//���̊֐��͐������Ă���
DigitalOut nya(LED1);
Ticker hello_world;

void hello(){
    printf("hello world\n");
    nya = 1 ;
    wait(1);
    printf("The world\n\n");
    nya = 0;   
}

//���荞�݂̏��������邩�ǂ����̊֐�
//�����̕ϐ���int�^�ł�OK bool�ł�OK������
void switch_hello(){
    if(guhu){
        //�����Ŋ��荞�݊J�n
        hello_world.attach(&hello, 3);
    }else{
        //�����Ŋ��荞�ݏI��
        hello_world.detach();
        printf("good bye\n");
    }
}