#pragma once

cPopup* Setup_SystemWindow(cPopup* btn);
void SysWindow_ReturnEvent_whitespace(EventType message, cPopup* popup);
void SysWindow_ContinueBtnEvent(EventType message, cPopup* btn);
void SysWindow_OptionBtnEvent(EventType message, cPopup* btn);
void SysWindow_ToStartEvent(EventType message, cPopup* btn);
void SysWindow_END_Game(EventType message, cPopup* btn);
