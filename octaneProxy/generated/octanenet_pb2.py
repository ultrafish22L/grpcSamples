# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: octanenet.proto
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
    'octanenet.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0foctanenet.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\"H\n\x10NetInterfaceInfo\x12\x11\n\tadapterIP\x18\x01 \x01(\r\x12\x13\n\x0b\x62\x61seAddress\x18\x02 \x01(\r\x12\x0c\n\x04mask\x18\x03 \x01(\r\"\x8e\x01\n\rSocketAddress\x12\x11\n\tipAddress\x18\x01 \x01(\r\x12\x0c\n\x04port\x18\x02 \x01(\r\x1a\x39\n\x0eisValidRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a!\n\x0fisValidResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\"\x98\x02\n\x0fNetRenderStatus\x12\x15\n\rnetSlaveCount\x18\x01 \x01(\r\x12\x1d\n\x15updatingNetSlaveCount\x18\x02 \x01(\r\x12\x1c\n\x14updatedNetSlaveCount\x18\x03 \x01(\r\x12\x13\n\x0bpendingSize\x18\x04 \x01(\r\x12\x11\n\ttotalSize\x18\x05 \x01(\r\x12\x13\n\x0bnetGpuCount\x18\x06 \x01(\r\x12\x18\n\x10inUseNetGpuCount\x18\x07 \x01(\r\x12!\n\x19\x63\x61nRenderUsingRenderNodes\x18\x08 \x01(\x08\x1a\x37\n\x0c\x63learRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\"\xd1\x01\n\rNetDaemonInfo\x12\x11\n\tipAddress\x18\x01 \x01(\r\x12\x0c\n\x04name\x18\x02 \x01(\t\x12(\n\x05state\x18\x03 \x01(\x0e\x32\x19.octaneapi.NetDaemonState\x12\x10\n\x08gpuCount\x18\x04 \x01(\r\x12\x14\n\x0cslaveVersion\x18\x05 \x01(\r\x12\x34\n\x12\x62oundMasterAddress\x18\x06 \x01(\x0b\x32\x18.octaneapi.SocketAddress\x12\x17\n\x0f\x62oundMasterName\x18\x07 \x01(\t\"\xeb\x01\n\x11NetRenderSettings\x12\x12\n\nmasterPort\x18\x01 \x01(\r\x12\x12\n\ndaemonPort\x18\x02 \x01(\r\x12\x33\n\x14\x64\x61\x65monSearchAdapters\x18\x03 \x01(\x0b\x32\x15.octaneapi.UintArrayT\x12 \n\x18\x64\x61\x65monSearchAdapterCount\x18\x04 \x01(\r\x12\x35\n\x14\x64\x61\x65monSearchAdresses\x18\x05 \x01(\x0b\x32\x17.octaneapi.StringArrayT\x12 \n\x18\x64\x61\x65monSearchAddressCount\x18\x06 \x01(\r*\xfe\x01\n\x0eNetDaemonState\x12\x18\n\x14\x44\x41\x45MON_STATE_UNKNOWN\x10\x00\x12$\n DAEMON_SLAVE_HAS_INVALID_VERSION\x10\x01\x12\x18\n\x14\x44\x41\x45MON_SLAVE_UNBOUND\x10\x02\x12\x1f\n\x1b\x44\x41\x45MON_SLAVE_BOUND_TO_OTHER\x10\x03\x12\x1f\n\x1b\x44\x41\x45MON_SLAVE_AUTHENTICATING\x10\x04\x12\x18\n\x14\x44\x41\x45MON_SLAVE_RUNNING\x10\x05\x12\x1c\n\x18\x44\x41\x45MON_SLAVE_DEACTIVATED\x10\x06\x12\x18\n\x14\x44\x41\x45MON_SLAVE_CRASHED\x10\x07*$\n\x10NetTransportMode\x12\x10\n\x0cNET_MODE_TCP\x10\x00\x32\x62\n\x16NetRenderStatusService\x12H\n\x05\x63lear\x12\'.octaneapi.NetRenderStatus.clearRequest\x1a\x16.google.protobuf.Empty2t\n\x14SocketAddressService\x12\\\n\x07isValid\x12\'.octaneapi.SocketAddress.isValidRequest\x1a(.octaneapi.SocketAddress.isValidResponseB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'octanenet_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_NETDAEMONSTATE']._serialized_start=1026
  _globals['_NETDAEMONSTATE']._serialized_end=1280
  _globals['_NETTRANSPORTMODE']._serialized_start=1282
  _globals['_NETTRANSPORTMODE']._serialized_end=1318
  _globals['_NETINTERFACEINFO']._serialized_start=73
  _globals['_NETINTERFACEINFO']._serialized_end=145
  _globals['_SOCKETADDRESS']._serialized_start=148
  _globals['_SOCKETADDRESS']._serialized_end=290
  _globals['_SOCKETADDRESS_ISVALIDREQUEST']._serialized_start=198
  _globals['_SOCKETADDRESS_ISVALIDREQUEST']._serialized_end=255
  _globals['_SOCKETADDRESS_ISVALIDRESPONSE']._serialized_start=257
  _globals['_SOCKETADDRESS_ISVALIDRESPONSE']._serialized_end=290
  _globals['_NETRENDERSTATUS']._serialized_start=293
  _globals['_NETRENDERSTATUS']._serialized_end=573
  _globals['_NETRENDERSTATUS_CLEARREQUEST']._serialized_start=518
  _globals['_NETRENDERSTATUS_CLEARREQUEST']._serialized_end=573
  _globals['_NETDAEMONINFO']._serialized_start=576
  _globals['_NETDAEMONINFO']._serialized_end=785
  _globals['_NETRENDERSETTINGS']._serialized_start=788
  _globals['_NETRENDERSETTINGS']._serialized_end=1023
  _globals['_NETRENDERSTATUSSERVICE']._serialized_start=1320
  _globals['_NETRENDERSTATUSSERVICE']._serialized_end=1418
  _globals['_SOCKETADDRESSSERVICE']._serialized_start=1420
  _globals['_SOCKETADDRESSSERVICE']._serialized_end=1536
# @@protoc_insertion_point(module_scope)
