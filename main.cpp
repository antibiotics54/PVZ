//
//  main.cpp
//  P_VS_Z
//
//  Created by Valeria Alfaro on 6/5/23.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define loginPic "/Users/valeriaalfaro/Desktop/1173 progra III/P_VS_Z/assets/bmp/fondo_login.bmp"
#define introM "/Users/valeriaalfaro/Desktop/1173 progra III/P_VS_Z/assets/audios/introTheme.wav"


// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {
    
    if (audio_len ==0)
        return;
    
    len = ( len > audio_len ? audio_len : len );
    //SDL_memcpy (stream, audio_pos, len);                     // simply copy from one buffer into the other
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
    
    audio_pos += len;
    audio_len -= len;
}


int main(int argc, char** argv) {
    bool quit = true;
    string txt;
    SDL_Event evento;
    
    //===================================================
    //inicio + ventana
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_Window *window = SDL_CreateWindow("PVZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    //===================================================
    //renderer & imagen de fondo
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = SDL_LoadBMP(loginPic);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    
    //===================================================
    //requerimientos para text
    SDL_Color txtColor = { 0, 0, 0, 0xFF };
    SDL_StartTextInput();
    
    //===================================================
    //requerimientos para audio
    static Uint32 wav_length; // length of our sample
    static Uint8 *wav_buffer; // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music
    
    /* Load the WAV */
        // the specs, length and buffer of our wav are filled
        if( SDL_LoadWAV(introM, &wav_spec, &wav_buffer, &wav_length) == NULL ){
          return 1;
        }
        // set the callback function
        wav_spec.callback = my_audio_callback;
        wav_spec.userdata = NULL;
        // set our global static variables
        audio_pos = wav_buffer; // copy sound buffer
        audio_len = wav_length; // copy file length
        
        /* Open the audio device */
        if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
          fprintf(stderr, "Couldn't open audio: ", SDL_GetError());
          exit(-1);
        }
        
    //===================================================
    //while loop encargado de todo
    while(quit){
        SDL_WaitEvent(&evento);
        /* Start playing */
        SDL_PauseAudio(0);

        // wait until we're don't playing
        while ( audio_len > 0 ) {
            SDL_Delay(100);
        }
        
        switch(evento.type){
            case SDL_QUIT:
                SDL_CloseAudio();
                quit = false;
                break;
            case SDL_TEXTINPUT:
                txt+=evento.text.text;
                break;
            case SDL_KEYDOWN:
                //if para borrar cuando se presiona el backspace
                if( evento.key.keysym.sym == SDLK_BACKSPACE && txt.length() > 0 )
                    {
                        txt.pop_back();
                    }
                break;
                
                
        }
        //si el txt no esta vacio
//        if(txt != ""){
//            gInputTextTexture.loadFromRenderedText( txt.c_str(), txtColor );
//        }else{
//            gInputTextTexture.loadFromRenderedText( " ", txtColor );
//        }
        
        // shut everything down
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_StopTextInput();
        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);

    }
    
    SDL_Quit();
    
    return 0;
    
}
