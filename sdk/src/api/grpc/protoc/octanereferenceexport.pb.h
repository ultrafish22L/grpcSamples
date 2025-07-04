// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: octanereferenceexport.proto
// Protobuf C++ Version: 5.28.3

#ifndef GOOGLE_PROTOBUF_INCLUDED_octanereferenceexport_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_octanereferenceexport_2eproto_2epb_2eh

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
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
#include "octanetime.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_octanereferenceexport_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_octanereferenceexport_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_octanereferenceexport_2eproto;
namespace octaneapi {
class ReferencePackageExportSettings;
struct ReferencePackageExportSettingsDefaultTypeInternal;
extern ReferencePackageExportSettingsDefaultTypeInternal _ReferencePackageExportSettings_default_instance_;
}  // namespace octaneapi
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace octaneapi {

// ===================================================================


// -------------------------------------------------------------------

class ReferencePackageExportSettings final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:octaneapi.ReferencePackageExportSettings) */ {
 public:
  inline ReferencePackageExportSettings() : ReferencePackageExportSettings(nullptr) {}
  ~ReferencePackageExportSettings() PROTOBUF_FINAL;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR ReferencePackageExportSettings(
      ::google::protobuf::internal::ConstantInitialized);

  inline ReferencePackageExportSettings(const ReferencePackageExportSettings& from) : ReferencePackageExportSettings(nullptr, from) {}
  inline ReferencePackageExportSettings(ReferencePackageExportSettings&& from) noexcept
      : ReferencePackageExportSettings(nullptr, std::move(from)) {}
  inline ReferencePackageExportSettings& operator=(const ReferencePackageExportSettings& from) {
    CopyFrom(from);
    return *this;
  }
  inline ReferencePackageExportSettings& operator=(ReferencePackageExportSettings&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ReferencePackageExportSettings& default_instance() {
    return *internal_default_instance();
  }
  static inline const ReferencePackageExportSettings* internal_default_instance() {
    return reinterpret_cast<const ReferencePackageExportSettings*>(
        &_ReferencePackageExportSettings_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(ReferencePackageExportSettings& a, ReferencePackageExportSettings& b) { a.Swap(&b); }
  inline void Swap(ReferencePackageExportSettings* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ReferencePackageExportSettings* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ReferencePackageExportSettings* New(::google::protobuf::Arena* arena = nullptr) const PROTOBUF_FINAL {
    return ::google::protobuf::Message::DefaultConstruct<ReferencePackageExportSettings>(arena);
  }
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(ReferencePackageExportSettings* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "octaneapi.ReferencePackageExportSettings"; }

 protected:
  explicit ReferencePackageExportSettings(::google::protobuf::Arena* arena);
  ReferencePackageExportSettings(::google::protobuf::Arena* arena, const ReferencePackageExportSettings& from);
  ReferencePackageExportSettings(::google::protobuf::Arena* arena, ReferencePackageExportSettings&& from) noexcept
      : ReferencePackageExportSettings(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const PROTOBUF_FINAL;
  static const ::google::protobuf::Message::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kCustomAnimationTimespanFieldNumber = 7,
    kIncludeInstancePercentageFieldNumber = 2,
    kIgnoreSmallObjectPercentageFieldNumber = 3,
    kMergeScatterInstancesFieldNumber = 1,
    kExportAnimationFieldNumber = 4,
    kEnableCustomAnimationTimespanFieldNumber = 6,
    kExportNestedReferenceGraphsFieldNumber = 8,
    kAnimationFramerateFieldNumber = 5,
  };
  // .octaneapi.TimeSpanT customAnimationTimespan = 7;
  bool has_customanimationtimespan() const;
  void clear_customanimationtimespan() ;
  const ::octaneapi::TimeSpanT& customanimationtimespan() const;
  PROTOBUF_NODISCARD ::octaneapi::TimeSpanT* release_customanimationtimespan();
  ::octaneapi::TimeSpanT* mutable_customanimationtimespan();
  void set_allocated_customanimationtimespan(::octaneapi::TimeSpanT* value);
  void unsafe_arena_set_allocated_customanimationtimespan(::octaneapi::TimeSpanT* value);
  ::octaneapi::TimeSpanT* unsafe_arena_release_customanimationtimespan();

  private:
  const ::octaneapi::TimeSpanT& _internal_customanimationtimespan() const;
  ::octaneapi::TimeSpanT* _internal_mutable_customanimationtimespan();

  public:
  // float includeInstancePercentage = 2;
  void clear_includeinstancepercentage() ;
  float includeinstancepercentage() const;
  void set_includeinstancepercentage(float value);

  private:
  float _internal_includeinstancepercentage() const;
  void _internal_set_includeinstancepercentage(float value);

  public:
  // float ignoreSmallObjectPercentage = 3;
  void clear_ignoresmallobjectpercentage() ;
  float ignoresmallobjectpercentage() const;
  void set_ignoresmallobjectpercentage(float value);

  private:
  float _internal_ignoresmallobjectpercentage() const;
  void _internal_set_ignoresmallobjectpercentage(float value);

  public:
  // bool mergeScatterInstances = 1;
  void clear_mergescatterinstances() ;
  bool mergescatterinstances() const;
  void set_mergescatterinstances(bool value);

  private:
  bool _internal_mergescatterinstances() const;
  void _internal_set_mergescatterinstances(bool value);

  public:
  // bool exportAnimation = 4;
  void clear_exportanimation() ;
  bool exportanimation() const;
  void set_exportanimation(bool value);

  private:
  bool _internal_exportanimation() const;
  void _internal_set_exportanimation(bool value);

  public:
  // bool enableCustomAnimationTimespan = 6;
  void clear_enablecustomanimationtimespan() ;
  bool enablecustomanimationtimespan() const;
  void set_enablecustomanimationtimespan(bool value);

  private:
  bool _internal_enablecustomanimationtimespan() const;
  void _internal_set_enablecustomanimationtimespan(bool value);

  public:
  // bool exportNestedReferenceGraphs = 8;
  void clear_exportnestedreferencegraphs() ;
  bool exportnestedreferencegraphs() const;
  void set_exportnestedreferencegraphs(bool value);

  private:
  bool _internal_exportnestedreferencegraphs() const;
  void _internal_set_exportnestedreferencegraphs(bool value);

  public:
  // float animationFramerate = 5;
  void clear_animationframerate() ;
  float animationframerate() const;
  void set_animationframerate(float value);

  private:
  float _internal_animationframerate() const;
  void _internal_set_animationframerate(float value);

  public:
  // @@protoc_insertion_point(class_scope:octaneapi.ReferencePackageExportSettings)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      3, 8, 1,
      0, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_ReferencePackageExportSettings_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const ReferencePackageExportSettings& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::octaneapi::TimeSpanT* customanimationtimespan_;
    float includeinstancepercentage_;
    float ignoresmallobjectpercentage_;
    bool mergescatterinstances_;
    bool exportanimation_;
    bool enablecustomanimationtimespan_;
    bool exportnestedreferencegraphs_;
    float animationframerate_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_octanereferenceexport_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ReferencePackageExportSettings

// bool mergeScatterInstances = 1;
inline void ReferencePackageExportSettings::clear_mergescatterinstances() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.mergescatterinstances_ = false;
}
inline bool ReferencePackageExportSettings::mergescatterinstances() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.mergeScatterInstances)
  return _internal_mergescatterinstances();
}
inline void ReferencePackageExportSettings::set_mergescatterinstances(bool value) {
  _internal_set_mergescatterinstances(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.mergeScatterInstances)
}
inline bool ReferencePackageExportSettings::_internal_mergescatterinstances() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.mergescatterinstances_;
}
inline void ReferencePackageExportSettings::_internal_set_mergescatterinstances(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.mergescatterinstances_ = value;
}

// float includeInstancePercentage = 2;
inline void ReferencePackageExportSettings::clear_includeinstancepercentage() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.includeinstancepercentage_ = 0;
}
inline float ReferencePackageExportSettings::includeinstancepercentage() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.includeInstancePercentage)
  return _internal_includeinstancepercentage();
}
inline void ReferencePackageExportSettings::set_includeinstancepercentage(float value) {
  _internal_set_includeinstancepercentage(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.includeInstancePercentage)
}
inline float ReferencePackageExportSettings::_internal_includeinstancepercentage() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.includeinstancepercentage_;
}
inline void ReferencePackageExportSettings::_internal_set_includeinstancepercentage(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.includeinstancepercentage_ = value;
}

