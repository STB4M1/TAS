#include <Adafruit_MAX31856.h>

#define PIN_CS   10      // SPI CS
#define PIN_DRDY 5       // DRDY ピン（LOWでデータ準備完了）

// SPIハードウェア使用（CS だけ指定）
Adafruit_MAX31856 thermo = Adafruit_MAX31856(PIN_CS);

void setup() {
  Serial.begin(9600);

  pinMode(PIN_DRDY, INPUT);

  // --- 初期化 ---
  if (!thermo.begin()) {
    Serial.println("ERROR: INIT");
    while (1) delay(10);
  }

  // 熱電対タイプ設定（K）
  thermo.setThermocoupleType(MAX31856_TCTYPE_K);

  // 連続変換モードに設定
  thermo.setConversionMode(MAX31856_CONTINUOUS);
}

void loop() {

  // --- DRDY が LOW になるまで待つ（変換完了） ---
  while (digitalRead(PIN_DRDY) == HIGH) {
    // 忙しすぎるループを避けるため軽いスリープ
    delayMicroseconds(50);
  }

  // --- 温度読み取り ---
  double tempC = thermo.readThermocoupleTemperature();

  // // --- エラー処理 ---
  // // NaN または Fault フラグのとき
  // if (isnan(tempC) || thermo.readFault() != 0) {
  //   Serial.println("ERROR");
  //   return;
  // }

  // --- Qtアプリが扱いやすい温度だけ出力 ---
  Serial.println(tempC, 2);  // 小数2桁
}
