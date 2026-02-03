# Shoreline Wave Analysis & Generator Control

## Project Overview
This repository houses the software suite developed for the **NSF Urban Shorelines Reconfiguration Research** project. The system is designed to simulate, track, and analyze ocean waves in a physical tank to optimize seawall architectures for coastal protection (specifically for NYC shorelines).

## Physical Engineering & TPMS

This software controls a custom-built **six-foot physical wave tank**, engineered to simulate realistic ocean conditions using high-torque stepper motors.

### TPMS Seawall Design
A core focus of this research is the optimization of **Triply Periodic Minimal Surfaces (TPMS)** for shoreline protection.
* **The Goal:** We utilized these geometries to design porous, structurally efficient seawalls.
* **Optimization:** By iterating on the TPMS parameters, we aimed to find the optimal geometry that maximizes wave energy dissipation while using minimal material.

### Hardware-Software Integration
The setup requires precise calibration between the physical generator and the analysis software. The `WaveGeneratorApp` drives the physical motors to create specific wave frequencies.

## Repository Structure

### 1. Wave Analysis (MATLAB)
* **`WaveTankAnalyzer.mlapp`**: Primary GUI.
* **`WaveTankFunction.m`**: Core backend logic.
* **`createMask.m`**: HSV color space thresholding.

### 2. Hardware Control (Python & Arduino)
**Arduino Firmware:**
* **`BlueTooth.ino`**: Establishes a BLE peripheral service.
* **`switch.ino`**: Firmware for standalone operation using physical limit switches.

**Python & Serial Control:**
* **`bluetooth_bleak.py`**: Python script using `bleak` to communicate with the Arduino.
* **`WaveGeneratorApp_serial.mlapp`**: MATLAB interface for serial commands.

## Contributors
* **Daniel Halpern** - *Developer (CV Pipeline, MATLAB Architecture)*
* **Ryan Zhang** - *Developer (MQTT, Stepper Logic)*
* **Michael Wen** - *Developer (Arduino Firmware)*
* **Gavin Brady** - *Developer (UI/UX)*
* **Chin-Sung Lin** - *Research Advisor*

## License
This project is open-source and available under the MIT License.