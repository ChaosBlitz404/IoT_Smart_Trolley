//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 03 ESP32 CAM RC Car Robot with Pan and Tilt Mount SM (Station Mode)
/*
 * Reference :
 * - ESP32-CAM Pan and Tilt Video Streaming Web Server (2 Axis) : https://randomnerdtutorials.com/esp32-cam-pan-and-tilt-2-axis/
 * - ESP32Servo (Author: Kevin Harrington,John K. Bennett) : - https://www.arduino.cc/reference/en/libraries/esp32servo/
 *                                                           - https://github.com/madhephaestus/ESP32Servo
 * - Timer on ESP32 : https://openlabpro.com/guide/timer-on-esp32/
 * - HTML DOM TouchEvent : https://www.w3schools.com/jsref/obj_touchevent.asp
 * - HTML DOM MouseEvent : https://www.w3schools.com/jsref/obj_mouseevent.asp
 * - Add Space Between Buttons in HTML : https://www.delftstack.com/howto/html/html-space-between-buttons/
 * - CSS Buttons : https://www.w3schools.com/css/css3_buttons.asp
 * - How TO - Range Sliders : https://www.w3schools.com/howto/howto_js_rangeslider.asp
 * - CameraCarWithPanTiltControl by un0038998 : https://github.com/un0038998/CameraCarWithPanTiltControl
 * - ESP32-CAM Remote Controlled Car Robot Web Server : https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/
 * - ESP32-CAM AI-Thinker Pinout Guide: GPIOs Usage Explained : https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/
 * - ESP32-CAM: high resolution pinout and specs : https://www.mischianti.org/2021/09/02/esp32-cam-high-resolution-pinout-and-specs/
 * - HTML vs Body: How to Set Width and Height for Full Page Size : https://www.freecodecamp.org/news/html-page-width-height/
 * - ESP32 PWM with Arduino IDE (Analog Output) : https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
 * - ESP32 PWM Frequency selection : https://rntlab.com/question/esp32-pwm-frequency-selection/
 * - arduino-esp32/cores/esp32/esp32-hal-ledc.c : https://github.com/espressif/arduino-esp32/blob/2fd39b1aff1c1f2be60bbd9b5fbd9c88638b0fcc/cores/esp32/esp32-hal-ledc.c
 * - ESP32 PWM Tutorial & Examples (AnalogWrite) – Arduino : https://deepbluembedded.com/esp32-pwm-tutorial-examples-analogwrite-arduino/
 * 
 * and from various other sources.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            IMPORTANT INFORMATION                                                                                //
//                                                                            ---------------------                                                                                //
//                                                                                                                                                                                  //
// > This project uses ESP32-CAM, L298N DC Motor Driver Module, DC Step Down Module (2 pieces), Servo (2 pieces) and DC Motor (4 pieces).                                           //
//   To power the modules and devices above, I recommend using a 12V Main Power Supply with 2A or more amperage.                                                                    //
//   12V Main Power Supply to power the L298N DC Motor Driver Module + DC Motor and DC Step Down Module,                                                                            //
//   while to power the ESP32-CAM and Servo using the DC Step Down Module whose output must be set to 5V.                                                                           //
//   For more information about this project (including other supporting components), please take a look at the installation image I shared with this code file.                    //
//   Look at the installation image carefully, because I wrote a lot of important information there.                                                                                //
//                                                                                                                                                                                  //
// > I suggest that every time you upload the program code to the ESP32-CAM, make sure that the switch that connects the Power Supply to the L298N DC Motor Driver Module is off    //
//   (OFF/0). Then if the process of uploading the program code to the ESP32-CAM is complete, you can change the switch to on (ON/1).                                               //
//   I suggest this because from what I experienced, if the switch is on when uploading the program code to the ESP32-CAM, the DC Motor will spin.                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// I realized that the HTML code in this project could have been better or simpler. But because of my limited knowledge on WEB programming,                                         //
// then that code is the best code I can make. If you can make it better or simpler, I hope you can share it with me or with the video viewers of this project.                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sorry if my English is confusing, I use the help of an online translator because my English is not good.                                                                         //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ======================================== Including the libraries. */
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <WiFi.h>
#include "esp_http_server.h"
#include <ESP32Servo.h>
#include "quirc.h"
/* ======================================== */

/* ======================================== Select camera model. */
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
#define CAMERA_MODEL_AI_THINKER
/* ======================================== */

/* ======================================== GPIO of camera models. */
#if defined(CAMERA_MODEL_WROVER_KIT)
  #define PWDN_GPIO_NUM    -1
  #define RESET_GPIO_NUM   -1
  #define XCLK_GPIO_NUM    21
  #define SIOD_GPIO_NUM    26
  #define SIOC_GPIO_NUM    27
  
  #define Y9_GPIO_NUM      35
  #define Y8_GPIO_NUM      34
  #define Y7_GPIO_NUM      39
  #define Y6_GPIO_NUM      36
  #define Y5_GPIO_NUM      19
  #define Y4_GPIO_NUM      18
  #define Y3_GPIO_NUM       5
  #define Y2_GPIO_NUM       4
  #define VSYNC_GPIO_NUM   25
  #define HREF_GPIO_NUM    23
  #define PCLK_GPIO_NUM    22

