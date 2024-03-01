//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 06 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Pengujian Potensiometer sebagai SV
*/
//-------------------------------- -------------------------------------\\

float SV;

void setup() {
  Serial.begin(9600);
}

void loop() {
  SV = analogRead(1)*0.0049;
  Serial.print("SV: ");
  Serial.println(SV);
  delay(10);
  
}
