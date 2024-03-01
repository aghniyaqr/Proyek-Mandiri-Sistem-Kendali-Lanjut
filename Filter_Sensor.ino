//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 19 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Filter Sensor Soil Moisture YL-69
*/
//-------------------------------- -------------------------------------\\
//  [1]. Deklarasi 
      float pv, PV, PVf, PVf_1, fc, RC, a, Ts;
      
void setup() {
//  [2]
//2a. Setup untuk sistem
      Serial.begin(9600);
//2b. Setup parameter filter yang dipakai
      fc=0.275;
      RC=1/(6.28*fc);
      Ts=0.01;
      a=RC/Ts;
      PVf_1=0;
}

void loop() {
//  [3] 
//3a. Membaca PV
      pv = analogRead(0)*0.0049*1000;//satuan mV
//3b. Mengkonversi pv ke persen
      PV = (100-(PV*100/5000.0));//konversi ke persen    
//3c. Filter PV
      PVf=(PV+a*PVf_1)/(a+1);
      PVf_1=PVf;
      
//  [4]. Tampilan di display plotter
      Serial.print(PV);
      Serial.print(" ");
      Serial.println(PVf);
}
