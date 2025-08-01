# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apiociocontextmanager.proto
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
    'apiociocontextmanager.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
import octaneenums_pb2 as octaneenums__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1b\x61piociocontextmanager.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x11octaneenums.proto\"\x95\x0b\n\x15\x41piOcioContextManager\x1aJ\n\"guessIntermediateColorSpaceRequest\x12$\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x86\x01\n#guessIntermediateColorSpaceResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x12\x36\n\x12guessedOctaneValue\x18\x02 \x01(\x0e\x32\x1a.octaneapi.NamedColorSpace\x12\x17\n\x0fguessedOcioName\x18\x03 \x01(\t\x1a\x0f\n\rcreateRequest\x1a\x36\n\x0e\x63reateResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1az\n\x12\x61\x64\x64\x43\x61llbackRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12&\n\x08\x63\x61llback\x18\x02 \x01(\x0b\x32\x14.octaneapi.CallbackT\x12\x13\n\x0bprivateData\x18\x03 \x01(\x04\x1a)\n\x13\x61\x64\x64\x43\x61llbackResponse\x12\x12\n\ncallbackId\x18\x01 \x01(\r\x1a}\n\x15removeCallbackRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12&\n\x08\x63\x61llback\x18\x02 \x01(\x0b\x32\x14.octaneapi.CallbackT\x12\x13\n\x0bprivateData\x18\x03 \x01(\x04\x1a,\n\x16removeCallbackResponse\x12\x12\n\ncallbackId\x18\x01 \x01(\r\x1aJ\n\x1fgetDefaultConfigFilenameRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x32\n getDefaultConfigFilenameResponse\x12\x0e\n\x06result\x18\x01 \x01(\t\x1aK\n getLastConfigLoadFilenameRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x33\n!getLastConfigLoadFilenameResponse\x12\x0e\n\x06result\x18\x01 \x01(\t\x1a>\n\x13\x63reateConfigRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a<\n\x14\x63reateConfigResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aO\n$getContextUsableForConversionRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x37\n%getContextUsableForConversionResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1av\n\x13\x64onateConfigRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x10\n\x08\x66ilename\x18\x02 \x01(\t\x12$\n\x06\x63onfig\x18\x03 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aM\n\"handlePendingConfigDonationRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef2\xd5\x0b\n\x1c\x41piOcioContextManagerService\x12\xa8\x01\n\x1bguessIntermediateColorSpace\x12\x43.octaneapi.ApiOcioContextManager.guessIntermediateColorSpaceRequest\x1a\x44.octaneapi.ApiOcioContextManager.guessIntermediateColorSpaceResponse\x12i\n\x06\x63reate\x12..octaneapi.ApiOcioContextManager.createRequest\x1a/.octaneapi.ApiOcioContextManager.createResponse\x12R\n\x07\x64\x65stroy\x12/.octaneapi.ApiOcioContextManager.destroyRequest\x1a\x16.google.protobuf.Empty\x12x\n\x0b\x61\x64\x64\x43\x61llback\x12\x33.octaneapi.ApiOcioContextManager.addCallbackRequest\x1a\x34.octaneapi.ApiOcioContextManager.addCallbackResponse\x12\x81\x01\n\x0eremoveCallback\x12\x36.octaneapi.ApiOcioContextManager.removeCallbackRequest\x1a\x37.octaneapi.ApiOcioContextManager.removeCallbackResponse\x12\x9f\x01\n\x18getDefaultConfigFilename\x12@.octaneapi.ApiOcioContextManager.getDefaultConfigFilenameRequest\x1a\x41.octaneapi.ApiOcioContextManager.getDefaultConfigFilenameResponse\x12\xa2\x01\n\x19getLastConfigLoadFilename\x12\x41.octaneapi.ApiOcioContextManager.getLastConfigLoadFilenameRequest\x1a\x42.octaneapi.ApiOcioContextManager.getLastConfigLoadFilenameResponse\x12{\n\x0c\x63reateConfig\x12\x34.octaneapi.ApiOcioContextManager.createConfigRequest\x1a\x35.octaneapi.ApiOcioContextManager.createConfigResponse\x12\xae\x01\n\x1dgetContextUsableForConversion\x12\x45.octaneapi.ApiOcioContextManager.getContextUsableForConversionRequest\x1a\x46.octaneapi.ApiOcioContextManager.getContextUsableForConversionResponse\x12\\\n\x0c\x64onateConfig\x12\x34.octaneapi.ApiOcioContextManager.donateConfigRequest\x1a\x16.google.protobuf.Empty\x12z\n\x1bhandlePendingConfigDonation\x12\x43.octaneapi.ApiOcioContextManager.handlePendingConfigDonationRequest\x1a\x16.google.protobuf.EmptyB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apiociocontextmanager_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APIOCIOCONTEXTMANAGER']._serialized_start=105
  _globals['_APIOCIOCONTEXTMANAGER']._serialized_end=1534
  _globals['_APIOCIOCONTEXTMANAGER_GUESSINTERMEDIATECOLORSPACEREQUEST']._serialized_start=130
  _globals['_APIOCIOCONTEXTMANAGER_GUESSINTERMEDIATECOLORSPACEREQUEST']._serialized_end=204
  _globals['_APIOCIOCONTEXTMANAGER_GUESSINTERMEDIATECOLORSPACERESPONSE']._serialized_start=207
  _globals['_APIOCIOCONTEXTMANAGER_GUESSINTERMEDIATECOLORSPACERESPONSE']._serialized_end=341
  _globals['_APIOCIOCONTEXTMANAGER_CREATEREQUEST']._serialized_start=343
  _globals['_APIOCIOCONTEXTMANAGER_CREATEREQUEST']._serialized_end=358
  _globals['_APIOCIOCONTEXTMANAGER_CREATERESPONSE']._serialized_start=360
  _globals['_APIOCIOCONTEXTMANAGER_CREATERESPONSE']._serialized_end=414
  _globals['_APIOCIOCONTEXTMANAGER_DESTROYREQUEST']._serialized_start=416
  _globals['_APIOCIOCONTEXTMANAGER_DESTROYREQUEST']._serialized_end=473
  _globals['_APIOCIOCONTEXTMANAGER_ADDCALLBACKREQUEST']._serialized_start=475
  _globals['_APIOCIOCONTEXTMANAGER_ADDCALLBACKREQUEST']._serialized_end=597
  _globals['_APIOCIOCONTEXTMANAGER_ADDCALLBACKRESPONSE']._serialized_start=599
  _globals['_APIOCIOCONTEXTMANAGER_ADDCALLBACKRESPONSE']._serialized_end=640
  _globals['_APIOCIOCONTEXTMANAGER_REMOVECALLBACKREQUEST']._serialized_start=642
  _globals['_APIOCIOCONTEXTMANAGER_REMOVECALLBACKREQUEST']._serialized_end=767
  _globals['_APIOCIOCONTEXTMANAGER_REMOVECALLBACKRESPONSE']._serialized_start=769
  _globals['_APIOCIOCONTEXTMANAGER_REMOVECALLBACKRESPONSE']._serialized_end=813
  _globals['_APIOCIOCONTEXTMANAGER_GETDEFAULTCONFIGFILENAMEREQUEST']._serialized_start=815
  _globals['_APIOCIOCONTEXTMANAGER_GETDEFAULTCONFIGFILENAMEREQUEST']._serialized_end=889
  _globals['_APIOCIOCONTEXTMANAGER_GETDEFAULTCONFIGFILENAMERESPONSE']._serialized_start=891
  _globals['_APIOCIOCONTEXTMANAGER_GETDEFAULTCONFIGFILENAMERESPONSE']._serialized_end=941
  _globals['_APIOCIOCONTEXTMANAGER_GETLASTCONFIGLOADFILENAMEREQUEST']._serialized_start=943
  _globals['_APIOCIOCONTEXTMANAGER_GETLASTCONFIGLOADFILENAMEREQUEST']._serialized_end=1018
  _globals['_APIOCIOCONTEXTMANAGER_GETLASTCONFIGLOADFILENAMERESPONSE']._serialized_start=1020
  _globals['_APIOCIOCONTEXTMANAGER_GETLASTCONFIGLOADFILENAMERESPONSE']._serialized_end=1071
  _globals['_APIOCIOCONTEXTMANAGER_CREATECONFIGREQUEST']._serialized_start=1073
  _globals['_APIOCIOCONTEXTMANAGER_CREATECONFIGREQUEST']._serialized_end=1135
  _globals['_APIOCIOCONTEXTMANAGER_CREATECONFIGRESPONSE']._serialized_start=1137
  _globals['_APIOCIOCONTEXTMANAGER_CREATECONFIGRESPONSE']._serialized_end=1197
  _globals['_APIOCIOCONTEXTMANAGER_GETCONTEXTUSABLEFORCONVERSIONREQUEST']._serialized_start=1199
  _globals['_APIOCIOCONTEXTMANAGER_GETCONTEXTUSABLEFORCONVERSIONREQUEST']._serialized_end=1278
  _globals['_APIOCIOCONTEXTMANAGER_GETCONTEXTUSABLEFORCONVERSIONRESPONSE']._serialized_start=1280
  _globals['_APIOCIOCONTEXTMANAGER_GETCONTEXTUSABLEFORCONVERSIONRESPONSE']._serialized_end=1335
  _globals['_APIOCIOCONTEXTMANAGER_DONATECONFIGREQUEST']._serialized_start=1337
  _globals['_APIOCIOCONTEXTMANAGER_DONATECONFIGREQUEST']._serialized_end=1455
  _globals['_APIOCIOCONTEXTMANAGER_HANDLEPENDINGCONFIGDONATIONREQUEST']._serialized_start=1457
  _globals['_APIOCIOCONTEXTMANAGER_HANDLEPENDINGCONFIGDONATIONREQUEST']._serialized_end=1534
  _globals['_APIOCIOCONTEXTMANAGERSERVICE']._serialized_start=1537
  _globals['_APIOCIOCONTEXTMANAGERSERVICE']._serialized_end=3030
# @@protoc_insertion_point(module_scope)
