#pragma once


void StartGameBtnEvent(EventType message, cPopUp* btn);
void ContinueGameBtnEvent(EventType message, cPopUp* btn);
void SetupGameBtnEvent(EventType message, cPopUp* btn);
void ExitGameBtnEvent(EventType message, cPopUp* btn);

void Setup_OptionWindow();
void Option_SetBtnEvent(EventType message, cPopUp* btn);
void Option_ControlBtnEvent(EventType message, cPopUp* btn);
void Option_CameraBtnEvent(EventType message, cPopUp* btn);
void Option_AudioBtnEvent(EventType message, cPopUp* btn);
void Option_ESC_Event(EventType message, cPopUp* btn);
void Option_ReturnTitle(EventType message, cPopUp* btn);

void Setup_SystemWindow();
void SysWindow_OptionBtnEvent(EventType message, cPopUp* btn);
void SysWindow_ExitGame(EventType message, cPopUp* btn);