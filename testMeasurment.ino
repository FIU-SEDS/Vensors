int startTime = millis(); //used for our timing loop
int mInterval = 50; //refresh rate of 20hz

void setupTest() {}

void loopTest() {
    if((millis()- startTime) > mInterval)
    {
      int A = getLDistanceSensor();
      int B = getRDistanceSensor();

        Serial.print("R: ");
        Serial.print(A); //Get a reading in millimeters
        Serial.print(",");
        Serial.print("L: ");
        Serial.print(B); //Get a reading in millimeters
        // Serial.print("D: ");
        // Serial.print((A + B) / 2);

        Serial.println();
        startTime = millis();
    }
}