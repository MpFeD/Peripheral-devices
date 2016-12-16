#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#define SIZE 4

// signaux enregistres
int16_t AccelerationX[SIZE+1];
int16_t AccelerationY[SIZE+1];
int16_t AccelerationZ[SIZE+1];
int16_t Temperature[SIZE+1];
int16_t GyroscopeX[SIZE+1];
int16_t GyroscopeY[SIZE+1];
int16_t GyroscopeZ[SIZE+1];  
  
// pour le filtrage
int16_t X_sig[SIZE+1]; // signal bruite
int16_t X_fir[SIZE+1]; // signal filtre FIR
int16_t X_iir[SIZE+1]; // signal filtre IIR

int g_c; // compteur
int g_i; // indice

// pour la fonction calc_stats
int32_t S_sig, Sx_sig, Sxx_sig;
int32_t S_fir, Sx_fir, Sxx_fir;
int32_t S_iir, Sx_iir, Sxx_iir;

// ---------------------------
void arduino_init_filter(void)
// ---------------------------
{
	g_c = 0;
    g_i = SIZE + 1;
    
    S_sig = Sx_sig = Sxx_sig = 0;
    S_fir = Sx_fir = Sxx_fir = 0;
    S_iir = Sx_iir = Sxx_iir = 0;
}

void setup() {
  // put your setup code here, to run once:
  arduino_init_filter();
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}
// ---------------------
void myDisplay(int16_t x) {
  int16_t a = abs(x);
  if(x > 0)  Serial.print(" ");
        if(a > 10000) Serial.print(" ");
   else if(a > 1000)  Serial.print("  ");
   else if(a > 100)   Serial.print("   ");
   else if(a > 10)    Serial.print("    ");
   else if(a >= 0)    Serial.print("     ");

   Serial.print(x);
}

void acquireMPU(int *global_i, int *global_c, int16_t *X) {
  int i = *global_i;
  int c = *global_c;
  int16_t x;
    
  // increment de l'indice et du compteur
  c = c + 1;
  if(i < SIZE) i = i + 1; else i = 0;
    
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX = Wire.read()<<8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  AccelerationX[i] = AcX;
  AccelerationY[i] = AcY;
  AccelerationZ[i] = AcZ;
  Temperature[i] = Tmp;
  GyroscopeX[i] = GyX;
  GyroscopeY[i] = GyY;
  GyroscopeZ[i] = GyZ;
  
  x = GyY; // choisir parmi les grandeurs lues  
  X[i] = x / 2;
  //printf("X[%3d] <- %3d ", i, x);  
  Serial.print("iter = "); myDisplay(c);
  Serial.print(" x = "); myDisplay(x);
  *global_i = i;
  *global_c = c;
}
// -------------------------------------------------------------------------
void calc_stats(int i, int c, int16_t* X, int32_t *S, int32_t *Sx, int32_t *Sxx)
// -------------------------------------------------------------------------
{
    //Serial.print(" moy = "); myDisplay(moyenne);
    //Serial.print(" var = "); myDisplay(variance);
}
// ----------------------------------------------
void calc_iir(int i, int c, int16_t *X, int16_t *Y)
// ----------------------------------------------
{
    
    //Serial.print(" IIR = "); myDisplay(y);
}

void loop() {
  acquireMPU(&g_i, &g_c, X_sig);
  calc_stats( g_i,  g_c, X_sig, &S_sig, &Sx_sig, &Sxx_sig); Serial.print("  |  ");
  //calc_iir  (  g_i,  g_c, X_sig, X_iir); Serial.print("  |  ");
  //calc_stats(  g_i,  g_c, X_iir, &S_iir, &Sx_iir, &Sxx_iir); Serial.println(" ");
        
  delay(500);

}
