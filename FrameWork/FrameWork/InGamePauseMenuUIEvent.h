#pragma once

cPopup* Setup_InGamePauseMenu(cPopup* btn);
void InGamePauseMenu_returnEvent_whitespace(EventType message, cPopup* popup);
void InGamePauseMenu_returnEvent(EventType message, cPopup* btn);
void InGamePauseMenu_OptionBtnEvent(EventType message, cPopup* btn);
void InGamePauseMenu_ToStartEvent(EventType message, cPopup* btn);
void InGamePauseMenu_END_Game(EventType message, cPopup* btn);
