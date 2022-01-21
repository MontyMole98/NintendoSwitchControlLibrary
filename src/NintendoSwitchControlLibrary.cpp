/*
Copyright (c) 2021 lefmarna
released under the MIT license
https://opensource.org/licenses/mit-license.php
*/

#include "./NintendoSwitchControlLibrary.h"

// ボタンを押してから離すまでの時間（ミリ秒）
const uint16_t INPUT_TIME = 100;

// ボタンを連打する際に、押して認識後、離して認識するまでの合計時間（ミリ秒）
const uint16_t INPUT_TIME_TWICE = INPUT_TIME * 2;

/**
 * Switchコントローラーのボタンを押す
 *
 * @param uint16_t button     押すボタン
 * @param int      delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param int      loop       ボタンを押す回数（省略可、デフォルトは1）
 */
void pushButton(uint16_t button, int delay_time, int loop) {
    for (int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressButton(button);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseButton(button);
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーのボタンを指定の時間押し続ける
 *
 * @param uint16_t button    押し続けるボタン
 * @param int      hold_time ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdButton(uint16_t button, int hold_time) {
    SwitchControlLibrary().pressButton(button);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseButton(button);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーの十字キーを押す
 *
 * @param uint8_t hat        押す十字キーのボタン
 * @param int     delay_time ボタンを押した後の待ち時間（1秒 = 1000）
 * @param int     loop       ボタンを押す回数（省略可、デフォルトは1）
 */
void pushHat(uint8_t hat, int delay_time, int loop) {
    for (int i = 0; i < loop; i++) {
        SwitchControlLibrary().pressHatButton(hat);
        SwitchControlLibrary().sendReport();
        delay(INPUT_TIME);
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport();
        delay(delay_time);
    }
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーの十字キーを指定の時間押し続ける
 *
 * @param uint8_t hat:       押し続ける十字キーのボタン
 * @param int     hold_time: ボタンを押す時間の長さ（1秒 = 1000）
 */
void holdHat(uint8_t hat, int hold_time) {
    SwitchControlLibrary().pressHatButton(hat);
    SwitchControlLibrary().sendReport();
    delay(hold_time);
    SwitchControlLibrary().releaseHatButton();
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーの左スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t  lx:        左スティックのx軸
 * @param uint8_t  ly:        左スティックのy軸
 * @param int      tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time, uint16_t button = NULL) {
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーの右スティックを指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t  rx:        右スティックのx軸
 * @param uint8_t  ry:        右スティックのy軸
 * @param int      tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL) {
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}

/**
 * Switchコントローラーの左スティックと右スティックを同時に指定の時間傾け続ける
 * 128を基準とし、0~255の値を指定する
 *
 * @param uint8_t  lx:        左スティックのx軸
 * @param uint8_t  ly:        左スティックのy軸
 * @param uint8_t  rx:        右スティックのx軸
 * @param uint8_t  ry:        右スティックのy軸
 * @param int      tilt_time: スティックを傾ける時間の長さ
 * @param uint16_t button:    連打するボタン
 *
 * @see Stick::MIN       0
 * @see Stick::NEUTRAL 128
 * @see Stick::MAX     255
 */
void tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry,
                           int tilt_time, uint16_t button = NULL) {
    SwitchControlLibrary().moveLeftStick(lx, ly);
    SwitchControlLibrary().moveRightStick(rx, ry);
    SwitchControlLibrary().sendReport();
    if (button) {
        while (INPUT_TIME_TWICE <= tilt_time) {
            SwitchControlLibrary().pressButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            SwitchControlLibrary().releaseButton(button);
            SwitchControlLibrary().sendReport();
            delay(INPUT_TIME);
            tilt_time -= INPUT_TIME_TWICE;
        }
    }
    delay(tilt_time);
    SwitchControlLibrary().moveLeftStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    SwitchControlLibrary().sendReport();
    delay(INPUT_TIME);
}