// float ignoreSmallObjectPercentage = 3;
inline void ReferencePackageExportSettings::clear_ignoresmallobjectpercentage() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.ignoresmallobjectpercentage_ = 0;
}
inline float ReferencePackageExportSettings::ignoresmallobjectpercentage() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.ignoreSmallObjectPercentage)
  return _internal_ignoresmallobjectpercentage();
}
inline void ReferencePackageExportSettings::set_ignoresmallobjectpercentage(float value) {
  _internal_set_ignoresmallobjectpercentage(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.ignoreSmallObjectPercentage)
}
inline float ReferencePackageExportSettings::_internal_ignoresmallobjectpercentage() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.ignoresmallobjectpercentage_;
}
inline void ReferencePackageExportSettings::_internal_set_ignoresmallobjectpercentage(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.ignoresmallobjectpercentage_ = value;
}

// bool exportAnimation = 4;
inline void ReferencePackageExportSettings::clear_exportanimation() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.exportanimation_ = false;
}
inline bool ReferencePackageExportSettings::exportanimation() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.exportAnimation)
  return _internal_exportanimation();
}
inline void ReferencePackageExportSettings::set_exportanimation(bool value) {
  _internal_set_exportanimation(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.exportAnimation)
}
inline bool ReferencePackageExportSettings::_internal_exportanimation() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.exportanimation_;
}
inline void ReferencePackageExportSettings::_internal_set_exportanimation(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.exportanimation_ = value;
}

