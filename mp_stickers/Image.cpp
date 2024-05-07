#include"Image.h"
#include"cs225/HSLAPixel.h"

Image::Image():PNG() {}
Image::Image(unsigned int width, unsigned int height):PNG(width,height) {}
Image::Image(Image const & other):PNG(other) {}

void Image::lighten()
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).l+0.1<=1)
            {
                getPixel(i, j).l+=0.1;
            }
            else
            {
                getPixel(i, j).l=1;
            }
                   
        }
    }
}

void Image::lighten(double amount)
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).l+amount<=1)
            {
                getPixel(i, j).l+=amount;
            }
            else
            {
                getPixel(i, j).l=1;
            }       
        }
    }
}

void Image::darken()
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).l-0.1>=0)
            {
                getPixel(i, j).l-=0.1;
            }
            else
            {
                getPixel(i, j).l=0;
            }       
        }
    }
}

void Image::darken(double amount)
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).l-amount>=0)
            {
                getPixel(i, j).l-=amount;
            }
            else
            {
                getPixel(i, j).l=0;
            }       
        }
    }
}

void Image::saturate()
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).s+0.1<=1)
            {
                getPixel(i, j).s+=0.1;
            }
            else
            {
                getPixel(i, j).s=1;
            }       
        }
    }
}

void Image::saturate(double amount)
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).s+amount<=1)
            {
                getPixel(i, j).s+=amount;
            }
            else
            {
                getPixel(i, j).s=1;
            }          
        }
    }
}

void Image::desaturate()
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).s-0.1>=0)
            {
                getPixel(i, j).s-=0.1;
            }
            else
            {
                getPixel(i, j).s=0;
            }         
        }
    }
}

void Image::desaturate(double amount)
{
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            if(getPixel(i, j).s-amount>=0)
            {
                getPixel(i, j).s-=amount;
            }
            else
            {
                getPixel(i, j).s=0;
            }          
        }
    }
}

void Image::grayscale()
{
   for (unsigned int x = 0; x < width(); x++)
   {
       for (unsigned int y = 0; y < height(); y++) 
       {
           getPixel(x, y).s=0;
       }
   }
}

void Image::rotateColor(double degrees)
{
    while(degrees<0)
    {
        degrees+=360;
    }
    for(unsigned int i=0;i<width();i++)
    {
        for(unsigned int j=0;j<height();j++)
        {
            getPixel(i, j).h=getPixel(i, j).h+degrees-((int)(getPixel(i, j).h+degrees))/360*360;                   
        }
    }
    
}

void Image::illinify()
{
    for (unsigned int x = 0; x < width(); x++) 
    {
        for (unsigned int y = 0; y < height(); y++) 
        {
            cs225::HSLAPixel & pixel = getPixel(x, y);
            if(pixel.h > 113.5 && pixel.h < 293.5)
            {
                pixel.h = 216;
            }
            else
            {
                pixel.h = 11;
            }
        }
    }
}


void Image::scale(double factor)
{
    Image other(factor*width(),factor*height());

    for(unsigned int i=0; i<width(); i++)
    {
        for(unsigned int j=0; j<height(); j++)
        {
            cs225::HSLAPixel currentPixel=getPixel(i,j);
            for(unsigned int k=i*factor; k<i*factor+factor; k++)
            {
                for(unsigned int z=j*factor; z<i*factor+factor; z++)
                {
                    if(k<other.width() && z<other.height())
                        other.getPixel(k,z)=currentPixel;
                }
            }
        }
    }
    *this=other;
}

void Image::scale(unsigned w, unsigned h)
{
    double factorw = (double)w/(double)width();
    double factorh = (double)h/(double)height();
    double minFactor;
    if(factorw>factorh)
        minFactor=factorh;
    else
        minFactor=factorw;
    scale(minFactor);
}