#include "Comet.h"
#include "QEI.h"

#define PI 3.141592

QEI r_wheel(p28, p27, NC , ROTATE_PER_REVOLUTION ,QEI::X4_ENCODING);
QEI l_wheel(p29, p30, NC , ROTATE_PER_REVOLUTION ,QEI::X4_ENCODING);

//ファイルを使うときに外す
//LocalFileSystem local("local");
DigitalOut myled(LED4);

//Ticker encoder;     //エンコーダ用割り込み
Ticker odome;       //オドメトリ用割り込み

float l_Rad=0.0;
float g_Rad=0.0;       //グローバル座標系の角度[rad]
int cnt = 0, n = 0;

//割り込み周期の関係でwaitをかけなくてもOK
void encoder_read(){
    r_pulses = r_wheel.getPulses();    l_pulses = l_wheel.getPulses();
    r_wheel.reset();        l_wheel.reset();
}

//オドメトリの計算
void odometry(){
    float v;       //現在の速度 
    r_pulses = r_wheel.getPulses();    l_pulses = l_wheel.getPulses();
    
    //角速度の計算
    //角速度＝パルスの偏差÷(1回転あたりのパル×分解能)÷読み込み時間÷ギア比×２π
    r_omega = (float)r_pulses / (ROTATE_PER_REVOLUTION * BUNKAINOU ) / DELTA_T / GEAR * PI * 2.0;
    l_omega = (float)l_pulses / (ROTATE_PER_REVOLUTION * BUNKAINOU ) / DELTA_T / GEAR * PI * 2.0;
    
    //全体の速度，角速度の計算
    v = WHEEL_RADIUS * (r_omega + l_omega) /2.0;
    omega = WHEEL_RADIUS *( r_omega - l_omega ) / T;
        
    //角度を計算
    l_Rad = omega * DELTA_T;
    g_Rad += l_Rad;
    l_theta += l_Rad * 180.0 / PI;
    g_theta = g_Rad * 180.0 / PI;
    if(g_theta >= 360) g_theta -= 360;
    else if(g_theta <= -360) g_theta += 360;
    
    //座標の計算

    l_X += v * sin(l_Rad) * DELTA_T;
    l_Y += v * cos(l_Rad) * DELTA_T;
    g_X += v * sin(g_Rad) * DELTA_T;
    g_Y += v * cos(g_Rad) * DELTA_T;
    printf("%lf, %lf, %lf\n", l_X, l_Y, l_theta);
/*    cnt++;
    if(cnt == 25){
        coordinates[n][0] = l_X;
        coordinates[n][1] = l_Y;
        coordinates[n][2] = l_theta;
        n++;
        cnt = 0;
    }
//    printf("%lf, %lf, %lf\n", l_X, l_Y, l_theta);
*/    
    r_wheel.reset();        l_wheel.reset();
    l_time += DELTA_T;
}


///*
//割り込みの処理をするかどうかの関数
//条件の変数はint型でもOK boolでもOKだった
//flag がON の時は割り込みし続ける
//複数の割り込み同間隔で行う場合は上にある方から処理していく
void switch_encoder(){
    r_wheel.reset();        l_wheel.reset();
    if(encoder_flag){
        //ここで割り込み開始
//        encoder.attach(&encoder_read, DELTA_T);
        odome.attach(&odometry, DELTA_T);
    }
    else{
        //ここで割り込み終了
//        encoder.detach();
        odome.detach();
    }
}
//*/

/*
void switch_file(){
    if(file_flag){
        FILE *fp;

        if( (fp = fopen( "/local/TEST.TXT", "w" )) == NULL )
            error( "" );
        else{
            myled = 1;
            for( int i = 0; i < n; i++ ) {
                fprintf( fp, "%lf %lf %lf\n", coordinates[i][0], coordinates[i][1], coordinates[i][2] );
                wait(0.1);
            }
            myled = 0;
            fclose(fp);
            //servo_throw();
        }
    }
    else{
    }
}
*/

///*
//ローカルなオドメトリのリセット
//何もないところでリセットするのはどうかと思うけど・・・
void l_odometry_reset(){
    l_X = 0.0;
    l_Y = 0.0;
    l_theta = 0.0;
}
//*/