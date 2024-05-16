import com.sun.jna.Native;
import com.sun.jna.Memory;

public class javaReaderTest {

    public static void main(String[] args) {
        jImarisReader.bpReaderTypesC_Options vOptions = new jImarisReader.bpReaderTypesC_Options();
        int vImageIndex = 0;
        jImarisReader.bpImageReaderUInt8 vReader = new jImarisReader.bpImageReaderUInt8("/path/to/UInt8Image.ims", 0, vOptions);
        // jImarisReader.bpImageReaderUInt16 vReader = new jImarisReader.bpImageReaderUInt16("/path/to/UInt16Image.ims", 0, vOptions);

        // read image block
        jImarisReader.bp5D vBegin = new jImarisReader.bp5D(0, 0, 0, 0, 0);
        jImarisReader.bp5D vEnd = new jImarisReader.bp5D(2, 2, 1, 1, 1);
        int vResolutionIndex = 0;
        int vNumberOfVoxels = (vEnd.mX - vBegin.mX) * (vEnd.mY - vBegin.mY) * (vEnd.mZ - vBegin.mZ) * (vEnd.mC - vBegin.mC) * (vEnd.mT - vBegin.mT);
        int vBufferSize = vNumberOfVoxels * Native.getNativeSize(Byte.TYPE); // for 8-bit image
        // int vBufferSize = vNumberOfVoxels * Native.getNativeSize(Short.TYPE); // for 16-bit image
        Memory vBuffer = new Memory(vBufferSize);
        vReader.ReadData(vBegin, vEnd, vResolutionIndex, vBuffer);
        int vVoxelIndex = 1;
        System.out.println(vBuffer.getByte(vVoxelIndex * Native.getNativeSize(Byte.TYPE))); // for 8-bit image
        // System.out.println(vBuffer.getShort(vVoxelIndex * Native.getNativeSize(Short.TYPE))); // for 16-bit image

        // read metadata
        jImarisReader.bpMetadata vMetadata = vReader.ReadMetadata();
        int vResolution = 0;
        System.out.println(vMetadata.mImageSizePerResolution.get(vResolution).mX);
        System.out.println(vMetadata.mBlockSizePerResolution.get(vResolution).mX);
        System.out.println(vMetadata.mImageExtents.mExtentMaxX);
        int vTimePoint = 0;
        System.out.println(vMetadata.mTimeInfos.get(vTimePoint).mJulianDay);
        int vChannel = 0;
        System.out.println(vMetadata.mColorInfos.get(vChannel).mBaseColor.mRed);
        // System.out.println(vMetadata.mColorInfos.get(vChannel).mColorTable.get(2).mRed);
        System.out.println(vMetadata.mCompression);

        // read parameters
        jImarisReader.bpParameters vParameters = vReader.ReadParameters();
        System.out.println(vParameters.mSections.get("Image").get("Lenspower"));

        // read histogram
        jImarisReader.bpReaderTypesC_IndexTCR vIndex = new jImarisReader.bpReaderTypesC_IndexTCR(0, 1, 1);
        jImarisReader.bpReaderTypesC_Histogram vHistogram = vReader.ReadHistogram(vIndex);
        int vHistogramValueIndex = 5;
        long[] vHistogramValues = vHistogram.mBins.getLongArray(0, (vHistogram.mBinsSize - 1) * Native.getNativeSize(Long.TYPE));
        System.out.println(vHistogramValues[vHistogramValueIndex]);

        // read thumbnail
        int vThumbnailValueIndex = 1024*30;
        jImarisReader.bpReaderTypesC_Thumbnail vThumbnail = vReader.ReadThumbnail();
        byte[] vThumbnailValues = vThumbnail.mInterleavedRGBA.getByteArray(0, (vThumbnail.mInterleavedRGBASize - 1) * Native.getNativeSize(Byte.TYPE));
        System.out.println(vThumbnailValues[vThumbnailValueIndex]);

        vReader.Destroy();
    }

}