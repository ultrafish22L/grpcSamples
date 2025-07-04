// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: control.proto
// Protobuf C++ Version: 5.28.3

#include "control.pb.h"

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

inline constexpr ApiControl_StartBlockingRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : uniquemoduleid_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        message_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ApiControl_StartBlockingRequest::ApiControl_StartBlockingRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ApiControl_StartBlockingRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiControl_StartBlockingRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiControl_StartBlockingRequestDefaultTypeInternal() {}
  union {
    ApiControl_StartBlockingRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiControl_StartBlockingRequestDefaultTypeInternal _ApiControl_StartBlockingRequest_default_instance_;

inline constexpr ApiControl_ControlResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : success_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ApiControl_ControlResponse::ApiControl_ControlResponse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ApiControl_ControlResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiControl_ControlResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiControl_ControlResponseDefaultTypeInternal() {}
  union {
    ApiControl_ControlResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiControl_ControlResponseDefaultTypeInternal _ApiControl_ControlResponse_default_instance_;

inline constexpr ApiControl_ApiLogRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : filepath_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        savetotextfile_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ApiControl_ApiLogRequest::ApiControl_ApiLogRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ApiControl_ApiLogRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiControl_ApiLogRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiControl_ApiLogRequestDefaultTypeInternal() {}
  union {
    ApiControl_ApiLogRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiControl_ApiLogRequestDefaultTypeInternal _ApiControl_ApiLogRequest_default_instance_;
              template <typename>
PROTOBUF_CONSTEXPR ApiControl::ApiControl(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(_class_data_.base()){}
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase() {
}
#endif  // PROTOBUF_CUSTOM_VTABLE
struct ApiControlDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ApiControlDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ApiControlDefaultTypeInternal() {}
  union {
    ApiControl _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ApiControlDefaultTypeInternal _ApiControl_default_instance_;
}  // namespace octaneapi
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_control_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_control_2eproto = nullptr;
const ::uint32_t
    TableStruct_control_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_StartBlockingRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_StartBlockingRequest, _impl_.uniquemoduleid_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_StartBlockingRequest, _impl_.message_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_ApiLogRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_ApiLogRequest, _impl_.savetotextfile_),
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_ApiLogRequest, _impl_.filepath_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_ControlResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl_ControlResponse, _impl_.success_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::octaneapi::ApiControl, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::octaneapi::ApiControl_StartBlockingRequest)},
        {10, -1, -1, sizeof(::octaneapi::ApiControl_ApiLogRequest)},
        {20, -1, -1, sizeof(::octaneapi::ApiControl_ControlResponse)},
        {29, -1, -1, sizeof(::octaneapi::ApiControl)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::octaneapi::_ApiControl_StartBlockingRequest_default_instance_._instance,
    &::octaneapi::_ApiControl_ApiLogRequest_default_instance_._instance,
    &::octaneapi::_ApiControl_ControlResponse_default_instance_._instance,
    &::octaneapi::_ApiControl_default_instance_._instance,
};
const char descriptor_table_protodef_control_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\rcontrol.proto\022\toctaneapi\"\254\001\n\nApiContro"
    "l\032\?\n\024StartBlockingRequest\022\026\n\016uniqueModul"
    "eId\030\001 \001(\t\022\017\n\007message\030\002 \001(\t\0329\n\rApiLogRequ"
    "est\022\026\n\016saveToTextFile\030\001 \001(\010\022\020\n\010filePath\030"
    "\002 \001(\t\032\"\n\017ControlResponse\022\017\n\007success\030\001 \001("
    "\0102\341\001\n\021ApiControlService\022k\n\026startBlocking"
    "Operation\022*.octaneapi.ApiControl.StartBl"
    "ockingRequest\032%.octaneapi.ApiControl.Con"
    "trolResponse\022_\n\021setApiLogFilePath\022#.octa"
    "neapi.ApiControl.ApiLogRequest\032%.octanea"
    "pi.ApiControl.ControlResponseB\002H\002b\006proto"
    "3"
};
static ::absl::once_flag descriptor_table_control_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_control_2eproto = {
    false,
    false,
    441,
    descriptor_table_protodef_control_2eproto,
    "control.proto",
    &descriptor_table_control_2eproto_once,
    nullptr,
    0,
    4,
    schemas,
    file_default_instances,
    TableStruct_control_2eproto::offsets,
    file_level_enum_descriptors_control_2eproto,
    file_level_service_descriptors_control_2eproto,
};
namespace octaneapi {
// ===================================================================

class ApiControl_StartBlockingRequest::_Internal {
 public:
};

ApiControl_StartBlockingRequest::ApiControl_StartBlockingRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiControl.StartBlockingRequest)
}
inline PROTOBUF_NDEBUG_INLINE ApiControl_StartBlockingRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::octaneapi::ApiControl_StartBlockingRequest& from_msg)
      : uniquemoduleid_(arena, from.uniquemoduleid_),
        message_(arena, from.message_),
        _cached_size_{0} {}

