#include <Mouse.h>
#include <Keyboard.h>

#define BTN_L_STK_TRIG_A 18  //A0 親指丸ボタン
#define BTN_L_STK_TRIG_B 19  //A1 人差し指トリガーボタン
#define BTN_L_STK_UP 9
#define BTN_L_STK_DOWN 10
#define BTN_L_STK_LEFT 11
#define BTN_L_STK_RIGHT 12
#define BTN_R_STK_TRIG_A 20  //A0 親指丸ボタン
#define BTN_R_STK_TRIG_B 21  //A1 人差し指トリガーボタン
#define BTN_R_STK_UP 5
#define BTN_R_STK_DOWN 6
#define BTN_R_STK_LEFT 7
#define BTN_R_STK_RIGHT 8
#define BTN_R_STK_TRIG_C 3  // 追加ボタン
#define BTN_L_STK_TRIG_C 4  // 追加ボタン
#define BTN_EX_1 22         // 追加ボタン
#define LED0 13             // Arduino基板上のLED
#define FRAME_DURATION 10
#define FRAME_TWICE_INPUT_INTERVAL_L_STK 15
#define FRAME_TWICE_INPUT_INTERVAL_R_STK 22
#define Y_DIFF 10

bool LED_CHECK1 = true;
int y_dist = 0;  // y軸リセット用のキープ値
int y_times = 0; // y軸リセット用のキープ値

int stk_R_left_wait = 0; // 連続入力判定の待ち時間用変数
int stk_R_left_nomal_turn_angle = -9; // 1フレームでのマウス移動量(最大-127程度)
int stk_R_left_quick_turn_angle = -120; // 1フレームでのマウス最大移動量(最大127程度)
int stk_R_left_quick_turn_times = 2; // 連続入力時のstk_R_right_quick_turn_angle 実行回数
bool stk_R_left_past = false; // 連続入力判定用のフラ

int stk_R_right_wait = 0;
int stk_R_right_nomal_turn_angle = 9; 
int stk_R_right_quick_turn_angle = 120;
int stk_R_right_quick_turn_times = 2;
bool stk_R_right_past = false;

int stk_R_down_wait = 0;
int stk_R_down_quick_turn_angle = -120;
int stk_R_down_quick_turn_times = 2;
bool stk_R_down_past = false;

int stk_L_up_wait = 0;
bool stk_L_up_past = false;

int stk_L_down_wait = 0;
bool stk_L_down_past = false;

int stk_L_right_wait = 0;
bool stk_L_right_past = false;

int stk_L_left_wait = 0;
bool stk_L_left_past = false;

/* タイマー管理用の変数 */
long mrd_t_mil = (long)millis();  // フレーム管理時計の時刻 Meridian Clock.
long now_t_mil = (long)millis();  // 現在時刻を取得
long now_t_mic = (long)micros();  // 現在時刻を取得
//
void setup() {
  pinMode(BTN_L_STK_TRIG_A, INPUT_PULLUP);
  pinMode(BTN_L_STK_TRIG_B, INPUT_PULLUP);
  pinMode(BTN_L_STK_UP, INPUT_PULLUP);
  pinMode(BTN_L_STK_DOWN, INPUT_PULLUP);
  pinMode(BTN_L_STK_LEFT, INPUT_PULLUP);
  pinMode(BTN_L_STK_RIGHT, INPUT_PULLUP);
  pinMode(BTN_R_STK_TRIG_A, INPUT_PULLUP);
  pinMode(BTN_R_STK_TRIG_B, INPUT_PULLUP);
  pinMode(BTN_R_STK_UP, INPUT_PULLUP);
  pinMode(BTN_R_STK_DOWN, INPUT_PULLUP);
  pinMode(BTN_R_STK_LEFT, INPUT_PULLUP);
  pinMode(BTN_R_STK_RIGHT, INPUT_PULLUP);
  pinMode(BTN_L_STK_TRIG_C, INPUT_PULLUP);
  pinMode(BTN_R_STK_TRIG_C, INPUT_PULLUP);
  pinMode(BTN_EX_1, INPUT_PULLUP);
  pinMode(LED0, OUTPUT);
  Mouse.begin();
  Keyboard.begin();

  //Serial.begin(115200);
  mrd_t_mil = (long)millis();
}

