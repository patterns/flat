/* pico2wave.c

 * Copyright (C) 2009 Mathieu Parent <math.parent@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *   Convert text to .wav using svox text-to-speech system.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <picoapi.h>
#include <picoapid.h>
#include <picoos.h>


/* adaptation layer defines */
#define PICO_MEM_SIZE       2500000
#define DummyLen 100000000

/* string constants */
#define MAX_OUTBUF_SIZE     128
#ifdef picolangdir
const char * PICO_LINGWARE_PATH             = picolangdir "/";
#else
const char * PICO_LINGWARE_PATH             = "./lang/";
#endif
const char * PICO_VOICE_NAME                = "PicoVoice";

/* supported voices
   Pico does not seperately specify the voice and locale.   */
const char * picoSupportedLangIso3[]        = { "eng",              "eng",              "deu",              "spa",              "fra",              "ita" };
const char * picoSupportedCountryIso3[]     = { "USA",              "GBR",              "DEU",              "ESP",              "FRA",              "ITA" };
const char * picoSupportedLang[]            = { "en-US",            "en-GB",            "de-DE",            "es-ES",            "fr-FR",            "it-IT" };
const char * picoInternalLang[]             = { "en-US",            "en-GB",            "de-DE",            "es-ES",            "fr-FR",            "it-IT" };
const char * picoInternalTaLingware[]       = { "en-US_ta.bin",     "en-GB_ta.bin",     "de-DE_ta.bin",     "es-ES_ta.bin",     "fr-FR_ta.bin",     "it-IT_ta.bin" };
const char * picoInternalSgLingware[]       = { "en-US_lh0_sg.bin", "en-GB_kh0_sg.bin", "de-DE_gl0_sg.bin", "es-ES_zl0_sg.bin", "fr-FR_nk0_sg.bin", "it-IT_cm0_sg.bin" };
const char * picoInternalUtppLingware[]     = { "en-US_utpp.bin",   "en-GB_utpp.bin",   "de-DE_utpp.bin",   "es-ES_utpp.bin",   "fr-FR_utpp.bin",   "it-IT_utpp.bin" };
const int picoNumSupportedVocs              = 6;

/* adapation layer global variables */
void *          picoMemArea         = NULL;
pico_System     picoSystem          = NULL;
pico_Resource   picoTaResource      = NULL;
pico_Resource   picoSgResource      = NULL;
pico_Resource   picoUtppResource    = NULL;
pico_Engine     picoEngine          = NULL;
pico_Char *     picoTaFileName      = NULL;
pico_Char *     picoSgFileName      = NULL;
pico_Char *     picoUtppFileName    = NULL;
pico_Char *     picoTaResourceName  = NULL;
pico_Char *     picoSgResourceName  = NULL;
pico_Char *     picoUtppResourceName = NULL;
int     picoSynthAbort = 0;

#define CHUNK_SIZE 16384UL
/* buffered read from source until EOF; user should free the buffer */
size_t myread(FILE *source, char **buffer) {
    size_t count;
    size_t size = 0;
    size_t offset = 0;
    *buffer = NULL;
    do {
        // printf("allocate %ld chars\n", CHUNK_SIZE);
        *buffer = (char *)realloc(*buffer, size + CHUNK_SIZE);
        assert(*buffer);
        size += CHUNK_SIZE;
        // printf("size = %ld\n", size);
        count = fread(&((*buffer)[offset]), 1, CHUNK_SIZE, source);
        // printf("read chars = %ld\n", count);
        assert(!ferror(source));
        if (feof(source)) {
            // printf("feof = %ld\n", offset + count);
            (*buffer)[offset + count] = 0;
            return offset + count;
        }
        offset += CHUNK_SIZE;
        // printf("offset = %ld\n", offset);
    } while (1);
}

int main(int argc, const char *argv[]) {
    char * wavefile = NULL;
    char * lang = "en-US";
    int langIndex = -1, langIndexTmp = -1;
    char * text = NULL;
    int8_t * buffer;
    size_t bufferSize = 256;

        // read from stdin
        size_t len = myread(stdin, &text);

    buffer = malloc( bufferSize );

    int ret, getstatus;
    pico_Char * inp = NULL;
    pico_Char * local_text = NULL;
    short       outbuf[MAX_OUTBUF_SIZE/2];
    pico_Int16  bytes_sent, bytes_recv, text_remaining, out_data_type;
    pico_Retstring outMessage;

    picoSynthAbort = 0;

    picoMemArea = malloc( PICO_MEM_SIZE );
    if((ret = pico_initialize( picoMemArea, PICO_MEM_SIZE, &picoSystem ))) {
        pico_getSystemStatusMessage(picoSystem, ret, outMessage);
        fprintf(stderr, "Cannot initialize pico (%i): %s\n", ret, outMessage);
        goto terminate;
    }

    /* Create a new Pico engine. */
    if((ret = pico_newEngine( picoSystem, (const pico_Char *) PICO_VOICE_NAME, &picoEngine ))) {
        pico_getSystemStatusMessage(picoSystem, ret, outMessage);
        fprintf(stderr, "Cannot create a new pico engine (%i): %s\n", ret, outMessage);
        goto disposeEngine;
    }



disposeEngine:
    if (picoEngine) {
        pico_disposeEngine( picoSystem, &picoEngine );
        pico_releaseVoiceDefinition( picoSystem, (pico_Char *) PICO_VOICE_NAME );
        picoEngine = NULL;
    }
unloadUtppResource:
    if (picoUtppResource) {
        pico_unloadResource( picoSystem, &picoUtppResource );
        picoUtppResource = NULL;
    }
unloadSgResource:
    if (picoSgResource) {
        pico_unloadResource( picoSystem, &picoSgResource );
        picoSgResource = NULL;
    }
unloadTaResource:
    if (picoTaResource) {
        pico_unloadResource( picoSystem, &picoTaResource );
        picoTaResource = NULL;
    }
terminate:
    if (picoSystem) {
        pico_terminate(&picoSystem);
        picoSystem = NULL;
    }
    if (text)
      free(text);
    exit(ret);
}

