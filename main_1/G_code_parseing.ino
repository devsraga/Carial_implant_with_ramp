
// Parse G-code command to extract X, Y, Z positions
bool parseGCode(String line, float &X, float &Y, float &Z) {
    if (line.startsWith("G1")) { // Linear movement command
        int xIndex = line.indexOf("X");
        int yIndex = line.indexOf("Y");
        int zIndex = line.indexOf("Z");

        if (xIndex > 0) X = line.substring(xIndex + 1).toFloat();
        if (yIndex > 0) Y = line.substring(yIndex + 1).toFloat();
        if (zIndex > 0) Z = line.substring(zIndex + 1).toFloat();

        return true;
    }
    return false;
}




// Read G-code from SD card and execute movements
void readGCodeFromSD() {
    File gcodeFile = SD.open("GCODE.txt");

    if (!gcodeFile) {
        Serial.println("Error opening GCODE.txt");
        return;
    }

    while (gcodeFile.available()) {
        String line = gcodeFile.readStringUntil('\n');
        Serial.print("Processing: ");
        Serial.println(line);

        float X = 0, Y = 0, Z = 0;
        if (parseGCode(line, X, Y, Z)) {
            Serial.print("Moving to: X=");
            Serial.print(X);
            Serial.print(" Y=");
            Serial.print(Y);
            Serial.print(" Z=");
            Serial.println(Z);

            moveToPosition(X, Y, Z, 1000, 500);
        }
    }

    gcodeFile.close();
}


// Function to initialize SD card and read G-code
void initializeAndReadGCode() {
    if (!SD.begin(chipSelect)) {
        Serial.println("SD Card Initialization Failed!");
        return;
    }

    Serial.println("SD Card Ready!");
    readGCodeFromSD();
}
