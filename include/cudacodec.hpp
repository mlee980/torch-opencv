#include <CUDACommon.hpp>
#include <include/Classes.hpp>
#include <opencv2/cudacodec.hpp>

namespace cudacodec = cv::cudacodec;

extern "C"
struct cudacodec::EncoderParams EncoderParams_ctor_default();

extern "C"
struct cudacodec::EncoderParams EncoderParams_ctor(const char *configFile);

extern "C"
void EncoderParams_save(struct cudacodec::EncoderParams params, const char *configFile);

struct VideoWriterPtr {
    void *ptr;

    inline cudacodec::VideoWriter * operator->() { return static_cast<cudacodec::VideoWriter *>(ptr); }
    inline VideoWriterPtr(cudacodec::VideoWriter *ptr) { this->ptr = ptr; }
    inline cudacodec::VideoWriter & operator*() { return *static_cast<cudacodec::VideoWriter *>(this->ptr); }
};

struct VideoReaderPtr {
    void *ptr;

    inline cudacodec::VideoReader * operator->() { return static_cast<cudacodec::VideoReader *>(ptr); }
    inline VideoReaderPtr(cudacodec::VideoReader *ptr) { this->ptr = ptr; }
    inline cudacodec::VideoReader & operator*() { return *static_cast<cudacodec::VideoReader *>(this->ptr); }
};

extern "C"
struct VideoWriterPtr VideoWriter_ctor(
        const char *filename, struct SizeWrapper frameSize,
        double fps, struct cudacodec::EncoderParams params, int format);

extern "C"
void VideoWriter_dtor(struct VideoWriterPtr ptr);

extern "C"
void VideoWriter_write(struct VideoWriterPtr ptr, struct TensorWrapper frame, bool lastFrame);

extern "C"
struct cudacodec::EncoderParams VideoWriter_getEncoderParams(struct VideoWriterPtr ptr);

extern "C"
struct VideoReaderPtr VideoReader_ctor(const char *filename);

extern "C"
void VideoReader_dtor(struct VideoReaderPtr ptr);

extern "C"
struct TensorWrapper VideoReader_nextFrame(
        struct cutorchInfo info, struct VideoReaderPtr ptr, struct TensorWrapper frame);

extern "C"
struct cudacodec::FormatInfo VideoReader_format(struct VideoReaderPtr ptr);