#include<Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcX1, AcX2, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float accel, ax, az, phi;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);  // PWR_MGMT_1 register
  Wire.write(0b0001100);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);  // PWR_MGMT_1 register
  Wire.write(0b0001100);      // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void myDisplay(int16_t x) {
  int16_t a = abs(x);
  if (x > 0)  Serial.print(" ");
  if (a > 100000)  Serial.print(" ");
  else if (a > 10000)  Serial.print("  ");
  else if (a > 1000)  Serial.print("   ");
  else if (a > 100)  Serial.print("    ");
  else if (a > 10)  Serial.print("     ");
  else if (a > 1)  Serial.print("      ");
  Serial.print(x);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX1 = Wire.read();
  AcX2 = Wire.read();
  AcX = AcX1 << 8 | AcX2;
  AcY = Wire.read() << 8 ; //| Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcY |= Wire.read();
  AcZ = Wire.read() << 8 ; //| Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  AcZ |= Wire.read();
  Tmp = Wire.read() << 8 ; //| Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp |= Wire.read();
  GyX = Wire.read() << 8 ; //| Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyX |= Wire.read();
  GyY = Wire.read() << 8 ; //| Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyY |= Wire.read();
  GyZ = Wire.read() << 8 ; //| Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyZ |= Wire.read();

  az = (float)(AcZ + 1400);
      //AcX = -15900 au repos AcX =17000
      ax = (float)(AcX - 500);
      accel = sqrt(ax*ax+az*az);
      // test d'immobilité
      if ((accel > 15200) && (accel < 17400)) { // valeur normale 16384
        phi = atan2(ax,az);
        Serial.print("Phi = "); Serial.println(phi);
      }

  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
/*
  Serial.print("AcX = "); myDisplay(AcX);
  Serial.print(" | AcY = "); myDisplay(AcY);
  Serial.print(" | AcZ = "); myDisplay(AcZ);
  Serial.print(" | AcY = "); myDisplay(AcY);
  Serial.print(" | AcZ = "); myDisplay(AcZ);
  Serial.print(" | GyX = "); myDisplay(GyX);
  Serial.print(" | GyY = "); myDisplay(GyY);
  Serial.print(" | GyZ = "); myDisplay(GyZ);*/
  Serial.println("");
  delay(333);

}
