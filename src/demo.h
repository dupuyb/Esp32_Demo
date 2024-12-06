#ifndef DEMO_h
#define DEMO_h

//---- Start Generated from src/demo.html file --- 2024-11-18 09:38:31.258986
const char HTTP_DEMO[] PROGMEM = "<!DOCTYPE html><html><style>.l12 {text-align: right;width: 10em;display: inline-block;}.c12 {text-align: center;width: 10em;display: inline-block;}.r12 {text-align: left;width: 15em;display: inline-block;}.myButton {font-weight: bold;text-align: center;}.myButton:hover {background: linear-gradient(to bottom, #60ec03 5%, #a7c61f 100%);background-color: #60ff05;}.myButton:active {position: relative;top: 1px;}</style><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>%%TITLE%%</title></head><body><center><h3>AD-ELENA Dot Configurations</h3><div style=' width: 40em; display: inline-block; text-align: left; padding:20px 5px; '><fieldset><legend> Open specific page : </legend><ul><li>Current date %%DATE%% .</li><li>WebSocket page <a href='/websocket.html'> open here </a> for a direct control.</li><li>Specialist tool <a href='/'> open here </a> for upload or download files.</li></ul></fieldset></div><div style=' width: 40em; display: block; text-align: left; '><fieldset><legend> Action : </legend>Dot Display:<button><a href=\"/demo?Cmd=open\" class=\"myButton\">Switch ON</a> </button><button><a href=\"/demo?Cmd=close\" class=\"myButton\">Switch OFF</a> </button><button><a href=\"/demo?Cmd=reset\" class=\"myButton\">Reset</a> </button></fieldset><!-- Add command Open CLose Reset--></div><div style=' width: 40em; display: block; text-align: left; '><fieldset><legend> ESP32 Parameters : </legend><ul><li>Software versiobn : <b>%%VL%%</b></li><li>Last Reboot date  : <b>%%RB%%</b></li><li>Network Host Name : <b>%%HOS%%</b></li><li>Mac adress        : <b>%%MAC%%</b></li><li>IP adresss        : <b>%%IP%%</b></li><li>Memory Total/Used : <b>%%MFREE%%</b> Kbytes</li></ul></fieldset></div></center></body></html>";
//---- len : 1791 bytes
//---- End Generated 


// -------- Web tranlat wrapper Get Set  -------------
char strtmp [20];
char* getRB()  {  return (char*) rebootTime.c_str();}
char* getMFREE() { 
  int a = SPIFFS.totalBytes()/1024; int b = SPIFFS.usedBytes()/1024;
  snprintf(strtmp, sizeof(strtmp), "%d/%d",  a, b);
  return strtmp;
}
char* getVL() { return (char*) VERSION; }
char* getHOS() { return frame.config.HostName;}
char* getIP() { snprintf(strtmp, sizeof(strtmp), "%s", WiFi.localIP().toString().c_str()); return strtmp;}
char* getTITLE() { snprintf(strtmp, sizeof(strtmp), "%s",frame.config.HostName); return strtmp;}
char* getMAC() { snprintf(strtmp, sizeof(strtmp), "%s",WiFi.macAddress().c_str()); return strtmp;}
char* getDATE() { snprintf(strtmp, sizeof(strtmp), "%s",getDate().c_str()); return strtmp;}

struct Equiv {
  char key[10];
  char* (*get_ptr)(void);
  void  (*set_ptr)(String);
};

#define NBRITEMINDICO 8

Equiv dico[] ={
  {"%%RB%%"   , &getRB   ,  NULL   },
  {"%%MFREE%%", &getMFREE,  NULL   },
  {"%%VL%%"   , &getVL   ,  NULL   },
  {"%%HOS%%"  , &getHOS  ,  NULL   },
  {"%%IP%%"   , &getIP   ,  NULL   },
  {"%%TITLE%%", &getTITLE,  NULL   },
  {"%%MAC%%"  , &getMAC  ,  NULL   },
  {"%%DATE%%" , &getDATE ,  NULL   },
};

String getKey(int i) {
  return  "%%"+frame.server.argName(i)+"%%";
}

void callbackSetWwm(int i){
  for (int idx=0; idx<NBRITEMINDICO; idx++) {
    if (getKey(i)==dico[idx].key  && dico[idx].set_ptr != NULL) {
      (*dico[idx].set_ptr)(frame.server.arg(i));
      return;
    }
  }
}

String callbackGetWwm(int i){
  for (int idx=0; idx<NBRITEMINDICO; idx++) {
    if (getKey(i)==dico[idx].key  && dico[idx].get_ptr!=NULL) {
      return (*dico[idx].get_ptr)();
    }
  }
  return "";
}

String sentHtmlDemo(){
  // Http get or post action
  if (frame.server.method() == HTTP_POST || frame.server.method() == HTTP_GET) {
    for (uint8_t i=0; i<frame.server.args(); i++) { // Scan if Post or Get contain %%key%%
#ifdef DEBUG_MAIN
      Serial.printf("sentHtmlDemo(Post or Get)  Arg->[%s]:[%s]\n\r", frame.server.argName(i).c_str(), frame.server.arg(i).c_str() );
#endif   
      if (frame.server.arg(i).isEmpty()) // Received a Get like "Cmd=" wihtout Arg will return "Open" As text
        return callbackGetWwm(i); // Return immediate value only
      else
        callbackSetWwm(i);
    }
  }  
  // Return html page with substitution 
  String rt = HTTP_DEMO; 
  for (int idx=0; idx<NBRITEMINDICO; idx++){ 
    if (dico[idx].get_ptr!=NULL) rt.replace(dico[idx].key, (*dico[idx].get_ptr)() ); 
  } 
  return rt; 
}

#endif
