// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/system/message_in_transit.h"

#include <string.h>

#include <new>

#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/aligned_memory.h"
#include "mojo/system/constants.h"

namespace mojo {
namespace system {

// Avoid dangerous situations, but making sure that the size of the "header" +
// the size of the data fits into a 31-bit number.
COMPILE_ASSERT(static_cast<uint64_t>(sizeof(MessageInTransit)) +
                   kMaxMessageNumBytes <= 0x7fffffff,
               kMaxMessageNumBytes_too_big);

COMPILE_ASSERT(
    sizeof(MessageInTransit) % MessageInTransit::kMessageAlignment == 0,
    sizeof_MessageInTransit_not_a_multiple_of_alignment);

STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::Type
    MessageInTransit::kTypeMessagePipeEndpoint;
STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::Type
    MessageInTransit::kTypeMessagePipe;
STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::Type
    MessageInTransit::kTypeChannel;
STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::Subtype
    MessageInTransit::kSubtypeMessagePipeEndpointData;
STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::Subtype
    MessageInTransit::kSubtypeMessagePipePeerClosed;
STATIC_CONST_MEMBER_DEFINITION const MessageInTransit::EndpointId
    MessageInTransit::kInvalidEndpointId;
STATIC_CONST_MEMBER_DEFINITION const size_t MessageInTransit::kMessageAlignment;

// static
MessageInTransit* MessageInTransit::Create(Type type,
                                           Subtype subtype,
                                           const void* bytes,
                                           uint32_t num_bytes,
                                           uint32_t num_handles) {
  DCHECK_LE(num_bytes, kMaxMessageNumBytes);
  DCHECK_LE(num_handles, kMaxMessageNumHandles);

  const size_t data_size = num_bytes;
  const size_t size_with_header = sizeof(MessageInTransit) + data_size;
  const size_t size_with_header_and_padding =
      RoundUpMessageAlignment(size_with_header);

  char* buffer = static_cast<char*>(
      base::AlignedAlloc(size_with_header_and_padding, kMessageAlignment));
  // The buffer consists of the header (a |MessageInTransit|, constructed using
  // a placement new), followed by the data, followed by padding (of zeros).
  MessageInTransit* rv = new (buffer) MessageInTransit(
      static_cast<uint32_t>(data_size), type, subtype, num_bytes, num_handles);
  memcpy(buffer + sizeof(MessageInTransit), bytes, num_bytes);
  memset(buffer + size_with_header, 0,
         size_with_header_and_padding - size_with_header);
  return rv;
}

void MessageInTransit::Destroy() {
  // No need to call the destructor, since we're POD.
  base::AlignedFree(this);
}

MessageInTransit::MessageInTransit(uint32_t data_size,
                                   Type type,
                                   Subtype subtype,
                                   uint32_t num_bytes,
                                   uint32_t num_handles)
    : data_size_(data_size),
      type_(type),
      subtype_(subtype),
      source_id_(kInvalidEndpointId),
      destination_id_(kInvalidEndpointId),
      num_bytes_(num_bytes),
      num_handles_(num_handles),
      reserved0_(0),
      reserved1_(0) {
  DCHECK_GE(data_size_, num_bytes_);
}

}  // namespace system
}  // namespace mojo