#elif defined(CAMERA_MODEL_M5STACK_PSRAM)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     25
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       32
  #define VSYNC_GPIO_NUM    22
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_M5STACK_PSRAM_B)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     22
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       32
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_M5STACK_WITHOUT_PSRAM)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     25
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       17
  #define VSYNC_GPIO_NUM    22
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_AI_THINKER)
  #define PWDN_GPIO_NUM     32
  #define RESET_GPIO_NUM    -1
  #define XCLK_GPIO_NUM      0
  #define SIOD_GPIO_NUM     26
  #define SIOC_GPIO_NUM     27
  
  #define Y9_GPIO_NUM       35
  #define Y8_GPIO_NUM       34
  #define Y7_GPIO_NUM       39
  #define Y6_GPIO_NUM       36
  #define Y5_GPIO_NUM       21
  #define Y4_GPIO_NUM       19
  #define Y3_GPIO_NUM       18
  #define Y2_GPIO_NUM        5
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     23
  #define PCLK_GPIO_NUM     22
#else
  #error "Camera model not selected"
#endif
/* ======================================== */

/* ======================================== GPIO for controlling dc motors. */
// For more details, please see the installation picture.
#define Motor_R_Dir_Pin   2
#define Motor_R_PWM_Pin   3
#define Motor_L_Dir_Pin   13
#define Motor_L_PWM_Pin   12
/* ======================================== */

/* ======================================== SERVOs GPIO */
#define servo_LeftRight_Pin   14
#define servo_UpDown_Pin      15
/* ======================================== */

// LEDs GPIO
#define LED_OnBoard 4

/* ======================================== Variables declaration */
// setting PWM properties for LED
const int PWM_LED_Freq = 5000;
const int PWM_LED_Channel = 6;
const int PWM_LED_resolution = 8;

// setting PWM properties for DC Motor
const int PWM_Mtr_Freq = 5000;
const int PWM_Mtr_Resolution = 8;
const int PWM_Channel_Mtr_R = 4;
const int PWM_Channel_Mtr_L = 5;

// Variable for DC Motor/Motor Drive PWM value
int PWM_Motor_DC = 0;

// Variable for servo position
int servo_LeftRight_Pos = 75;
int servo_UpDown_Pos = 75;
/* ======================================== */

/* ======================================== Initialize servos */
/*
 * Maybe in this section you are a little confused, why did I initialize 4 servos, even though in this project only 2 servos are used. Below is a brief explanation.
 * 
 * The ESP32 has 4 hardware timers (please correct me if I'm wrong). If only initialize 2 servos, then automatically based on servo library, 
 * then servo_1 will use timer_0 (channel_0) and servo_2 will use timer_1 (channel_1). 
 * That would be a problem because timer_0 (channel_0) and timer_1 (channel_1) are already in use by the camera.
 * 
 * Therefore, initialization of 4 servos is used, so that the 2 servos that are actually used will shift to timer_2 (channel_2) and timer_3 (channel_3). Below is the simple flow:
 * 
 * servo_Dummy_1    --> timer_0 or channel_0
 * servo_Dummy_2    --> timer_1 or channel_1
 * servo_LeftRight  --> timer_2 or channel_2
 * servo_UpDown     --> timer_3 or channel_3
 * 
 * Based on the flow above, the initialization of servo_Dummy_1 and servo_Dummy_2 is only used to shift the timer, 
 * so the 2 servos used in this project will use timer_2 (channel_2) and timer_3 (channel_3). 
 * servo_Dummy_1 and servo_Dummy_2 are not actually used, because timer_0 (channel_0) and timer_1 (channel_1) are already used by the camera.
 */
Servo servo_Dummy_1;
Servo servo_Dummy_2;
Servo servo_LeftRight;
Servo servo_UpDown;


// LEDs GPIO
#define LED_OnBoard 4
#define LED_Green   12
#define LED_Blue    13

// creating a task handle
TaskHandle_t QRCodeReader_Task; 

/* ======================================== Variables declaration */
struct QRCodeData
{
  bool valid;
  int dataType;
  uint8_t payload[1024];
  int payloadLen;
};

struct quirc *q = NULL;
uint8_t *image = NULL;  
struct quirc_code code;
struct quirc_data data;
quirc_decode_error_t err;
struct QRCodeData qrCodeData;  
String QRCodeResult = "";
String QRCodeResultSend = "";
/* ======================================== */

/* ======================================== */
bool ws_run = false;
int wsLive_val = 0;
int last_wsLive_val;
byte get_wsLive_interval = 0;
bool get_wsLive_val = true;

unsigned long previousMillis = 0;
const long interval = 1000;

/* ======================================== */

