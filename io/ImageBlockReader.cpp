#include "ImageBlockReader.h"

ImageBlockReader::ImageBlockReader(unsigned int n) : _sectionId(n)
{
    registerInput(_block, "block");
}