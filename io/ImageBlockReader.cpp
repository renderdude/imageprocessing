#include "ImageBlockReader.h"

ImageBlockReader::ImageBlockReader()
{
    registerInput(_block, "block");
	registerInput(_sectionId, "section");
}