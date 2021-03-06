 

# DATA RELAY
A project in MQTT protocol using [Eclipse Mosquitto library](https://github.com/eclipse/mosquitto), employing multithreading, JsonParsing and Run-Length-Encoding Compression Algorithm, a solution to the [Data Relay task by SRA VJTI](https://github.com/SRA-VJTI/practice-assignments/blob/master/Data-Relay/data-relay.md)


<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Tech Stack](#tech-stack)
  * [File Structure](#file-structure)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Results and Demo](#results-and-demo)
* [Future Work](#future-work)
* [Troubleshooting](#troubleshooting)
* [Contributors](#contributors)
* [Acknowledgements and Resources](#acknowledgements-and-resources)
* [License](#license)


<!-- ABOUT THE PROJECT -->
## About The Project


Aim : This project aims to employ MQTT protocol and multithreading to publish information from 50 sensor bots every 500ms, read the messages from a single subscriber, parse and segregate the data types and compress the messages every 2 minutes
and Description of project.  
Refer this [documentation](https://github.com/MOLOCH-dev/DATA_RELAY_SRA/blob/master/Report%20_DATA_RELAY.pdf)

### Tech Stack
Technologies used for this project
* [Eclipse Mosquitto - An open source MQTT broker](https://mosquitto.org/)
* [Json-parser](https://github.com/udp/json-parser)

### File Structure
    .
    ├── data_relay_sra_pub.c        # Publishes data from 50 sensor bots using MQTT at a  frequency of 500ms
    ├── Report_DATA_RELAY.pdf                  # Project report
   
    ├── src                         # Source files
        ├── data_relay_sra_pub.c    # Publishes data from 50 sensor bots using MQTT at a  frequency of 500ms
        ├── data_relay_sra_sub.c    # Suscriber that receives data from 50 sensor bots as JSON streams, parses it and compresses after every 2 minutes
        ├── cpp_test                # Contains test code for Eclipse Paho CPP library
            ├── data_relay_0.cpp    # Publishes data from 50 sensor bots using MQTT at a  frequency of 500ms
    ├── json.c                      # Library for parsing Json
    ├── LICENSE
    ├── README.md 

    

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites


* In Ubuntu:
```sh
sudo apt-get install gcc mosquitto mosquitto-clients libmosquitto-dev
```
* Testing the installation :
```sh
gcc -v
```

* **GCC v7.5.0

  You can visit the [this installation guide](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04) for the installation steps.
  
 
```sh

sudo apt update
sudo apt install build-essential
sudo apt-get install manpages-dev
sudo apt-get install gcc
```

  Checking the installation :

  ```sh
  gcc --version
  ```

* **Eclipse Mosquitto Broker v1.6.12
```sh

sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install mosquitto mosquitto-clients libmosquitto-dev
  ```

Checking the installation : 
If you have installed a binary package the broker should have been started
automatically. If not, it can be started with a basic configuration:

```sh


    mosquitto
```
Then use `mosquitto_sub` to subscribe to a topic:
```sh
    mosquitto_sub -t 'test/topic' -v
```
And use `mosquitto_pub` publish a message:
```sh
    mosquitto_pub -t 'test/topic' -m 'hello world'

```


### Installation
1. Clone the repo
```sh
git clone https://github.com/MOLOCH-dev/DATA_RELAY_SRA.git
```


<!-- USAGE EXAMPLES -->
## Usage

cd to the folder which contains the files `data_relay_sra_pub.c`, `data_relay_sra_sub.c` and `json.c`
```sh
mosquitto -v
```
```sh
gcc data_relay_sra_pub.c -o data_relay_sra_pub -lmosquitto
mosquitto_sub -t home/sensordata -q 1

```
```sh

gcc data_relay_sra_sub.c -o data_relay_sra_sub json.c -lm -lmosquitto
```

<!-- RESULTS AND DEMO -->
## Results and Demo
  
[**Result**](https://drive.google.com/file/d/1vu0kHFow-P4ALGTotDlIIeDD5RTnYyN4/view?usp=sharing)  




<!-- FUTURE WORK -->
## Future Work

- [x] Created 50 bots to publish data at a frequency of 500ms
- [x] Created a subscriber client and parsed the Json streams of received payloads
- [x] Implemented run-length-encoding to write the compressed data into a file
- [ ] Fix the segmentation error:core dumped that occurs after 2-3 loops of publishing from 50 bots
- [ ] Fix library linking error for json-parser
- [ ] Create a python implementation of this project with interactive UI


<!-- TROUBLESHOOTING -->
## Troubleshooting
* The file data_relay_sra_pub.c is supposed to run in an infinite loop, but a segmentation error is encountered after 2 loops


<!-- CONTRIBUTORS -->
## Contributors

* [Anushree Sabnis](https://github.com/MOLOCH-dev)



<!-- ACKNOWLEDGEMENTS AND REFERENCES -->
## Acknowledgements and Resources
* [SRA VJTI](http://sra.vjti.info/)  
* References:
* [Theory](https://www.hivemq.com/mqtt-essentials/)
* [Json Library](https://github.com/udp/json-parser/blob/master/json.h)
* [Compression Algorithm in Cpp](https://www.geeksforgeeks.org/run-length-encoding/)
...


<!-- LICENSE -->

