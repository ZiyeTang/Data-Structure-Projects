#include "Image.h"
#include "StickerSheet.h"

int main() 
{

  //StickerSheet stkSht();
  Image baseImg,sampleSticker,res;
  baseImg.readFromFile("alma.png");
  sampleSticker.readFromFile("i.png");
  StickerSheet sheet1(baseImg,4);

  unsigned int width=baseImg.width();
  unsigned int height=baseImg.height();

  sheet1.addSticker(sampleSticker,width/5,height/4);
  sheet1.addSticker(sampleSticker,width/3,height/2);
  sheet1.addSticker(sampleSticker,width/9,height/9);

  res=sheet1.render();
  res.writeToFile("myImage.png");
  return 0;
}