ApiControl_StartBlockingRequest::ApiControl_StartBlockingRequest(
    ::google::protobuf::Arena* arena,
    const ApiControl_StartBlockingRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ApiControl_StartBlockingRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:octaneapi.ApiControl.StartBlockingRequest)
}
inline PROTOBUF_NDEBUG_INLINE ApiControl_StartBlockingRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : uniquemoduleid_(arena),
        message_(arena),
        _cached_size_{0} {}

inline void ApiControl_StartBlockingRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
ApiControl_StartBlockingRequest::~ApiControl_StartBlockingRequest() {
  // @@protoc_insertion_point(destructor:octaneapi.ApiControl.StartBlockingRequest)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void ApiControl_StartBlockingRequest::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.uniquemoduleid_.Destroy();
  _impl_.message_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiControl_StartBlockingRequest::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_ApiControl_StartBlockingRequest_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiControl_StartBlockingRequest::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<ApiControl_StartBlockingRequest>(),
            ::google::protobuf::Message::GetNewImpl<ApiControl_StartBlockingRequest>(),
            ::google::protobuf::Message::ClearImpl, ::google::protobuf::Message::ByteSizeLongImpl,
                ::google::protobuf::Message::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiControl_StartBlockingRequest, _impl_._cached_size_),
            false,
        },
        &ApiControl_StartBlockingRequest::kDescriptorMethods,
        &descriptor_table_control_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiControl_StartBlockingRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 71, 2> ApiControl_StartBlockingRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::octaneapi::ApiControl_StartBlockingRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string message = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(ApiControl_StartBlockingRequest, _impl_.message_)}},
    // string uniqueModuleId = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(ApiControl_StartBlockingRequest, _impl_.uniquemoduleid_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string uniqueModuleId = 1;
    {PROTOBUF_FIELD_OFFSET(ApiControl_StartBlockingRequest, _impl_.uniquemoduleid_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string message = 2;
    {PROTOBUF_FIELD_OFFSET(ApiControl_StartBlockingRequest, _impl_.message_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\51\16\7\0\0\0\0\0"
    "octaneapi.ApiControl.StartBlockingRequest"
    "uniqueModuleId"
    "message"
  }},
};

void ApiControl_StartBlockingRequest::InternalSwap(ApiControl_StartBlockingRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::google::protobuf::Metadata ApiControl_StartBlockingRequest::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ApiControl_ApiLogRequest::_Internal {
 public:
};

ApiControl_ApiLogRequest::ApiControl_ApiLogRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiControl.ApiLogRequest)
}
inline PROTOBUF_NDEBUG_INLINE ApiControl_ApiLogRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::octaneapi::ApiControl_ApiLogRequest& from_msg)
      : filepath_(arena, from.filepath_),
        _cached_size_{0} {}

ApiControl_ApiLogRequest::ApiControl_ApiLogRequest(
    ::google::protobuf::Arena* arena,
    const ApiControl_ApiLogRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ApiControl_ApiLogRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  _impl_.savetotextfile_ = from._impl_.savetotextfile_;

  // @@protoc_insertion_point(copy_constructor:octaneapi.ApiControl.ApiLogRequest)
}
inline PROTOBUF_NDEBUG_INLINE ApiControl_ApiLogRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : filepath_(arena),
        _cached_size_{0} {}

