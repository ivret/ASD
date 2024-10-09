// Created by Иван on 07.10.2024.
#include "form2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int StrError;
// Инициализация строки
void InitStr(string1 st, unsigned n) {
    if (st == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    st->s = (char *)malloc((n + 3) * sizeof(char)); // +2 для длины и +1 для '\0'
    if (st->s == NULL) {
        StrError = STR_ERR_MEMORY_ALLOCATION;
        return;
    }
    st->max = n;
    st->s[0] = st->s[1] = 0; // Инициализация длины строки
    StrError = STR_OK;
}

void WriteToStr(string1 st, char *s) {
    if (st == NULL || s == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len = strlen(s);
    if (len > st->max) {
        StrError = STR_ERR_OUT_OF_BOUNDS;
        return;
    }
    st->s[0] = len >> 8;
    st->s[1] = len & 0xFF;
    strncpy(st->s + 2, s, len);
    st->s[len + 2] = '\0';
    StrError = STR_OK;
}


void WriteFromStr(char *s, string1 st){
    if(st == NULL || s == NULL){
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len = (st->s[0] <<8) |(st->s[1]);
    strncpy(s,st->s+2,len);
    s[len] = '\0';
    StrError = STR_OK;
}

void InputStr(string1 st){
    if(st == NULL){
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    char buffer[st->max + 1];
    if (fgets(buffer, st->max + 1, stdin) == NULL) {
        StrError = STR_ERR_OUT_OF_BOUNDS;
        return;
    }
    buffer[strcspn(buffer,"\n")] = '\0';
    WriteToStr(st, buffer);
}

void OutputStr(string1 st) {
    if (st == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len = (st->s[0] << 8) | st->s[1];
    printf("%.*s\n", len, st->s + 2);
    StrError = STR_OK;
}

int Comp(string1 s1, string1 s2){
    if(s1 == NULL || s2 == NULL){
        StrError = STR_ERR_NULL_POINTER;
        return 0;
    }
    unsigned len1 = (s1->s[0]<<8) |(s1->s[1]);
    unsigned len2 = (s2->s[0]<<8) |(s2->s[1]);
    int cmp = strncmp(s1->s+2,s2->s+2,(len1<len2)?len1:len2);
    if(cmp == 0){
        return len1 - len2;
    }
    return cmp;
}

void Delete(string1 s, unsigned Index, unsigned Count){
    if (s == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len = (s->s[0] << 8) | s->s[1];
    if (Index >= len || Index + Count > len) {
        StrError = STR_ERR_INVALID_INDEX;
        return;
    }
    memmove(s->s + 2 + Index, s->s + 2 + Index + Count, len - Index - Count);
    len -= Count;
    s->s[0] = len >> 8;
    s->s[1] = len & 0xFF;
    s->s[len + 2] = '\0';
    StrError = STR_OK;
}

void Insert(string1 Subs, string1 s, unsigned Index){
    if (Subs == NULL || s == NULL){
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len_s = (s->s[0]<<8)|(s->s[1]);
    unsigned len_subs = (Subs->s[0]<<8)|(Subs->s[1]);
    if(Index > len_s || len_s + len_subs > s->max){
        StrError = STR_ERR_INVALID_INDEX;
        return;
    }
    memmove(s->s + 2 + Index + len_subs, s->s + 2 + Index, len_s - Index+2);
    memcpy(s->s + 2 + Index, Subs->s + 2, len_subs);
    len_s += len_subs;
    s->s[0] = len_s >> 8;
    s->s[1] = len_s & 0xFF;
    s->s[len_s + 2] = '\0';
    StrError = STR_OK;
}

void Concat(string1 s1, string1 s2, string1 srez) {
    if (s1 == NULL || s2 == NULL || srez == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    unsigned len1 = (s1->s[0] << 8) | s1->s[1];
    unsigned len2 = (s2->s[0] << 8) | s2->s[1];
    if (len1 + len2 > srez->max) {
        StrError = STR_ERR_OUT_OF_BOUNDS;
        return;
    }
    memcpy(srez->s + 2, s1->s + 2, len1);
    memcpy(srez->s + 2 + len1, s2->s + 2, len2);
    srez->s[0] = (len1 + len2) >> 8;
    srez->s[1] = (len1 + len2) & 0xFF;
    srez->s[len1 + len2 + 2] = '\0';
    StrError = STR_OK;
}

void Copy(string1 s, unsigned Index, unsigned Count, string1 Subs){
    if(s == NULL || Subs == NULL){
        StrError = STR_ERR_NULL_POINTER;
    }
    unsigned len = (s->s[0]<<8) | s->s[1];
    if(Index > len || Index + Count > len || Subs->max < Count){
        StrError = STR_ERR_INVALID_INDEX;
        return;
    }
    memcpy(Subs->s + 2, s->s + 2 + Index,Count);
    Subs->s[0] = Count >> 8;
    Subs->s[1] = Count & 0xFF;
    Subs->s[Count + 2] = '\0';
    StrError = STR_OK;

}

unsigned Length(string1 s) {
    if (s == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return 0;
    }
    unsigned len = (s->s[0] << 8) | s->s[1];
    StrError = STR_OK;
    return len;
}

unsigned Pos(string1 SubS, string1 s) {
    if (s == NULL || SubS == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return 0;
    }
    unsigned len = (s->s[0] << 8) | s->s[1];
    unsigned sublen = (SubS->s[0] << 8) | SubS->s[1];
    if (sublen > len) {
        StrError = STR_ERR_INVALID_INDEX;
        return 0;
    }
    char *pos = strstr(s->s + 2, SubS->s + 2);
    if (pos == NULL) {
        StrError = STR_OK;
        return 0;
    }
    unsigned index = pos - (s->s + 2);
    StrError = STR_OK;
    return index + 1;
}

void DoneStr(string1 s) {
    if (s == NULL) {
        StrError = STR_ERR_NULL_POINTER;
        return;
    }
    free(s->s);
    s->s = NULL;
    s->max = 0;
    StrError = STR_OK;
}




