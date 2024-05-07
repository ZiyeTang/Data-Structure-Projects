/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector> 
using namespace std;
struct Sticker
{
    int x;
    int y;
    int index;
    Image* img;
};

class StickerSheet
{        
    public:
        vector<Sticker> stk;
        Image* baseImg;
        int maxSize;
        
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render () const;
        void copy(const StickerSheet& other);
        void clear();
};
