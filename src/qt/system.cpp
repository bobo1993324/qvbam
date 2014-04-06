#include "system.h"
int  systemRedShift;
int  systemGreenShift;
int  systemBlueShift;
int  systemColorDepth;
int  systemVerbose;
int  systemSaveUpdateCounter;
int  systemFrameSkip;
u32  systemColorMap32[0x10000];
u16  systemColorMap16[0x10000];
u16  systemGbPalette[24];


int  emulating;
int  RGB_LOW_BITS_MASK;
extern Window * w;
Window * GUI() {
    return w;
}

void systemMessage(int _iId, const char * _csFormat, ...)
{
    qDebug() << "TODO:: systemMessage";
//  va_list args;
//  va_start(args, _csFormat);

//  GUI()->vPopupErrorV(_(_csFormat), args);

//  va_end(args);
}

void debuggerBreakOnWrite(u32 address, u32 oldvalue, u32 value, int size, int t)
{
}

void log(const char *defaultMsg, ...)
{
    qDebug() << "TODO:: log";

//  static FILE *out = NULL;

//  if(out == NULL) {
//    out = fopen("trace.log","w");
//  }

//  va_list valist;

//  va_start(valist, defaultMsg);
//  vfprintf(out, defaultMsg, valist);
//  va_end(valist);
}

int systemGetSensorX()
{
  return 0;
}

int systemGetSensorY()
{
  return 0;
}

void debuggerOutput(const char *, u32)
{
}

void debuggerSignal(int, int)
{
}

void (*dbgOutput)(const char *, u32) = debuggerOutput;
void (*dbgSignal)(int, int) = debuggerSignal;

bool systemCanChangeSoundQuality()
{
  return true;
}

SoundDriver * systemSoundInit()
{
    soundShutdown();

    return new SoundSDL();
}

void systemOnSoundShutdown()
{
}

void systemOnWriteDataToSoundBuffer(const u16 * finalWave, int length)
{
}

bool systemReadJoypads()
{
  return true;
}

u32 systemReadJoypad(int joy)
{
  return inputReadJoypad(joy);
}

u32 systemGetClock()
{
    qDebug() << "TODO::systemGetClock";
    return 0;
//    Glib::TimeVal time;
//    time.assign_current_time();
//    return time.as_double() * 1000;
}

bool systemPauseOnFrame()
{
  return false;
}

void systemFrame()
{
}

void system10Frames(int _iRate)
{
    qDebug() << "TODO::system10Frames";
//  GUI()->vComputeFrameskip(_iRate);
}

void systemShowSpeed(int _iSpeed)
{
    qDebug() << "TODO::systemShowSpeed " << _iSpeed;
//  GUI()->vShowSpeed(_iSpeed);
}

void systemUpdateMotionSensor()
{
}

void systemScreenCapture(int _iNum)
{
    qDebug() << "TODO::systemScreenCapture";
//  GUI()->vCaptureScreen(_iNum);
}

void systemDrawScreen()
{
    qDebug() << "TODO::systemDrawScreen";
    GUI()->vDrawScreen();
}

void systemGbBorderOn()
{
}
