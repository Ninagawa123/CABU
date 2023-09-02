# CABU
Control Assist Bypath Unit is an Arduino Leonardo/Micro USB Device for gaming.  

<img width="600" alt="cabu" src="https://github.com/Ninagawa123/CABU/assets/8329123/9c05de82-95bd-440b-9e29-c7737dbd3e0d">

# What is this
CABUはArduinoをUSBキーボード、マウスとしてPCに認識させ、Arduinoに接続したスイッチによって様々な入力を可能にします。
CABUを使う利点としては以下のようなものがあります。
CABU allows the PC to recognize the Arduino as a USB keyboard and mouse, and enables various inputs via switches connected to the Arduino.
The advantages of using CABU include

- 好きなコントローラ、ジョイスティック、スイッチを自由に活用できる。
- キーボード入力やマウスの移動量などを自由にアサインできる。
- 2つ以上のスイッチに、同じキー入力をアサインすることができる。
- コンボ入力を自由にコーディングすることができる。
- Free use of any controller, joystick, or switch you like.
- You can freely assign keyboard input, mouse movement, etc.
- You can assign the same key input to two or more switches.
- Combo inputs can be freely coded.
  
# Caution  
必ず、Arduino Leonardo もしくは micro を利用してください。この二つはArduinoシリーズの中でもPCからUSB機器として認識される能力があります。  
Be sure to use Arduino Leonardo or micro. These two have the ability to be recognized as USB devices within the Arduino series.  
  
# How to install  
コントローラーのボタン等のスイッチの配線を、GNDと任意のピンに一つ一つ接続してください。  
Connect the wires of the buttons and other switches on the controller to GND and any pins one by one.  

ソースコードを実態に合わせて改造してください。  
Please modify the source code to match the actual situation.  

ソースコードをArduinoに書き込んでください。  
Write the source code to the Arduino.  
  
# Default  
デフォルトのコードではアーマードコア６に合わせ、おおむね以下のようなアサインになっています。  

|ピン番号|ボタン|キーアサイン|備考|
|--|--|--|--|
|18|右スティック_丸ボタン|m||
|19|右スティック_トリガーボタン|l||
|9|右スティック_UP|マウスY-||
|10|右スティック_DOWN|マウスY+||
|11|右スティック_LEFT|マウスX-|マウスに相当,2回入力に反応|
|12|右スティック_RIGHT|マウスX+|マウスに相当,2回入力に反応|
|20|左スティック_丸ボタン|h||
|21|左スティック_トリガーボタン|j||
|5|左スティック_UP|w|2回入力で"w"+"←"(前ダッシュ)|
|6|左スティック_DOWN|s|2回入力で"s"+"←"(後ダッシュ)|
|7|左スティック_LEFT|a|2回入力で"a"+"←"(左ダッシュ)|
|8|左スティック_RIGHT|d|2回入力で"d"+"←"(右ダッシュ)|
|3|増設ボタン_1|i||
|4|増設ボタン_2|o||
|22|増設ボタン_3|p||
