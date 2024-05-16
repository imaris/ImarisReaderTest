#include "ImarisReader/interface/bpReaderTypes.h"
#include "ImarisReader/interface/bpImageReader.h"

using namespace bpConverterTypes;


template<typename TDataType>
void ReadFile(const bpString& aInputFileName, bpSize aImageIndex, const bpReaderTypes::cReadOptions& aOptions)
{
  // create Reader
  bpImageReader<TDataType>  vReader(aInputFileName, aImageIndex, aOptions);

  // read metadata
  std::vector<tSize5D> vImageSizePerResolution;
  std::vector<tSize5D> vBlockSizePerResolution;
  cImageExtent vImageExtent;
  tTimeInfoVector vTimeInfoPerTimePoint;
  tColorInfoVector vColorInfoPerChannel;
  tCompressionAlgorithmType vCompressionAlgorithmType;
  vReader.ReadMetadata(vImageSizePerResolution, vBlockSizePerResolution, vImageExtent, vTimeInfoPerTimePoint, vColorInfoPerChannel, vCompressionAlgorithmType);

  // get number of resolutions, timepoints and channels
  bpSize vSizeX, vSizeY, vSizeZ, vBlockSizeX, vBlockSizeY, vBlockSizeZ, vNumTimePoints, vNumChannels, vNumResolutions;
  vNumResolutions = vImageSizePerResolution.size();
  vNumTimePoints = vTimeInfoPerTimePoint.size();
  vNumChannels = vColorInfoPerChannel.size();
  // image and block sizes
  vSizeX = vImageSizePerResolution[0][X];
  vSizeY = vImageSizePerResolution[0][Y];
  vSizeZ = vImageSizePerResolution[0][Z];
  vBlockSizeX = vBlockSizePerResolution[0][X];
  vBlockSizeY = vBlockSizePerResolution[0][Y];
  vBlockSizeZ = vBlockSizePerResolution[0][Z];
  tSize5D vImageSize(X, vSizeX, Y, vSizeY, Z, vSizeZ, C, vNumChannels, T, vNumTimePoints);
  tSize5D vReadSize(X, vBlockSizeX, Y, vBlockSizeY, Z, vBlockSizeZ, C, 1, T, 1);

  // ReadData parameters
  tIndex5D vBegin({ X, 0 }, { Y, 0 }, { Z, 0 }, { C, 0 }, { T, 0 });
  tIndex5D vEnd({ X, 0 }, { Y, 0 }, { Z, 0 }, { C, 0 }, { T, 0 });
  bpSize vBufferSize = vReadSize[X] * vReadSize[Y] * vReadSize[Z] * vReadSize[C] * vReadSize[T];
  tDimensionSequence5D vDimensionSequence(X, Y, Z, C, T);
  tSize5D vBlocksPerDimension(X, 0, Y, 0, Z, 0, C, 0, T, 0);
  for (bpSize vDimIndex = 0; vDimIndex < 5; ++vDimIndex) {
    Dimension vDim = vDimensionSequence[vDimIndex];
    vBlocksPerDimension[vDim] = (vImageSize[vDim] + vReadSize[vDim] - 1) / vReadSize[vDim];
  }
  
  // read data loop
  TDataType* vBuffer = new TDataType[vBufferSize];
  for (bpSize vIndexT = 0; vIndexT < vBlocksPerDimension[T]; vIndexT++) {
    for (bpSize vIndexC = 0; vIndexC < vBlocksPerDimension[C]; vIndexC++) {
      for (bpSize vIndexZ = 0; vIndexZ < vBlocksPerDimension[Z]; vIndexZ++) {
        for (bpSize vIndexY = 0; vIndexY < vBlocksPerDimension[Y]; vIndexY++) {
          for (bpSize vIndexX = 0; vIndexX < vBlocksPerDimension[X]; vIndexX++) {

            vBegin = { { X, vIndexX * vReadSize[X] },{ Y, vIndexY * vReadSize[Y] },{ Z, vIndexZ * vReadSize[Z] },{ C, vIndexC * vReadSize[C] },{ T, vIndexT * vReadSize[T] } };
            vEnd = { { X, vBegin[X] + vReadSize[X] }, { Y, vBegin[Y] + vReadSize[Y] }, { Z, vBegin[Z] + vReadSize[Z] }, { C, vBegin[C] + vReadSize[C] }, { T, vBegin[T] + vReadSize[T] } };

            vReader.ReadData(vBegin, vEnd, 0, vBuffer);

          }
        }
      }
    }
  }
  delete[] vBuffer;

  // read image parameters
  tParameters vParameters;
  vReader.ReadParameters(vParameters);

  // read histogram
  std::array<bpSize, 3> vIndexTCR = {0, 0, 0}; // specify timepoint, channel and resolution level
  bpImageReaderBaseInterface::cHistogram vHist = vReader.ReadHistogram(vIndexTCR);

  // read thumbnail
  bpImageReaderBaseInterface::cThumbnail vThumbnail = vReader.ReadThumbnail();
}

int main(int argc, char* argv[])
{
  bpString vInputFileName = "/path/to/image.ims";

  bpReaderTypes::cReadOptions vOptions;
  vOptions.mSWMR = false;
  bpSize vImageIndex = 0; // for multi-image files
  std::vector<tDataType> vDataTypes = GetFileImagesInformation(vInputFileName, vOptions.mSWMR);
  switch (vDataTypes[vImageIndex]) {
    case bpUInt8Type:
      ReadFile<bpUInt8>(vInputFileName,vImageIndex, vOptions);
      break;
    case bpUInt16Type:
      ReadFile<bpUInt16>(vInputFileName,vImageIndex, vOptions);
      break;
    case bpUInt32Type:
      ReadFile<bpUInt32>(vInputFileName,vImageIndex, vOptions);
      break;
    case bpFloatType:
      ReadFile<bpFloat>(vInputFileName,vImageIndex, vOptions);
      break;
    default:
      throw "DataType not supported";
  }

  return 0;
}
