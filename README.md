Project Description

This project demonstrates the configuration and communication of the MCP3562 24-bit Delta-Sigma ADC with an STM32 microcontroller using the SPI protocol.
To ensure reliable and isolated communication, the ADuM3154ARSZ SPI digital isolator is used.
    Although the hardware design supports multiple ADCs through the isolator, 
this implementation focuses on interfacing and testing a single MCP3562 ADC.

The main objectives of this project are:
✅ Configure the MCP3562 ADC for data acquisition.
✅ Establish SPI communication between STM32 and MCP3562 through ADuM3154ARSZ.
✅ Read and verify single-ended input data from one ADC.
✅ Provide a foundation for scaling the design to multiple ADCs in future implementations.

🛠️ Hardware Used
STM32F429 (Microcontroller)
MCP3562 (24-bit ADC)
ADuM3154ARSZ (Quad-channel SPI Digital Isolator)
Supporting components (power supply, resistors, capacitors, connectors)



Extend the setup to interface with multiple MCP3562 ADCs on the same SPI bus via the ADuM3154ARSZ.

Implement advanced features such as synchronized sampling, interrupt-based data acquisition, and DMA support on STM32.
