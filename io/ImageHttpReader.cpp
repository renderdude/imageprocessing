
#include <util/httpclient.h>
#include <ImageMagick/Magick++.h>
#include <util/Logger.h>
#include "ImageHttpReader.h"

logger::LogChannel imagehttpreaderlog("imagehttpreaderlog", "[ImageHttpReader] ");

ImageHttpReader::ImageHttpReader(std::string url) :
    _url(url)
{
    
}

void
ImageHttpReader::readImage()
{
    LOG_DEBUG(imagehttpreaderlog) << "Will attempt to read image from " << _url << std::endl;
    
    //Read the image url
    HttpClient::response res = HttpClient::get(_url);
    //TODO check that res.code == 200 OK
    int size = res.body.size();
    
    LOG_DEBUG(imagehttpreaderlog) << "Read " << size << " things" << std::endl;
    
    // Create a blob from the body as an array of char.
    // I'm frankly surprised that this works.
    Magick::Blob blob(res.body.c_str(), size);
    // Make the image.
    Magick::Image image(blob);
    // Define the pixel packet reference.
    Magick::PixelPacket *pixels;
    // Get the size of the image.
    int w = image.columns(), h = image.rows();
    // We'll push the image values to this in a second.
    boost::shared_ptr<std::vector<float> > pixelVector = boost::make_shared<std::vector<float> >(w * h, 0);
    
    LOG_DEBUG(imagehttpreaderlog) << "Image is size " << w << " by " << h << std::endl;
    
    // Get a pixel reference
    pixels = image.getPixels(0, 0, w, h);
    
    LOG_DEBUG(imagehttpreaderlog) << "Pushing pixels..." << std::endl;
    
    for (int i = 0; i < w * h; ++i)
    {
        Magick::Color color = pixels[i];
        Magick::ColorGray gColor = color;
        double dval = gColor.shade();
        (*pixelVector)[i] = (float)dval;
    }
    
    LOG_DEBUG(imagehttpreaderlog) << "Creating image object" << std::endl;
    
    *_image = Image(w, h, pixelVector);
    
}
