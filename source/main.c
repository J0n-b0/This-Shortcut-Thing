#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <3ds.h>
	
#define PATH_SPLASH "romfs:/splash.bin"
#define PATH_PAYLOADRFS "romfs:/payload.firm"
#define PATH_BOOTFIRM "boot.firm"
#define PATH_PAYLOADSD "TST/payloads/" APP_TITLE ".firm"
#define PATH_FB3DSCFGSD "3DS/fastbootcfg.txt"
#define PATH_FB3DSCFGCTR "/fastboot3ds/fastbootcfg.txt"
#define PATH_LOG "TST/log.txt"

#define FB3DS_FIRMBOOTSTR "RAM_FIRM_BOOT = Enabled"

#define FIRM_MAXSIZE (1024 * 1024 * 4 - 0x200)
#define FIRM_OFFSET (0x1000)
#define CONF_REG	0x17

void *buf = NULL;

void __attribute__((weak)) __appInit(void) 
{
    buf = linearAlloc(FIRM_OFFSET + FIRM_MAXSIZE);    
    
	// Initialize services
    srvInit();
	mcuHwcInit();
	aptInit();
    acInit();
    hidInit();
    fsInit();
	romfsInit();
	
}

void __attribute__((weak)) __appExit(void) 
{
	// Exit services
	romfsExit();
    fsExit();
	gfxExit();
    hidExit();
	acExit();
    aptExit();
    srvExit();
	mcuHwcExit();

    GSPGPU_FlushDataCache(buf, FIRM_MAXSIZE);
    linearFree(buf);
}

void setLED(InfoLedPattern* pat, u8 r, u8 g, u8 b)
{
	memset(pat->redPattern, r, 32);
    memset(pat->greenPattern, g, 32);
    memset(pat->bluePattern, b, 32);
	MCUHWC_SetInfoLedPattern(pat);
}

int main() 
{
	
    gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
	
	u8 *contents;
	FILE *payload, *splash;
	size_t splash_size, payload_size;
	
	if (!buf)
	{
		printf("Error: out of memory\n");
    }

    printf("firm@%08lX\n", (u32) buf + FIRM_OFFSET);
    if ((u32) buf != 0x14000000) 
	{
		// must be at the start of FCRAM
        printf("Bad firm location\n");
    }
	
	splash = fopen(PATH_SPLASH, "rb");
	fseek(splash, 0, SEEK_END);
	splash_size = ftell(splash);
	rewind(splash);
	contents = malloc(splash_size);
	fread(contents, 1, splash_size, splash);
	memcpy(gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL), contents, splash_size);
	free(contents);
	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();
	
	payload = fopen(PATH_PAYLOADSD, "r");
	
	if(!payload)
	{
		payload = fopen(PATH_PAYLOADRFS, "r");
	}
	else
	{
		printf("Custom payload found on SD\n");
	}
	
	fseek(payload, 0, SEEK_END);
	payload_size = ftell(payload);
	rewind(payload);

	InfoLedPattern pattern;
	pattern.smoothing = 0xFF;
	if(fread(buf + 0x1000, 1, payload_size, payload) != payload_size)
		setLED(&pattern, 255, 0, 0);
	else
		setLED(&pattern, 0, 255, 0);

	fclose(payload);
	
	for(int i=0; i<=60; i++) gspWaitForVBlank();
	setLED(&pattern, 0, 0, 0);
	APT_HardwareResetAsync();
	
    
    return 0;
}
