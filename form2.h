//
// Created by Иван on 07.10.2024.
//

#ifndef LAB2_FORM2_H
#define LAB2_FORM2_H
// Определение исключительных ситуаций
#define STR_OK 0
#define STR_ERR_NULL_POINTER -1
#define STR_ERR_INVALID_INDEX -2
#define STR_ERR_OUT_OF_BOUNDS -3
#define STR_ERR_MEMORY_ALLOCATION -4

typedef struct str
{
    char* s; // Признак конца строки - символ '\0'
    unsigned max; /* Максимальное количество символов в строке, определяющееся при инициализации */
}str;
typedef str *string1;
void InitStr(string1 st, unsigned n);
void WriteToStr(string1 st, char *s);
void WriteFromStr(char *s, string1 st);
void InputStr(string1 st);
void OutputStr(string1 st);
int Comp(string1 s1, string1 s2);
void Delete(string1 s, unsigned Index, unsigned Count);
void Insert(string1 Subs, string1 s, unsigned Index);
void Concat(string1 s1, string1 s2, string1 srez);
void Copy(string1 s, unsigned Index, unsigned Count,  	string1 Subs);
unsigned Length(string1 s);
unsigned Pos(string1 SubS, string1 s);
void DoneStr(string1 s);

extern int StrError;

#endif //LAB2_FORM2_H
