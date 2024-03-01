//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 24 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program PID
*/
//-------------------------------- -------------------------------------\\
//  [1]
//1a. Deklarasi SV, PV, MV
      int SV, PV, sv, pv;
      int MV;//di kendali ini, MV adalah nilai PWM 0 s.d 255;
      int en1=9;
      int in1=6;
      int in2=7;
//1b. Deklarasi perhitungan PID-Control
      float Kp, et, et_1, et_2, Ti, Ki, edif, Td, Kd, P, I, D;
      float eint, eint_1, eint_update;
//1c. Deklarasi perhitungan filter
      float PVf, PVf_1, fc, RC, a;
//1d. Deklarasi variable Time Sampling
      unsigned long t;
      double t_1, Ts;
//1e Deklarasi untuk plotting
      float interval_elapsed, interval_limit;
//1f Deklarasi LCD
      #include <Wire.h>
      #include <LiquidCrystal_I2C.h>
      //Library LCD I2C
      LiquidCrystal_I2C lcd (0x27,16,2);

void setup() {
//  [2]
//2a. Setup untuk sistem
      Serial.begin(19200);
//2b. Setup pin yang dipakai
      pinMode(9,OUTPUT);//Keluaran sinyal kendali
//2c. Setup parameter filter 
      fc=0.275;//tidak boleh terlalu jauh fc nya
      RC=1/(6.28*fc);
      Ts=0.03;//diukur manual terlebih dahulu
      a=RC/Ts;
      PVf_1=0;
//2d. Setting untuk mengatur durasi tampilan
      interval_elapsed = 0;//besarnya interval yang sudah dilewati
      interval_limit = 0.01;//setiap berapa lama data akan ditampilkan (dalam detik)
      t = 0; 
//2e. Men set, besaran dan satuan di LCD
        lcd.init();
        lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print("Kendali Kelembaban PID"); 
        lcd.setCursor(6,1);
        lcd.print("SKL");
        delay(3000);
        lcd.clear();
//2f. set Parameter Kendali
        Kp = 82.2;//82.5;//25.2012;
        Ti = 110.12;//110.12;//11.928;
        Td = 0.24;//0.24;//2.982;
        if(Ti==0){
          Ki=0;
        }
        else {
          Ki=Kp/Ti;
        }
          Kd = Kp*Td;
          eint_1=0;//set awal untuk luasan
    
//2g. keluaran sinyal kendali
        pinMode(en1, OUTPUT);
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
}

void loop() {
//  [3] 
//3a. Baca SV
      sv=analogRead(1)*0.0049*1000;//satuan mV
      SV=(sv*100/5000);//satuan %
//3b. Membaca PV
      pv= analogRead(0)*0.0049*1000;//satuan mV
      PV=(100-(pv*100/5000)); //Konversi ke persen
//3c. Filter PV
      PVf=(PV+a*PVf_1)/(a+1);
      PVf_1=PVf;
//3d. Hitung error, e=SV-PVf
      et=SV-PVf;
//3e. Hitung P
      P=Kp*et;
//3f. Hitung I
      eint_update=((et+et_1)*Ts)/2;//hitung I
      eint=eint_1+eint_update;
      I=Ki*eint;
//3g. Hitung D
      edif=(et-et_1)/Ts;//hitung D
      D=edif*Kd;
//3h. Hitung PID
      MV=P+I+D;//hitung keluaran PID     
      
//  [4] 
//4a. Membatasi keluaran MV agar tidak lebih dari spesifikasi arduino (PWM=0 s.d 255)
      if (MV>255){
        MV=255;
      }
         else if(MV<0){
              MV=0;
              }
            else {
              MV=MV;
            }
//4b. Menuliskan MV ke pin output
      analogWrite(en1,MV);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      
//  [5]
//5a. Menghitung Ts
      t_1 = t;
      t = millis();
      Ts=(t - t_1)/1000;//Proses perhitungan Time Sampling Ts sudah dalam second
//5b. Menghitung waktu elapsed untuk menentukan kapan nilai di display
      interval_elapsed=interval_elapsed + Ts;//menjumlahkan besarnya Ts secara terus menerus.

//[6]. Cek hasil penjumlahan Ts akan di cek apakah sudah sama/lebih dari batas interval
      if (interval_elapsed >= interval_limit){
        
//  [7]
//7a. Tampilan di display plotter dan LCD
      Serial.print(80);
      Serial.print(" ");
      Serial.print(PVf);
      Serial.print(" ");
      Serial.print(SV);
      Serial.print(" ");
      Serial.println(0);// membaca nilai PV dan langsung ditampilkan
//7b. Untuk menampilkan di LCD
      lcd.setCursor(0,0);
      lcd.print("SV: ");
      lcd.setCursor(3,0);
      lcd.print(SV);
      lcd.setCursor(11,0);//Letak koordinat tulisan "%" di kolom 11, baris 0
      lcd.print("%"); 
      lcd.setCursor(0,1);
      lcd.print("PV: ");
      lcd.setCursor(3,1);
      lcd.print(PVf);
      lcd.setCursor(11,1);//Letak koordinat tulisan "%" di kolom 11, baris 1
      lcd.print("%");
      
//7c. reset nilai IE
      interval_elapsed=0;
        }
        //setelah ditampilkan agar perhitungan diulang dari nol lagi
        else{
          interval_elapsed=interval_elapsed;
        }
//[8]. Set untuk perhitungan selanjutnya.
       et_1=et;
       eint_1=eint;
}
