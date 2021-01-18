#include "AudioProcessor.h"

int main()
{

    AudioProcessor processor;

    std::vector<short> audioSamples{1, 4, 25, 15, 0, -7, -40, 10};
    std::vector<short> compressedAudio;
    std::vector<short> answerCompressed{1, 4, 20, 13, 0, -7, -30, 10};

    for(int i = 0; i < audioSamples.size(); i++){
        std::cout << audioSamples[i] << " ";
    } 
    std::cout << std::endl;

    std::cout << "Compressing Audio by 10 at a rate of 1.5" << std::endl;
    compressedAudio = processor.Compress(audioSamples, 10, 1.5);

    for(int i = 0; i < compressedAudio.size(); i++){
        std::cout << compressedAudio[i] << " ";
    }   

    std::cout << std::endl;

    if(compressedAudio == answerCompressed)
        std::cout << "Successfully Compressed" << std::endl;
    else
        std::cout << "compressed failed" << std::endl;

    std::cout << std::endl;

    std::vector<short> audio{1, -3, 10, 25, 56, -1, -2, -16, -20, -8, -1, 1, 7, 12};
    std::vector<short> silencedAudio;
    std::vector<short> answerAudio{25, 56, -1, -2, -16, -20, 12};

    for(int i = 0; i < audio.size(); i++){
        std::cout << audio[i] << " ";
    } 
    std::cout << std::endl;

    std::cout << "Silencing Audio in range of 10 at a length of 3" << std::endl;
    silencedAudio = processor.CutOutSilence(audio, 10, 3);

    for(int i = 0; i < silencedAudio.size(); i++){
        std::cout << silencedAudio[i] << " ";
    } 

    std::cout << std::endl;

    if(silencedAudio == answerAudio)
        std::cout << "Successfully Silenced" << std::endl;
    else
        std::cout << "silenced failed" << std::endl;

    std::cout << std::endl;

    std::vector<short> stretched{1, 4, 23, -2, -28, 10 };
    std::vector<short> stretchedAudio;
    std::vector<short> answerStretched{1, 3, 4, 14, 23, 11, -2, -15, -28, -9, 10};

    for(int i = 0; i < stretched.size(); i++){
        std::cout << stretched[i] << " ";
    } 
    std::cout << std::endl;

    std::cout << "Stretching Audio" << std::endl;
    stretchedAudio = processor.StretchTwice(stretched);

    for(int i = 0; i < stretchedAudio.size(); i++){
        std::cout << stretchedAudio[i] << " ";
    } 

    std::cout << std::endl;

    if(stretchedAudio == answerStretched)
        std::cout << "Successfully Stretched" << std::endl;
    else
        std::cout << "stretched failed" << std::endl;

    std::cout << std::endl;

    std::vector<short> normalized{1, 3, -2, 5, -4, 0};
    std::vector<short> normalizedAudio;
    std::vector<short> answerNormal{2, 6, -4, 10, -8, 0};

    for(int i = 0; i < normalized.size(); i++){
        std::cout << normalized[i] << " ";
    } 
    std::cout << std::endl;

    std::cout << "Normalizing Audio by 10" << std::endl;
    normalizedAudio = processor.Normalize(normalized, 10);

    for(int i = 0; i < normalizedAudio.size(); i++){
        std::cout << normalizedAudio[i] << " ";
    } 

    std::cout << std::endl;

    if(normalizedAudio == answerNormal)
        std::cout << "Successfully Normalized" << std::endl;
    else
        std::cout << "normal failed" << std::endl;
        
    return 0;
}
