#include <LiquidCrystal.h>
#include <stdio.h>

constexpr int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7;
constexpr int SIG_IN = 1, SIG_REF = 2;
constexpr int HZ = 3;
constexpr int FW58 = 0, FW61 = 1;
constexpr double ANALOG_MAX = 1023.;
constexpr double SIG_MAX_VOL = 50.;
LiquidCrystal lcd = LiquidCrystal(RS, EN, D4, D5, D6, D7);
char lpszDisp1[17];
char lpszDisp2[17];

// 信号電圧をワットに変換
// nDet: 検波器番号 (FW58 or FW61)
// vol: 信号電圧 [mV]
// hertz: 周波数 [MHz]
double vol_to_watt(int nDet, double vol, double hertz);

void setup() {
    Serial.begin(9600);
    pinMode(SIG_IN, INPUT);
    pinMode(SIG_REF, INPUT);
    pinMode(HZ, INPUT);
    lcd.begin(16, 2);
}

void loop() {
    double dVol_in = analogRead(SIG_IN) * SIG_MAX_VOL / ANALOG_MAX;
    double dVol_ref = analogRead(SIG_REF) * SIG_MAX_VOL / ANALOG_MAX;
    double dHertz = analogRead(HZ) * 20. / ANALOG_MAX + 10;
    double dWatt_in = vol_to_watt(FW61, dVol_in, dHertz);
    double dWatt_ref = vol_to_watt(FW58, dVol_ref, dHertz);
    // ↓↓↓テスト用
    dWatt_in = 21.3882;
    dWatt_ref = 0.932;
    dHertz = 13.56286;
    // ↑↑↑テスト用
    lcd.clear();
    lcd.setCursor(0, 0);
    char lpszTmp1[17] = { '\0' };
    char lpszTmp2[17] = { '\0' };
    char lpszTmp3[17] = { '\0' };
    dtostrf(dHertz, 4, 2, lpszTmp1);
    sprintf(lpszDisp1, "f:%sMHz", lpszTmp1);
    dtostrf(dWatt_in, 2, 1, lpszTmp2);
    dtostrf(dWatt_ref, 2, 1, lpszTmp3);
    sprintf(lpszDisp2, "In:%sW R:%sW", lpszTmp2, lpszTmp3);
    lcd.print(lpszDisp1);
    lcd.setCursor(0, 1);
    lcd.print(lpszDisp2);
    delay(1000);
}

double vol_to_watt(int nDet, double vol, double hertz) {
}
