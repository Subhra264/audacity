/*!********************************************************************

  Audacity: A Digital Audio Editor

  @file AudioUnitEffectsModule.h

  Dominic Mazzoni
  Leland Lucius

  Paul Licameli split from AudioUnitEffect.h

**********************************************************************/
#ifndef AUDACITY_AUDIOUNIT_EFFECTS_MODULE_H
#define AUDACITY_AUDIOUNIT_EFFECTS_MODULE_H

#if USE_AUDIO_UNITS

#include <AudioToolbox/AudioUnitUtilities.h>
#include "PluginProvider.h"

///////////////////////////////////////////////////////////////////////////////
//
// AudioUnitEffectsModule
//
///////////////////////////////////////////////////////////////////////////////

class AudioUnitEffectsModule final : public PluginProvider
{
public:
   AudioUnitEffectsModule();
   virtual ~AudioUnitEffectsModule();

   // ComponentInterface implementation

   PluginPath GetPath() const override;
   ComponentInterfaceSymbol GetSymbol() const override;
   VendorSymbol GetVendor() const override;
   wxString GetVersion() const override;
   TranslatableString GetDescription() const override;

   // PluginProvider implementation

   bool Initialize() override;
   void Terminate() override;
   EffectFamilySymbol GetOptionalFamilySymbol() override;

   const FileExtensions &GetFileExtensions() override;
   FilePath InstallPath() override { return {}; }

   void AutoRegisterPlugins(PluginManagerInterface & pm) override;
   PluginPaths FindModulePaths(PluginManagerInterface & pm) override;
   unsigned DiscoverPluginsAtPath(
      const PluginPath & path, TranslatableString &errMsg,
      const RegistrationCallback &callback)
         override;

   bool IsPluginValid(const PluginPath & path, bool bFast) override;

   std::unique_ptr<ComponentInterface>
      LoadPlugin(const PluginPath & path) override;

   // AudioUnitEffectModule implementation

   void LoadAudioUnitsOfType(OSType inAUType, PluginPaths & effects);
   AudioComponent FindAudioUnit(const PluginPath & path, wxString & name);

   wxString FromOSType(OSType type);
   OSType ToOSType(const wxString & type);
};

#endif

#endif
