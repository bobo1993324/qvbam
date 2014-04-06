#include "window.h"

extern int RGB_LOW_BITS_MASK;

int Init_2xSaI(u32);

Window::Window() :
    m_iGBAScreenWidth (240),
    m_iGBAScreenHeight(160),
    m_eCartridge(CartridgeNone) {
    vInitSystem();
    idleTimer.setInterval(10);
    vApplyConfigScreenArea();
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
        //        vSaveBattery();
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
    qDebug() << "TODO:: stopEmu" << endl;
}

void Window::vApplyPerGameConfig() {
    qDebug() << "TODO:: vApplyPerGameConfig" << endl;
}

void Window::vLoadBattery() {
    qDebug() << "TODO:: vLoadBattery" << endl;
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
    vSDLPollEvents();

    m_stEmulator.emuMain(m_stEmulator.emuCount);
    idleTimer.singleShot(1, this, SLOT(bOnEmuIdle()));
    return true;
}

void Window::vSDLPollEvents()
{
    //TODO: configure joytick first
    qDebug() << "TODO::vSDLPollEvents" << endl;
    //    SDL_Event event;
    //    while(SDL_PollEvent(&event))
    //    {
    //        switch(event.type)
    //        {
    //        case SDL_JOYHATMOTION:
    //        case SDL_JOYBUTTONDOWN:
    //        case SDL_JOYBUTTONUP:
    //        case SDL_JOYAXISMOTION:
    //        case SDL_KEYDOWN:
    //        case SDL_KEYUP:
    //            qDebug() << "input recieved";
    //            inputProcessSDLEvent(event);
    //            break;
    //        }
    //    }
}

void Window::vDrawScreen()
{
    m_iFrameCount++;
    sDrawScreen();
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
