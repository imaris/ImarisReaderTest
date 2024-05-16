from PyImarisReader import *

# create reader
input_filename = '/path/to/image.ims'
image_index = 0
options = Options()
reader = ImageReaderUInt8(input_filename, image_index, options)

# read image block
begin = Index5D(0, 0, 36, 0, 0)
end = Index5D(2, 2, 37, 1, 1)
buffer_size = (end.mX - begin.mX) * (end.mY - begin.mY) * (end.mZ - begin.mZ) * (end.mC - begin.mC) * (end.mT - begin.mT)
buffer = (bpReaderTypesC_UInt8 * buffer_size)()
resolution = 0
reader.ReadData(begin, end, resolution, buffer)
for byte in buffer:
    print(byte)

# read metadata
imageSizePerResolution, blockSizePerResolution, imageExtents, timeInfoPerTimepoint, colorInfoPerChannel, compression = reader.ReadMetadata()
print(imageSizePerResolution[1].mSizeY)
print(blockSizePerResolution[1].mSizeZ)
print(imageExtents.mMaxX)
print(timeInfoPerTimepoint[0].mJulianDay)
print(colorInfoPerChannel[1].mIsBaseColorMode)
print(compression)

# read parameters
parameters = reader.ReadParameters()
print(list(parameters.mSections.keys()))

# read histogram
index = IndexTCR(0, 1, 1)
histogram = reader.ReadHistogram(index)
print(histogram.contents.mBins[5])

# read thumbnail
thumbnail = reader.ReadThumbnail()
print("Thumbnail SizeY: ", thumbnail.contents.mSizeY)

# destroy reader
reader.Destroy()