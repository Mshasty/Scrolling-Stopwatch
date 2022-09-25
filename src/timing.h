int16_t myTime = 0;
unsigned long newtime = 0;
unsigned long oldtime;
unsigned long keytime = 0;
boolean started = false;
boolean stopped = true;
boolean paused = false;
boolean pressed = false;

void time2buf(int16_t t) {
  int isMin = t / 600;
  int allSec = t - isMin * 600;
  int isSec = allSec / 10;
  int dSec = allSec % 10;
  sprintf_P(message, (PGM_P)F(" %1d:%02d.%1d"), isMin, isSec, dSec);
}

void NextTime() {
  //static uint8_t  putIndex = 0; 
  myTime++;
  if (myTime >= 6000) myTime = 0;
  if (!paused) time2buf(myTime);
}
