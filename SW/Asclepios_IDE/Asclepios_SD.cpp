#include "Asclepios_SD.h"


void SD_setup() {
  SPI1 = new SPIClass();
  SPI1->begin(SPI1_SCLK, SPI1_MISO, SPI1_MOSI, SPI1_SS);
  pinMode(SPI1->pinSS(), OUTPUT);
  
  if(!SD.begin(SPI1_SS, *SPI1)){
      Serial.println("Card Mount Failed");
      return;
  }
  
  cardType = SD.cardType();

  if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
  }

  Serial.print("SD Card Detected: ");
  if(cardType == CARD_MMC){
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.println();

  // Open the original file in read mode
  File file = SD.open("/setup.txt");
  
  // Check if the file opened successfully
  if (file) {
    // Read the original file and store its contents
    String fileContents = "";
    while (file.available()) {
      String line = file.readStringUntil('\n');
      fileContents += line + "\n";
      
      // Check if the line contains "ssid:"
      if (line.startsWith("#ssid:")) {
        // Extract the wifi name
        String ssid_string = line.substring(line.indexOf(":") + 2).c_str();
        strcpy(ssid, ssid_string.c_str());
        Serial.println("SSID :" + ssid_string);
      }
      
      // Check if the line contains "password:"
      if (line.startsWith("#password:")) {
        // Extract the wifi password
        String password_string = line.substring(line.indexOf(":") + 2);
        strcpy(password, password_string.c_str());
        Serial.println("Password :" + password_string);
      }

      // Check if the line contains "log number:"
      if (line.startsWith("#log:")) {
        // Extract the mission log number
        mission_log_nbr = (line.substring(line.indexOf(":") + 1).toInt());
        Serial.println("Current Mission Log Number:" + String(mission_log_nbr));
      }
    }
    
    // Close the original file
    file.close();
    
    // Modify the desired value in memory
    String modifiedContents = fileContents;
    modifiedContents.replace("#log: " + String(mission_log_nbr), "#log: " + String(mission_log_nbr + 1) );
    
    // Create a new file with the modified contents
    file = SD.open("/temp.txt", FILE_WRITE);
    if (file) {

      file.print(modifiedContents);
      file.close();

      SD.remove("/setup.txt");
      SD.rename("/temp.txt", "/setup.txt");
      
      Serial.println("Value updated successfully");

      Serial.println("Start of file");
      readFile(SD, "/setup.txt");
      Serial.println("End of file");

    } else {
      Serial.println("Log number could not be updated...");
    }
  }
  else {
    // Setup file opening failed
    Serial.println("Error opening setup file");
  }
  
  String mission_log_folder = "/mission_log_" + String(mission_log_nbr);
  // Create a folder on the SD card
  if (SD.mkdir(mission_log_folder)) {
    Serial.println("Folder created!");
  } else {
    Serial.println("Failed to create folder!");
  }

  String mission_log_string = mission_log_folder + "/mission_log_" + String(mission_log_nbr) + ".txt\0";
  Serial.println("mission_log_string");
  Serial.println(mission_log_string);
  strcpy(mission_log_file, mission_log_string.c_str());

  Serial.println("Mission file number: ");
  Serial.println(String(mission_log_nbr));
  Serial.println("Mission file: ");
  Serial.println(String(mission_log_file));
  writeFile(SD, mission_log_file, "Asclepios mission sensor file\n");
  appendFile(SD, mission_log_file, "=============================\n");
  appendFile(SD, mission_log_file, "Timestamp [s]; O2 [%]; Humidity [%]; Pressure [hPa]; Temperature [*C]; Gas [KOHm]; Altitude [m]\n");
}


void SD_update() {
  if(!SD.begin(SPI1_SS, *SPI1)){
    Serial.println("Card Mount Failed");
    SD_setup();
    return;
  }
  char line[10];
  unsigned long time = millis()/1000;
  Serial.println("Mission file 2: ");
  Serial.println(String(mission_log_file));
  appendFile(SD, mission_log_file, dtostrf(time,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(O2_val,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(bme.humidity,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(bme.pressure / 100.0,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(bme.temperature,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(bme.gas_resistance / 1000.0,3,2,line));
  appendFile(SD, mission_log_file, ";");
  appendFile(SD, mission_log_file, dtostrf(bme.readAltitude(SEALEVELPRESSURE_HPA),3,2,line));
  appendFile(SD, mission_log_file, "\n");

//  Serial.println();
//  readFile(SD, mission_log_file);
//  Serial.println();
}



void appendFile(fs::FS &fs, const char * path, const char * message) {
//    Serial.printf("Appending to file: %s\n", path);

    Serial.println("String(path) :");
    Serial.println(String(path));

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
//        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
//    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
//        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char * path) {
//    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

//    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

