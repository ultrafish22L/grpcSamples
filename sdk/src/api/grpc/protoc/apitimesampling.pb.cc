// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: apitimesampling.proto
// Protobuf C++ Version: 5.28.3

#include "apitimesampling.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace octaneapi {

inline constexpr ApiTimeSampling_endTimeAutoResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : result_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ApiTimeSampling_endTimeAutoResponse::ApiTimeSampling_endTimeAutoResponse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ApiTimeSampling_endTimeAutoResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiTimeSampling_endTimeAutoResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiTimeSampling_endTimeAutoResponseDefaultTypeInternal() {}
  union {
    ApiTimeSampling_endTimeAutoResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiTimeSampling_endTimeAutoResponseDefaultTypeInternal _ApiTimeSampling_endTimeAutoResponse_default_instance_;
              template <typename>
PROTOBUF_CONSTEXPR ApiTimeSampling_endTimeAutoRequest::ApiTimeSampling_endTimeAutoRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(_class_data_.base()){}
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase() {
}
#endif  // PROTOBUF_CUSTOM_VTABLE
struct ApiTimeSampling_endTimeAutoRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiTimeSampling_endTimeAutoRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiTimeSampling_endTimeAutoRequestDefaultTypeInternal() {}
  union {
    ApiTimeSampling_endTimeAutoRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiTimeSampling_endTimeAutoRequestDefaultTypeInternal _ApiTimeSampling_endTimeAutoRequest_default_instance_;

inline constexpr ApiTimeSampling::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        pattern_{nullptr},
        period_{nullptr},
        endtime_{nullptr},
        patternsize_{0u},
        animationtype_{static_cast< ::octaneapi::AnimationType >(0)} {}

template <typename>
PROTOBUF_CONSTEXPR ApiTimeSampling::ApiTimeSampling(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ApiTimeSamplingDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiTimeSamplingDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiTimeSamplingDefaultTypeInternal() {}
  union {
    ApiTimeSampling _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiTimeSamplingDefaultTypeInternal _ApiTimeSampling_default_instance_;
}  // namespace octaneapi
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_apitimesampling_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_apitimesampling_2eproto = nullptr;
const ::uint32_t
    TableStruct_apitimesampling_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling_endTimeAutoRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling_endTimeAutoResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling_endTimeAutoResponse, _impl_.result_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_.pattern_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_.patternsize_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_.period_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_.animationtype_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiTimeSampling, _impl_.endtime_),
        0,
        ~0u,
        1,
        ~0u,
        2,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::octaneapi::ApiTimeSampling_endTimeAutoRequest)},
        {8, -1, -1, sizeof(::octaneapi::ApiTimeSampling_endTimeAutoResponse)},
        {17, 30, -1, sizeof(::octaneapi::ApiTimeSampling)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::octaneapi::_ApiTimeSampling_endTimeAutoRequest_default_instance_._instance,
    &::octaneapi::_ApiTimeSampling_endTimeAutoResponse_default_instance_._instance,
    &::octaneapi::_ApiTimeSampling_default_instance_._instance,
};
const char descriptor_table_protodef_apitimesampling_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\025apitimesampling.proto\022\toctaneapi\032\014comm"
    "on.proto\032\021octaneenums.proto\"\201\002\n\017ApiTimeS"
    "ampling\022&\n\007pattern\030\001 \001(\0132\025.octaneapi.Tim"
    "eArrayT\022\023\n\013patternSize\030\002 \001(\r\022 \n\006period\030\003"
    " \001(\0132\020.octaneapi.TimeT\022/\n\ranimationType\030"
    "\004 \001(\0162\030.octaneapi.AnimationType\022!\n\007endTi"
    "me\030\005 \001(\0132\020.octaneapi.TimeT\032\024\n\022endTimeAut"
    "oRequest\032%\n\023endTimeAutoResponse\022\016\n\006resul"
    "t\030\001 \001(\0022\206\001\n\026ApiTimeSamplingService\022l\n\013en"
    "dTimeAuto\022-.octaneapi.ApiTimeSampling.en"
    "dTimeAutoRequest\032..octaneapi.ApiTimeSamp"
    "ling.endTimeAutoResponseB\002H\002b\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_apitimesampling_2eproto_deps[2] =
    {
        &::descriptor_table_common_2eproto,
        &::descriptor_table_octaneenums_2eproto,
};
static ::absl::once_flag descriptor_table_apitimesampling_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_apitimesampling_2eproto = {
    false,
    false,
    476,
    descriptor_table_protodef_apitimesampling_2eproto,
    "apitimesampling.proto",
    &descriptor_table_apitimesampling_2eproto_once,
    descriptor_table_apitimesampling_2eproto_deps,
    2,
    3,
    schemas,
    file_default_instances,
    TableStruct_apitimesampling_2eproto::offsets,
    file_level_enum_descriptors_apitimesampling_2eproto,
    file_level_service_descriptors_apitimesampling_2eproto,
};
namespace octaneapi {
// ===================================================================

class ApiTimeSampling_endTimeAutoRequest::_Internal {
 public:
};

ApiTimeSampling_endTimeAutoRequest::ApiTimeSampling_endTimeAutoRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiTimeSampling.endTimeAutoRequest)
}
ApiTimeSampling_endTimeAutoRequest::ApiTimeSampling_endTimeAutoRequest(
    ::google::protobuf::Arena* arena,
    const ApiTimeSampling_endTimeAutoRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ApiTimeSampling_endTimeAutoRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);

  // @@protoc_insertion_point(copy_constructor:octaneapi.ApiTimeSampling.endTimeAutoRequest)
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiTimeSampling_endTimeAutoRequest::_class_data_ = {
        ::google::protobuf::internal::ZeroFieldsBase::ClassData{
            &_ApiTimeSampling_endTimeAutoRequest_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiTimeSampling_endTimeAutoRequest::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::internal::ZeroFieldsBase::GetDeleteImpl<ApiTimeSampling_endTimeAutoRequest>(),
            ::google::protobuf::internal::ZeroFieldsBase::GetNewImpl<ApiTimeSampling_endTimeAutoRequest>(),
            ::google::protobuf::internal::ZeroFieldsBase::ClearImpl, ::google::protobuf::internal::ZeroFieldsBase::ByteSizeLongImpl,
                ::google::protobuf::internal::ZeroFieldsBase::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiTimeSampling_endTimeAutoRequest, _impl_._cached_size_),
            false,
        },
        &ApiTimeSampling_endTimeAutoRequest::kDescriptorMethods,
        &descriptor_table_apitimesampling_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiTimeSampling_endTimeAutoRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 0, 0, 0, 2> ApiTimeSampling_endTimeAutoRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    0, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967295,  // skipmap
    offsetof(decltype(_table_), field_names),  // no field_entries
    0,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::octaneapi::ApiTimeSampling_endTimeAutoRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }},
  // no field_entries, or aux_entries
  {{
  }},
};