inline void ApiControl_ApiLogRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.savetotextfile_ = {};
}
ApiControl_ApiLogRequest::~ApiControl_ApiLogRequest() {
  // @@protoc_insertion_point(destructor:octaneapi.ApiControl.ApiLogRequest)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void ApiControl_ApiLogRequest::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.filepath_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiControl_ApiLogRequest::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_ApiControl_ApiLogRequest_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiControl_ApiLogRequest::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<ApiControl_ApiLogRequest>(),
            ::google::protobuf::Message::GetNewImpl<ApiControl_ApiLogRequest>(),
            ::google::protobuf::Message::ClearImpl, ::google::protobuf::Message::ByteSizeLongImpl,
                ::google::protobuf::Message::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiControl_ApiLogRequest, _impl_._cached_size_),
            false,
        },
        &ApiControl_ApiLogRequest::kDescriptorMethods,
        &descriptor_table_control_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiControl_ApiLogRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 51, 2> ApiControl_ApiLogRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::octaneapi::ApiControl_ApiLogRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string filePath = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(ApiControl_ApiLogRequest, _impl_.filepath_)}},
    // bool saveToTextFile = 1;
    {::_pbi::TcParser::FastV8S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(ApiControl_ApiLogRequest, _impl_.savetotextfile_)}},
  }}, {{
    65535, 65535
  }}, {{
    // bool saveToTextFile = 1;
    {PROTOBUF_FIELD_OFFSET(ApiControl_ApiLogRequest, _impl_.savetotextfile_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
    // string filePath = 2;
    {PROTOBUF_FIELD_OFFSET(ApiControl_ApiLogRequest, _impl_.filepath_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\42\0\10\0\0\0\0\0"
    "octaneapi.ApiControl.ApiLogRequest"
    "filePath"
  }},
};

void ApiControl_ApiLogRequest::InternalSwap(ApiControl_ApiLogRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::google::protobuf::Metadata ApiControl_ApiLogRequest::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ApiControl_ControlResponse::_Internal {
 public:
};

ApiControl_ControlResponse::ApiControl_ControlResponse(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiControl.ControlResponse)
}
ApiControl_ControlResponse::ApiControl_ControlResponse(
    ::google::protobuf::Arena* arena, const ApiControl_ControlResponse& from)
    : ApiControl_ControlResponse(arena) {
  MergeFrom(from);
}
inline PROTOBUF_NDEBUG_INLINE ApiControl_ControlResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void ApiControl_ControlResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.success_ = {};
}
ApiControl_ControlResponse::~ApiControl_ControlResponse() {
  // @@protoc_insertion_point(destructor:octaneapi.ApiControl.ControlResponse)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void ApiControl_ControlResponse::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiControl_ControlResponse::_class_data_ = {
        ::google::protobuf::Message::ClassData{
            &_ApiControl_ControlResponse_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiControl_ControlResponse::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::Message::GetDeleteImpl<ApiControl_ControlResponse>(),
            ::google::protobuf::Message::GetNewImpl<ApiControl_ControlResponse>(),
            ::google::protobuf::Message::ClearImpl, ::google::protobuf::Message::ByteSizeLongImpl,
                ::google::protobuf::Message::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiControl_ControlResponse, _impl_._cached_size_),
            false,
        },
        &ApiControl_ControlResponse::kDescriptorMethods,
        &descriptor_table_control_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiControl_ControlResponse::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 0, 2> ApiControl_ControlResponse::_table_ = {
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
    ::_pbi::TcParser::GetTable<::octaneapi::ApiControl_ControlResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // bool success = 1;
    {::_pbi::TcParser::FastV8S1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(ApiControl_ControlResponse, _impl_.success_)}},
  }}, {{
    65535, 65535
  }}, {{
    // bool success = 1;
    {PROTOBUF_FIELD_OFFSET(ApiControl_ControlResponse, _impl_.success_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
  }},
  // no aux_entries
  {{
  }},
};

void ApiControl_ControlResponse::InternalSwap(ApiControl_ControlResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  GetReflection()->Swap(this, other);}

::google::protobuf::Metadata ApiControl_ControlResponse::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ApiControl::_Internal {
 public:
};

ApiControl::ApiControl(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(arena_constructor:octaneapi.ApiControl)
}
ApiControl::ApiControl(
    ::google::protobuf::Arena* arena,
    const ApiControl& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::internal::ZeroFieldsBase(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ApiControl* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);

  // @@protoc_insertion_point(copy_constructor:octaneapi.ApiControl)
}

PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::MessageLite::ClassDataFull
    ApiControl::_class_data_ = {
        ::google::protobuf::internal::ZeroFieldsBase::ClassData{
            &_ApiControl_default_instance_._instance,
            &_table_.header,
            nullptr,  // OnDemandRegisterArenaDtor
            nullptr,  // IsInitialized
            &ApiControl::MergeImpl,
#if defined(PROTOBUF_CUSTOM_VTABLE)
            ::google::protobuf::internal::ZeroFieldsBase::GetDeleteImpl<ApiControl>(),
            ::google::protobuf::internal::ZeroFieldsBase::GetNewImpl<ApiControl>(),
            ::google::protobuf::internal::ZeroFieldsBase::ClearImpl, ::google::protobuf::internal::ZeroFieldsBase::ByteSizeLongImpl,
                ::google::protobuf::internal::ZeroFieldsBase::_InternalSerializeImpl,
#endif  // PROTOBUF_CUSTOM_VTABLE
            PROTOBUF_FIELD_OFFSET(ApiControl, _impl_._cached_size_),
            false,
        },
        &ApiControl::kDescriptorMethods,
        &descriptor_table_control_2eproto,
        nullptr,  // tracker
};
const ::google::protobuf::MessageLite::ClassData* ApiControl::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 0, 0, 0, 2> ApiControl::_table_ = {
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
    ::_pbi::TcParser::GetTable<::octaneapi::ApiControl>(),  // to_prefetch
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


::google::protobuf::Metadata ApiControl::GetMetadata() const {
  return ::google::protobuf::internal::ZeroFieldsBase::GetMetadataImpl(GetClassData()->full());
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
        (::_pbi::AddDescriptors(&descriptor_table_control_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
