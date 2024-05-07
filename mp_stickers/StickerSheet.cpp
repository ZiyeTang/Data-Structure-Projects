#include"StickerSheet.h"

StickerSheet::StickerSheet (const Image &picture, unsigned max)
{
    maxSize=max;
    baseImg=new Image(picture);
}

void StickerSheet::clear()
{
    for(auto i=stk.begin();i!=stk.end();i++)
    {
        if((*i).img!=nullptr)
        {
            delete i->img;
            (*i).img=nullptr;
        }
    }
    if(baseImg!=nullptr)
    {
        delete baseImg;
        baseImg=nullptr;
    }
}       
    
StickerSheet::~StickerSheet ()
{
    clear();
}
   
void StickerSheet::copy(const StickerSheet &other)
{
    maxSize=other.maxSize;
    baseImg=new Image(*(other.baseImg));
    stk.clear();
    for(auto i=other.stk.begin();i!=other.stk.end();i++)
    {
        Sticker s;
        stk.push_back(s);
        (stk.end()-1)->x=i->x;
        (stk.end()-1)->y=i->y;
        (stk.end()-1)->index=i->index;
        (stk.end()-1)->img=new Image(*(i->img));
        
    }
}  
   
StickerSheet::StickerSheet (const StickerSheet &other)
{
    copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
    maxSize=(int)max;
    if(max<stk.size())
    {
        int diff=stk.size()-max;
        for(int i=1;i<=diff;i++)
        {
            stk.pop_back();
        }
    }
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y)
{
    if((int)stk.size()<maxSize)
    {
        Sticker s;
       
        stk.push_back(s);
        (stk.end()-1)->x=x;
        (stk.end()-1)->y=y;
        (stk.end()-1)->index=stk.size()-1;
        (stk.end()-1)->img=new Image(sticker);        
        return stk.size()-1;
    }
    return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y)
{
    for(auto i=stk.begin();i!=stk.end();i++)
    {
        if((*i).index==(int)(index))
        {
            (*i).x=(int)x;
            (*i).y=(int)y;
            return true;
        }
    }
    return false;
}

void StickerSheet::removeSticker (unsigned index)
{
    for(auto i=stk.begin();i!=stk.end();i++)
    {
        if((*i).index==(int)(index))
        {
            for(auto j=i;j!=stk.end()-1;j++)
            {
                j->x=(j+1)->x;
                j->y=(j+1)->y;
                //j->index=(j+1)->index;
                if(j->img!=nullptr)
                {
                    delete j->img;
                    j->img=nullptr;
                }
                j->img=new Image(*((j+1)->img));
            }
            stk.pop_back();
            return;
        }
    }
}

Image * StickerSheet::getSticker (unsigned index)
{
    for(auto i=stk.begin();i!=stk.end();i++)
    {
        if((*i).index==(int)(index))
        {
            return i->img;
        }
    }
    return NULL;
}


Image StickerSheet::render() const
{


    Image res(*baseImg);


    for(auto i=stk.begin();i!=stk.end();i++)
    {
        for(unsigned int j=0;j<i->img->width();j++)
        {
            for(unsigned int k=0;k<i->img->height();k++)
            {
                if(i->x+j>=res.width())
                {
                    unsigned int oldWidth=res.width();                    
                    res.resize(i->x+j+1,res.height());
                    for(unsigned int a=oldWidth;a<res.width();a++)
                    {
                        for(unsigned int b=0;b<res.height();b++)
                        {
                            res.getPixel(a,b).a=0;
                        }
                    }
                    
                }
                if(i->y+k >= res.height())
                {
                    unsigned int oldHeight=res.height();
                    res.resize(res.width(),i->y+k+1);
                    for(unsigned int a=0;a<res.width();a++)
                    {
                        for(unsigned int b=oldHeight;b<res.height();b++)
                        {
                            res.getPixel(a,b).a=0;
                        }
                    }
                }
                cs225::HSLAPixel& resPixel=res.getPixel(i->x+j,i->y+k);
                cs225::HSLAPixel stickerPixel=i->img->getPixel(j,k);
                if(stickerPixel.a!=0)
                {
                    resPixel.h=stickerPixel.h;
                    resPixel.l=stickerPixel.l;
                    resPixel.s=stickerPixel.s;
                    resPixel.a=stickerPixel.a;
                }

            }
        }
    }
    return res;
}
