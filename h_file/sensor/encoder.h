//encoder.cpp
GLOBAL bool encoder_flag;               //エンコーダ＆オドメトリのフラグ
GLOBAL void switch_encoder();
//GLOBAL bool file_flag;
//GLOBAL void switch_file();
//GLOBAL float coordinates[500][3];
GLOBAL void l_odometry_reset();         //現在のロボットの位置を基準にする関数
GLOBAL int r_pulses,l_pulses;           //左右のパルス
GLOBAL float r_omega,l_omega,omega;    //左右輪の回転角速度[rad/sec]
GLOBAL float g_X;                      //グローバルなx
GLOBAL float g_Y;                      //グローバルなy
GLOBAL float g_theta;                  //グローバルな角度[deg]
GLOBAL float l_X;                      //ローカルなx
GLOBAL float l_Y;                      //ローカルなy
GLOBAL float l_theta;                  //ローカルな角度[deg]