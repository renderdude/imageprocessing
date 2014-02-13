#ifndef PIPELINE_IMAGE_READER_H__
#define PIPELINE_IMAGE_READER_H__

#include <pipeline/all.h>
#include <imageprocessing/Image.h>

class ImageReader : public pipeline::SimpleProcessNode<> {


protected:
	ImageReader();

	/**
	 * Reads the image.
	 */
	virtual void readImage() = 0;

	// the output image
	pipeline::Output<Image> _image;
	

private:

	void updateOutputs();
};

#endif // PIPELINE_IMAGE_READER_H__