void loop() {

  LED_CHECK1 = false;


  // LEFT & RIGHT STICK COUNTDOWN /////////////////////////////////////////////////////////////////////////////////////
  if (stk_L_left_wait > 0) {
    stk_L_left_wait -= 1;
  }

  if (stk_L_right_wait > 0) {
    stk_L_right_wait -= 1;
  }

  if (stk_R_left_wait > 0) {
    stk_R_left_wait -= 1;
  }

  if (stk_R_right_wait > 0) {
    stk_R_right_wait -= 1;
  }

  // ALL BUTTONS //////////////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(BTN_EX_1) == LOW) {  //追加ボタン（でかい赤ボタン）
    Keyboard.press('p');
    LED_CHECK1 = true;
  } else {
    Keyboard.release('p');
  }

  if (digitalRead(BTN_L_STK_TRIG_B) == LOW) {  //左スティック_人差し指トリガー
    Keyboard.press('j');
    LED_CHECK1 = true;
  } else {
    Keyboard.release('j');
  }

  if (digitalRead(BTN_L_STK_TRIG_A) == LOW) {  //左スティック親_指丸ボタン
    //Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('h');
    LED_CHECK1 = true;
  } else {
    //Keyboard.release(KEY_LEFT_SHIFT);
    Keyboard.release('h');
  }

  if (digitalRead(BTN_R_STK_TRIG_A) == LOW) {  //右スティック親_指丸ボタン
    Keyboard.press('m');
    /*
    LED_CHECK1 = true;
    y_times = abs(int(float(y_dist) / 100));
    for (int i = 0; i < (y_times-1); i++) {  //
      if (y_dist > 0) {
        Mouse.move(0, -100);
      } else {
        Mouse.move(0, 100);
      }
      delay(FRAME_DURATION);
    }
    Mouse.move(0, -int(y_dist % 100));
    y_dist = 0;
    */
  } else {
    Keyboard.release('m');
  }

  if (digitalRead(BTN_R_STK_TRIG_B) == LOW) {  //右スティック_人差し指トリガー
    Keyboard.press('l');
    LED_CHECK1 = true;
  } else {
    Keyboard.release('l');
  }

  if (digitalRead(BTN_L_STK_TRIG_C) == LOW) { //左親指追加ボタン
    Keyboard.press('i');
    LED_CHECK1 = true;
  } else {
    Keyboard.release('i');
  }

  if (digitalRead(BTN_R_STK_TRIG_C) == LOW) { // 右親指追加ボタン
    Keyboard.press('o');
    LED_CHECK1 = true;
  } else {
    Keyboard.release('o');
  }


  // LEFT STICK LEVER ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(BTN_L_STK_UP) == LOW) {
    LED_CHECK1 = true;
    if (stk_L_up_wait > 0) {
      Keyboard.press('w');
      Keyboard.release(KEY_LEFT_ARROW);
      delay(2);
      Keyboard.press(KEY_LEFT_ARROW);
      delay(14);
      Keyboard.release(KEY_LEFT_ARROW);
      stk_L_up_wait = 0;
    } else {
      Keyboard.press('w');
      stk_L_up_past = true;
    }
  } else {
    if (stk_L_up_past) {
      stk_L_up_past = false;
      stk_L_up_wait = 25;
    }
    Keyboard.release('w');
  }

  if (digitalRead(BTN_L_STK_DOWN) == LOW) {
    LED_CHECK1 = true;
    if (stk_L_down_wait > 0) {
      Keyboard.press('s');
      Keyboard.release(KEY_LEFT_ARROW);
      delay(2);
      Keyboard.press(KEY_LEFT_ARROW);
      delay(14);
      Keyboard.release(KEY_LEFT_ARROW);
      stk_L_down_wait = 0;
    } else {
      Keyboard.press('s');
      stk_L_down_past = true;
    }
  } else {
    if (stk_L_down_past) {
      stk_L_down_past = false;
      stk_L_down_wait = FRAME_TWICE_INPUT_INTERVAL_R_STK;
    }
    Keyboard.release('s');
  }

  if (digitalRead(BTN_L_STK_LEFT) == LOW) {
    LED_CHECK1 = true;
    if (stk_L_left_wait > 0) {
      Keyboard.press('a');
      Keyboard.release(KEY_LEFT_ARROW);
      delay(2);
      Keyboard.press(KEY_LEFT_ARROW);
      delay(14);
      Keyboard.release(KEY_LEFT_ARROW);
      stk_L_left_wait = 0;
    } else {
      Keyboard.press('a');
      stk_L_left_past = true;
    }
  } else {
    if (stk_L_left_past) {
      stk_L_left_past = false;
      stk_L_left_wait = 20;
    }
    Keyboard.release('a');
  }

  if (digitalRead(BTN_L_STK_RIGHT) == LOW) {
    LED_CHECK1 = true;
    if (stk_L_right_wait > 0) {
      Keyboard.press('d');
      Keyboard.release(KEY_LEFT_ARROW);
      delay(2);
      Keyboard.press(KEY_LEFT_ARROW);
      delay(14);
      Keyboard.release(KEY_LEFT_ARROW);
      stk_L_right_wait = 0;
    } else {
      Keyboard.press('d');
      stk_L_right_past = true;
    }
  } else {
    if (stk_L_right_past) {
      stk_L_right_past = false;
      stk_L_right_wait = 20;
    }
    Keyboard.release('d');
  }


  // RIGHT STICK LEVER
  if (digitalRead(BTN_R_STK_UP) == LOW) {
    Mouse.move(0, Y_DIFF);
    y_dist += Y_DIFF;
    LED_CHECK1 = true;
  } else {
    //
  }

  if (digitalRead(BTN_R_STK_DOWN) == LOW) {
    Mouse.move(0, -Y_DIFF);
    y_dist -= Y_DIFF;
    LED_CHECK1 = true;
  } else {
    //
  }

  if (digitalRead(BTN_R_STK_LEFT) == LOW) {
    LED_CHECK1 = true;
    if (stk_R_left_wait > 0) {
      for (int i = 0; i < stk_R_left_quick_turn_times; i++) {  //4 -120 で90度
        Mouse.move(stk_R_left_quick_turn_angle, 0);
        delay(FRAME_DURATION);
      }
      stk_R_left_wait = 0;
    } else {
      Mouse.move(stk_R_left_nomal_turn_angle, 0);
      stk_R_left_past = true;
    }
  } else {
    if (stk_R_left_past) {
      stk_R_left_past = false;
      stk_R_left_wait = FRAME_TWICE_INPUT_INTERVAL_L_STK;
    }
  }

  if (digitalRead(BTN_R_STK_RIGHT) == LOW) {
    if (stk_R_right_wait > 0) {
      for (int i = 0; i < stk_R_right_quick_turn_times; i++) {  //4 120 で90度 2,120で実践向き
        Mouse.move(stk_R_right_quick_turn_angle, 0);
        delay(FRAME_DURATION);
      }
      LED_CHECK1 = true;
      stk_R_right_wait = 0;
    } else {
      Mouse.move(stk_R_right_nomal_turn_angle, 0);
      LED_CHECK1 = true;
      stk_R_right_past = true;
    }
  } else {
    if (stk_R_right_past) {
      stk_R_right_past = false;
      stk_R_right_wait = FRAME_TWICE_INPUT_INTERVAL_L_STK;
    }
  }


  digitalWrite(LED0, LED_CHECK1);

  //////// フ レ ー ム 終 端 処 理 ///////////////////////////////////////////////

  // フレーム内の処理に対し時間が余っていたら時間消化。時間がオーバーしていたらこの処理を自然と飛ばす。
  now_t_mil = (long)millis();
  now_t_mic = (long)micros();  // 現在時刻を取得
  while (now_t_mil < mrd_t_mil) {
    now_t_mil = (long)millis();
  }
  // フレーム管理時計のカウントアップ
  mrd_t_mil = mrd_t_mil + FRAME_DURATION;  // フレーム管理時計を1フレーム分進める
  if (y_times > 0) {
    mrd_t_mil = (y_times + 1) * FRAME_DURATION;
    y_times = 0;
  }
}
