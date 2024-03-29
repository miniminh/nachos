/**************************************************************
 *
 * userprog/ksyscallhelper.h
 *
 * Helper function for ksyscall.h
 *
 *
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALLHELPER_H__
#define __USERPROG_KSYSCALLHELPER_H__

#include "kernel.h"
#include "synchconsole.h"

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

/* maximum length of an interger (included the minus sign) */
#define MAX_NUM_LENGTH 11
/* A buffer to read and write number */
char _numberBuffer[MAX_NUM_LENGTH + 2];

char isBlank(char c) { return c == LF || c == CR || c == TAB || c == SPACE; }

int string_to_float(const char *string, float *result) {
    int sign = 1;
    int whole = 0;
    int decimal = 0;
    int decimalPlaces = 0;
    int state = 0; // 0: before decimal, 1: after decimal

    // Handle optional sign
    if (*string == '-') {
        sign = -1;
        string++;
    } else if (*string == '+') {
        string++;
    }

    // Process whole part
    while (*string >= '0' && *string <= '9') {
        whole = whole * 10 + (*string - '0');
        string++;
    }

    // Check for decimal point
    if (*string == '.') {
        string++;
        state = 1;
    }

    // Process decimal part
    while (*string >= '0' && *string <= '9') {
        decimal = decimal * 10 + (*string - '0');
        decimalPlaces++;
        string++;
    }

    // Check for extra characters
    if (*string != '\0') {
        return -1; // Error: extra characters
    }

    // Calculate final value
    float divisor = 1.0;
    for (int i = 0; i < decimalPlaces; i++) {
        divisor *= 10.0;
    }
    *result = sign * (whole + decimal / divisor);

    return 0; // Success
}

char* float_to_string(float value, int& required_size) {
    required_size = snprintf(NULL, 0, "%f", value); // Determine necessary buffer size
    char *str = new char[required_size + 1];  // Allocate space
    snprintf(str, required_size + 1, "%f", value); // Format float into string
    return str;
}


/**
 * Read and store characters in the _numberBuffer until blank
 * or end of file
 *
 * It will read at most MAX_NUM_LENGTH + 1 character
 **/
void readUntilBlank() {
    memset(_numberBuffer, 0, sizeof(_numberBuffer));
    char c = kernel->synchConsoleIn->GetChar();

    if (c == EOF) {
        DEBUG(dbgSys, "Unexpected end of file - number expected");
        return;
    }

    if (isBlank(c)) {
        DEBUG(dbgSys, "Unexpected white-space - number expected");
        return;
    }

    int n = 0;

    while (!(isBlank(c) || c == EOF)) {
        _numberBuffer[n++] = c;
        if (n > MAX_NUM_LENGTH) {
            DEBUG(dbgSys, "Number is too long");
            return;
        }
        c = kernel->synchConsoleIn->GetChar();
    }
}

/**
 * Return true of the interger equals to the
 * interger stored in the string
 **/
bool compareNumAndString(int integer, const char *s) {
    if (integer == 0) return strcmp(s, "0") == 0;

    int len = strlen(s);

    if (integer < 0 && s[0] != '-') return false;

    if (integer < 0) s++, --len, integer = -integer;

    while (integer > 0) {
        int digit = integer % 10;

        if (s[len - 1] - '0' != digit) return false;

        --len;
        integer /= 10;
    }

    return len == 0;
}

#endif /* ! __USERPROG_KSYSCALLHELPER_H__ */

