//////ロボットの情報を格納するファイル/////////
#define WHEEL_RADIUS 25.5           //車輪半径[mm]
#define GEAR 44.0                     //ギア比
#define T 190.0                       //車輪間距離[mm]

#define ROTATE_PER_REVOLUTION 100.0   //1回転あたりのパルス
#define BUNKAINOU 4.0                //分解能

#define DELTA_T 0.005                //制御周期0.02[s]=20[ms]
#define WAIT_DELTA_T 0.2             //wait用 delta_t

///////////////サーボモータ用変数を格納/////////////////////////
/////////////////////id 0が下////////////////////////////////
#define SERVO_0 0                                       
#define SERVO_0_UPWARD 4900                                 
#define SERVO_0_LOWER 7500                               
#define SERVO_0_THROW 7100                             
                                                        
#define SERVO_1 1                                       
#define SERVO_1_OPEN 7500                               
#define SERVO_1_CLOSE 11500                              
////////////////////////////////////////////////////////////

//中心からの距離
//使わない可能性が・・・
#define PHOTO_LL -40                    //一番左のセンサの距離
#define PHOTO_L -20                     //中心左のセンサの距離
#define PHOTO_R 20                      //中心右のセンサの距離
#define PHOTO_RR 40                     //一番右のセンサの距離

//////////制御するときに使用//////////////////
#define PID_R_KP -0.24      //Pゲイン      -0.19   //0.24
#define PID_R_KI -0.39      //Iゲイン      -0.38   //0.19     
#define PID_R_KD 0.0        //Dゲイン

#define PID_L_KP -0.22      //Pゲイン      -0.26   //0.22
#define PID_L_KI -0.38      //Iゲイン      -0.36   //0.18
#define PID_L_KD 0.0        //Dゲイン

#define LINE_KP 0.0         //ライントレース用Pゲイン
#define LINE_KI 0.0         //Iゲイン
#define LINE_KD 0.0         //Dゲイン