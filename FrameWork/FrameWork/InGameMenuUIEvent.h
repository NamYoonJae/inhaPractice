#pragma once

cPopup* Setup_InGameMenu(cPopup* btn);
void InGameMenu_returnEvent_whitespace(EventType message, cPopup* popup);
void InGameMenu_returnEvent(EventType message, cPopup* btn);
void InGameMenu_OptionBtnEvent(EventType message, cPopup* btn);
void InGameMenu_ToStartEvent(EventType message, cPopup* btn);
void InGameMenu_END_Game(EventType message, cPopup* btn);
