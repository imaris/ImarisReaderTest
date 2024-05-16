#include <stdio.h>
#include <stdlib.h>

#include "ImarisReader/interfaceC/bpImageReaderInterfaceC.h"


int main(int argc, char* argv[])
{
    // create reader
    bpReaderTypesC_String vName = "/path/to/image.ims";
    bpReaderTypesC_Options vOptions;
    vOptions.mSWMR = false;
    unsigned int vImageIndex = 0;
    bpImageReaderCPtr vReader = bpImageReaderC_CreateUInt8(vName, vImageIndex, &vOptions);

    // read metadata
    bpReaderTypesC_Size5DVector vImageSizePerResolution;
    bpReaderTypesC_Size5DVector vBlockSizePerResolution;
    bpReaderTypesC_ImageExtent vImageExtent;
    bpReaderTypesC_TimeInfos vTimeInfoPerTimePoint;
    bpReaderTypesC_ColorInfos vColorInfoPerChannel;
    bpReaderTypesC_CompressionAlgorithmType vCompressionAlgorithmType;
    bpImageReaderC_ReadMetadataUInt8(vReader, &vImageSizePerResolution, &vBlockSizePerResolution, &vImageExtent, &vTimeInfoPerTimePoint, &vColorInfoPerChannel, vCompressionAlgorithmType);
    printf("Max X: %f\n", vImageExtent.mExtentMaxX);
    printf("Size X: %u\n", vImageSizePerResolution.mSizePerResolution[0].mValueX);
    printf("Time: %u\n", vTimeInfoPerTimePoint.mValues[0].mJulianDay);
    printf("Color: %f\n", vColorInfoPerChannel.mValues[0].mBaseColor.mRed);
    bpImageReaderC_FreeMetadata(&vImageSizePerResolution, &vBlockSizePerResolution, &vTimeInfoPerTimePoint, &vColorInfoPerChannel);

    // read image block (a single voxel in this example)
    bpReaderTypesC_Index5D vBegin;
    vBegin.mValueX = 0;
    vBegin.mValueY = 0;
    vBegin.mValueZ = 36;
    vBegin.mValueC = 0;
    vBegin.mValueT = 0;
    bpReaderTypesC_Index5D vEnd;
    vEnd.mValueX = 1;
    vEnd.mValueY = 1;
    vEnd.mValueZ = 37;
    vEnd.mValueC = 1;
    vEnd.mValueT = 1;
    bpReaderTypesC_UInt8* vBuffer = (unsigned char*)malloc(sizeof (unsigned char));
    bpImageReaderC_ReadDataUInt8(vReader, &vBegin, &vEnd, 0, vBuffer);
    printf("Intensity: %u\n", *(vBuffer));
    free(vBuffer);

    // read parameters
    bpReaderTypesC_Parameters vParams;
    bpImageReaderC_ReadParametersUInt8(vReader, &vParams);
    printf("Section %s, Parameter %s: %s\n", vParams.mValues[2].mName, vParams.mValues[2].mValues[7].mName, vParams.mValues[2].mValues[7].mValue);
    bpImageReaderC_FreeParameters(&vParams);

    // read histogram
    bpReaderTypesC_IndexTCR vIndex;
    vIndex.mT = 0;
    vIndex.mC = 0;
    vIndex.mR = 0;
    bpReaderTypesC_HistogramPtr vHistogram = bpImageReaderC_ReadHistogramUInt8(vReader, &vIndex);
    printf("Bin value: %llu\n", vHistogram->mBins[115]);
    free(vHistogram);

    // read thumbnail
    bpReaderTypesC_ThumbnailPtr vThumbnail = bpImageReaderC_ReadThumbnailUInt8(vReader);
    printf("Thumbnail Size X: %u\n", vThumbnail->mSizeX);
    free(vThumbnail);

    // destroy reader
    bpImageReaderC_DestroyUInt8(vReader);

    return 0;
}
