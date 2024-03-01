//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 06 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Pengujian Arduino
*/
//-------------------------------- -------------------------------------\\

void setup() {
  // inisialisasi digital pin 13 sebagai output.
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);   // LED on (HIGH)
  delay(1000);                       // delay 1 detik
  digitalWrite(13, LOW);    // LED off(LOW)
  delay(1000);                       // delay 1 detik
}
