import processing.serial.*;
import java.io.*;

int baudRate = 9600;
int mySerialPort = 0; // Change this to the port number of the Arduino
Serial myPort;

FileWriter output;

void setup () { 
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[mySerialPort], baudRate);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n'); 
  
  size(300, 100);
  
  textSize(18);
  text("Read lines:", 10, 30);
 
  try {
    String filePath = sketchPath("../data/data.csv");
    println("File path: "+filePath);
    
    File file = new File(filePath);
    if (!file.exists()){
      print("File does not exist: "+filePath);
      println(" Creating...");
      if (!file.createNewFile()){
        println("Cannot create file "+filePath);
      }
    }
    output = new FileWriter(file, true);
  }
  catch(IOException e) {
    println("Cannot open file for writing");
    e.printStackTrace();
  }
}

void stop(){
  try {
    output.close();
  }
  catch(IOException e) {
    println("Cannot close file");
    e.printStackTrace();
  }
}

int readLines = 0;

void draw() {
  fill(0);  
  rect(10, 40, 100, 30);
  fill(255);
  text(readLines, 15, 60); 
}

String inString;
String dataMarker = "$data:";

void serialEvent(Serial p) {
  if (output == null) return;
  inString = p.readString();
  
  println("Received line: "+inString);
  
  if (inString == null || !inString.startsWith(dataMarker)){
    return;
  }
  
  try {
    output.write(Long.toString(System.currentTimeMillis()));
    output.write(',');
    output.write(inString.substring(dataMarker.length()));
    output.flush();
  }
  catch(IOException e) {
    println("Cannot write to file: "+inString);
    e.printStackTrace();
  }
  
  readLines++;
}
