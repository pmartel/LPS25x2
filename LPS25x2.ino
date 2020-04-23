// Demo for getting individual unified sensor data from the 2 LPS2X series

#include <Adafruit_LPS2X.h>

Adafruit_LPS2X lps, lps1;
Adafruit_Sensor *lps_temp, *lps_pressure, *lps1_temp, *lps1_pressure;


//#define PLOT_TEST

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

#ifndef PLOT_TEST
  Serial.println("Dual Adafruit LPS2X test!");
#endif

  // default address is 0x5D
  if (!lps.begin_I2C()) {
    Serial.println("Failed to find LPS2X (0x5D) chip");
    while (1) {
      delay(10);
    }
  }
  if (!lps1.begin_I2C(0x5C)) {
    Serial.println("Failed to find LPS2X (0x5C) chip");
    while (1) {
      delay(10);
    }
  }


  lps_temp = lps.getTemperatureSensor();
  lps_pressure = lps.getPressureSensor();
  lps1_temp = lps1.getTemperatureSensor();
  lps1_pressure = lps1.getPressureSensor();

#ifndef PLOT_TEST
  Serial.println("Both LPS2X Found!");
  lps_temp->printSensorDetails();
  lps_pressure->printSensorDetails();
  lps1_temp->printSensorDetails();
  lps1_pressure->printSensorDetails();
#else
  Serial.println("dTemp(C), dPressure(10KPa)");
#endif  
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t pressure, pressure1;
  sensors_event_t temp, temp1;

  lps_temp->getEvent(&temp);
  lps_pressure->getEvent(&pressure);
  lps1_temp->getEvent(&temp1);
  lps1_pressure->getEvent(&pressure1);


#ifndef PLOT_TEST
  /* Display the results (pressure is measured in hPa) */
  Serial.print("\n\t\tTime: ");Serial.println(pressure.timestamp);
  Serial.print("\t\tdelta Pressure: ");Serial.print(pressure.pressure-pressure1.pressure);Serial.println(" hPa");
  Serial.print("\t\tdelta Temperature: ");Serial.print(temp.temperature-temp1.temperature);Serial.println(" degrees C");

  delay(5000);

#else
  //   serial plotter friendly format
  Serial.print(temp.temperature-temp1.temperature);
  Serial.print(",");

  Serial.print({pressure.pressure-pressure1.pressure)/100);

  Serial.println();
  delay(100);
#endif 
}
