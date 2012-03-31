#include "Globals.h"

void SInitSound(SApp *App)
{
    App->Music = NULL;

     int audio_rate = 22050;
     Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
     int audio_channels = 2;
     int audio_buffers = 512; 

     if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
	 printf("Unable to open audio!\n");
	 exit(1);
     }

     App->Music = Mix_LoadMUS("./sound/this.ogg");
     Mix_PlayMusic(App->Music, -1);
     
     App->Nyam.Snd = Mix_LoadWAV("./sound/nom.ogg");
     App->Nyam.Chnl = -1;
}

void SPlaySound(Sound *Snd) 
{
    if (Snd->Chnl < 0) Snd->Chnl = Mix_PlayChannel(Snd->Chnl, Snd->Snd, 0);
    Snd->Chnl = -1;
}
