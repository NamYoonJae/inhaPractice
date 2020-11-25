#pragma once

void Setup_SystemWindow(cPopUp* btn);
void SysWindow_OptionBtnEvent(EventType message, cPopUp* btn);
void SysWindow_ExitGame(EventType message, cPopUp* btn);

cButton* Setup_BarGaugePopupBtn(cPopUp* popup, D3DXVECTOR3 position);
void Sys_TmpBarMoveEvent(EventType message, cPopUp* btn);