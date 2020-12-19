#pragma once

cButton* Setup_CheckBtn(cPopup* popup, D3DXVECTOR3 position, function<void(EventType&, cPopup*)> EventFuction);
void CheckBtnEvent(EventType message, cPopup* btn);

cButton* Setup_BarSliderPopupBtn(cPopup* popup, D3DXVECTOR3 position, function<void(EventType&, cPopup*)> EventFuction);
void BarSliderMoveEvent(EventType message, cPopup* btn);
void BarSliderMoveEvent2(EventType message, cPopup* btn);

void BGM_Setting_Event(EventType message, cPopup* btn);
void SFX_Setting_Event(EventType message, cPopup* btn);
void MouseSensitivity_Total_Event(EventType message, cPopup* btn);
void MouseSensitivity_Normal_Event(EventType message, cPopup* btn);
void MouseSensitivity_Special_Event(EventType message, cPopup* btn);


cButton* Setup_BarGaugePopupBtn_Legacy(cPopup* popup, D3DXVECTOR3 position);
void GaugeBarMoveEvent_Legacy(EventType message, cPopup* btn);