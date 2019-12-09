#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define TEST_COUNT 23
#define FLOAT_EPSILON 0.00001f

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned int quad;

int BinaryToOctalTest (void);
int OctalToBinaryTest (void);

int BinaryToDecimalTest (void);
int DecimalToBinaryTest (void);

int BinaryToHexadecimalTest (void);
int HexadecimalToBinaryTest (void);

int OctalToDecimalTest (void);
int DecimalToOctalTest (void);

int OctalToHexadecimalTest (void);
int HexadecimalToOctalTest (void);

int DecimalToHexadecimalTest (void);
int HexadecimalToDecimalTest (void);

int BinaryAdditionTest (void);
int BinarySubtractionTest (void);

int ToSignedMagnitudeTest (void);
int FromSignedMagnitudeTest (void);

int ToOnesComplementTest (void);
int FromOnesComplementTest (void);

int ToTwosComplementTest (void);
int FromTwosComplementTest (void);

int TwosComplementAdditionTest (void);

int DecimalToIEEEByteTest (void);
int IEEEByteToDecimalTest (void);

int (*const tests[TEST_COUNT])(void) = {
    BinaryToOctalTest,
    OctalToBinaryTest,
    BinaryToDecimalTest,
    DecimalToBinaryTest,
    BinaryToHexadecimalTest,
    HexadecimalToBinaryTest,
    OctalToDecimalTest,
    DecimalToOctalTest,
    OctalToHexadecimalTest,
    HexadecimalToOctalTest,
    DecimalToHexadecimalTest,
    HexadecimalToDecimalTest,
    BinaryAdditionTest,
    BinarySubtractionTest,
    ToSignedMagnitudeTest,
    FromSignedMagnitudeTest,
    ToOnesComplementTest,
    FromOnesComplementTest,
    ToTwosComplementTest,
    FromTwosComplementTest,
    TwosComplementAdditionTest,
    DecimalToIEEEByteTest,
    IEEEByteToDecimalTest
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
    return (byte)(rand() % 0x100);
}

sbyte RandomSignedByte (void) {
    return (sbyte)(0x80 + (rand() % 0x80));
}

float RandomFloat (void) {
    return (float)rand() / RAND_MAX;
}

byte RandomByteBetween (byte _min, byte _max) {
    return _min + (byte)(RandomFloat() * (_max - _min));
}

float RandomFloatBetween (float _min, float _max) {
    return _min + RandomFloat() * (_max - _min);
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

int OctalToDecimalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert octal %o into decimal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%d",question)) {
        printf("Correct! The answer is %d.\n",question);
    } else {
        printf("Wrong! The answer is %d.\n",question);
    }

    return 0;

}

int DecimalToOctalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert decimal %d into octal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%o",question)) {
        printf("Correct! The answer is %o.\n",question);
    } else {
        printf("Wrong! The answer is %o.\n",question);
    }

    return 0;

}

int OctalToHexadecimalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert octal %o into hexadecimal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%x",question)) {
        printf("Correct! The answer is %X.\n",question);
    } else {
        printf("Wrong! The answer is %X.\n",question);
    }

    return 0;

}

int HexadecimalToOctalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert hexadecimal %X into octal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%o",question)) {
        printf("Correct! The answer is %o.\n",question);
    } else {
        printf("Wrong! The answer is %o.\n",question);
    }

    return 0;

}

int DecimalToHexadecimalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert decimal %d into hexadecimal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%x",question)) {
        printf("Correct! The answer is %X.\n",question);
    } else {
        printf("Wrong! The answer is %X.\n",question);
    }

    return 0;

}

int HexadecimalToDecimalTest (void) {
    
    /* declaring variables */
    byte question = RandomByte();

    /* print question */
    printf("Convert hexadecimal %X into decimal form: \n",question);

    /* scanf answer */
    if (ScanfByteAnswer("%d",question)) {
        printf("Correct! The answer is %d.\n",question);
    } else {
        printf("Wrong! The answer is %d.\n",question);
    }

    return 0;

}

