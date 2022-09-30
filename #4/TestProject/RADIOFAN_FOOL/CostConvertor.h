#pragma once

class CostConvertor{
    public:
        /// Конвертирует стоимость карты в букву
        static wchar_t cost2letter(uint8_t cost){
            return L'\0';
        }

        /// Конвертирует букву в стоимость карты
        static uint8_t letter2cost(wchar_t letter){
            return 0;
        }

};