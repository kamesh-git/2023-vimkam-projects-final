void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
  String s = Serial.readString();
  int space = s.indexOf(" ");
  int l = s.length();
  String one =  s.substring(0,space);
  String two =  s.substring(space+1 , l);
  Serial.println( one.toInt() + two.toInt() );

}
}
