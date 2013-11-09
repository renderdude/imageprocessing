#include "ImageBlockFileReader.h"

ImageBlockFileReader::ImageBlockFileReader(std::string filename, unsigned int n) :
    ImageBlockReader(n)
{
    _fileReader = boost::make_shared<ImageFileReader>(filename);
    //_imageCrop = boost::make_shared<ImageCrop>();
    //_imageCrop->setInput("image", _fileReader->getInput("image"));
}

void
ImageBlockFileReader::readImage()
{
    int xMin = _block->xMin();
    
    boost::shared_ptr<int> x = boost::make_shared(&xMin);
    boost::shared_ptr<int> y = boost::make_shared(&(_block->yMin()));
    boost::shared_ptr<int> w = boost::make_shared(&(_block->width()));
    boost::shared_ptr<int> h = boost::make_shared(&(_block->height()));
    
    _imageCrop = boost::make_shared<ImageCrop>();
    _imageCrop->setInput("image", _fileReader->getInput("image"));
    _imageCrop->setInput("x", x);
    _imageCrop->setInput("y", y);
    _imageCrop->setInput("width", w);
    _imageCrop->setInput("height", h);

    *_image = _imageCrop->getOutput("cropped image");
}