// float animationFramerate = 5;
inline void ReferencePackageExportSettings::clear_animationframerate() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.animationframerate_ = 0;
}
inline float ReferencePackageExportSettings::animationframerate() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.animationFramerate)
  return _internal_animationframerate();
}
inline void ReferencePackageExportSettings::set_animationframerate(float value) {
  _internal_set_animationframerate(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.animationFramerate)
}
inline float ReferencePackageExportSettings::_internal_animationframerate() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.animationframerate_;
}
inline void ReferencePackageExportSettings::_internal_set_animationframerate(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.animationframerate_ = value;
}

// bool enableCustomAnimationTimespan = 6;
inline void ReferencePackageExportSettings::clear_enablecustomanimationtimespan() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.enablecustomanimationtimespan_ = false;
}
inline bool ReferencePackageExportSettings::enablecustomanimationtimespan() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.enableCustomAnimationTimespan)
  return _internal_enablecustomanimationtimespan();
}
inline void ReferencePackageExportSettings::set_enablecustomanimationtimespan(bool value) {
  _internal_set_enablecustomanimationtimespan(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.enableCustomAnimationTimespan)
}
inline bool ReferencePackageExportSettings::_internal_enablecustomanimationtimespan() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.enablecustomanimationtimespan_;
}
inline void ReferencePackageExportSettings::_internal_set_enablecustomanimationtimespan(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.enablecustomanimationtimespan_ = value;
}