::google::protobuf::Metadata ApiTimeSampling_endTimeAutoRequest::GetMetadata() const {
  return ::google::protobuf::internal::ZeroFieldsBase::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ApiTimeSampling_endTimeAutoResponse::_Internal {
 public:
};

ApiTimeSampling_endTimeAutoResponse::ApiTimeSampling_endTimeAutoResponse(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiTimeSampling.endTimeAutoResponse)
}
ApiTimeSampling_endTimeAutoResponse::ApiTimeSampling_endTimeAutoResponse(
    ::google::protobuf::Arena* arena, const ApiTimeSampling_endTimeAutoResponse& from)
    : ApiTimeSampling_endTimeAutoResponse(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE ApiTimeSampling_endTimeAutoResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void ApiTimeSampling_endTimeAutoResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.result_ = {};
}
ApiTimeSampling_endTimeAutoResponse::~ApiTimeSampling_endTimeAutoResponse() {
  // @@protoc_insertion_point(destructor:octaneapi.ApiTimeSampling.endTimeAutoResponse)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void ApiTimeSampling_endTimeAutoResponse::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiTimeSampling_endTimeAutoResponse::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_ApiTimeSampling_endTimeAutoResponse_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiTimeSampling_endTimeAutoResponse::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<ApiTimeSampling_endTimeAutoResponse>(),
            ::google::protobuf::Message::GetNewImpl<ApiTimeSampling_endTimeAutoResponse>(),
            ::google::protobuf::Message::ClearImpl, ::google::protobuf::Message::ByteSizeLongImpl,
                ::google::protobuf::Message::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiTimeSampling_endTimeAutoResponse, _impl_._cached_size_),
            false,
        },
        &ApiTimeSampling_endTimeAutoResponse::kDescriptorMethods,
        &descriptor_table_apitimesampling_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiTimeSampling_endTimeAutoResponse::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 0, 2> ApiTimeSampling_endTimeAutoResponse::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::octaneapi::ApiTimeSampling_endTimeAutoResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // float result = 1;
    {::_pbi::TcParser::FastF32S1,
     {13, 63, 0, PROTOBUF_FIELD_OFFSET(ApiTimeSampling_endTimeAutoResponse, _impl_.result_)}},
  }}, {{
    65535, 65535
  }}, {{
    // float result = 1;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling_endTimeAutoResponse, _impl_.result_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kFloat)},
  }},
  // no aux_entries
  {{
  }},
};

