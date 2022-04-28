#include <SPI.h>

#include <Ethernet.h>

 

int len;

 

byte bu[80];

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

byte ip[] = { 169, 254, 103, 120 }; // IP address in LAN – need to change according to your Network address

byte gateway[] = { 169, 254, 103, 134}; // sinternet access via router

byte subnet[] = { 255, 255, 0, 0 }; //subnet mask

byte server[] = { 169,254,103,134 };

EthernetClient client;

 

void(* resetFunc) (void) = 0; // resetFunc();

 

void setup() {

 

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

//  while (!Serial) {

//    ; // wait for serial port to connect. Needed for native USB port only

//  }

 

  // start the Ethernet connection:

//  Serial.println("Initialize Ethernet with DHCP:");

  // print your local IP address:

  Ethernet.begin(mac, ip, gateway, subnet);

  delay(1000);

  Serial.print("My IP address: ");

  Serial.println(Ethernet.localIP());

  if (client.connect(server, 10000)) {

    Serial.println("connected");

  } else {

    Serial.println("connection failed");

  }

}

 

 

 

void loop() {

  len = client.available();

  if(len>0){

   

    if(len>80) len=80;

    client.read(bu,len);

   

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

Serial.println();

if(!client.connected())

{ client.stop();

  while(1){;}

  }

  delay(2000);

}
