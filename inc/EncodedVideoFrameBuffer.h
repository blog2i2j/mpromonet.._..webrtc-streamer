
/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** EncodedVideoFrameBuffer.h
**
** -------------------------------------------------------------------------*/

#pragma once

#include "rtc_base/ref_counted_object.h"
#include "absl/strings/match.h"

class EncodedVideoI420Buffer : public webrtc::I420BufferInterface {
 public:
   EncodedVideoI420Buffer(int width, int height, const rtc::scoped_refptr<webrtc::EncodedImageBufferInterface>& encoded_data) : width_(width), height_(height), encoded_data_(encoded_data) {
  }
  virtual int width() const { return width_; }
  virtual int height() const { return height_; }
  virtual const uint8_t* DataY() const { return encoded_data_->data(); }
  virtual const uint8_t* DataU() const { return encoded_data_->data(); }
  virtual const uint8_t* DataV() const { return encoded_data_->data(); }
  virtual int StrideY() const { return encoded_data_->size(); }
  virtual int StrideU() const { return (encoded_data_->size()+1)/2; }
  virtual int StrideV() const { return (encoded_data_->size()+1)/2; }

 private:
  const int width_;
  const int height_;  
  rtc::scoped_refptr<webrtc::EncodedImageBufferInterface> encoded_data_;
};

class EncodedVideoFrameBuffer : public webrtc::VideoFrameBuffer {
 public:
  EncodedVideoFrameBuffer(int width, int height, const rtc::scoped_refptr<webrtc::EncodedImageBufferInterface>& encoded_data) : width_(width), height_(height) {
	  buffer_ = new rtc::RefCountedObject<EncodedVideoI420Buffer>(width_, height_, encoded_data);
  }
  virtual Type type() const { return webrtc::VideoFrameBuffer::Type::kNative; }
  virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() { return webrtc::I420Buffer::Create(width(), height()); }
  virtual int width() const { return width_; }
  virtual int height() const { return height_; }
  const webrtc::I420BufferInterface* GetI420() const final { return buffer_.get();  }

 private:
  const int width_;
  const int height_;  
  rtc::scoped_refptr<EncodedVideoI420Buffer> buffer_;
};



