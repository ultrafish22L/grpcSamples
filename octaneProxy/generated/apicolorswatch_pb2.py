# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apicolorswatch.proto
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
    'apicolorswatch.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x14\x61picolorswatch.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\"\xe4\x03\n\x0e\x41piColorSwatch\x1av\n\rcreateRequest\x12\x1e\n\x16\x64isableGammaCorrection\x18\x01 \x01(\x08\x12\x30\n\x0e\x63hangeCallback\x18\x02 \x01(\x0b\x32\x18.octaneapi.ColorChangedT\x12\x13\n\x0bprivateData\x18\x03 \x01(\x04\x1aJ\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x12\n\ncallbackId\x18\x02 \x01(\r\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x61\n\x0fsetColorRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12%\n\x05\x63olor\x18\x02 \x01(\x0b\x32\x16.octaneapi.ApiColorHdr\x1a\x37\n\x0c\x63olorRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x37\n\rcolorResponse\x12&\n\x06result\x18\x01 \x01(\x0b\x32\x16.octaneapi.ApiColorHdr2\xea\x02\n\x15\x41piColorSwatchService\x12[\n\x06\x63reate\x12\'.octaneapi.ApiColorSwatch.createRequest\x1a(.octaneapi.ApiColorSwatch.createResponse\x12K\n\x07\x64\x65stroy\x12(.octaneapi.ApiColorSwatch.destroyRequest\x1a\x16.google.protobuf.Empty\x12M\n\x08setColor\x12).octaneapi.ApiColorSwatch.setColorRequest\x1a\x16.google.protobuf.Empty\x12X\n\x05\x63olor\x12&.octaneapi.ApiColorSwatch.colorRequest\x1a\'.octaneapi.ApiColorSwatch.colorResponseB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apicolorswatch_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APICOLORSWATCH']._serialized_start=79
  _globals['_APICOLORSWATCH']._serialized_end=563
  _globals['_APICOLORSWATCH_CREATEREQUEST']._serialized_start=97
  _globals['_APICOLORSWATCH_CREATEREQUEST']._serialized_end=215
  _globals['_APICOLORSWATCH_CREATERESPONSE']._serialized_start=217
  _globals['_APICOLORSWATCH_CREATERESPONSE']._serialized_end=291
  _globals['_APICOLORSWATCH_DESTROYREQUEST']._serialized_start=293
  _globals['_APICOLORSWATCH_DESTROYREQUEST']._serialized_end=350
  _globals['_APICOLORSWATCH_SETCOLORREQUEST']._serialized_start=352
  _globals['_APICOLORSWATCH_SETCOLORREQUEST']._serialized_end=449
  _globals['_APICOLORSWATCH_COLORREQUEST']._serialized_start=451
  _globals['_APICOLORSWATCH_COLORREQUEST']._serialized_end=506
  _globals['_APICOLORSWATCH_COLORRESPONSE']._serialized_start=508
  _globals['_APICOLORSWATCH_COLORRESPONSE']._serialized_end=563
  _globals['_APICOLORSWATCHSERVICE']._serialized_start=566
  _globals['_APICOLORSWATCHSERVICE']._serialized_end=928
# @@protoc_insertion_point(module_scope)
