#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEST_COUNT 6

typedef unsigned char byte;

int BinaryToOctalTest (void);
int OctalToBinaryTest (void);

int BinaryToDecimalTest (void);
int DecimalToBinaryTest (void);

int BinaryToHexadecimalTest (void);
int HexadecimalToBinaryTest (void);

int (*const tests[TEST_COUNT])(void) = {
    BinaryToOctalTest,
    OctalToBinaryTest,
    BinaryToDecimalTest,
    DecimalToBinaryTest,
    BinaryToHexadecimalTest,
    HexadecimalToBinaryTest
};

int main (void) {

    /* declaring variables */
    int studLevel = 0;

    /* set a seed for rand() */
    srand((unsigned int)time(NULL));

    /* print some shit */
    printf("\n<< CS100 CONVERSION PRACTICE >>\n");

    /* temporary 'game' loop */
    while (studLevel < TEST_COUNT) {

        /* print stud level */
        printf("\nstud level: %d\n",studLevel);

        /* run test */
        tests[studLevel]();

        /* increase stud level */
        ++studLevel;
    }

    /* k bye */
    printf("\nok break\n\n");
    return 0;

}

byte RandomByte (void) {

    /* get a random byte (8-bit) */
    return (byte)(rand() % 0x100);

}

int BinaryToByte (const char *_binary, byte *const _result) {

    byte i = 8;
    *_result = 0;

    while (i-- && *_binary) {
        char c = *(_binary++);
        
        /* if not binary then go away */
        if (c != '1' && c != '0') {
            return 0;
        }

        /* bit-shift magic */
        *_result <<= 1;
        if (c == '1') ++(*_result);

    }
    
    /* check if size is correct (or not) */
    /* return (i == 0); */
    return 1;

}

void PrintBinaryByte (byte _byte) {

    /* print out byte in binary form */
    byte i = 8;
    while (i--) {
        byte target = _byte >> i;
        printf((target % 2) ? "1" : "0");
    }

}

void ClearScanfBuffer (void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ScanfByteAnswer (char *const format, byte _check) {

    /* octal and hexadecimal requires 4 bytes */
    unsigned int answer = 0;
    int sr;
    
    /* do the scanf */
    printf("> ");
    sr = scanf(format,&answer);
    ClearScanfBuffer();
    
    /* return if correct answer */
    if (sr != 1 || answer != _check) {
        return 0;
    }
    return 1;

}

int ScanfBinaryByteAnswer (byte _check) {

    /* octal and hexadecimal requires 4 bytes */
    char input[9];
    int sr;
    byte answer;
    
    /* do the scanf */
    printf("> ");
    sr = scanf("%8s",input);
    ClearScanfBuffer();
    if (sr != 1) return 0;

    /* convert to answer */
    sr = BinaryToByte(input,&answer);
    
    /* return if correct answer */
    if (sr != 1 || answer != _check) {
        return 0;
    }
    return 1;

}

int BinaryToOctalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" into octal form: \n");

    /* scanf answer */
    if (ScanfByteAnswer("%o",question)) {
        printf("Correct! The answer is %o.\n",question);
    } else {
        printf("Wrong! The answer is %o.\n",question);
    }

    return 0;

}

int OctalToBinaryTest (void) {

    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert octal %o into 8-bit binary form: \n",question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(question)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(question);
    printf(".\n");

    return 0;

}

int BinaryToDecimalTest (void) {

    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" into decimal form: \n");

    /* scanf answer */
    if (ScanfByteAnswer("%d",question)) {
        printf("Correct! The answer is %d.\n",question);
    } else {
        printf("Wrong! The answer is %d.\n",question);
    }

    return 0;

}

int DecimalToBinaryTest (void) {

    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert decimal %d into 8-bit binary form: \n",question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(question)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(question);
    printf(".\n");

    return 0;

}

int BinaryToHexadecimalTest (void) {

    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" into hexadecimal form: \n");

    /* scanf answer */
    if (ScanfByteAnswer("%x",question)) {
        printf("Correct! The answer is %X.\n",question);
    } else {
        printf("Wrong! The answer is %X.\n",question);
    }

    return 0;

}

int HexadecimalToBinaryTest (void) {

    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert hexadecimal %X into 8-bit binary form: \n",question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(question)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(question);
    printf(".\n");

    return 0;

}