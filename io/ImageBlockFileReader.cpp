#include "ImageBlockFileReader.h"
#include <pipeline/Value.h>

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
    pipeline::Value<Image> cropped;
    boost::shared_ptr<pipeline::Wrap<int> > x =
        boost::make_shared<pipeline::Wrap<int> >(_block->xMin());
    boost::shared_ptr<pipeline::Wrap<int> > y =
        boost::make_shared<pipeline::Wrap<int> >(_block->yMin());
    boost::shared_ptr<pipeline::Wrap<int> > w =
        boost::make_shared<pipeline::Wrap<int> >(_block->width());
    boost::shared_ptr<pipeline::Wrap<int> > h =
        boost::make_shared<pipeline::Wrap<int> >(_block->height());

	_imageCrop = boost::make_shared<ImageCrop>();
    _imageCrop->setInput("image", _fileReader->getOutput("image"));
    _imageCrop->setInput("x", x);
    _imageCrop->setInput("y", y);
    _imageCrop->setInput("width", w);
    _imageCrop->setInput("height", h);

    cropped = _imageCrop->getOutput("cropped image");
   
    *_image = *cropped;
}