int BinaryAdditionTest (void) {

    byte total = RandomByteBetween(150,255);
    byte byte1 = (byte)(total * RandomFloatBetween(0.25f,0.75f));
    byte byte2 = total - byte1;

    /* print question */
    printf("Unsigned binary addition: ");
    PrintBinaryByte(byte1);
    printf(" + ");
    PrintBinaryByte(byte2);
    printf(" =\n");

    /* scanf answer */
    if (ScanfBinaryByteAnswer(total)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(total);
    printf(".\n");

    return 0;

}

int BinarySubtractionTest (void) {

    byte total = RandomByteBetween(150,255);
    byte byte1 = (byte)(total * RandomFloatBetween(0.25f,0.75f));
    byte byte2 = total - byte1;

    /* print question */
    printf("Unsigned binary subtraction: ");
    PrintBinaryByte(total);
    printf(" - ");
    PrintBinaryByte(byte1);
    printf(" =\n");

    /* scanf answer */
    if (ScanfBinaryByteAnswer(byte2)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(byte2);
    printf(".\n");

    return 0;

}

int ScanfSByteAnswer (char *const format, sbyte _check) {

    /* octal and hexadecimal requires 4 bytes */
    int answer = 0;
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

byte EncodeSignedMagnitude (sbyte _sbyte) {

    byte result = (byte)(_sbyte < 0 ? -_sbyte : _sbyte);
    if (_sbyte < 0) result |= 0x80;
    return result;

}

int ToSignedMagnitudeTest (void) {

    /* declaring variables */
    sbyte question = RandomSignedByte();
    byte answer = EncodeSignedMagnitude(question);

    /* print question */
    printf("Convert decimal %d into signed magnitude 8-bit binary: \n",
        question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(answer)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(answer);
    printf(".\n");

    return 0;

}

int FromSignedMagnitudeTest (void) {

    /* declaring variables */
    sbyte answer = RandomSignedByte();
    byte question = EncodeSignedMagnitude(answer);

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" from signed magnitude to decimal: \n");

    /* scanf answer */
    if (ScanfSByteAnswer("%d",answer)) {
        printf("Correct! The answer is %d.\n",answer);
    } else {
        printf("Wrong! The answer is %d.\n",answer);
    }

    return 0;

}

byte EncodeOnesComplement (sbyte _sbyte) {
    
    byte result = (byte)(_sbyte < 0 ? -_sbyte : _sbyte);
    if (_sbyte < 0) result ^= 0xFF;
    return result;

}

int ToOnesComplementTest (void) {

    /* declaring variables */
    sbyte question = RandomSignedByte();
    byte answer = EncodeOnesComplement(question);

    /* print question */
    printf("Convert decimal %d into one\'s complement 8-bit binary: \n",
        question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(answer)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(answer);
    printf(".\n");

    return 0;

}

int FromOnesComplementTest (void) {

    /* declaring variables */
    sbyte answer = RandomSignedByte();
    byte question = EncodeOnesComplement(answer);

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" from one\'s complement to decimal: \n");

    /* scanf answer */
    if (ScanfSByteAnswer("%d",answer)) {
        printf("Correct! The answer is %d.\n",answer);
    } else {
        printf("Wrong! The answer is %d.\n",answer);
    }

    return 0;

}

byte EncodeTwosComplement (sbyte _sbyte) {
    
    byte result = (byte)(_sbyte < 0 ? -_sbyte : _sbyte);
    if (_sbyte < 0) result = (result ^ 0xFF) + 1;
    return result;

}

int ToTwosComplementTest (void) {

    /* declaring variables */
    sbyte question = RandomSignedByte();
    byte answer = EncodeTwosComplement(question);

    /* print question */
    printf("Convert decimal %d into two\'s complement 8-bit binary: \n",
        question);

    /* scanf answer */
    if (ScanfBinaryByteAnswer(answer)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(answer);
    printf(".\n");

    return 0;

}

int FromTwosComplementTest (void) {

    /* declaring variables */
    sbyte answer = RandomSignedByte();
    byte question = EncodeTwosComplement(answer);

    /* print question */
    printf("Convert ");
    PrintBinaryByte(question);
    printf(" from two\'s complement to decimal: \n");

    /* scanf answer */
    if (ScanfSByteAnswer("%d",answer)) {
        printf("Correct! The answer is %d.\n",answer);
    } else {
        printf("Wrong! The answer is %d.\n",answer);
    }

    return 0;

}

int TwosComplementAdditionTest (void) {

    /* declaring variables */
    sbyte sbyte1 = RandomSignedByte();
    sbyte min = (sbyte1 - 128 < -128) ? -128 : (sbyte1 - 128);
    sbyte max = (sbyte1 + 127 > 127) ? 127 : (sbyte1 + 127);
    sbyte total = min + (sbyte)(RandomFloat() * (max - min) * 0.9f);
    sbyte sbyte2 = total - sbyte1;

    byte totalEncoded = EncodeTwosComplement(total);
    
    /* print question */
    printf("Two\'s complement binary addition: ");
    PrintBinaryByte(EncodeTwosComplement(sbyte1));
    printf(" + ");
    PrintBinaryByte(EncodeTwosComplement(sbyte2));
    printf(" =\n");

    /* scanf answer */
    if (ScanfBinaryByteAnswer(totalEncoded)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryByte(totalEncoded);
    printf(".\n");

    return 0;

}

quad RandomIEEEQuad (int _exponent, int _mantissa) {

    /* randomize mantissa */
    quad result = rand() % (1 << _mantissa);

    /* randomize exponent but don't NaN, INF or subnormal */
    quad exp = 1 + rand() % ((1 << _exponent) - 2);
    result |= exp << _mantissa;

    /* shift result all the way back */
    result <<= 31 - _exponent - _mantissa;

    /* give a random sign */
    if (RandomFloat() > 0.5f) result |= 0x80000000;

    /* return result */
    return result;

}

float QuadToFloat (quad _quad, int _exponent, int _mantissa) {

    float result = 1.0f, sign = 10.0f;
    byte i;
    int scale = 0;

    /* compute exponent */
    for (i = 0; i < _exponent; ++i) {
        quad target = _quad >> (30 - i);
        if (target % 2) {
            scale += 1 << (_exponent - 1 - i);
        }
    }

    /* apply bias */
    scale -= (1 << (_exponent - 1)) - 1;
    if (scale < 0) {
        scale = -scale;
        sign = 0.1f;
    }

    /* compute mantissa */
    for (i = 0; i < _mantissa; ++i) {
        quad target = _quad >> (30 - _exponent - i);
        if (target % 2) {
            result += 1.0f / (2 << i);
        }
    }

    /* apply scale */
    for (i = 0; i < scale; ++i) {
        result *= sign;
    }

    /* apply sign */
    if ((_quad >> 31) % 2) result = -result;

    return result;

}

int ComputePrecision (quad _quad, int _exponent, int _mantissa) {

    int i, scale = 0;

    /* compute exponent */
    for (i = 0; i < _exponent; ++i) {
        quad target = _quad >> (30 - i);
        if (target % 2) {
            scale += 1 << (_exponent - 1 - i);
        }
    }

    /* apply bias */
    scale -= (1 << (_exponent - 1)) - 1;

    /* find least significant mantissa */
    for (i = _mantissa - 1; i >= 0; --i) {
        quad target = _quad >> (30 - _exponent - i);
        if (target % 2) {
            scale -= i + 1;
            break;
        }
    }

    return scale < 0 ? -scale : 0;

}

void PrintBinaryQuad (quad _quad, int _length) {

    /* print out byte in binary form */
    byte i = 0;
    while (i < _length) {
        quad target = _quad >> (31 - i++);
        printf((target % 2) ? "1" : "0");
    }

}

int ScanfFloatAnswer (float _check) {

    /* declare variables */
    float answer = 0;
    int sr;
    
    /* do the scanf */
    printf("> ");
    sr = scanf("%f",&answer);
    ClearScanfBuffer();
    
    /* return if correct answer */
    if (sr != 1 || fabsf(answer - _check) > FLOAT_EPSILON) {
        return 0;
    }
    return 1;

}

int BinaryToQuad (const char *_binary, int _length, quad *const _result) {

    int i = _length;
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

    /* extra shifting */
    *_result <<= 33 - (_length - i);

    return 1;

}

int ScanfBinaryQuadAnswer (quad _check, int _length) {

    /* octal and hexadecimal requires 4 bytes */
    char input[33];
    int sr;
    quad answer;
    
    /* do the scanf */
    printf("> ");
    sr = scanf("%32s",input);
    ClearScanfBuffer();
    if (sr != 1) return 0;

    /* convert to answer */
    sr = BinaryToQuad(input,_length,&answer);

    /* return if correct answer */
    if (sr != 1 || answer != _check) {
        return 0;
    }
    return 1;

}

int DecimalToIEEEByteTest (void) {

    /* declaring variables */
    quad question = RandomIEEEQuad(4,4);
    float answer = QuadToFloat(question,4,4);
    int precision = ComputePrecision(question,4,4);

    /* print question */
    printf("Assume IEEE754 standard, with 4-bit exponent and 4-bit mantissa.\n"
        "Convert ");
    PrintBinaryQuad(question,9);
    printf(" into decimal form: \n");

    /* scanf answer */
    if (ScanfFloatAnswer(answer)) {
        printf("Correct! The answer is %.*f.\n",precision,answer);
    } else {
        printf("Wrong! The answer is %.*f.\n",precision,answer);
    }

    return 0;
    
}

int IEEEByteToDecimalTest (void) {

    /* declaring variables */
    quad answer = RandomIEEEQuad(4,4);
    float question = QuadToFloat(answer,4,4);
    int precision = ComputePrecision(answer,4,4);

    /* print question */
    printf("Assume IEEE754 standard, with 4-bit exponent and 4-bit mantissa.\n"
        "Convert decimal %.*f into 9-bit binary form: \n",precision,question);

    /* scanf answer */
    if (ScanfBinaryQuadAnswer(answer,9)) {
        printf("Correct! The answer is ");
    } else {
        printf("Wrong! The answer is ");
    }
    PrintBinaryQuad(answer,9);
    printf(".\n");

    return 0;

}
