#include "window.h"

extern int RGB_LOW_BITS_MASK;

int Init_2xSaI(u32);

Window::Window() :
    m_iGBAScreenWidth (240),
    m_iGBAScreenHeight(160),
    m_eCartridge(CartridgeNone) {
    //SDLdoesn't work on TOUCH yet
    vInitSDL();
    vInitSystem();

    // Get config
    //
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    m_sUserDataDir = (QString(homedir)
            + QString("/.local/share/com.ubuntu.developer.bobo1993324.qvbam/")
            ).toStdString();
    QDir qDir(QString::fromStdString(m_sUserDataDir));
    if (!qDir.exists()) {
        qDir.mkpath(QString::fromStdString(m_sUserDataDir));
    }

//    m_sConfigFile  = m_sUserDataDir + "/config";

//    vInitConfig();

//    if (Glib::file_test(m_sConfigFile, Glib::FILE_TEST_EXISTS))
//    {
//      vLoadConfig(m_sConfigFile);
//      vCheckConfig();
//    }
//    else
//    {
//      vSaveConfig(m_sConfigFile);
//    }


    vApplyConfigScreenArea();
    vApplyConfigFrameskip();
}

Window::~Window() {
    qDebug() << "~Windows called";
    vOnFileClose();
//    vUnInitSystem();
//    vSaveJoypadsToConfig();
//    vSaveConfig(m_sConfigFile);
}

bool Window::bLoadROM(const std::string &_rsFile) {
    vOnFileClose();

    // clear cheat list
    //    cheatsDeleteAll(false);
    //    gbCheatRemoveAll();

    m_sRomFile = _rsFile;
    const char * csFile = _rsFile.c_str();

    IMAGE_TYPE eType = utilFindType(csFile);
    if (eType == IMAGE_UNKNOWN)
    {
        qDebug () << "Unknown file type" << csFile;
        return false;
    }

    bool bLoaded = false;
    //    if (eType == IMAGE_GB)
    //    {
    //        bLoaded = gbLoadRom(csFile);
    //        if (bLoaded)
    //        {
    //            m_eCartridge = CartridgeGB;
    //            m_stEmulator = GBSystem;

    //            useBios = m_poCoreConfig->oGetKey<bool>("gb_use_bios_file");
    //            gbGetHardwareType();

    //            if (gbHardware & 5)
    //            {
    //                gbCPUInit(m_poCoreConfig->sGetKey("gb_bios_file").c_str(), useBios);
    //            }

    //            // If the bios file was rejected by gbCPUInit
    //            if (m_poCoreConfig->oGetKey<bool>("gb_use_bios_file") && ! useBios)
    //            {
    //                m_poCoreConfig->vSetKey("gb_bios_file", "");
    //            }

    //            gbReset();
    //        }
    //    }
    //    else
    if (eType == IMAGE_GBA)
    {
        int iSize = CPULoadRom(csFile);
        bLoaded = (iSize > 0);
        if (bLoaded)
        {
            m_eCartridge = CartridgeGBA;
            m_stEmulator = GBASystem;

            vApplyPerGameConfig();

            //            useBios = m_poCoreConfig->oGetKey<bool>("use_bios_file");
            useBios = false;
            //            CPUInit(m_poCoreConfig->sGetKey("bios_file").c_str(), useBios);
            CPUInit("", useBios);
            CPUReset();

            // If the bios file was rejected by CPUInit
            //            if (m_poCoreConfig->oGetKey<bool>("use_bios_file") && ! useBios)
            //            {
            //                m_poCoreConfig->vSetKey("bios_file", "");
            //            }
        }
    }

    if (! bLoaded)
    {
        return false;
    }

    vLoadBattery();
    //    vLoadCheats();
    vUpdateScreen();

    emulating = 1;
    m_bWasEmulating = false;

    //    vApplyConfigSoundSampleRate();

    //    vUpdateGameSlots();
    //    vHistoryAdd(_rsFile);

    //    for (std::list<Gtk::Widget *>::iterator it = m_listSensitiveWhenPlaying.begin();
    //         it != m_listSensitiveWhenPlaying.end();
    //         it++)
    //    {
    //        (*it)->set_sensitive();
    //    }

    //    if (m_poCoreConfig->oGetKey<bool>("load_game_auto"))
    //    {
    //        vOnLoadGameMostRecent();
    //    }

    vStartEmu();

    return true;
}

void Window::vOnFileClose() {
    if (m_eCartridge != CartridgeNone)
    {
        soundPause();
        vStopEmu();
        //        vSetDefaultTitle();
        //        vDrawDefaultScreen();
        vSaveBattery();
        //        vSaveCheats();
        m_stEmulator.emuCleanUp();
        m_eCartridge = CartridgeNone;
        emulating = 0;

        //        vUpdateGameSlots();

        //      for (std::list<Gtk::Widget *>::iterator it = m_listSensitiveWhenPlaying.begin();
        //           it != m_listSensitiveWhenPlaying.end();
        //           it++)
        //      {
        //        (*it)->set_sensitive(false);
        //      }

        //      m_poFilePauseItem->set_active(false);
    }
}