void ApiTimeSampling_endTimeAutoResponse::InternalSwap(ApiTimeSampling_endTimeAutoResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::google::protobuf::Metadata ApiTimeSampling_endTimeAutoResponse::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ApiTimeSampling::_Internal {
 public:
  using HasBits =
      decltype(std::declval<ApiTimeSampling>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_._has_bits_);
};

void ApiTimeSampling::clear_pattern() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.pattern_ != nullptr) _impl_.pattern_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
void ApiTimeSampling::clear_period() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.period_ != nullptr) _impl_.period_->Clear();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
void ApiTimeSampling::clear_endtime() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.endtime_ != nullptr) _impl_.endtime_->Clear();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
ApiTimeSampling::ApiTimeSampling(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiTimeSampling)
}
inline PROTOBUF_NDEBUG_INLINE ApiTimeSampling::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::octaneapi::ApiTimeSampling& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

ApiTimeSampling::ApiTimeSampling(
    ::google::protobuf::Arena* arena,
    const ApiTimeSampling& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ApiTimeSampling* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.pattern_ = (cached_has_bits & 0x00000001u) ? ::google::protobuf::Message::CopyConstruct<::octaneapi::TimeArrayT>(
                              arena, *from._impl_.pattern_)
                        : nullptr;
  _impl_.period_ = (cached_has_bits & 0x00000002u) ? ::google::protobuf::Message::CopyConstruct<::octaneapi::TimeT>(
                              arena, *from._impl_.period_)
                        : nullptr;
  _impl_.endtime_ = (cached_has_bits & 0x00000004u) ? ::google::protobuf::Message::CopyConstruct<::octaneapi::TimeT>(
                              arena, *from._impl_.endtime_)
                        : nullptr;
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, patternsize_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, patternsize_),
           offsetof(Impl_, animationtype_) -
               offsetof(Impl_, patternsize_) +
               sizeof(Impl_::animationtype_));

  // @@protoc_insertion_point(copy_constructor:octaneapi.ApiTimeSampling)
}
inline PROTOBUF_NDEBUG_INLINE ApiTimeSampling::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void ApiTimeSampling::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, pattern_),
           0,
           offsetof(Impl_, animationtype_) -
               offsetof(Impl_, pattern_) +
               sizeof(Impl_::animationtype_));
}
ApiTimeSampling::~ApiTimeSampling() {
  // @@protoc_insertion_point(destructor:octaneapi.ApiTimeSampling)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void ApiTimeSampling::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.pattern_;
  delete _impl_.period_;
  delete _impl_.endtime_;
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiTimeSampling::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_ApiTimeSampling_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiTimeSampling::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<ApiTimeSampling>(),
            ::google::protobuf::Message::GetNewImpl<ApiTimeSampling>(),
            ::google::protobuf::Message::ClearImpl, ::google::protobuf::Message::ByteSizeLongImpl,
                ::google::protobuf::Message::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_._cached_size_),
            false,
        },
        &ApiTimeSampling::kDescriptorMethods,
        &descriptor_table_apitimesampling_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiTimeSampling::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<3, 5, 3, 0, 2> ApiTimeSampling::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_._has_bits_),
    0, // no _extensions_
    5, 56,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967264,  // skipmap
    offsetof(decltype(_table_), field_entries),
    5,  // num_field_entries
    3,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::octaneapi::ApiTimeSampling>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // .octaneapi.TimeArrayT pattern = 1;
    {::_pbi::TcParser::FastMtS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.pattern_)}},
    // uint32 patternSize = 2;
    {::_pbi::TcParser::FastV32S1,
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.patternsize_)}},
    // .octaneapi.TimeT period = 3;
    {::_pbi::TcParser::FastMtS1,
     {26, 1, 1, PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.period_)}},
    // .octaneapi.AnimationType animationType = 4;
    {::_pbi::TcParser::FastV32S1,
     {32, 63, 0, PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.animationtype_)}},
    // .octaneapi.TimeT endTime = 5;
    {::_pbi::TcParser::FastMtS1,
     {42, 2, 2, PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.endtime_)}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // .octaneapi.TimeArrayT pattern = 1;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.pattern_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // uint32 patternSize = 2;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.patternsize_), -1, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUInt32)},
    // .octaneapi.TimeT period = 3;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.period_), _Internal::kHasBitsOffset + 1, 1,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // .octaneapi.AnimationType animationType = 4;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.animationtype_), -1, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // .octaneapi.TimeT endTime = 5;
    {PROTOBUF_FIELD_OFFSET(ApiTimeSampling, _impl_.endtime_), _Internal::kHasBitsOffset + 2, 2,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::octaneapi::TimeArrayT>()},
    {::_pbi::TcParser::GetTable<::octaneapi::TimeT>()},
    {::_pbi::TcParser::GetTable<::octaneapi::TimeT>()},
  }}, {{
  }},
};

void ApiTimeSampling::InternalSwap(ApiTimeSampling* PROTOBUF_RESTRICT other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::google::protobuf::Metadata ApiTimeSampling::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace octaneapi
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_apitimesampling_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
