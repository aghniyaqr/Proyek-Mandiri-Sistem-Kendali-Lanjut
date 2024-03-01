`//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 23 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Desain Kendali
*/
//-------------------------------- -------------------------------------\\
//  [1]
//1a. Deklarasi SV, PV, MV, start
      float SV, PV;
      int MV, start;//di kendali ini, MV adalah nilai PWM 0 s.d 255;
//1b. Deklarasi perhitungan P-Control
      float Kp, e, P;
//1c. Deklarasi perhitungan filter
      float PVf, PVf_1, fc, RC, a;
//1d. Deklarasi variable Time Sampling
      unsigned long t;
      double t_1, Ts;
//1e Deklarasi untuk plotting
      float interval_elapsed, interval_limit;

void setup() {
//  [2]
//2a. Setup untuk sistem
      Serial.begin(9600);
//2b. Setup pin yang dipakai
      pinMode(12,OUTPUT);
      pinMode(8,INPUT);//keluaran dari pin 5 akan dimasukan ke pin 8 untuk start-stop looping
      pinMode(9,OUTPUT);//Keluaran sinyal kendali
//2c. Setup parameter filter 
      fc=0.275;//tidak boleh terlalu jauh fc nya
      RC=1/(6.28*fc);
      Ts=0.01;//diukur manual terlebih dahulu
      a=RC/Ts;
      PVf_1=0;
//2d. setup untuk sistem start
      digitalWrite(12,HIGH);//dipakai sebagai logik 1 di pin start
      analogWrite(9,0);//nilai awal agar output 0 atau tidak ada tegangan ke plant
//2e. Setting untuk mengatur durasi tampilan
      interval_elapsed = 0;//besarnya interval yang sudah dilewati
      interval_limit = 0.001;//setiap berapa lama data akan ditampilkan (dalam detik)
      t = 0; 
//2f. set besarnya SV
      SV=0;//besarnya sinyal output ke driver (berupa PWM 0-255)
 
}

void loop() {
//  [3] 
//3a. Membaca kondisi start
      start = digitalRead(8);//membaca apakah switch pada posisi 1 atau 0
//3b. Cek nilai start (logik 1 atau 0)
      if (start==0){
        SV=51;
      }
      else if(start==1){
        SV=0;
      }
//3c. Mengeksekusi nilai SV ke driver
      analogWrite(9,SV);
//3d. Membaca PV
      PV=(100-(analogRead(0)*0.0049*100/5));
//3e. Filter PV
      PVf=(PV+a*PVf_1)/(a+1);
      PVf_1=PVf;

//  [4]
//4a. Menghitung Ts
      t_1 = t;
      t = millis();
      Ts=(t - t_1)/1000;//Proses perhitungan Time Sampling Ts sudah dalam second
//4b. Menghitung waktu elapsed untuk menentukan kapan nilai di display
      interval_elapsed=interval_elapsed + Ts;//menjumlahkan besarnya Ts secara terus menerus.

//[5]. Cek hasil penjumlahan Ts akan di cek apakah sudah sama/lebih dari batas interval
      if (interval_elapsed >= interval_limit){
        
//  [6]
//6a. Tampilan di display plotter 
      Serial.print(0);
      Serial.print(" ");
      Serial.print(80);
      Serial.print(" ");
      Serial.print(SV);
      Serial.print(" ");
      Serial.println(PVf);// membaca nilai PV dan langsung ditampilkan

//6b. reset nilai IE
      interval_elapsed=0;
        }
        //setelah ditampilkan agar perhitungan diulang dari nol lagi
        else{
          interval_elapsed=interval_elapsed;
        }
}
