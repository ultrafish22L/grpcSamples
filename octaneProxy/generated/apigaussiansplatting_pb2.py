# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apigaussiansplatting.proto
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
    'apigaussiansplatting.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1a\x61pigaussiansplatting.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\"\x86\x08\n\x19\x41piGaussianSplatCloudNode\x1a\x39\n\rcreateRequest\x12(\n\nownerGraph\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x36\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x33\n\robtainRequest\x12\"\n\x04node\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x36\n\x0eobtainResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\xd8\x05\n\x1bsetAttributesFromPlyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x16\n\x0enumberOfPoints\x18\x02 \x01(\r\x12!\n\x01x\x18\x03 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12!\n\x01y\x18\x04 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12!\n\x01z\x18\x05 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12\'\n\x07opacity\x18\x06 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12&\n\x06scale0\x18\x07 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12&\n\x06scale1\x18\x08 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12&\n\x06scale2\x18\t \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12$\n\x04rot0\x18\n \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12$\n\x04rot1\x18\x0b \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12$\n\x04rot2\x18\x0c \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12$\n\x04rot3\x18\r \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12#\n\x03\x64\x63\x30\x18\x0e \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12#\n\x03\x64\x63\x31\x18\x0f \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12#\n\x03\x64\x63\x32\x18\x10 \x01(\x0b\x32\x16.octaneapi.FloatArrayT\x12\x1e\n\x16numberOfRestAttributes\x18\x11 \x01(\r\x12\x35\n\x15restAttributePointers\x18\x12 \x03(\x0b\x32\x16.octaneapi.FloatArrayT\x12\x10\n\x08\x65valuate\x18\x13 \x01(\x08\x1a.\n\x1csetAttributesFromPlyResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x32\xa6\x03\n ApiGaussianSplatCloudNodeService\x12q\n\x06\x63reate\x12\x32.octaneapi.ApiGaussianSplatCloudNode.createRequest\x1a\x33.octaneapi.ApiGaussianSplatCloudNode.createResponse\x12q\n\x06obtain\x12\x32.octaneapi.ApiGaussianSplatCloudNode.obtainRequest\x1a\x33.octaneapi.ApiGaussianSplatCloudNode.obtainResponse\x12\x9b\x01\n\x14setAttributesFromPly\x12@.octaneapi.ApiGaussianSplatCloudNode.setAttributesFromPlyRequest\x1a\x41.octaneapi.ApiGaussianSplatCloudNode.setAttributesFromPlyResponseB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apigaussiansplatting_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APIGAUSSIANSPLATCLOUDNODE']._serialized_start=56
  _globals['_APIGAUSSIANSPLATCLOUDNODE']._serialized_end=1086
  _globals['_APIGAUSSIANSPLATCLOUDNODE_CREATEREQUEST']._serialized_start=85
  _globals['_APIGAUSSIANSPLATCLOUDNODE_CREATEREQUEST']._serialized_end=142
  _globals['_APIGAUSSIANSPLATCLOUDNODE_CREATERESPONSE']._serialized_start=144
  _globals['_APIGAUSSIANSPLATCLOUDNODE_CREATERESPONSE']._serialized_end=198
  _globals['_APIGAUSSIANSPLATCLOUDNODE_OBTAINREQUEST']._serialized_start=200
  _globals['_APIGAUSSIANSPLATCLOUDNODE_OBTAINREQUEST']._serialized_end=251
  _globals['_APIGAUSSIANSPLATCLOUDNODE_OBTAINRESPONSE']._serialized_start=253
  _globals['_APIGAUSSIANSPLATCLOUDNODE_OBTAINRESPONSE']._serialized_end=307
  _globals['_APIGAUSSIANSPLATCLOUDNODE_SETATTRIBUTESFROMPLYREQUEST']._serialized_start=310
  _globals['_APIGAUSSIANSPLATCLOUDNODE_SETATTRIBUTESFROMPLYREQUEST']._serialized_end=1038
  _globals['_APIGAUSSIANSPLATCLOUDNODE_SETATTRIBUTESFROMPLYRESPONSE']._serialized_start=1040
  _globals['_APIGAUSSIANSPLATCLOUDNODE_SETATTRIBUTESFROMPLYRESPONSE']._serialized_end=1086
  _globals['_APIGAUSSIANSPLATCLOUDNODESERVICE']._serialized_start=1089
  _globals['_APIGAUSSIANSPLATCLOUDNODESERVICE']._serialized_end=1511
# @@protoc_insertion_point(module_scope)
