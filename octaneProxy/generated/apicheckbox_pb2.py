# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apicheckbox.proto
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
    'apicheckbox.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x11\x61picheckbox.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\"\xbb\x03\n\x0b\x41piCheckBox\x1a\x61\n\rcreateRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\x12-\n\x08\x63\x61llback\x18\x02 \x01(\x0b\x32\x1b.octaneapi.CheckedCallbackT\x12\x13\n\x0bprivateData\x18\x03 \x01(\x04\x1aJ\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x12\n\ncallbackId\x18\x02 \x01(\r\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a`\n\x11setCheckedRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0f\n\x07\x63hecked\x18\x02 \x01(\x08\x12\x11\n\tsendEvent\x18\x03 \x01(\x08\x1a;\n\x10isCheckedRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a#\n\x11isCheckedResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x32\xe5\x02\n\x12\x41piCheckBoxService\x12U\n\x06\x63reate\x12$.octaneapi.ApiCheckBox.createRequest\x1a%.octaneapi.ApiCheckBox.createResponse\x12H\n\x07\x64\x65stroy\x12%.octaneapi.ApiCheckBox.destroyRequest\x1a\x16.google.protobuf.Empty\x12N\n\nsetChecked\x12(.octaneapi.ApiCheckBox.setCheckedRequest\x1a\x16.google.protobuf.Empty\x12^\n\tisChecked\x12\'.octaneapi.ApiCheckBox.isCheckedRequest\x1a(.octaneapi.ApiCheckBox.isCheckedResponseB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apicheckbox_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APICHECKBOX']._serialized_start=76
  _globals['_APICHECKBOX']._serialized_end=519
  _globals['_APICHECKBOX_CREATEREQUEST']._serialized_start=91
  _globals['_APICHECKBOX_CREATEREQUEST']._serialized_end=188
  _globals['_APICHECKBOX_CREATERESPONSE']._serialized_start=190
  _globals['_APICHECKBOX_CREATERESPONSE']._serialized_end=264
  _globals['_APICHECKBOX_DESTROYREQUEST']._serialized_start=266
  _globals['_APICHECKBOX_DESTROYREQUEST']._serialized_end=323
  _globals['_APICHECKBOX_SETCHECKEDREQUEST']._serialized_start=325
  _globals['_APICHECKBOX_SETCHECKEDREQUEST']._serialized_end=421
  _globals['_APICHECKBOX_ISCHECKEDREQUEST']._serialized_start=423
  _globals['_APICHECKBOX_ISCHECKEDREQUEST']._serialized_end=482
  _globals['_APICHECKBOX_ISCHECKEDRESPONSE']._serialized_start=484
  _globals['_APICHECKBOX_ISCHECKEDRESPONSE']._serialized_end=519
  _globals['_APICHECKBOXSERVICE']._serialized_start=522
  _globals['_APICHECKBOXSERVICE']._serialized_end=879
# @@protoc_insertion_point(module_scope)
