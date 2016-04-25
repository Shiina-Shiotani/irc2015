#include "Comet.h"
#define NUM 5      //読み込むデータ数

//PSDセンサの読み込みとフィルタリングするためのもの

AnalogIn high(p20),low(p19);     

//ソート用フラグqsortで使う
int float_sort(const void* x,const void* y) {
    const float* high=(const float*)x;
    const float* low=(const float*)y;
    if(*high>*low)return 1;
    if(*high<*low)return -1;
    return 0;
}

//PSDの値を取得する関数×2
float Get_PSD_high() {
    float data[NUM] = {};
    int i;
    
    for(i = 0; i < NUM; i++){
        data[i] = high.read();
//        wait(PSD_DELTA_T);
    }
    
    qsort(data, NUM, sizeof(float), float_sort);

    return data[(NUM - 1) / 2];
}

float Get_PSD_low() {
    float data[NUM] = {};
    int i;
    
    for(i = 0; i < NUM; i++){
        data[i] = low.read();
    }
    
    qsort(data, NUM, sizeof(float), float_sort);

    return data[(NUM - 1) / 2];
}

void PSD_reset(){
    serch_data[0][0] = 0.0;
    serch_data[0][1] = 0.0;
    serch_data[1][0] = 0.0;
    serch_data[1][1] = 0.0;
}