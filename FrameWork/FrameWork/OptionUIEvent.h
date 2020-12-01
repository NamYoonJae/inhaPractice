#pragma once

cPopup* Setup_OptionWindow(cPopup* btn);
void Option_ReturnEvent(EventType message, cPopup* btn);





cPopup* Setup_OptionWindow_Legacy(cPopup* btn);
void Option_SetBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_ControlBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_CameraBtnEvent_Legacy(EventType message, cPopup* btn);
void Option_AudioBtnEvent_Legacy(EventType message, cPopup* btn);