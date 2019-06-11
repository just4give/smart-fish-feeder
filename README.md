# smart-fish-feeder
WiFi enabled aquarium fish feeder using ESP8266 and AWS Cloud


## Hardware you need

 - ESP8266 NodeMCU ( ~ $5 ) 
 - Servo Motor ( ~ $1 )
 - A plastic container to store the food
 - (Optional) A case, PCB circuit board and soldering tools


## AWS Resources you need to create

 - IAM user with access key and secret with full access to IoT
 - A lambda role with full access to IoT and SNS
 - A SNS topic with subcription to SMS
 - One AWS IoT Thing named FishFeeder (watch this video for step by step instruction on how to create IoT Shadow in AWS https://youtu.be/MCXXoyV_j4w ) 
 - Two lambda functions, fishFeeder and fishFeederAlert
 - Two Cloud Watch Events to trigger above lambda functions 
 
 
 ## ESP8266 Diagram
 
 ![fish_feeder_dia](https://user-images.githubusercontent.com/9275193/52969510-9cbc6900-337e-11e9-8689-b5135bfdf46c.png)
 
 ## External Arduino Libraries used
 
 - Wifi Manager. [Click](https://github.com/tzapu/WiFiManager) here for detail instruction how to add it to Arduino IDE
 - AWS SDK. This is a [forked](https://github.com/just4give/aws-sdk-arduino) from original aws-sdk-ardunio library as I was facing some issues with SHA1 foot print. You may use the original. 
