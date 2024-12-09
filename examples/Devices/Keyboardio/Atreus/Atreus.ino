/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  // Switch IME (ctrl+space).
  MACRO_IME,
};

#define Key_Plus        LSHIFT(Key_Equals)
#define Key_Underscore  LSHIFT(Key_Minus)
#define Key_DoubleQuote LSHIFT(Key_Quote)
#define Key_LeftCurly   LSHIFT(Key_LeftBracket)
#define Key_RightCurly  LSHIFT(Key_RightBracket)

#define Key_Mute        Consumer_Mute
#define Key_VolDown     Consumer_VolumeDecrement
#define Key_VolUp       Consumer_VolumeIncrement
#define Key_LightDown   Consumer_DisplayBrightnessDecrement
#define Key_LightUp     Consumer_DisplayBrightnessIncrement

enum {
  QWERTY,
  SYMS,
  MISC,
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
     Key_Q           ,Key_W           ,Key_E           ,Key_R            ,Key_T
    ,Key_A           ,Key_S           ,Key_D           ,Key_F            ,Key_G
    ,Key_Z           ,Key_X           ,Key_C           ,Key_V            ,Key_B           ,Key_Esc
    ,Key_LeftShift   ,MO(MISC)        ,Key_LeftAlt     ,Key_LeftShift    ,Key_Space       ,Key_LeftControl

                     ,Key_Y           ,Key_U           ,Key_I            ,Key_O           ,Key_P
                     ,Key_H           ,Key_J           ,Key_K            ,Key_L           ,Key_Semicolon
    ,Key_Backspace   ,Key_N           ,Key_M           ,Key_Comma        ,Key_Period      ,Key_Slash
    ,Key_Tab         ,Key_Enter       ,MO(SYMS)        ,M(MACRO_IME)     ,Key_Minus       ,Key_Quote
  ),

  [SYMS] = KEYMAP_STACKED
  (
     Key_1           ,Key_2           ,Key_3           ,Key_4            ,Key_5
    ,Key_Backtick    ,Key_Backslash   ,Key_Equals      ,Key_Minus        ,Key_Quote
    ,___             ,___             ,Key_Plus        ,Key_Underscore   ,Key_DoubleQuote ,Key_Esc
    ,Key_LeftShift   ,___             ,Key_LeftAlt     ,Key_LeftShift    ,Key_Space       ,Key_LeftControl

                     ,Key_6           ,Key_7           ,Key_8            ,Key_9           ,Key_0
                     ,___             ,Key_LeftParen   ,Key_RightParen   ,Key_LeftCurly   ,Key_RightCurly
    ,Key_Backspace   ,___             ,Key_LeftBracket ,Key_RightBracket ,___             ,___
    ,Key_Tab         ,Key_Enter       ,___             ,___              ,___             ,___
  ),

  [MISC] = KEYMAP_STACKED
  (
     ___             ,___             ,___             ,___              ,___
    ,___             ,___             ,___             ,___              ,___
    ,___             ,___             ,___             ,___              ,___             ,___
    ,___             ,___             ,___             ,___              ,___             ,___

                     ,Key_Mute        ,Key_VolDown     ,Key_VolUp        ,Key_LightDown   ,Key_LightUp
                     ,Key_LeftArrow   ,Key_DownArrow   ,Key_UpArrow      ,Key_RightArrow  ,___
    ,Key_PrintScreen ,___             ,___             ,___              ,___             ,___
    ,___             ,___             ,___             ,___              ,___             ,___
  ),
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig  //,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_QWERTY:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    case MACRO_IME:
      return MACRO(D(LeftControl), D(Space), U(Space));
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();
}

void loop() {
  Kaleidoscope.loop();
}
