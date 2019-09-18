/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /pot.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#ifndef IGEEK_MBED_POT
#define IGEEK_MBED_POT 1

namespace _ {

/* A potentiometer.
  

@code
Pot<SI2> pot
@endcode
*/
class KABUKI Pot {
 public:
  /* Constructs a pot from the given ADC pin and assigned channel number. */
  Pot(ch_t channel, PinName adc_pin);

  /* Polls the pot. */
  inline void Poll(UI2 new_value, _::Expr* expr, UI2 value, UI2 min_value,
                   UI2 max_channel);

  /* Script operations. */
  const _::Operation* Star(char_t index, _::Expr* expr);

  /* Prints this object to a terminal. */
  void Print(_::Log& log);

 private:
  ch_t channel_;  //< Mixer channel number.
  AnalogIn ain_;  //< Pot ADC input.
};                //< class Pot

class PotOp : public _::Operand {
 public:
  /* Constructs a Pot Operation. */
  PotOp(Pot* object);

  /* Script operations. */
  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  Pot* object_;  //< The Pot.
};               //< class PotOp
}  // namespace _
#endif