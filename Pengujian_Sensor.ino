//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 19 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Pengujian Sensor Soil Moisture YL-69
*/
//-------------------------------- -------------------------------------\\

float PV,pv;

void setup() {
  Serial.begin(9600);
}

void loop() {
  PV = analogRead(0)*0.0049*1000;//satuan mV
  pv = (100-(PV*100/5000.0));//konversi ke persen

  Serial.print("Hasil Pembacaan (mV): ");
  Serial.print(PV);
  Serial.print("Kelembapan (%): ");
  Serial.println(pv);
  
}
