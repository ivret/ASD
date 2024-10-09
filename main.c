#include <stdio.h>
#include "form2.h"
#include <string.h>
#include <malloc.h>

void Overlay(string1 s, string1 s1, unsigned n) {
    if (s == NULL || s1 == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }

    unsigned len_s = Length(s);
    unsigned len_s1 = Length(s1);

    // Проверка на выход за пределы строки s
    if (n > len_s) {
        StrError = STR_ERR_INVALID_INDEX;
        return;
    }

    // Проверка на превышение максимальной длины
    if (n + len_s1 > s->max) {
        StrError = STR_ERR_OUT_OF_BOUNDS;
        return;
    }

    // Копируем s1 в s, начиная с позиции n
    memcpy(s->s + 2 + n, s1->s + 2, len_s1);

    // Обновляем длину s, если необходимо
    if (n + len_s1 > len_s) {
        len_s = n + len_s1;
        s->s[0] = len_s >> 8;
        s->s[1] = len_s & 0xFF;
        s->s[len_s + 2] = '\0';
    }

    StrError = STR_OK;
}
int main(void) {
        string1 str1 = (string1)malloc(sizeof(str));
        string1 str2 = (string1)malloc(sizeof(str));

        InitStr(str1, 10);
        InitStr(str2, 10);

        WriteToStr(str1, "Hello");
        WriteToStr(str2, "World");

        Overlay(str1, str2, 2); // Индекс изменен на 2
        if (StrError == STR_OK) {
            OutputStr(str1); // Выводим str1, так как она была изменена
        } else {
            printf("mistake: %d\n", StrError);
        }

        DoneStr(str1);
        DoneStr(str2);

        return 0;
    }
