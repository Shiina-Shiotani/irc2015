//switchで使う時の状態を格納，上から0,1,2な感じ
GLOBAL enum state{
    init_state,         //初期設定
    free_ball,          //スタートから探索エリアまで
    ball_search,        //ボール探索
    ball_shoot,         //各ボールシュート
    area_move,          //ボールが見つからない場合、探索エリアを移動
    finish
}state;

//state.cpp
GLOBAL void initialize();
GLOBAL void fine(int num);
GLOBAL float l_time;
GLOBAL int ball_count;