// .octaneapi.TimeSpanT customAnimationTimespan = 7;
inline bool ReferencePackageExportSettings::has_customanimationtimespan() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.customanimationtimespan_ != nullptr);
  return value;
}
inline const ::octaneapi::TimeSpanT& ReferencePackageExportSettings::_internal_customanimationtimespan() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  const ::octaneapi::TimeSpanT* p = _impl_.customanimationtimespan_;
  return p != nullptr ? *p : reinterpret_cast<const ::octaneapi::TimeSpanT&>(::octaneapi::_TimeSpanT_default_instance_);
}
inline const ::octaneapi::TimeSpanT& ReferencePackageExportSettings::customanimationtimespan() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.customAnimationTimespan)
  return _internal_customanimationtimespan();
}
inline void ReferencePackageExportSettings::unsafe_arena_set_allocated_customanimationtimespan(::octaneapi::TimeSpanT* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.customanimationtimespan_);
  }
  _impl_.customanimationtimespan_ = reinterpret_cast<::octaneapi::TimeSpanT*>(value);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:octaneapi.ReferencePackageExportSettings.customAnimationTimespan)
}
inline ::octaneapi::TimeSpanT* ReferencePackageExportSettings::release_customanimationtimespan() {
  ::google::protobuf::internal::TSanWrite(&_impl_);

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::octaneapi::TimeSpanT* released = _impl_.customanimationtimespan_;
  _impl_.customanimationtimespan_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old = reinterpret_cast<::google::protobuf::MessageLite*>(released);
  released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  if (GetArena() == nullptr) {
    delete old;
  }
#else   // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArena() != nullptr) {
    released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return released;
}
inline ::octaneapi::TimeSpanT* ReferencePackageExportSettings::unsafe_arena_release_customanimationtimespan() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:octaneapi.ReferencePackageExportSettings.customAnimationTimespan)

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::octaneapi::TimeSpanT* temp = _impl_.customanimationtimespan_;
  _impl_.customanimationtimespan_ = nullptr;
  return temp;
}
inline ::octaneapi::TimeSpanT* ReferencePackageExportSettings::_internal_mutable_customanimationtimespan() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.customanimationtimespan_ == nullptr) {
    auto* p = ::google::protobuf::Message::DefaultConstruct<::octaneapi::TimeSpanT>(GetArena());
    _impl_.customanimationtimespan_ = reinterpret_cast<::octaneapi::TimeSpanT*>(p);
  }
  return _impl_.customanimationtimespan_;
}
inline ::octaneapi::TimeSpanT* ReferencePackageExportSettings::mutable_customanimationtimespan() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  _impl_._has_bits_[0] |= 0x00000001u;
  ::octaneapi::TimeSpanT* _msg = _internal_mutable_customanimationtimespan();
  // @@protoc_insertion_point(field_mutable:octaneapi.ReferencePackageExportSettings.customAnimationTimespan)
  return _msg;
}
inline void ReferencePackageExportSettings::set_allocated_customanimationtimespan(::octaneapi::TimeSpanT* value) {
  ::google::protobuf::Arena* message_arena = GetArena();
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (message_arena == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.customanimationtimespan_);
  }

  if (value != nullptr) {
    ::google::protobuf::Arena* submessage_arena = reinterpret_cast<::google::protobuf::MessageLite*>(value)->GetArena();
    if (message_arena != submessage_arena) {
      value = ::google::protobuf::internal::GetOwnedMessage(message_arena, value, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }

  _impl_.customanimationtimespan_ = reinterpret_cast<::octaneapi::TimeSpanT*>(value);
  // @@protoc_insertion_point(field_set_allocated:octaneapi.ReferencePackageExportSettings.customAnimationTimespan)
}

// bool exportNestedReferenceGraphs = 8;
inline void ReferencePackageExportSettings::clear_exportnestedreferencegraphs() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.exportnestedreferencegraphs_ = false;
}
inline bool ReferencePackageExportSettings::exportnestedreferencegraphs() const {
  // @@protoc_insertion_point(field_get:octaneapi.ReferencePackageExportSettings.exportNestedReferenceGraphs)
  return _internal_exportnestedreferencegraphs();
}
inline void ReferencePackageExportSettings::set_exportnestedreferencegraphs(bool value) {
  _internal_set_exportnestedreferencegraphs(value);
  // @@protoc_insertion_point(field_set:octaneapi.ReferencePackageExportSettings.exportNestedReferenceGraphs)
}
inline bool ReferencePackageExportSettings::_internal_exportnestedreferencegraphs() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.exportnestedreferencegraphs_;
}
inline void ReferencePackageExportSettings::_internal_set_exportnestedreferencegraphs(bool value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.exportnestedreferencegraphs_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace octaneapi


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_octanereferenceexport_2eproto_2epb_2eh
