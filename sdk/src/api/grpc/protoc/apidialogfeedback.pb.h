// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: apidialogfeedback.proto
// Protobuf C++ Version: 5.28.3

#ifndef GOOGLE_PROTOBUF_INCLUDED_apidialogfeedback_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_apidialogfeedback_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5028003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_apidialogfeedback_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_apidialogfeedback_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_apidialogfeedback_2eproto;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace octaneapi {
enum MessageType : int {
  TYPE_INFO = 0,
  TYPE_ERROR = 1,
  MessageType_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  MessageType_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool MessageType_IsValid(int value);
extern const uint32_t MessageType_internal_data_[];
constexpr MessageType MessageType_MIN = static_cast<MessageType>(0);
constexpr MessageType MessageType_MAX = static_cast<MessageType>(1);
constexpr int MessageType_ARRAYSIZE = 1 + 1;
const ::google::protobuf::EnumDescriptor*
MessageType_descriptor();
template <typename T>
const std::string& MessageType_Name(T value) {
  static_assert(std::is_same<T, MessageType>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to MessageType_Name().");
  return MessageType_Name(static_cast<MessageType>(value));
}
template <>
inline const std::string& MessageType_Name(MessageType value) {
  return ::google::protobuf::internal::NameOfDenseEnum<MessageType_descriptor,
                                                 0, 1>(
      static_cast<int>(value));
}
inline bool MessageType_Parse(absl::string_view name, MessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType>(
      MessageType_descriptor(), name, value);
}
enum DialogResult : int {
  DIALOG_RESULT_YES = 0,
  DIALOG_RESULT_NO = 1,
  DIALOG_RESULT_CANCEL = 2,
  DialogResult_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  DialogResult_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool DialogResult_IsValid(int value);
extern const uint32_t DialogResult_internal_data_[];
constexpr DialogResult DialogResult_MIN = static_cast<DialogResult>(0);
constexpr DialogResult DialogResult_MAX = static_cast<DialogResult>(2);
constexpr int DialogResult_ARRAYSIZE = 2 + 1;
const ::google::protobuf::EnumDescriptor*
DialogResult_descriptor();
template <typename T>
const std::string& DialogResult_Name(T value) {
  static_assert(std::is_same<T, DialogResult>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to DialogResult_Name().");
  return DialogResult_Name(static_cast<DialogResult>(value));
}
template <>
inline const std::string& DialogResult_Name(DialogResult value) {
  return ::google::protobuf::internal::NameOfDenseEnum<DialogResult_descriptor,
                                                 0, 2>(
      static_cast<int>(value));
}
inline bool DialogResult_Parse(absl::string_view name, DialogResult* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DialogResult>(
      DialogResult_descriptor(), name, value);
}

// ===================================================================



// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace octaneapi


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::octaneapi::MessageType> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::octaneapi::MessageType>() {
  return ::octaneapi::MessageType_descriptor();
}
template <>
struct is_proto_enum<::octaneapi::DialogResult> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::octaneapi::DialogResult>() {
  return ::octaneapi::DialogResult_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_apidialogfeedback_2eproto_2epb_2eh
