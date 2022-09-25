#include "sav_button.h"

#define CONTACT_BOUNCE 40
#define KEYS_TIME_HOLD 1000

/* uint8_t pin,uint16_t tm1, uint16_t tm2,uint16_t tm3, uint16_t tm4
 * tm1 - таймаут дребезга контактов. По умолчанию 50мс
 * tm2 - время длинного нажатия клавиши. По умолчанию 2000мс
 * tm3 - врямы перевода кнопки в генерацию серии нажатий. По умолсанию отключено
 * tm4 - время между кликами в серии. По умолчанию 500 мс. Если tm3 = 0 то не работает */

SButton button1(5,CONTACT_BOUNCE,KEYS_TIME_HOLD,0,1000);
SButton button2(3,CONTACT_BOUNCE,KEYS_TIME_HOLD,0,1000);

