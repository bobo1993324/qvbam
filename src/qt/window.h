#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QAbstractEventDispatcher>
#include <QString>
#include "../gba/Sound.h"
#include "../Util.h"
#include "../gba/GBA.h"
#include "../gb/gbGlobals.h"
#include "../sdl/inputSDL.h"
#include <SDL_keysym.h>
#include <pwd.h>
#include <QDir>

#ifndef WINDOW
#define WINDOW
class Window : public QObject {
    Q_OBJECT

public:

    int m_iScreenWidth;
    int m_iScreenHeight;

    enum ECartridge
    {
      CartridgeNone,
      CartridgeGB,
      CartridgeGBA
    };

    enum EColorFormat
    {
      ColorFormatRGB,
      ColorFormatBGR
    };

    Window();
    ~Window();
    bool bLoadROM(const std::string & _rsFile);
    void vDrawScreen();

    Q_INVOKABLE bool on_key_press_event(Qt::Key key);
    Q_INVOKABLE bool on_key_release_event(Qt::Key key);
public slots:
    bool bOnEmuIdle();

signals:
    void sDrawScreen();

private:
    int m_iFrameCount;

    const int m_iGBAScreenWidth;
    const int m_iGBAScreenHeight;

    std::string       m_sUserDataDir;

    std::string    m_sRomFile;
    ECartridge     m_eCartridge;
    EmulatedSystem m_stEmulator;

    bool m_bWasEmulating;
    QTimer idleTimer;

    void vOnFileClose();
    void vStopEmu();
    void vApplyPerGameConfig();
    void vLoadBattery();
    void vUpdateScreen();
    void vStartEmu();
    void vInitSystem();
    void vInitSDL();
    void vSDLPollEvents();
    void vApplyConfigScreenArea();
    void vInitColors(EColorFormat _eColorFormat);
    void vSaveBattery();
};
#endif
