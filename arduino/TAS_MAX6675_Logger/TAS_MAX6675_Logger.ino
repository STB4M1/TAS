#include <SPI.h>

const int PIN_CS = 10;   // Uno R4 の SSピン（D10）

void setup() {
  Serial.begin(9600);

  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);

  SPI.begin();  // Uno R4 ではこれだけでOK！
}

void loop() {
  delay(250);  // MAX6675 の変換時間（220ms以上）

  // ---- SPI 開始 ----
  SPI.beginTransaction(SPISettings(
      4000000,      // クロック 4MHz（MAX6675の最大 4.3MHz）
      MSBFIRST,     // ビット順
      SPI_MODE0     // モード0
  ));

  digitalWrite(PIN_CS, LOW);

  // 16bit 一括受信（Uno R4 でもOK）
  uint16_t raw = SPI.transfer16(0x0000);

  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
  // -------------------

  // ---- エラーチェック ----
  if (raw & 0x04) {     // bit2 = 1 → 熱電対未接続
    Serial.println("Error");
    return;
  }

  // ---- 温度変換 ----
  double tempC = (raw >> 3) * 0.25;

  // ---- Qtアプリ用に温度だけ出力 ----
  Serial.println(tempC, 2);
}