/* ======================================== Replace with your network credentials */
const char* ssid = "Mi 10T Pro";
const char* password = "12345678";
/* ======================================== */
// ==================== Function Prototypes (Deklarasi) ====================
void dumpData(const struct quirc_data *data);
String getValue(String data, char separator, int index);
void Move_Forward(int pwm_val);
void Move_Backward(int pwm_val);
void Move_Right(int pwm_val);
void Move_Left(int pwm_val);
void Move_Stop();
void createTaskQRCodeReader();
void QRCodeReader(void * pvParameters);

/* ======================================== */
#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
/* ======================================== */

/* ======================================== Empty handle to esp_http_server */
httpd_handle_t index_httpd = NULL;
httpd_handle_t stream_httpd = NULL;
/* ======================================== */

/* ======================================== HTML code for index / main page */
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>

  <head>
  
    <title>ESP32-CAM RC ROBOT CAR</title>
    
    <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
    
    <style>
    
      body {
        font-family: Arial; 
        text-align: center; 
        padding-top: 10px;
        max-width: 400px;   
        margin: 0 auto;
      }

      /* ----------------------------------- Slider */
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 100%;
        height: 5px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 13px;
        height: 13px;
        border-radius: 50%;
        background: #04AA6D;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 13px;
        height: 13px;
        border-radius: 50%;
        background: #04AA6D;
        cursor: pointer;
      }
      /* ----------------------------------- */
      
      /* ----------------------------------- Button */
      .button {
        display: inline-block;
        padding: 5px;
        font-size: 8px;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #4CAF50;
        border: none;
        border-radius: 15px;
        box-shadow: 0 2px #999;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        width: 20%;
        height: 20px;
      }

      .button:hover {background-color: #3e8e41}

      .button:active {
        background-color: #3e8e41;
        box-shadow: 0 0px #666;
        transform: translateY(2px);
      }
      /* ----------------------------------- */
      
      /* ----------------------------------- */
      .space {
        width: 15%;
        height: auto;
        display: inline-block;
      }
      /* ----------------------------------- */

      /* ----------------------------------- Stream Viewer */
      img {
        width: auto ;
        max-width: 100% ;
        height: auto ; 
      }
      /* ----------------------------------- */
      
    </style>
    
  </head>
  
  <body>
  
    <h3>ESP32-CAM RC ROBOT CAR</h3>
    
    <img src="" id="vdstream">
    <br><br>
    <div class="slidecontainer">
      <span style="font-size:15;">LED Flash &nbsp;</span>
      <input type="range" min="0" max="20" value="0" class="slider" id="mySlider">
    </div>
    <p>QR Code Scan Result :</p>
    <div style="padding: 5px; border: 3px solid #075264; text-align: center; width: 70%; margin: auto; color:#0A758F;" id="showqrcodeval">...</div>
    <br>

    <button type="button" onclick="CopyQRCodeRslt()">Copy Result</button>
    <button type="button" onclick="send_btn_cmd('clr')">Clear Result</button>
    <br><br>

    <div>
      <!-- The "T" and "M" suffixes are used to differentiate between touch screen input and mouse pointer input on buttons. -->
      <button class="button" ontouchstart="button_ontouchstart_handle('FT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('FM')" onmouseup="button_onmouseup_handle()"><b>FORWARD</b></button>
      <br><br>
      <button class="button" ontouchstart="button_ontouchstart_handle('LT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('LM')" onmouseup="button_onmouseup_handle()"><b>LEFT</b></button>
      <div class="space"></div>
      <button class="button" ontouchstart="button_ontouchstart_handle('RT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('RM')" onmouseup="button_onmouseup_handle()"><b>RIGHT</b></button>
      <br><br>
      <button class="button" ontouchstart="button_ontouchstart_handle('BT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('BM')" onmouseup="button_onmouseup_handle()"><b>BACKWARD</b></button>
    </div>
    
    <br>
    
    <table style="width:320px;margin:auto;table-layout:fixed" CELLSPACING=10>
      <tr>
        <td style="text-align:left;width:50px;">Speed</td>
        <td style="width:200px;">
          <div class="slidecontainer">
            <input type="range" min="0" max="10" value="5" class="slider" id="mySlider_pwm_Speed">
          </div>
        </td>
        <td style="text-align:right;font-weight:normal;width:20px;" id="slider_pwm_Speed_id">NN</td>
      </tr>
      
      <tr>
        <td>LED</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="10" value="0" class="slider" id="mySlider_pwm_LED">
          </div>
        </td>
        <td style="text-align:right;" id="slider_pwm_LED_id">NN</td>
      </tr>
      
      <tr>
        <td>Pan</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="180" value="75" class="slider" id="mySlider_Pan">
          </div>
        </td>
        <td style="text-align:right;" id="slider_Pan_id">NN</td>
      </tr>
      
      <tr>
        <td>Tilt</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="180" value="75" class="slider" id="mySlider_Tilt">
          </div>
        </td>
        <td style="text-align:right;" id="slider_Tilt_id">NN</td>
      </tr>
    </table>
    
    <script>
      /* ----------------------------------- Calls the video stream link and displays it. */ 
      document.addEventListener("DOMContentLoaded", function() {
        let host = window.location.hostname;
        window.onload = document.getElementById("vdstream").src = window.location.href.slice(0, -1) + ":81/stream";
      });
      var slider = document.getElementById("mySlider");
      /* ----------------------------------- */
      
      /* ----------------------------------- Variables to get and display the values of the sliders. */
      var slider_pwm_Speed = document.getElementById("mySlider_pwm_Speed");
      var show_slider_pwm_Speed = document.getElementById("slider_pwm_Speed_id")
      show_slider_pwm_Speed.innerHTML = slider_pwm_Speed.value;
      send_cmd("SS," + slider_pwm_Speed.value);
      
      var slider_pwm_LED = document.getElementById("mySlider_pwm_LED");
      var show_slider_pwm_LED = document.getElementById("slider_pwm_LED_id")
      show_slider_pwm_LED.innerHTML = slider_pwm_LED.value;
      
      var slider_Pan = document.getElementById("mySlider_Pan");
      var show_slider_Pan = document.getElementById("slider_Pan_id")
      show_slider_Pan.innerHTML = slider_Pan.value;
      
      var slider_Tilt = document.getElementById("mySlider_Tilt");
      var show_slider_Tilt = document.getElementById("slider_Tilt_id")
      show_slider_Tilt.innerHTML = slider_Tilt.value;

      let slider_PanTilt_send_rslt = "";
      /* ----------------------------------- */
      
      /* ----------------------------------- Variable declarations for timers and their intervals. */
      /* :::::::::::::::::::::::::::::::::::::::::::::::: myTmr */
      // This timer is used to send commands to stop the rotation of the dc motor (the robot car stops).
      // Actually, when "ontouchend" and "onmouseup" the robot car stop command has been sent, but to make sure the stop command is sent,
      // I created this timer to send the stop command once again. In essence the stop command will be sent 2 times.
      var myTmr;
      var myTmr_Interval = 500;
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: myTmr_PanTiltCtr */
      // This timer is used to handle sending request data to control the servos on the Pan and Tilt Camera Mount using the "range slider".
      // Sending data requests to control servos must use a "delay" with the next sending of data requests.
      // Therefore this timer is used as a "delay".
      // Based on what I experienced, without "delay", there will be errors in the process of controlling the servos using the "range slider".
      // My knowledge is limited to web/html/javascript programming. So to solve that error, then using timer is the best I can do.
      // But the error does not occur on sending requests to "control the LED" and "Adjust Speed" using the "range slider".
      var myTmr_PanTiltCtr;
      var myTmr_PanTiltCtr_Interval = 200;
      var myTmr_PanTiltCtr_Start = 1;
      var myTmr_PanTiltCtr_Send = 0;
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */
      /* ----------------------------------- */

      // Variable declarations to differentiate the sending of button commands when the button is held down or just a single press.
      var onmousedown_stat = 0;

      /* ----------------------------------- Variable declaration for sending commands to ESP32 Cam from index/web page. */
      let btn_commands_rslt = "";
      /* ----------------------------------- */

      // Variable declarations to distinguish between button presses using the mouse or using the touch screen (on a mobile browser or in a browser on a touch screen device).
      var join_TM = 0;

      /* ---------------------------------------------------------------------- Update the current slider value (each time you drag the slider handle) */
      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_pwm_Speed */
      slider_pwm_Speed.oninput = function() {
        show_slider_pwm_Speed.innerHTML = slider_pwm_Speed.value;
        let slider_pwm_Speed_send = "SS," + slider_pwm_Speed.value;
        send_cmd(slider_pwm_Speed_send);
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_pwm_LED */
      slider_pwm_LED.oninput = function() {
        show_slider_pwm_LED.innerHTML = slider_pwm_LED.value;
        let slider_pwm_LED_send = "SL," + slider_pwm_LED.value;
        send_cmd(slider_pwm_LED_send);
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_Pan */
      slider_Pan.oninput = function() {
        show_slider_Pan.innerHTML = slider_Pan.value;
        let slider_Pan_send = "SP," + slider_Pan.value;
        slider_PanTilt_send_rslt = slider_Pan_send;
        myTmr_PanTiltCtr_Send = 1;
        if (myTmr_PanTiltCtr_Start == 1) {
          myTmr_PanTiltCtr = setInterval(myTimer_PanTiltCtr, myTmr_PanTiltCtr_Interval);
          myTmr_PanTiltCtr_Start = 0;
        }
      }

      slider_Pan.onchange = function() {
        myTmr_PanTiltCtr_Start = 1;
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_Tilt */
      slider_Tilt.oninput = function() {
        show_slider_Tilt.innerHTML = slider_Tilt.value;
        let slider_Tilt_send = "ST," + slider_Tilt.value;
        slider_PanTilt_send_rslt = slider_Tilt_send;
        myTmr_PanTiltCtr_Send = 1;
        if (myTmr_PanTiltCtr_Start == 1) {
          myTmr_PanTiltCtr = setInterval(myTimer_PanTiltCtr, myTmr_PanTiltCtr_Interval);
          myTmr_PanTiltCtr_Start = 0;
        }
      }

      slider_Tilt.onchange = function() {
        myTmr_PanTiltCtr_Start = 1;
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- Functions to handle input of buttons. */
      function button_onmousedown_handle(cmds) {
        clearInterval(myTmr);
        btn_commands_rslt = cmds.substring(0, 1);
        if (join_TM == 0) {
          if (onmousedown_stat == 0) {
            send_btn_cmd(btn_commands_rslt);
            onmousedown_stat = 1;
          }   
        }  
      }

      function button_ontouchstart_handle(cmds) {
        clearInterval(myTmr);
        join_TM = 1;
        btn_commands_rslt = cmds.substring(0, 1);
        if (onmousedown_stat == 0) {
          send_btn_cmd(btn_commands_rslt);
          onmousedown_stat = 1;
        }
      }
      
      function button_onmouseup_handle() {
        if (join_TM == 0) {
          onmousedown_stat = 0;
          send_btn_cmd("S");  
          myTmr = setInterval(myTimer, myTmr_Interval);
        }
      }

      function button_ontouchend_handle() {
        join_TM = 1;
        onmousedown_stat = 0;
        send_btn_cmd("S");
        myTmr = setInterval(myTimer, myTmr_Interval);
      }
      /* ----------------------------------------------------------------------

      /* ---------------------------------------------------------------------- myTimer */
      function myTimer() {
        send_btn_cmd("S");
        clearInterval(myTmr);
      }
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- myTimer_PanTiltCtr */
      function myTimer_PanTiltCtr() {
        if (myTmr_PanTiltCtr_Send == 1) {
          send_cmd(slider_PanTilt_send_rslt);
          if (myTmr_PanTiltCtr_Start == 1) clearInterval(myTmr_PanTiltCtr);
          myTmr_PanTiltCtr_Send = 0;
        }
      }
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- Function to send commands to the ESP32 Cam whenever the button is clicked/touched. */
      function send_btn_cmd(cmds) {
        let btn_cmd = "B," + cmds;
        send_cmd(btn_cmd);
      }
      /* ---------------------------------------------------------------------- */
      
      /* ---------------------------------------------------------------------- Function for sending commands */
      function send_cmd(cmds) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/action?go=" + cmds, true);
        xhr.send();
      }
      var myTmr_qr;
      let qrcodeval = "...";
      start_timer_qr();

      slider.oninput = function() {
        let slider_pwm_val = "S," + slider.value;
        send_cmd(slider_pwm_val);
      }      
      function start_timer_qr() {
          myTmr_qr = setInterval(myTimer_qr, 500);
      }

      function myTimer_qr() {
        getQRCodeVal();
        textQRCodeVal();
      }

      function getQRCodeVal() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            qrcodeval = this.responseText;
          }
      };
      xhttp.open("GET", "/getqrcodeval", true);
      xhttp.send();
      }

      function send_cmd(cmds) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/action?go=" + cmds, true);
        xhr.send();
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: Start and stop the timer */
      function start_timer() {
        myTmr = setInterval(myTimer, 500)
      }
      
      function stop_timer() {
        clearInterval(myTmr)
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: Timer to get QR Code reading result and display it. */
      function myTimer() {
        getQRCodeVal();
        textQRCodeVal();
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: Function to display the results of reading the QR Code. */
      function textQRCodeVal() {
        document.getElementById("showqrcodeval").innerHTML = qrcodeval;
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: Function to send commands to the ESP32 Cam whenever the button is clicked. */
      function send_btn_cmd(cmds) {
        let btn_cmd = "B," + cmds;
        send_cmd(btn_cmd);
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: Function to copy QR Code reading result to clipboard. */
      // Source: https://techoverflow.net/2018/03/30/copying-strings-to-the-clipboard-using-pure-javascript/
      function CopyQRCodeRslt() {
        // Create new element
        var el = document.createElement('textarea');
        // Set value (string to be copied)
        el.value = qrcodeval;
        // Set non-editable to avoid focus and move outside of view
        el.setAttribute('readonly', '');
        el.style = {position: 'absolute', left: '-9999px'};
        document.body.appendChild(el);
        // Select text inside element
        el.select();
        // Copy text to clipboard
        document.execCommand('copy');
        // Remove temporary element
        document.body.removeChild(el);
        /* Alert the copied text */
        alert("The result of reading the QR Code has been copied.");
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* ---------------------------------------------------------------------- */
    </script>
  
  </body>
  
</html>
)rawliteral";
/* ======================================== */

/* ________________________________________________________________________________ Index handler function to be called during GET or uri request */
static esp_err_t index_handler(httpd_req_t *req){
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ stream handler function to be called during GET or uri request. */
static esp_err_t stream_handler(httpd_req_t *req){
  ws_run = true;
  vTaskDelete(QRCodeReader_Task);
  Serial.print("stream_handler running on core ");
  Serial.println(xPortGetCoreID());

  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t * _jpg_buf = NULL;
  char * part_buf[64];

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if(res != ESP_OK){
    return res;
  }

  /* ---------------------------------------- Loop to show streaming video from ESP32 Cam camera and read QR Code. */
  while(true){
    ws_run = true;
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed (stream_handler)");
      res = ESP_FAIL;
    } else {
      q = quirc_new();
      if (q == NULL){
        Serial.print("can't create quirc object\r\n");  
        continue;
      }
      
      quirc_resize(q, fb->width, fb->height);
      image = quirc_begin(q, NULL, NULL);
      memcpy(image, fb->buf, fb->len);
      quirc_end(q);
      
      int count = quirc_count(q);
      if (count > 0) {
        quirc_extract(q, 0, &code);
        err = quirc_decode(&code, &data);
    
        if (err){
          QRCodeResult = "Decoding FAILED";
          Serial.println(QRCodeResult);
        } else {
          Serial.printf("Decoding successful:\n");
          dumpData(&data);
        } 
        Serial.println();
      } 
      
      image = NULL;  
      quirc_destroy(q);
      
      if(fb->width > 200){
        if(fb->format != PIXFORMAT_JPEG){
          bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
          esp_camera_fb_return(fb);
          fb = NULL;
          if(!jpeg_converted){
            Serial.println("JPEG compression failed");
            res = ESP_FAIL;
          }
        } else {
          _jpg_buf_len = fb->len;
          _jpg_buf = fb->buf;
        }
      }
    }
    if(res == ESP_OK){
      size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
      res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
    }
    if(fb){
      esp_camera_fb_return(fb);
      fb = NULL;
      _jpg_buf = NULL;
    } else if(_jpg_buf){
      free(_jpg_buf);
      _jpg_buf = NULL;
    }
    if(res != ESP_OK){
      break;
    }
    
    wsLive_val++;
    if (wsLive_val > 999) wsLive_val = 0;
  }
  /* ---------------------------------------- */
  return res;
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ cmd handler function to be called during GET or uri request. */
static esp_err_t cmd_handler(httpd_req_t *req){
  char*  buf;
  size_t buf_len;
  char variable[32] = {0,};
   
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = (char*)malloc(buf_len);
    if(!buf){
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      if (httpd_query_key_value(buf, "go", variable, sizeof(variable)) == ESP_OK) {
      } else {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    } else {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  } else {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }
 
  int res = 0;

  Serial.println();
  Serial.print("Incoming command : ");
  Serial.println(variable);
  String getData = String(variable);
  String resultData = getValue(getData, ',', 0);

  /* ---------------------------------------- Controlling the LEDs on the ESP32-CAM Board with PWM. */
  // Example :
  // Incoming command = S,10
  // S = Slider
  // 10 = slider value
  // I set the slider value range from 0 to 10.
  // Then the slider value is changed from 0 - 10 or vice versa to 0 - 255 or vice versa.
  if (resultData == "SL") {
    resultData = getValue(getData, ',', 1);
    int pwm = map(resultData.toInt(), 0, 20, 0, 255);
    ledcWrite(PWM_LED_Channel, pwm);
    Serial.print("PWM LED On Board : ");
    Serial.println(pwm);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Controlling the servos on the Pan and Tilt Camera Mount. */
  if (resultData == "SP") {
    resultData = getValue(getData, ',', 1);
    servo_LeftRight_Pos = resultData.toInt();
    servo_LeftRight.write(servo_LeftRight_Pos);
    Serial.print("Pan Servo Value : ");
    Serial.println(servo_LeftRight_Pos);
  }

  if (resultData == "ST") {
    resultData = getValue(getData, ',', 1);
    servo_UpDown_Pos = resultData.toInt();
    servo_UpDown.write(servo_UpDown_Pos);
    Serial.print("Tilt Servo Value : ");
    Serial.println(servo_UpDown_Pos);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Controlling the speed of dc motors with PWM. */
  if (resultData == "SS") {
    resultData = getValue(getData, ',', 1);
    int pwm = map(resultData.toInt(), 0, 10, 0, 255);
    PWM_Motor_DC = pwm;
    Serial.print("PWM Motor DC Value : ");
    Serial.println(PWM_Motor_DC);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Processes and executes commands received from the index page/web server. */
  // Example :
  // Incoming Command = B,F
  // B = Button
  // F = Command for the car to move forward.
  
  if (resultData == "B") {
    resultData = getValue(getData, ',', 1);

    if (resultData == "clr") {
      QRCodeResult = "";
    }
  

    if (resultData == "F") {
      Move_Forward(PWM_Motor_DC);
    }

    if (resultData == "B") {
      Move_Backward(PWM_Motor_DC);
    }

    if (resultData == "R") {
      Move_Right(PWM_Motor_DC);
    }

    if (resultData == "L") {
      Move_Left(PWM_Motor_DC);
    }

    if (resultData == "S") {
      Move_Stop();
    }

    Serial.print("Button : ");
    Serial.println(resultData);
  }
  /* ---------------------------------------- */
  
  if(res){
    return httpd_resp_send_500(req);
  }
 
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}

static esp_err_t qrcoderslt_handler(httpd_req_t *req){
  if (QRCodeResult != "Decoding FAILED") QRCodeResultSend = QRCodeResult;
  httpd_resp_send(req, QRCodeResultSend.c_str(), HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ Subroutine for starting the web server / startCameraServer. */
void startCameraWebServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = index_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t cmd_uri = {
    .uri       = "/action",
    .method    = HTTP_GET,
    .handler   = cmd_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t qrcoderslt_uri = {
    .uri       = "/getqrcodeval",
    .method    = HTTP_GET,
    .handler   = qrcoderslt_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };
    
  if (httpd_start(&index_httpd, &config) == ESP_OK) {
      httpd_register_uri_handler(index_httpd, &index_uri);
      httpd_register_uri_handler(index_httpd, &cmd_uri);
      httpd_register_uri_handler(index_httpd, &qrcoderslt_uri);
  }

  config.server_port += 1;
  config.ctrl_port += 1;  
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
      httpd_register_uri_handler(stream_httpd, &stream_uri);
  }

  Serial.println();
  Serial.println("Camera Server started successfully");
  Serial.print("Camera Stream Ready! Go to: http://");
  Serial.println(WiFi.localIP());
  Serial.println();
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ String function to process the data command */
// I got this from : https://www.electroniclinic.com/reyax-lora-based-multiple-sensors-monitoring-using-arduino/
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car is moving forward. */
void Move_Forward(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_R, pwm_result);
  digitalWrite(Motor_L_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_L, pwm_result);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car is moving backwards. */
void Move_Backward(int pwm_val) {
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, pwm_val);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, pwm_val);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car turns right (rotates right). */
void Move_Right(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, pwm_val);
  digitalWrite(Motor_L_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_L, pwm_result);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car turns left (rotates left). */
void Move_Left(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_R, pwm_result);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, pwm_val);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ */
void Move_Stop() {
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, 0);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, 0);
}
/* ________________________________________________________________________________ The subroutine for the robot car stops (stops moving). */

/* ________________________________________________________________________________ VOID SETUP() */
void setup() {
  // put your setup code here, to run once:

  // Disable brownout detector.
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  /* ---------------------------------------- Init serial communication speed (baud rate). */
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  /* ---------------------------------------- */

  pinMode(LED_OnBoard, OUTPUT);

  /* ---------------------------------------- Setting Servos */
  Serial.println();
  Serial.println("------------");
  Serial.println("Start setting Servos...");
  servo_LeftRight.setPeriodHertz(50); //--> // Standard 50hz servo
  servo_UpDown.setPeriodHertz(50);    //--> // Standard 50hz servo
  servo_Dummy_1.attach(14, 1000, 2000);
  servo_Dummy_2.attach(15, 1000, 2000);
  servo_LeftRight.attach(servo_LeftRight_Pin, 1000, 2000);
  servo_UpDown.attach(servo_UpDown_Pin, 1000, 2000);
  
  servo_LeftRight.write(servo_LeftRight_Pos);
  servo_UpDown.write(servo_UpDown_Pos);
  Serial.println("Setting up the servos was successful.");
  Serial.println("------------");
  /* ---------------------------------------- */
  
  delay(500);

  /* ---------------------------------------- The pin to set the direction of rotation of the motor is set as OUTPUT. */
  pinMode(Motor_R_Dir_Pin, OUTPUT);
  pinMode(Motor_L_Dir_Pin, OUTPUT);
  /* ---------------------------------------- */

  /* ---------------------------------------- Setting PWM. */
  // Set the PWM for the On Board LED.
  Serial.println();
  Serial.println("------------");
  Serial.println("Start setting PWM for LED On Board...");
  ledcAttachPin(LED_OnBoard, PWM_LED_Channel);
  ledcSetup(PWM_LED_Channel, PWM_LED_Freq, PWM_LED_resolution);
  Serial.println("Setting the PWM for LED On Board was successful.");
  Serial.println();

  // Set the PWM for DC Motor / Motor Drive.
  Serial.println("Start setting PWM for DC Motor...");
  ledcAttachPin(Motor_R_PWM_Pin, PWM_Channel_Mtr_R);
  ledcAttachPin(Motor_L_PWM_Pin, PWM_Channel_Mtr_L);
  ledcSetup(PWM_Channel_Mtr_R, PWM_Mtr_Freq, PWM_Mtr_Resolution);
  ledcSetup(PWM_Channel_Mtr_L, PWM_Mtr_Freq, PWM_Mtr_Resolution);
  Serial.println("Setting the PWM for the DC Motor was successful.");
  Serial.println("------------");
  /* ---------------------------------------- */

  delay(500);

  /* ---------------------------------------- Camera configuration. */
  Serial.println();
  Serial.println("------------");
  Serial.println("Start configuring and initializing the camera...");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_GRAYSCALE;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 15;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  }
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QVGA);
  Serial.println("Configure and initialize the camera successfully.");
  Serial.println("------------");
  Serial.println();
  /* ---------------------------------------- */

  /* ---------------------------------------- Connect to Wi-Fi. */
  WiFi.mode(WIFI_STA);
  Serial.println("------------");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  /* ::::::::::::::::: The process of connecting ESP32 CAM with WiFi Hotspot / WiFi Router. */
  /*
   * The process timeout of connecting ESP32 CAM with WiFi Hotspot / WiFi Router is 20 seconds.
   * If within 20 seconds the ESP32 CAM has not been successfully connected to WiFi, the ESP32 CAM will restart.
   * I made this condition because on my ESP32-CAM, there are times when it seems like it can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.
   */
  int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    ledcWrite(PWM_LED_Channel, 255);
    delay(250);
    ledcWrite(PWM_LED_Channel, 0);
    delay(250);
    if(connecting_process_timed_out > 0) connecting_process_timed_out--;
    if(connecting_process_timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }
  ledcWrite(PWM_LED_Channel, 0);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("------------");
  Serial.println("");
  /* ::::::::::::::::: */
  /* ---------------------------------------- */

  // Start camera web server
  startCameraWebServer(); 
    // Calls the createTaskQRCodeReader() subroutine.
  createTaskQRCodeReader();
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ VOID LOOP */
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ws_run == true) {
      if (get_wsLive_val == true) {
        last_wsLive_val = wsLive_val;
        get_wsLive_val = false;
      }
   
      get_wsLive_interval++;
      if (get_wsLive_interval > 2) {
        get_wsLive_interval = 0;
        get_wsLive_val = true;
        if (wsLive_val == last_wsLive_val) {
          ws_run = false;
          last_wsLive_val = 0;
          createTaskQRCodeReader();
        }
      }
    }
  }
}
void createTaskQRCodeReader() {
  xTaskCreatePinnedToCore(
             QRCodeReader,          /* Task function. */
             "QRCodeReader_Task",   /* name of task. */
             10000,                 /* Stack size of task */
             NULL,                  /* parameter of the task */
             1,                     /* priority of the task */
             &QRCodeReader_Task,    /* Task handle to keep track of created task */
             0);                    /* pin task to core 0 */
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ QRCodeReader() */
void QRCodeReader( void * pvParameters ){
  Serial.print("QRCodeReader running on core ");
  Serial.println(xPortGetCoreID());

  while(!ws_run){
      camera_fb_t * fb = NULL;
      q = quirc_new();
      
      if (q == NULL){
        Serial.print("can't create quirc object\r\n");  
        continue;
      }
      
      fb = esp_camera_fb_get();
      if (!fb)
      {
        Serial.println("Camera capture failed (QRCodeReader())");
        continue;
      }
      
      quirc_resize(q, fb->width, fb->height);
      image = quirc_begin(q, NULL, NULL);
      memcpy(image, fb->buf, fb->len);
      quirc_end(q);
      
      int count = quirc_count(q);
      if (count > 0) {
        //Serial.println(count);
        quirc_extract(q, 0, &code);
        err = quirc_decode(&code, &data);
    
        if (err){
          QRCodeResult = "Decoding FAILED";
          Serial.println(QRCodeResult);
        } else {
          Serial.printf("Decoding successful:\n");
          dumpData(&data);
        } 
        Serial.println();
      } 
      
      esp_camera_fb_return(fb);
      fb = NULL;
      image = NULL;  
      quirc_destroy(q);
  }
}
void dumpData(const struct quirc_data *data)
{
  Serial.printf("-Version: %d\n", data->version);
  Serial.printf("-ECC level: %c\n", "MLHQ"[data->ecc_level]);
  Serial.printf("-Mask: %d\n", data->mask);
  Serial.printf("-Length: %d\n", data->payload_len);
  Serial.printf("-Payload: %s\n", data->payload);
  
  QRCodeResult = (const char *)data->payload;
}
void cmd_execution() {
  if (QRCodeResult == "LED BLUE ON") digitalWrite(LED_Blue, HIGH);
  if (QRCodeResult == "LED BLUE OFF") digitalWrite(LED_Blue, LOW);
  if (QRCodeResult == "LED GREEN ON") digitalWrite(LED_Green, HIGH);
  if (QRCodeResult == "LED GREEN OFF") digitalWrite(LED_Green, LOW);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ String function to process the data command */
// I got this from : https://www.electroniclinic.com/reyax-lora-based-multiple-sensors-monitoring-using-arduino/
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ String function to process the data command */
// I got this from : https://www.electroniclinic.com/reyax-lora-based-multiple-sensors-monitoring-using-arduino/
/* ________________________________________________________________________________ */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<