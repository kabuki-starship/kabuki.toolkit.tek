/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /kotary_bank.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "rotaryknobbank.h"

namespace _ {

RotaryKnobBank::RotaryKnobBank(ch_t num_knobs, ch_t start_channel,
                               ch_t num_banks, const IUA* rows,
                               const IUA* columns)
    : channel_count_(num_knobs),
      start_channel_(start_channel),
      num_banks_(num_banks),
      num_buttons_(0),
      current_bank_(0),
      current_channel_(start_channel),
      wiring_config_(0),
      rows_(rows),
      columns_(columns),
      buttons_(0),
      lights_(0) {}

ch_t RotaryKnobBank::GetNumChannels() { return channel_count_ * num_banks_; }

void RotaryKnobBank::SwitchBank(ch_t value) {
  if (value >= num_banks_) return;

  current_bank_ = value;
  current_channel_ = start_channel_ + channel_count_ * value;
}

void RotaryKnobBank::CycleBank() {
  current_channel_ += channel_count_;
  if (current_channel_ > start_channel_ + channel_count_ * num_banks_)
    current_channel_ = start_channel_;
}

void RotaryKnobBank::Update(ISB* channels, ISB* min_values, ISB* max_values,
                            IUA* spi_out_bytes, ISB row, int8_t count) {
  // for  (IUB i = 0; i < count; ++i)
  //   UpdateChannel  (i, channels, minValues, maxValues, spiOutBytes, row,
  //                   count, wiring_config_);
}

void RotaryKnobBank::UpdateChannel(IUB index, ISB* channels, ISB* min_values,
                                   ISB* max_values, IUA* spi_out_bytes, IUB row,
                                   IUA count) {
  if (channels == nullptr) return;
  if (min_values == nullptr) return;
  if (max_values == nullptr) return;
  // When we enter this algorithm, we will be stepping through the rows 1-8.

  static const int8_t kLedIndexToRowMap[3][16] = {
      {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, -1},
      //< LEDRingConfig::kNoButtons
      {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, 7},
      //< LEDRingConfig::ButtonsOnTopRows
      {0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0}};
  //< LEDRingConfig::ButtonsOnBottomRows

  ISB value = channels[index], min_value = min_values[index],
      max_value = max_values[index],
      ring_index = (value - min_value) % ((max_value - min_value) / 15),
      row_index = kLedIndexToRowMap[wiring_config_][ring_index];

  if (row != row_index) return;

  // IUB columnNumber =  (index - current_channel_) >> 2;
  //< >> 2 to divide by 2

  // IUA columnBit = columns[columnNumber],
  //    mask = 1 <<  (columnBit & BitNumberMask);
}

const Operation* RotaryKnobBank::Star(char_t index, Expr* expr) {
  static const Operation This = {"RotaryEncoderBank", NumOperations(0),
                                 FirstOperation('a'), "tek", 0};

  switch (index) {
    case '?':
      return &This;
  }

  return nullptr;
}

}  // namespace _
