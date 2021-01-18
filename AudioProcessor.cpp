#include "AudioProcessor.h"

std::vector<short> AudioProcessor::Compress(const std::vector<short> & audio, short threshold, float rate)
{
    // Base Cases
    if(threshold < 0)
        throw std::invalid_argument("Threshold is negative");
    else if(rate < 1.0)
        throw std::invalid_argument("Rate is less than 1.0");
    else if(audio.size() == 0)
        return audio;

    // Creates compressed vector to be returned
    std::vector<short> compressed = audio;

    // Variables to hold the sum and decimal
    double sum = 0, decimal = 0;

    int number;

    // For loop to itereate through audio and add the compressed values to compressed
    for(int i = 0; i < audio.size(); i++)
    {   
        number = abs(audio[i]);
        if(number > threshold){
            sum = (number - threshold) / rate + threshold;
            decimal = fmod(sum, 1);
            if(decimal != 0){                       // If decimal, round
                if(decimal >= .5)
                    sum += (1.0 - decimal);
                else 
                    sum -= decimal;
            }
            if(audio[i] >= 0)
                compressed[i] = sum;
            else
                compressed[i] = -sum;
        } else {
            compressed[i] = audio[i];
        }
    }
    
    // Returns the comppressed vector
    return compressed;
}

std::vector<short> AudioProcessor::CutOutSilence(const std::vector<short> & audio, short level, int silenceLength)
{
    // Base cases
    if(level < 0)
        throw std::invalid_argument("Level is negative");
    else if(silenceLength < 1)
        throw std::invalid_argument("Silence Length is below 1");
    else if(audio.size() == 0)
        return audio;

    // Creates the silenced vector to be returned
    std::vector<short> silenced = audio;

    // length is to count current length of number of silenced numbers & pastDelete is to adjust size of vector
    int length = 0, pastDelete = 0;

    // For loop to iterate through audio cutting out the silence
    for(int i = 0; i < audio.size(); i++){
        if(audio[i] >= -(level) && audio[i] <= level){
            length++;
        } else if(length >= silenceLength){
            silenced.erase(silenced.begin() + ((i - length) - pastDelete), silenced.begin() + (i - pastDelete));
            pastDelete += length;
            length = 0;
        } else {
            length = 0;
        }
    }

    // If the ending is silenced & fits silenceLength, cut it out
    if(length >= silenceLength)
       silenced.erase(silenced.begin() + (silenced.size() - length), silenced.begin() + silenced.size());

    // Returns the silenced vector
    return silenced;
}

std::vector<short> AudioProcessor::StretchTwice(const std::vector<short> & audio)
{   
    // Base case
    if(audio.size() <= 1)
        return audio;

    // Vector of stretched values to be returned
    std::vector<short> stretched;

    // Doubles to hold the left, right, sum, and decimal values
    double left = 0, right = 0, sum = 0, decimal = 0;

    // For loop to iterate through audio and stretch the appropriate values
    for(int i = 1; i < audio.size(); i++){
        left = audio[i - 1];
        right = audio[i];
        sum = (left + right) / 2.0;
        decimal = fmod(sum, 1);
        if(decimal != 0){                       // If decimal, round
            if(sum < 0){                        // Round negative numbers
                if(decimal <= -.5)              
                    sum += -(1.0 + decimal);
                else 
                    sum -= decimal;
            } else {                            // Round positive numbers
                if(decimal >= .5)
                    sum += (1.0 - decimal);
                else 
                    sum -= decimal;
            }
        }
        stretched.push_back(left);              // Add previous value
        stretched.push_back(sum);               // Add new stretched value
    }

    // Add last value
    stretched.push_back(right); 

    return stretched;
}

std::vector<short> AudioProcessor::Normalize(const std::vector<short> & audio, short normalizeTarget)
{   
    // Base cases
    if(normalizeTarget < 1)
       throw std::invalid_argument("Normalize Target is below 1"); 
    else if(audio.size() == 0)
        return audio;

    // Holds the max value of the vector
    int max = 0; 

    // Checks for an all zero vector
    bool allZeros = true;  

    // For loop to iterate through audio and check if its all zero as well as get max
    for(int i = 0; i < audio.size(); i++){
        if(audio[i] != 0)   
            allZeros = false;   
        if(audio[i] >= 0){
            if(audio[i] > max)
                max = audio[i];
        } else {
            if(-(audio[i]) > max)
                max = -(audio[i]);
        }
    }

    // If allZero return vector
    if(allZeros == true)
        return audio;

    // Scalar to normalize the vector
    double scalar = (double)normalizeTarget / (double)max;

    // Variables to hold the sum and decimal
    double sum = 0, decimal = 0;

    // Vector to hold normalized values
    std::vector<short> normalized;

    // For loop to iterate through audio and scale all the values
    for(int i = 0; i < audio.size(); i++){
        sum = audio[i] * scalar;
        decimal = fmod(sum, 1);
        if(decimal != 0){                       // If decimal, round
            if(sum < 0){                        // Round negative numbers
                if(decimal <= -.5)          
                    sum += -(1.0 + decimal);
                else 
                    sum -= decimal; 
            } else {                            // Round positive numbers
                if(decimal >= .5)   
                    sum += (1.0 - decimal);
                else 
                    sum -= decimal;
            }
        }
        normalized.push_back(sum);              // Add normalized value
    }   

    // Return normalized vector
    return normalized;
}   