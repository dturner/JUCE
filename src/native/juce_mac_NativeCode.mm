/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

/*
    This file wraps together all the mac-specific code, so that
    we can include all the native headers just once, and compile all our
    platform-specific stuff in one big lump, keeping it out of the way of
    the rest of the codebase.
*/

#include "mac/juce_mac_NativeIncludes.h"

BEGIN_JUCE_NAMESPACE

//==============================================================================
#include "../core/juce_Singleton.h"
#include "../core/juce_Random.h"
#include "../core/juce_SystemStats.h"
#include "../threads/juce_Process.h"
#include "../threads/juce_Thread.h"
#include "../threads/juce_InterProcessLock.h"
#include "../io/files/juce_FileInputStream.h"
#include "../io/files/juce_NamedPipe.h"
#include "../io/network/juce_URL.h"
#include "../core/juce_PlatformUtilities.h"
#include "../text/juce_LocalisedStrings.h"
#include "../utilities/juce_DeletedAtShutdown.h"
#include "../application/juce_Application.h"
#include "../utilities/juce_SystemClipboard.h"
#include "../events/juce_MessageManager.h"
#include "../gui/graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h"
#include "../gui/graphics/imaging/juce_ImageFileFormat.h"
#include "../gui/graphics/imaging/juce_CameraDevice.h"
#include "../gui/components/windows/juce_AlertWindow.h"
#include "../gui/components/juce_Desktop.h"
#include "../gui/components/menus/juce_MenuBarModel.h"
#include "../gui/components/special/juce_OpenGLComponent.h"
#include "../gui/components/special/juce_QuickTimeMovieComponent.h"
#include "../gui/components/mouse/juce_DragAndDropContainer.h"
#include "../gui/components/mouse/juce_MouseEvent.h"
#include "../gui/components/mouse/juce_MouseInputSource.h"
#include "../gui/components/keyboard/juce_KeyPressMappingSet.h"
#include "../gui/components/special/juce_NSViewComponent.h"
#include "../gui/components/layout/juce_ComponentMovementWatcher.h"
#include "../gui/components/special/juce_WebBrowserComponent.h"
#include "../gui/components/filebrowser/juce_FileChooser.h"
#include "../audio/audio_file_formats/juce_AudioCDBurner.h"
#include "../audio/audio_file_formats/juce_AudioCDReader.h"
#include "../audio/audio_sources/juce_AudioSource.h"
#include "../audio/dsp/juce_AudioDataConverters.h"
#include "../audio/devices/juce_AudioIODeviceType.h"
#include "../audio/devices/juce_MidiOutput.h"
#include "../audio/devices/juce_MidiInput.h"
#undef Point

//==============================================================================
#define JUCE_INCLUDED_FILE 1

// Now include the actual code files..

#include "mac/juce_mac_ObjCSuffix.h"
#include "mac/juce_mac_Strings.mm"
#include "mac/juce_mac_SystemStats.mm"
#include "mac/juce_mac_Network.mm"
#include "common/juce_posix_NamedPipe.cpp"
#include "mac/juce_mac_Threads.mm"
#include "common/juce_posix_SharedCode.h"
#include "mac/juce_mac_Files.mm"

#if JUCE_IPHONE
 #include "mac/juce_iphone_MiscUtilities.mm"
#else
 #include "mac/juce_mac_MiscUtilities.mm"
#endif

#include "mac/juce_mac_Debugging.mm"

#if ! JUCE_ONLY_BUILD_CORE_LIBRARY
 #if JUCE_IPHONE
  #include "mac/juce_mac_Fonts.mm"
  #include "mac/juce_mac_CoreGraphicsContext.mm"
  #include "mac/juce_iphone_UIViewComponentPeer.mm"
  #include "mac/juce_iphone_MessageManager.mm"
  #include "mac/juce_mac_FileChooser.mm"
  #include "mac/juce_mac_OpenGLComponent.mm"
  #include "mac/juce_mac_MouseCursor.mm"
  #include "mac/juce_mac_WebBrowserComponent.mm"
  #include "mac/juce_iphone_Audio.cpp"
  #include "mac/juce_mac_CoreMidi.cpp"
 #else
  #include "mac/juce_mac_Fonts.mm" // (must go before juce_mac_CoreGraphicsContext.mm)
  #include "mac/juce_mac_CoreGraphicsContext.mm"
  #include "mac/juce_mac_NSViewComponentPeer.mm"
  #include "mac/juce_mac_MouseCursor.mm"
  #include "mac/juce_mac_NSViewComponent.mm"
  #include "mac/juce_mac_AppleRemote.mm"
  #include "mac/juce_mac_OpenGLComponent.mm"
  #include "mac/juce_mac_MainMenu.mm"
  #include "mac/juce_mac_FileChooser.mm"
  #include "mac/juce_mac_QuickTimeMovieComponent.mm"
  #include "mac/juce_mac_AudioCDBurner.mm"
  #include "mac/juce_mac_MessageManager.mm"
  #include "mac/juce_mac_WebBrowserComponent.mm"
  #include "mac/juce_mac_CoreAudio.cpp"
  #include "mac/juce_mac_CoreMidi.cpp"
  #include "mac/juce_mac_CameraDevice.mm"
 #endif
#endif

END_JUCE_NAMESPACE
