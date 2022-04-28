#include <SPI.h>
#include <Ethernet.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
int len;
char angle;
byte bu[80];
byte wb[80];
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = { 169, 254, 103, 100 }; // IP address in LAN – need to change according to your Network address
byte gateway[] = { 169, 254, 103, 134}; // sinternet access via router
byte subnet[] = { 255, 255, 0, 0 }; //subnet mask
byte server[] = { 169,254,103,134 };
EthernetClient client;


void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  // start the Ethernet connection:
//  Serial.println("Initialize Ethernet with DHCP:");
  // print your local IP address:
  Ethernet.begin(mac,ip,gateway,subnet);
  delay(1000);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  if (client.connect(server, 12000)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
  }
}



void loop() {
  angle='d';
  mpu6050.update();
  len = client.available();
  if(len>0){
    
    if(len>80) len=80;
    client.read(bu,len);
    angle = bu[0];
    }
   
//  Serial.print(mpu6050.getAngleX());
//  Serial.print(mpu6050.getAngleY());
//  Serial.println(mpu6050.getAngleZ());
//  if(client.available()){
//    angle = client.read();
//    Serial.print(angle);
//    }
  
//  delay(1000);
Serial.write(bu,len);
 if(angle!='d'){
  String f;
  if (angle == 'x'){
    //Serial.println(angle);
    //client.print("X = \t");
    f=String(mpu6050.getAngleX());
    f.toCharArray(wb,f.length()+1);
    client.write(wb,f.length()+1);
    //Serial.println(mpu6050.getAngleX());
    }
  else if (angle == 'y'){
   
    //client.print("Y = \t");
    f=String(mpu6050.getAngleY());
   f.toCharArray(wb,f.length()+1);
    client.write(wb,f.length()+1);
    }
  else if (angle == 'z'){
    
    //client.print("Z = \t");
    f=String(mpu6050.getAngleZ());
    f.toCharArray(wb,f.length()+1);
    client.write(wb,f.length()+1);
    }
   else{
    f="Unrecognized command";
    f.toCharArray(wb,f.length()+1);
    client.write(wb,f.length()+1);
  
    }
  delay(1000);
 }
 if(!client.connected())
 {
   client.stop();
   while(1)
   {
    ;
    }
  }
}
