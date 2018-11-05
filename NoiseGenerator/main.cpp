//
//  main.cpp
//  NoiseGenerator
//
//  Created by Tom Apter on 01/11/2018.
//  Copyright © 2018 Tom Apter. All rights reserved.

//Perlin Noise generator inspired by https://www.youtube.com/watch?v=6-0UaeJBumA

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>
#include <fstream>
#include <SDL2/SDL.h>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

//Using timestamp generates an array of length arrayLength
vector<float> generateSeed(int arrayLength){
// Gets system time so pseudorandom seed can be generated
    auto time = std::chrono::system_clock::now();
    time_t seedTime = std::chrono::system_clock::to_time_t(time);
// Sets rand() function to use seedTime as basis for generation of pseudorandom numbers
    srand(static_cast<unsigned int>(time_t(seedTime)));
    vector<float>seedArray;
// Using rand() function to generate values between 0 and 99 to use in seedArray
    for (int i = 0; i < arrayLength; i++) {
        int randomValue = rand() % 100;
// Converting integers into floats
        float randomFloat = randomValue;
        randomFloat = randomFloat / 100;
        seedArray.push_back(randomFloat);
    }
    return seedArray;
}

//I need to get the length of both float and int vectors, not sure hwo to put both in same function?
int getLengthArray(vector<float>inputArray){
    int Length = 0;
    for (vector<float>::const_iterator i = inputArray.begin(); i != inputArray.end(); ++i){
        Length +=1;
    }
    return Length;
}

int getLengthArrayInt(vector<int>inputArray){
    int Length = 0;
    for (vector<int>::const_iterator i = inputArray.begin(); i != inputArray.end(); ++i){
        Length +=1;
    }
    return Length;
}

//Generates frequency array based on seedArray
vector<int> generateFrequency(vector<float> seedArray){
    vector<int>frequencyArray;
    int frequency = getLengthArray(seedArray);
    for (int i = 0; frequency > 1; i++) {
        frequencyArray.push_back(frequency);
        frequency = frequency / 2;
    }
    frequencyArray.push_back(1);
    return frequencyArray;
}

//Generates Amplitude array based on frequencyArray
vector<float> generateAmplitude(vector<int> frequencyArray){
    vector<float>amplitudeArray;
    float amplitude = 1;
    int amplitudeCount = 0;
    amplitudeArray.push_back(1.0);
    int length = getLengthArrayInt(frequencyArray);
    for (int i = 0; amplitudeCount+1 < length; i++) {
        amplitudeArray.push_back(amplitude/2);
        amplitude = amplitude/2;
        amplitudeCount = amplitudeCount +1;
    }
    return amplitudeArray;
}

void drawNoise(float x, float y){
    SDL_Rect pixel;
    pixel.h = 3;
    pixel.w = 3;
    std::cout << x;
    std::cout << "\n";
    std::cout << y;
    std::cout << "\n";
    pixel.x = (x*10);
    pixel.y = 720-(y*100);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &pixel);
    SDL_RenderPresent(renderer);
}

//Generates Perlin Noise values
void perlinNoise(vector<float> seed, vector<float> amplitude, vector<int> frequency ) {
    int numberSeed = getLengthArray(seed);
    int numberFrequency = getLengthArrayInt(frequency);
    for (int i = 0; i < numberSeed; i++) {
        float thisY = 0;
        float thisX = 0;
        for (int j = 0; j < numberFrequency; j++){
            thisY = 0;
            thisX = i+1;
            int modd = i % frequency[j];
            float thisAmp = amplitude[numberFrequency - j -1];
            float thisSeed = seed[i];
            if (modd == 0){
                thisY = thisY + thisAmp * thisSeed;
            }
        }
        drawNoise(thisX, thisY);
    }
}

void initializeGraphics(){
    if(SDL_Init(SDL_INIT_VIDEO) <0) {
        std::cout << "Graphics Initilaization has Failed\n";
        exit(1);
    } else {
        window = SDL_CreateWindow("Perlin Noise Generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2560, 1600, SDL_WINDOW_SHOWN);
        if(window == NULL){
            std::cout << "Graphics Window has Failed\n";
            exit(1);
        } else {
//            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer == nullptr){
                std::cout << "Renderer has Failed\n";
                exit(1);
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
}

// Main function
int main(int argc, const char * argv[]) {
    bool go = true;
    // insert code here...
    initializeGraphics();
    vector<float>seedArray = generateSeed(256);
    vector<int>frequencyArray = generateFrequency(seedArray);
    vector<float>amplitudeArray = generateAmplitude(frequencyArray);
    perlinNoise(seedArray, amplitudeArray, frequencyArray);
    
    while(go){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch( event.type){
                case SDL_QUIT:
                    go = false;
                    break;
                default:
                    break;
            }
        }
    }
    
}
