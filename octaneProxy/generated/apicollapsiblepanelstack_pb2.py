# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apicollapsiblepanelstack.proto
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
    'apicollapsiblepanelstack.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x61picollapsiblepanelstack.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\"\xb4\x03\n\x18\x41piCollapsiblePanelStack\x1a\x0f\n\rcreateRequest\x1a\x36\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x82\x01\n\x0f\x61\x64\x64PanelRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0f\n\x07\x63\x61ption\x18\x02 \x01(\t\x12\'\n\tcomponent\x18\x03 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04open\x18\x04 \x01(\x08\x1aV\n\x0esetOpenRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\x05\x12\x0c\n\x04open\x18\x03 \x01(\x08\x1a\x37\n\x0c\x63learRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef2\xec\x03\n\x1f\x41piCollapsiblePanelStackService\x12o\n\x06\x63reate\x12\x31.octaneapi.ApiCollapsiblePanelStack.createRequest\x1a\x32.octaneapi.ApiCollapsiblePanelStack.createResponse\x12U\n\x07\x64\x65stroy\x12\x32.octaneapi.ApiCollapsiblePanelStack.destroyRequest\x1a\x16.google.protobuf.Empty\x12W\n\x08\x61\x64\x64Panel\x12\x33.octaneapi.ApiCollapsiblePanelStack.addPanelRequest\x1a\x16.google.protobuf.Empty\x12U\n\x07setOpen\x12\x32.octaneapi.ApiCollapsiblePanelStack.setOpenRequest\x1a\x16.google.protobuf.Empty\x12Q\n\x05\x63lear\x12\x30.octaneapi.ApiCollapsiblePanelStack.clearRequest\x1a\x16.google.protobuf.EmptyB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apicollapsiblepanelstack_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APICOLLAPSIBLEPANELSTACK']._serialized_start=89
  _globals['_APICOLLAPSIBLEPANELSTACK']._serialized_end=525
  _globals['_APICOLLAPSIBLEPANELSTACK_CREATEREQUEST']._serialized_start=117
  _globals['_APICOLLAPSIBLEPANELSTACK_CREATEREQUEST']._serialized_end=132
  _globals['_APICOLLAPSIBLEPANELSTACK_CREATERESPONSE']._serialized_start=134
  _globals['_APICOLLAPSIBLEPANELSTACK_CREATERESPONSE']._serialized_end=188
  _globals['_APICOLLAPSIBLEPANELSTACK_DESTROYREQUEST']._serialized_start=190
  _globals['_APICOLLAPSIBLEPANELSTACK_DESTROYREQUEST']._serialized_end=247
  _globals['_APICOLLAPSIBLEPANELSTACK_ADDPANELREQUEST']._serialized_start=250
  _globals['_APICOLLAPSIBLEPANELSTACK_ADDPANELREQUEST']._serialized_end=380
  _globals['_APICOLLAPSIBLEPANELSTACK_SETOPENREQUEST']._serialized_start=382
  _globals['_APICOLLAPSIBLEPANELSTACK_SETOPENREQUEST']._serialized_end=468
  _globals['_APICOLLAPSIBLEPANELSTACK_CLEARREQUEST']._serialized_start=470
  _globals['_APICOLLAPSIBLEPANELSTACK_CLEARREQUEST']._serialized_end=525
  _globals['_APICOLLAPSIBLEPANELSTACKSERVICE']._serialized_start=528
  _globals['_APICOLLAPSIBLEPANELSTACKSERVICE']._serialized_end=1020
# @@protoc_insertion_point(module_scope)
