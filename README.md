# Perlin Noise Generator
Perlin Noise generator inspired by https://www.youtube.com/watch?v=6-0UaeJBumA

A simple Noise Geneartor implementing randomly generated seeds of a set value (256). The seeds vectors length is then used to calculate the Amplitude and Frequency values required for the function.

The function itself works in this way:

Noise Value = Amplitude * Seed Value (for all Seed values where their position in the vector MOD Frequency = 0)

With this algorithm, and a high seed length, pseudorandom terrain heightmaps can be generated. For the time being the Noise Values calculated are displayed on an SDL Graphics Window, but in the future I wish to add lines between these points to draw a proper 2D terrain, such as a mountain range
