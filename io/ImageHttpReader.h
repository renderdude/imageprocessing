#ifndef PIPELINE_IMAGE_HTTP_READER_H__
#define PIPELINE_IMAGE_HTTP_READER_H__

#include <pipeline/all.h>
#include <imageprocessing/Image.h>

class ImageHttpReader : public pipeline::SimpleProcessNode<>
{

public:
    ImageHttpReader(std::string url);

private:
    void readImage();
    
    pipeline::Output<Image> _image;

    std::string _url;
    
    void updateOutputs();
};

#endif //PIPELINE_IMAGE_HTTP_READER_H__
