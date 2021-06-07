// All configurable variable going hear !!!!


#ifndef DCCconfig
#define DCCconfig

const char* SSID = "Your SSID" ;       // Your network SSID (name)
const char* PASS = "Network password" ;      // Your network password
const char* HOST = "192.168.0.101" ; // DCC command Station / JMRI Address
const int PORT = 12060 ;             // DCC command Station / JMRI Port
String Id = "DCCthrottle-2" ;        // Your Throttle ID 
String Tname = "S-Throttle #02" ;    // Your Throttle name 


int Acceltime  = 250; // Set acceleration time of LocoSpeed 
int BrakealertDaTa = 2500 ; //Set limit of brake alert 0 = no alert 4000 = min brake 
int ThrottleLimit1[11] = {0, 10, 20, 30, 40, 60, 80, 100, 126, 250, 2500} ;
int ThrottleLimit[11] = {0, 10, 20, 30, 40, 60, 80, 100, 126, 250, 2500} ; // Throttle notch 0 to 8 , Accel time , Brake alert .
#endif
