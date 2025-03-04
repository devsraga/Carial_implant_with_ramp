void processMultipleGCodes() {
    // Example G-code commands (In real case, read from SD card or serial)
    String gcodeCommands[] = {
        "G1 X50 Y50 Z10",
        "G1 X100 Y100 Z20",
        "G1 X150 Y150 Z30",
        "G1 X200 Y200 Z40"
    };

    // Process each G-code command
    for (int i = 0; i < 4; i++) {
        float X = 0, Y = 0, Z = 0;
        if (parseGCode(gcodeCommands[i], X, Y, Z)) {
            Serial.print("Moving to: X=");
            Serial.print(X);
            Serial.print(" Y=");
            Serial.print(Y);
            Serial.print(" Z=");
            Serial.println(Z);

            moveToPosition(X, Y, Z, 1000, 500);
        }
    }
}
