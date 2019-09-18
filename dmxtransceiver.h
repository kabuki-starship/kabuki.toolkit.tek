/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /dmxreceiver.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef IGEEK_MBED_DMX_DMXTRANSCEIVER_H
#define IGEEK_MBED_DMX_DMXTRANSCEIVER_H

#include "c_dmxreceiver.h"
#include "c_dmxtransmitter.h"

namespace _ {

template <UI1 NumPorts>
class DMXTransceiver {
 public:
  /* Default constructor. */
  DMXTransceiver();

  /* Returns a reference to the DMXTransmitter. */
  DMXTransmitter& GetTransmitter();

  /* Returns a reference to the DMXReceiver. */
  DMXReceiver& GetReceiver;

 private:
  DMXTransmitter transmitter_;
  DMXReceiver receiver_;
};
}  // namespace _
#endif