void Window::vStopEmu() {
    idleTimer.stop();
    m_bWasEmulating = false;
}

void Window::vApplyPerGameConfig() {
    qDebug() << "TODO:: vApplyPerGameConfig" << endl;
}

void Window::vLoadBattery() {
    std::string sBattery;
    std::string sDir;
    sDir = m_sUserDataDir;
    sBattery = sDir + "/" + m_sRomFile + ".sav";
    if (m_stEmulator.emuReadBattery(sBattery.c_str()))
    {
      systemScreenMessage("Loaded battery");
    }
}

void Window::vUpdateScreen() {
    //    if (m_eCartridge == CartridgeGB)
    //    {
    //      if (gbBorderOn)
    //      {
    //        m_iScreenWidth     = m_iSGBScreenWidth;
    //        m_iScreenHeight    = m_iSGBScreenHeight;
    //        gbBorderLineSkip   = m_iSGBScreenWidth;
    //        gbBorderColumnSkip = (m_iSGBScreenWidth - m_iGBScreenWidth) / 2;
    //        gbBorderRowSkip    = (m_iSGBScreenHeight - m_iGBScreenHeight) / 2;
    //      }
    //      else
    //      {
    //        m_iScreenWidth     = m_iGBScreenWidth;
    //        m_iScreenHeight    = m_iGBScreenHeight;
    //        gbBorderLineSkip   = m_iGBScreenWidth;
    //        gbBorderColumnSkip = 0;
    //        gbBorderRowSkip    = 0;
    //      }
    //    }
    //    else
    if (m_eCartridge == CartridgeGBA)
    {
        m_iScreenWidth  = m_iGBAScreenWidth;
        m_iScreenHeight = m_iGBAScreenHeight;
    }

    Q_ASSERT(m_iScreenWidth >= 1 && m_iScreenHeight >= 1);

    //    m_poScreenArea->vSetSize(m_iScreenWidth, m_iScreenHeight);
    //    m_poScreenArea->vSetScale(m_poDisplayConfig->oGetKey<int>("scale"));

    //    resize(1, 1);

    //    if (emulating)
    //    {
    //      vDrawScreen();
    //    }
    //    else
    //    {
    //      vDrawDefaultScreen();
    //    }
}

void Window::vStartEmu() {
    idleTimer.singleShot(1, this, SLOT(bOnEmuIdle()));
}

void Window::vInitSystem()
{
    systemColorDepth = 32;
    systemVerbose = 0;
    systemSaveUpdateCounter = SYSTEM_SAVE_NOT_UPDATED;
    systemFrameSkip = 2;

    emulating = 0;

    gbFrameSkip = 0;

    soundInit();
}

bool Window::bOnEmuIdle()
{
    //    qDebug() << "Idle" ;
//    vSDLPollEvents();

    m_stEmulator.emuMain(m_stEmulator.emuCount);
    idleTimer.singleShot(0, this, SLOT(bOnEmuIdle()));
    return true;
}

void Window::vSDLPollEvents()
{
        SDL_Event event;
        qDebug() << "Window::vSDLPollEvents";
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_JOYHATMOTION:
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            case SDL_JOYAXISMOTION:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                qDebug() << "input recieved";
                inputProcessSDLEvent(event);
                break;
            }
        }
}

void Window::vDrawScreen()
{
    m_iFrameCount++;
    sDrawScreen();
}

bool Window::on_key_press_event(Qt::Key key) {
    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = (SDLKey)key;
//    qDebug() << "SDLKey pressed " << key << event.key.keysym.sym << endl;
    inputProcessSDLEvent(event);

    return true;
}

bool Window::on_key_release_event(Qt::Key key) {
//    qDebug() << "SDLKey on_key_release_event " << key << endl;
    SDL_Event event;
    event.type = SDL_KEYUP;
    event.key.keysym.sym = (SDLKey)key;
    inputProcessSDLEvent(event);
    return true;
}

void Window::vApplyConfigScreenArea() {
    vInitColors(ColorFormatRGB);
}

