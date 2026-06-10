#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "reciter.h"
#include "sam.h"
#include "lib.h"

int sam_debug = 0;

void setupSpeak(unsigned char pitch,unsigned char speed,unsigned char throat,unsigned char mouth) {
    SetPitch(pitch == 0 ? 64 : pitch);
    SetSpeed(speed == 0 ? 72 : speed);
    SetThroat(throat == 0 ? 128 :throat);
    SetMouth(mouth == 0 ? 128 : mouth);
}

int toUpper(int ch) {
   return ch - 32; 
}

struct AudioResult* speakText(char *input)
{
    int i;
    for(i=0; input[i] != 0; i++)
        input[i] = toUpper((int)input[i]);
    strncat(input, "[", 255);

    TextToPhonemes((unsigned char*) input);
    SetInput(input);
    struct AudioResult *resp = malloc(sizeof(struct AudioResult));
    resp -> res = SAMMain();
    resp -> buf = GetBuffer();
    resp -> buf_size = GetBufferLength()/50;
    return resp;
}

