# Arduino 2 FIWARE IoT Stack

## Introduction
This repository holds examples about how to persist your Arduino data into FIWARE IoT Stack cloud service.

Then, it will show you how to access these data using FIWARE NGSI standard APIs and its multiple connectors with external tools as Freeboard or CartoDB.

### First steps on your Arduino
If you are new with Arduino, we recommend you going first to [Arduino website](https://www.arduino.cc). 

### What is FIWARE IoT Stack?
[FIWARE](https://www.fiware.org/) is an open initiative aiming to create a sustainable ecosystem to grasp the opportunities that will emerge with the new wave of digitalization caused by the integration of recent Internet technologies. Based on this FIWARE technologies, and focused on IoT area, Telefonica created and [IoT Platform](http://iot.tid.es) to help Industrial Partners and Smart Cities building its IoT services. 

This FIWARE IoT Stack is also available for independent developers and startups, and will be used in this tutorial to persist your Arduino data in the cloud. You can go to its [ReadTheDocs](http://fiware-iot-stack.readthedocs.org/en/latest/index.html) to get familiar with it. 

## Using FIWARE IoT Stack
You have your Arduino collecting data from sensors. So what?

Next step is connecting your applications with FIWARE IoT Stack to access your data and show your magic to the rest of the world.

### Step #1: Sign up to get your credentials
You can get your FIWARE IoT Stack credentials at [http://signup.ttcloud.net/](http://signup.ttcloud.net).

You will receive an email with your API and portal credentials to send data from your Arduino and use FIWARE IoT Stack APIs on your App.

Please, in case you have any trouble signing up let us know at [iot_support@tid.es](mailto:iot_support@tid.es)

### Step #2: Upload .ino sketch to Arduino
Once you have your FIWARE IoT Stack API credentials, select one of these [.ino sample sketch](/arduino) depending on the connectivity used (WiFi or GSM) and set up your API key.

Upload the selected sketch to your Arduino and it will send A0 and A1 PIN values to FIWARE IoT Stack.

Ideally, connect there some sensors (temperature, luminosity) to have real data there.

### Step #3: FIWARE IoT Stack Management Portal
To check your data is correctly sent and stored, first thing is accessing the [Management Portal](http://ttcloud.net:8808/test). You can log-in using your given FIWARE user/password. In the "Entities" section (An Entity is a data object representation in FIWARE, so your Arduino is represented as an Entity) you will find an Entity called "thing:myArduino" with a list of attributes:
* "S0": Your A0 pin value
* "S1": Your A1 pin value

If you have connected more sensors to your Arduino, they will appear here with the given alias you selected in the arduino code.

### Step #4 : Drag&Drop visualizations with Freeboard
If you just need a dashboard to show your sensors data in real time, you can create it using [Freeboard](https://freeboard.io) without writing a line of code. 

Please, read our 
[FIWARE Orion Datasource Freedboard Tutorial](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-4-show-in-a-dashboard) if you have any trouble.

### Step #5 : Use FIWARE NGSI APIs
If you want to build your own app, with your own code and UX, you are looking for an API, right?. 

Integrating external apps is done via [NGSI APIs](https://fiware-orion.readthedocs.org/en/develop/), 
you have a getting started tutorial to start working with these APIs.