void Window::vInitColors(EColorFormat _eColorFormat) {
    switch (_eColorFormat)
    {
    case ColorFormatBGR:
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
        systemRedShift    = 3;
        systemGreenShift  = 11;
        systemBlueShift   = 19;
        RGB_LOW_BITS_MASK = 0x00010101;
#else
        systemRedShift    = 27;
        systemGreenShift  = 19;
        systemBlueShift   = 11;
        RGB_LOW_BITS_MASK = 0x01010100;
#endif
        break;
    default:
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
        systemRedShift    = 19;
        systemGreenShift  = 11;
        systemBlueShift   = 3;
        RGB_LOW_BITS_MASK = 0x00010101;
#else
        systemRedShift    = 11;
        systemGreenShift  = 19;
        systemBlueShift   = 27;
        RGB_LOW_BITS_MASK = 0x01010100;
#endif
        break;
    }

    for (int i = 0; i < 0x10000; i++)
    {
        systemColorMap32[i] = (((i & 0x1f) << systemRedShift)
                               | (((i & 0x3e0) >> 5) << systemGreenShift)
                               | (((i & 0x7c00) >> 10) << systemBlueShift));
    }

    for (int i = 0; i < 24; )
    {
        systemGbPalette[i++] = (0x1f) | (0x1f << 5) | (0x1f << 10);
        systemGbPalette[i++] = (0x15) | (0x15 << 5) | (0x15 << 10);
        systemGbPalette[i++] = (0x0c) | (0x0c << 5) | (0x0c << 10);
        systemGbPalette[i++] = 0;
    }

    Init_2xSaI(32);
}

void Window::vInitSDL()
{
    static bool bDone = false;

    if (bDone)
        return;

//    int iFlags = (SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE);

    //Currently we don't need to init, or not with everything.
//    if (SDL_Init(iFlags) < 0)
//    {
//        qDebug() << "Failed to init SDL: " << SDL_GetError();
//        abort();
//    }

    inputSetKeymap(PAD_DEFAULT, KEY_LEFT, Qt::Key_Left);
    inputSetKeymap(PAD_DEFAULT, KEY_RIGHT, Qt::Key_Right);
    inputSetKeymap(PAD_DEFAULT, KEY_UP, Qt::Key_Up);
    inputSetKeymap(PAD_DEFAULT, KEY_DOWN, Qt::Key_Down);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_A, Qt::Key_Z);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_B, Qt::Key_X);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_START, Qt::Key_Return);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_SELECT, Qt::Key_Backspace);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_L, Qt::Key_A);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_R, Qt::Key_S);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_SPEED, Qt::Key_Space);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_CAPTURE, Qt::Key_F12);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_AUTO_A, Qt::Key_Q);
    inputSetKeymap(PAD_DEFAULT, KEY_BUTTON_AUTO_B, Qt::Key_W);

    // TODO : remove
    int sdlNumDevices = SDL_NumJoysticks();
    for (int i = 0; i < sdlNumDevices; i++)
        SDL_JoystickOpen(i);

    inputInitJoysticks();

    bDone = true;
}

void Window::vSaveBattery() {
    std::string sBattery;
    std::string sDir;
    sDir = m_sUserDataDir;

    sBattery = sDir + "/" + m_sRomFile + ".sav";

    if (m_stEmulator.emuWriteBattery(sBattery.c_str()))
    {
      systemScreenMessage("Saved battery");
    }
}

void Window::vComputeFrameskip(int _iRate) {
    static QDateTime uiLastTime;
    static int iFrameskipAdjust = 0;

    QDateTime uiTime = QDateTime::currentDateTime();

    if (m_bWasEmulating)
    {
      if (m_bAutoFrameskip)
      {
        int uiDiff = uiTime.toMSecsSinceEpoch() - uiLastTime.toMSecsSinceEpoch();
        const int iWantedSpeed = 100;
        int iSpeed = iWantedSpeed;

        if (uiDiff != 0)
        {
          iSpeed = (1000000 / _iRate) / (uiDiff);
        }

        if (iSpeed >= iWantedSpeed - 2)
        {
          iFrameskipAdjust++;
          if (iFrameskipAdjust >= 3)
          {
            iFrameskipAdjust = 0;
            if (systemFrameSkip > 0)
            {
              systemFrameSkip--;
            }
          }
        }
        else
        {
          if (iSpeed < iWantedSpeed - 20)
          {
            iFrameskipAdjust -= ((iWantedSpeed - 10) - iSpeed) / 5;
          }
          else if (systemFrameSkip < 9)
          {
            iFrameskipAdjust--;
          }

          if (iFrameskipAdjust <= -4)
          {
            iFrameskipAdjust = 0;
            if (systemFrameSkip < 9)
            {
              systemFrameSkip++;
            }
          }
        }
      }
    }
    else
    {
      m_bWasEmulating = true;
    }
    qDebug() << "systemFrameSkip is " << systemFrameSkip << endl;

    uiLastTime = uiTime;
}

void Window::vApplyConfigFrameskip() {
//    std::string sFrameskip = m_poCoreConfig->oGetKey<std::string>("frameskip");
    std::string sFrameskip = "auto";
    if (sFrameskip == "auto")
    {
      m_bAutoFrameskip = true;
      gbFrameSkip      = 0;
      systemFrameSkip  = 0;
    }
    else
    {
      m_bAutoFrameskip = false;
      int iFrameskip = 0;
//      int iFrameskip = m_poCoreConfig->oGetKey<int>("frameskip");
      gbFrameSkip      = iFrameskip;
      systemFrameSkip  = iFrameskip;
    }
}
