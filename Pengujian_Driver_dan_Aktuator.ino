//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Rabu, 14 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Pengujian Driver dan Aktuator
*/
//-------------------------------- -------------------------------------\\

int in1=6;
int in2=7;
int EN_A=9;
float SV;
void setup() {
  Serial.begin(9600);
  
  pinMode(EN_A, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
}
void loop() {
  SV = analogRead(A1);
  SV = map(SV,0,1023,0,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(EN_A,SV);
  Serial.print(SV);
  Serial.print(0);
  Serial.print(" ");
  Serial.print(300);
  Serial.print(" ");
  Serial.println(SV);
}
