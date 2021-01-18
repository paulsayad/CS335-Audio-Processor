# CS335-Audio-Processor

## About the Project

* Create a program that can read in audio representated by an array of numbers, called samples
* Create functions to process the audio by compressing it, cutting out silence, stretching it, and normalizing it

## Project Design

* Compress(const vector & audio, short threshold, float rate) function where any number from audio that is larger than threshold or smaller than threshold has it’s “above the threshold” portion reduced rate time. Rate is called “compression rate”
* CutOutSilence(const vector & audio, short level, int silenceLength) function which cuts out silence and silence is a portion of audio where all numbers/samples are in the range [-level, level]
* StretchTwice(const vector & audio) function returns the version of audio where between each pair of original samples from audio an extra sample appears. This extra sample is an average (arithmetic mean) of the two original samples
* Normalize(const vector & audio, short normalizeTarget) function returns a version of audio where all samples are proportionally increases or decreased to ensure that the largest absolute value from all resulting samples is exactly normalizeTarget.

## How to Compile the Program

1. Download the files and put them in a directory
2. Navigate to your directory in your terminal and run the command
> g++ main.cpp AudioProcessor.cpp -o main
3. To execute the program run the command
> ./main
4. You will see original audio samples and the samples after they have been processed
