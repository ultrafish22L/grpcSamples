# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apititlecomponent.proto
# Protobuf Python Version: 6.31.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import runtime_version as _runtime_version
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
_runtime_version.ValidateProtobufRuntimeVersion(
    _runtime_version.Domain.PUBLIC,
    6,
    31,
    1,
    '',
    'apititlecomponent.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x17\x61pititlecomponent.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\"\xa5\x01\n\x11\x41piTitleComponent\x1a\x1d\n\rcreateRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\x1a\x36\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef2\xcd\x01\n\x18\x41piTitleComponentService\x12\x61\n\x06\x63reate\x12*.octaneapi.ApiTitleComponent.createRequest\x1a+.octaneapi.ApiTitleComponent.createResponse\x12N\n\x07\x64\x65stroy\x12+.octaneapi.ApiTitleComponent.destroyRequest\x1a\x16.google.protobuf.EmptyB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apititlecomponent_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APITITLECOMPONENT']._serialized_start=82
  _globals['_APITITLECOMPONENT']._serialized_end=247
  _globals['_APITITLECOMPONENT_CREATEREQUEST']._serialized_start=103
  _globals['_APITITLECOMPONENT_CREATEREQUEST']._serialized_end=132
  _globals['_APITITLECOMPONENT_CREATERESPONSE']._serialized_start=134
  _globals['_APITITLECOMPONENT_CREATERESPONSE']._serialized_end=188
  _globals['_APITITLECOMPONENT_DESTROYREQUEST']._serialized_start=190
  _globals['_APITITLECOMPONENT_DESTROYREQUEST']._serialized_end=247
  _globals['_APITITLECOMPONENTSERVICE']._serialized_start=250
  _globals['_APITITLECOMPONENTSERVICE']._serialized_end=455
# @@protoc_insertion_point(module_scope)
