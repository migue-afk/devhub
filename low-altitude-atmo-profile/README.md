# Low-Altitude Atmospheric Profile

An embedded data acquisition system designed to collect **atmospheric and telemetry measurements during low-altitude flights**.

The project combines UAV telemetry with environmental sensors to record altitude and temperature data for later analysis.

## Overview

The system receives **LTM (Lightweight Telemetry)** data from a flight controller while simultaneously reading several environmental sensors.

Measurements are periodically stored on an SD card, allowing the creation of an atmospheric profile based on altitude.

The project currently integrates:

* LTM telemetry
* GPS altitude
* DS18B20 digital temperature sensor
* NTC thermistor
* DHT22 temperature and humidity sensor
* SD card data logging
* NeoPixel status indicators
* Serial debugging

## System Architecture

```text
                 ┌───────────────────┐
                 │ Flight Controller │
                 │   LTM Telemetry   │
                 └─────────┬─────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Microcontroller │
                  └────────┬────────┘
                           │
           ┌───────────────┼───────────────┐
           │               │               │
           ▼               ▼               ▼
       DS18B20            NTC            DHT22
     Temperature      Temperature    Temp / Humidity
           │               │               │
           └───────────────┼───────────────┘
                           │
                           ▼
                     Data Processing
                           │
                  ┌────────┴─────────┐
                  │                  │
                  ▼                  ▼
              SD Logging       NeoPixel Status
```

## Features

### LTM Telemetry

The firmware receives and processes LTM telemetry frames through a serial connection.

Currently extracted telemetry information includes:

* GPS altitude
* Satellite count
* Battery voltage
* Armed / disarmed state
* Flight mode

Altitude data can be combined directly with environmental measurements.

### Temperature Measurement

The project supports multiple temperature sensing methods.

#### DS18B20

A digital temperature sensor connected through the OneWire protocol.

The sensor is configured with 12-bit resolution and asynchronous temperature conversion.

#### NTC Thermistor

An analog NTC thermistor is used as an additional temperature source.

This provides an alternative measurement method that can be compared with the DS18B20 data.

#### DHT22

The project also contains support for a DHT22 sensor for:

* Temperature
* Relative humidity

DHT22 support is currently available in the codebase and can be enabled when required.

## Data Logging

Measurements are written periodically to an SD card.

The current logging system can store values such as:

```text
Elapsed Time
Altitude
DS18B20 Temperature
NTC Temperature
```

These measurements can later be processed to study temperature variation with altitude.

## Project Structure

```text
low-altitude-atmo-profile/
├── low-altitude-atmo-profile.ino
├── DHTsensor.cpp
├── DHTsensor.h
├── ds18b20.cpp
├── ds18b20.h
├── ntc.cpp
├── ntc.h
├── LTMtelemetry.cpp
├── LTMtelemetry.h
├── SDsave.cpp
├── SDsave.h
├── Efectos.cpp
├── Efectos.h
├── debug.py
└── circuitadapter/
```

## Main Components

| File                            | Description                             |
| ------------------------------- | --------------------------------------- |
| `low-altitude-atmo-profile.ino` | Main firmware and acquisition loop      |
| `LTMtelemetry.cpp/.h`           | LTM telemetry processing                |
| `ds18b20.cpp/.h`                | DS18B20 temperature sensor interface    |
| `ntc.cpp/.h`                    | NTC thermistor measurement              |
| `DHTsensor.cpp/.h`              | DHT22 temperature/humidity interface    |
| `SDsave.cpp/.h`                 | SD card initialization and data logging |
| `Efectos.cpp/.h`                | NeoPixel visual status effects          |
| `debug.py`                      | Development/debugging utility           |

## Dependencies

The project uses Arduino-compatible libraries including:

```text
SoftwareSerial
Adafruit_NeoPixel
DHT
OneWire
DallasTemperature
SD
```

Install the required libraries using the Arduino IDE Library Manager or your preferred Arduino-compatible development environment.

## Getting Started

Clone the repository:

```bash
git clone https://github.com/migue-afk/devhub.git
```

Enter the project directory:

```bash
cd devhub/low-altitude-atmo-profile
```

Open:

```text
low-altitude-atmo-profile.ino
```

with the Arduino IDE.

Install the required libraries, select the correct microcontroller and serial port, and upload the firmware.

## Current Pin Configuration

The main firmware currently defines several hardware connections directly in the source code.

Examples include:

```cpp
#define DHT22_PIN 2
const int SENSOR_PIN = 5;
```

LTM telemetry is received through `SoftwareSerial`.

Pin assignments may need to be changed depending on the microcontroller and hardware configuration being used.

## Sampling

Environmental measurements are currently processed approximately once per second:

```cpp
const unsigned long interval = 1000;
```

This interval can be modified depending on the desired atmospheric profile resolution.

## Intended Data Flow

```text
Sensors
   │
   ▼
Microcontroller
   │
   ├── Read LTM altitude
   ├── Read DS18B20
   ├── Read NTC
   ├── Read DHT22
   │
   ▼
Combine Measurements
   │
   ▼
SD Card
   │
   ▼
Post-processing / Analysis
```

## Applications

The project can be used as a starting point for experiments involving:

* Low-altitude atmospheric profiling
* UAV-based environmental measurements
* Temperature vs. altitude studies
* Embedded data acquisition
* Flight telemetry integration
* Sensor comparison and calibration
* Environmental data logging

## Future Improvements

* [ ] Add barometric pressure sensing
* [ ] Enable DHT22 measurements in the main acquisition loop
* [ ] Store GPS coordinates
* [ ] Improve CSV data formatting
* [ ] Add timestamps to datasets
* [ ] Add sensor calibration routines
* [ ] Add telemetry integrity validation
* [ ] Create Python post-processing tools
* [ ] Automatically generate temperature-vs-altitude plots
* [ ] Document complete wiring diagrams
* [ ] Document the circuit adapter hardware
* [ ] Add example flight datasets

## License

This project is part of the `devhub` repository and is released under the **MIT License**.

See the repository's [LICENSE](../LICENSE) file for details.

