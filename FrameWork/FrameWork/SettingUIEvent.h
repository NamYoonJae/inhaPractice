#pragma once

cPopup* Setup_Setting_popup(cPopup* btn);
void Setting_popup_ReturnEvent_whitespace(EventType message, cPopup* popup);
void Setting_popup_ReturnEvent(EventType message, cPopup* Popup);




cPopup* Setup_OptionWindow_Legacy(cPopup* btn);
void Option_SetBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_ControlBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_CameraBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_AudioBtnEvent_Legacy(EventType message, cPopup* btn);