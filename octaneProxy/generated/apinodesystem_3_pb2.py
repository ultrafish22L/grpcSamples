# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: apinodesystem_3.proto
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
    'apinodesystem_3.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
import octaneids_pb2 as octaneids__pb2
import octaneinfos_pb2 as octaneinfos__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x15\x61pinodesystem_3.proto\x12\toctaneapi\x1a\x0c\x63ommon.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x0foctaneids.proto\x1a\x11octaneinfos.proto\"\x94<\n\x07\x41piItem\x1a>\n\x13\x61ttrAreDirtyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a&\n\x14\x61ttrAreDirtyResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a;\n\x10\x61ttrCountRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a#\n\x11\x61ttrCountResponse\x12\x0e\n\x06result\x18\x01 \x01(\r\x1aI\n\x0f\x61ttrIdIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a:\n\x10\x61ttrIdIxResponse\x12&\n\x06result\x18\x01 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a\x46\n\rattrIdRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a\x38\n\x0e\x61ttrIdResponse\x12&\n\x06result\x18\x01 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1aI\n\x10\x61ttrInfo1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a@\n\x11\x61ttrInfo1Response\x12+\n\x06result\x18\x01 \x01(\x0b\x32\x1b.octaneapi.ApiAttributeInfo\x1aK\n\x11\x61ttrInfoIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a\x41\n\x12\x61ttrInfoIxResponse\x12+\n\x06result\x18\x01 \x01(\x0b\x32\x1b.octaneapi.ApiAttributeInfo\x1a^\n\x0f\x61ttrInfoRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a?\n\x10\x61ttrInfoResponse\x12+\n\x06result\x18\x01 \x01(\x0b\x32\x1b.octaneapi.ApiAttributeInfo\x1aK\n\x11\x61ttrNameIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a$\n\x12\x61ttrNameIxResponse\x12\x0e\n\x06result\x18\x01 \x01(\t\x1a^\n\x0f\x61ttrNameRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a\"\n\x10\x61ttrNameResponse\x12\x0e\n\x06result\x18\x01 \x01(\t\x1aM\n\x10\x61ttrType1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x10\n\x08\x61ttrName\x18\x02 \x01(\t\x1a=\n\x11\x61ttrType1Response\x12(\n\x06result\x18\x01 \x01(\x0e\x32\x18.octaneapi.AttributeType\x1aK\n\x11\x61ttrTypeIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a>\n\x12\x61ttrTypeIxResponse\x12(\n\x06result\x18\x01 \x01(\x0e\x32\x18.octaneapi.AttributeType\x1a^\n\x0f\x61ttrTypeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a<\n\x10\x61ttrTypeResponse\x12(\n\x06result\x18\x01 \x01(\x0e\x32\x18.octaneapi.AttributeType\x1aP\n\x13\x63learAllAttrRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x10\n\x08\x65valuate\x18\x02 \x01(\x08\x1aJ\n\x11\x63learAnim1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1aL\n\x12\x63learAnimIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a_\n\x10\x63learAnimRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a\\\n\x11\x63learAttr1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x10\n\x08\x65valuate\x18\x03 \x01(\x08\x1a^\n\x12\x63learAttrIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x12\x10\n\x08\x65valuate\x18\x03 \x01(\x08\x1aq\n\x10\x63learAttrRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x12\x10\n\x08\x65valuate\x18\x03 \x01(\x08\x1a:\n\x0f\x63ollapseRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\"\n\x10\x63ollapseResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1aj\n\x16\x63ollectItemTreeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\'\n\ttreeItems\x18\x02 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x42\n\x17\x63ollectItemTreeResponse\x12\'\n\ttreeItems\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\xb5\x01\n\x14\x63opyAttrFrom1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12&\n\x06\x64\x65stId\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x12%\n\x07srcItem\x18\x03 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x13\n\x0bsrcAttrName\x18\x04 \x01(\t\x12\x10\n\x08\x65valuate\x18\x05 \x01(\x08\x1ax\n\x14\x63opyAttrFrom2Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12%\n\x07srcItem\x18\x02 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x10\n\x08\x65valuate\x18\x03 \x01(\x08\x1a\xb4\x01\n\x15\x63opyAttrFromIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12&\n\x06\x64\x65stId\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x12%\n\x07srcItem\x18\x03 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x11\n\tsrcAttrIx\x18\x04 \x01(\r\x12\x10\n\x08\x65valuate\x18\x05 \x01(\x08\x1a\xc6\x01\n\x13\x63opyAttrFromRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12&\n\x06\x64\x65stId\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x12%\n\x07srcItem\x18\x03 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12%\n\x05srcId\x18\x04 \x01(\x0e\x32\x16.octaneapi.AttributeId\x12\x10\n\x08\x65valuate\x18\x05 \x01(\x08\x1aH\n\x1d\x64\x65leteUnconnectedItemsRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0e\x64\x65stroyRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aS\n\x15\x64umpAttributesRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x11\n\tdirectory\x18\x02 \x01(\t\x1a:\n\x0f\x65valuateRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a@\n\x15\x65xpandOutOfPinRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a>\n\x16\x65xpandOutOfPinResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x38\n\rexpandRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aI\n\x10\x66indAttr1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a\x37\n\x11\x66indAttr1Response\x12\x0e\n\x06result\x18\x01 \x01(\x08\x12\x12\n\nfoundIndex\x18\x02 \x01(\r\x1a^\n\x0f\x66indAttrRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a\x36\n\x10\x66indAttrResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x12\x12\n\nfoundIndex\x18\x02 \x01(\r\x1a<\n\x11graphOwnedRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a$\n\x12graphOwnedResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a<\n\x11graphOwnerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a:\n\x12graphOwnerResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aH\n\x0fhasAttr1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a\"\n\x10hasAttr1Response\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a]\n\x0ehasAttrRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a!\n\x0fhasAttrResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a:\n\x0fhasOwnerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\"\n\x10hasOwnerResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1aK\n\x12isAnimated1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a%\n\x13isAnimated1Response\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1aM\n\x13isAnimatedIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a&\n\x14isAnimatedIxResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a`\n\x11isAnimatedRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a$\n\x12isAnimatedResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1aL\n\x13isDirtyAttr1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x0c\n\x04name\x18\x02 \x01(\t\x1a&\n\x14isDirtyAttr1Response\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1aN\n\x14isDirtyAttrIxRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05index\x18\x02 \x01(\r\x1a\'\n\x15isDirtyAttrIxResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a\x61\n\x12isDirtyAttrRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\"\n\x02id\x18\x02 \x01(\x0e\x32\x16.octaneapi.AttributeId\x1a%\n\x13isDirtyAttrResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a\x39\n\x0eisGraphRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a!\n\x0fisGraphResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a?\n\x14isInputLinkerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\'\n\x15isInputLinkerResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a:\n\x0fisLinkerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\"\n\x10isLinkerResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a\x38\n\risNodeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a \n\x0eisNodeResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a@\n\x15isOutputLinkerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a(\n\x16isOutputLinkerResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a\x36\n\x0bnameRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x1e\n\x0cnameResponse\x12\x0e\n\x06result\x18\x01 \x01(\t\x1a\x39\n\x0eoutTypeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0foutTypeResponse\x12&\n\x06result\x18\x01 \x01(\x0e\x32\x16.octaneapi.NodePinType\x1a>\n\x13persistentIdRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a&\n\x14persistentIdResponse\x12\x0e\n\x06result\x18\x01 \x01(\x04\x1a:\n\x0fpinOwnedRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\"\n\x10pinOwnedResponse\x12\x0e\n\x06result\x18\x01 \x01(\x08\x1a:\n\x0fpinOwnerRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aG\n\x10pinOwnerResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\r\n\x05pinIx\x18\x02 \x01(\r\x1a:\n\x0fpositionRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x36\n\x10positionResponse\x12\"\n\x06result\x18\x01 \x01(\x0b\x32\x12.octaneapi.float_2\x1a<\n\x11rootGraph1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a:\n\x12rootGraph1Response\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a;\n\x10rootGraphRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x11rootGraphResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x38\n\rselectRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1aZ\n\x17switchToFileDataRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x12\x16\n\x0e\x64\x65stinationDir\x18\x02 \x01(\t\x1a\x36\n\x0btimeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x30\n\x0ctimeResponse\x12 \n\x06result\x18\x01 \x01(\x0b\x32\x10.octaneapi.TimeT\x1a:\n\x0ftoGraph1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x38\n\x10toGraph1Response\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0etoGraphRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x37\n\x0ftoGraphResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x39\n\x0etoNode1Request\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x37\n\x0ftoNode1Response\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x38\n\rtoNodeRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x36\n\x0etoNodeResponse\x12$\n\x06result\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\x42\n\x17uiOperationFlagsRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a=\n\x18uiOperationFlagsResponse\x12!\n\x06result\x18\x01 \x01(\x0b\x32\x11.octaneapi.enum_t\x1a:\n\x0funiqueIdRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a\"\n\x10uniqueIdResponse\x12\x0e\n\x06result\x18\x01 \x01(\r\x1a\x39\n\x0eversionRequest\x12\'\n\tobjectPtr\x18\x01 \x01(\x0b\x32\x14.octaneapi.ObjectRef\x1a!\n\x0fversionResponse\x12\x0e\n\x06result\x18\x01 \x01(\r2\x89-\n\x0e\x41piItemService\x12\x44\n\x07\x64\x65stroy\x12!.octaneapi.ApiItem.destroyRequest\x1a\x16.google.protobuf.Empty\x12G\n\x04name\x12\x1e.octaneapi.ApiItem.nameRequest\x1a\x1f.octaneapi.ApiItem.nameResponse\x12S\n\x08position\x12\".octaneapi.ApiItem.positionRequest\x1a#.octaneapi.ApiItem.positionResponse\x12k\n\x10uiOperationFlags\x12*.octaneapi.ApiItem.uiOperationFlagsRequest\x1a+.octaneapi.ApiItem.uiOperationFlagsResponse\x12\x42\n\x06select\x12 .octaneapi.ApiItem.selectRequest\x1a\x16.google.protobuf.Empty\x12G\n\x04time\x12\x1e.octaneapi.ApiItem.timeRequest\x1a\x1f.octaneapi.ApiItem.timeResponse\x12P\n\x07outType\x12!.octaneapi.ApiItem.outTypeRequest\x1a\".octaneapi.ApiItem.outTypeResponse\x12_\n\x0cpersistentId\x12&.octaneapi.ApiItem.persistentIdRequest\x1a\'.octaneapi.ApiItem.persistentIdResponse\x12S\n\x08uniqueId\x12\".octaneapi.ApiItem.uniqueIdRequest\x1a#.octaneapi.ApiItem.uniqueIdResponse\x12h\n\x0f\x63ollectItemTree\x12).octaneapi.ApiItem.collectItemTreeRequest\x1a*.octaneapi.ApiItem.collectItemTreeResponse\x12\x62\n\x16\x64\x65leteUnconnectedItems\x12\x30.octaneapi.ApiItem.deleteUnconnectedItemsRequest\x1a\x16.google.protobuf.Empty\x12V\n\x10switchToFileData\x12*.octaneapi.ApiItem.switchToFileDataRequest\x1a\x16.google.protobuf.Empty\x12P\n\x07version\x12!.octaneapi.ApiItem.versionRequest\x1a\".octaneapi.ApiItem.versionResponse\x12P\n\x07isGraph\x12!.octaneapi.ApiItem.isGraphRequest\x1a\".octaneapi.ApiItem.isGraphResponse\x12M\n\x06isNode\x12 .octaneapi.ApiItem.isNodeRequest\x1a!.octaneapi.ApiItem.isNodeResponse\x12S\n\x08isLinker\x12\".octaneapi.ApiItem.isLinkerRequest\x1a#.octaneapi.ApiItem.isLinkerResponse\x12\x62\n\risInputLinker\x12\'.octaneapi.ApiItem.isInputLinkerRequest\x1a(.octaneapi.ApiItem.isInputLinkerResponse\x12\x65\n\x0eisOutputLinker\x12(.octaneapi.ApiItem.isOutputLinkerRequest\x1a).octaneapi.ApiItem.isOutputLinkerResponse\x12P\n\x07toGraph\x12!.octaneapi.ApiItem.toGraphRequest\x1a\".octaneapi.ApiItem.toGraphResponse\x12M\n\x06toNode\x12 .octaneapi.ApiItem.toNodeRequest\x1a!.octaneapi.ApiItem.toNodeResponse\x12S\n\x08toGraph1\x12\".octaneapi.ApiItem.toGraph1Request\x1a#.octaneapi.ApiItem.toGraph1Response\x12P\n\x07toNode1\x12!.octaneapi.ApiItem.toNode1Request\x1a\".octaneapi.ApiItem.toNode1Response\x12S\n\x08hasOwner\x12\".octaneapi.ApiItem.hasOwnerRequest\x1a#.octaneapi.ApiItem.hasOwnerResponse\x12Y\n\ngraphOwned\x12$.octaneapi.ApiItem.graphOwnedRequest\x1a%.octaneapi.ApiItem.graphOwnedResponse\x12S\n\x08pinOwned\x12\".octaneapi.ApiItem.pinOwnedRequest\x1a#.octaneapi.ApiItem.pinOwnedResponse\x12Y\n\ngraphOwner\x12$.octaneapi.ApiItem.graphOwnerRequest\x1a%.octaneapi.ApiItem.graphOwnerResponse\x12S\n\x08pinOwner\x12\".octaneapi.ApiItem.pinOwnerRequest\x1a#.octaneapi.ApiItem.pinOwnerResponse\x12V\n\trootGraph\x12#.octaneapi.ApiItem.rootGraphRequest\x1a$.octaneapi.ApiItem.rootGraphResponse\x12Y\n\nrootGraph1\x12$.octaneapi.ApiItem.rootGraph1Request\x1a%.octaneapi.ApiItem.rootGraph1Response\x12V\n\tattrCount\x12#.octaneapi.ApiItem.attrCountRequest\x1a$.octaneapi.ApiItem.attrCountResponse\x12P\n\x07hasAttr\x12!.octaneapi.ApiItem.hasAttrRequest\x1a\".octaneapi.ApiItem.hasAttrResponse\x12S\n\x08hasAttr1\x12\".octaneapi.ApiItem.hasAttr1Request\x1a#.octaneapi.ApiItem.hasAttr1Response\x12S\n\x08\x66indAttr\x12\".octaneapi.ApiItem.findAttrRequest\x1a#.octaneapi.ApiItem.findAttrResponse\x12V\n\tfindAttr1\x12#.octaneapi.ApiItem.findAttr1Request\x1a$.octaneapi.ApiItem.findAttr1Response\x12M\n\x06\x61ttrId\x12 .octaneapi.ApiItem.attrIdRequest\x1a!.octaneapi.ApiItem.attrIdResponse\x12S\n\x08\x61ttrIdIx\x12\".octaneapi.ApiItem.attrIdIxRequest\x1a#.octaneapi.ApiItem.attrIdIxResponse\x12S\n\x08\x61ttrName\x12\".octaneapi.ApiItem.attrNameRequest\x1a#.octaneapi.ApiItem.attrNameResponse\x12Y\n\nattrNameIx\x12$.octaneapi.ApiItem.attrNameIxRequest\x1a%.octaneapi.ApiItem.attrNameIxResponse\x12S\n\x08\x61ttrType\x12\".octaneapi.ApiItem.attrTypeRequest\x1a#.octaneapi.ApiItem.attrTypeResponse\x12V\n\tattrType1\x12#.octaneapi.ApiItem.attrType1Request\x1a$.octaneapi.ApiItem.attrType1Response\x12Y\n\nattrTypeIx\x12$.octaneapi.ApiItem.attrTypeIxRequest\x1a%.octaneapi.ApiItem.attrTypeIxResponse\x12S\n\x08\x61ttrInfo\x12\".octaneapi.ApiItem.attrInfoRequest\x1a#.octaneapi.ApiItem.attrInfoResponse\x12V\n\tattrInfo1\x12#.octaneapi.ApiItem.attrInfo1Request\x1a$.octaneapi.ApiItem.attrInfo1Response\x12Y\n\nattrInfoIx\x12$.octaneapi.ApiItem.attrInfoIxRequest\x1a%.octaneapi.ApiItem.attrInfoIxResponse\x12_\n\x0c\x61ttrAreDirty\x12&.octaneapi.ApiItem.attrAreDirtyRequest\x1a\'.octaneapi.ApiItem.attrAreDirtyResponse\x12\\\n\x0bisDirtyAttr\x12%.octaneapi.ApiItem.isDirtyAttrRequest\x1a&.octaneapi.ApiItem.isDirtyAttrResponse\x12_\n\x0cisDirtyAttr1\x12&.octaneapi.ApiItem.isDirtyAttr1Request\x1a\'.octaneapi.ApiItem.isDirtyAttr1Response\x12\x62\n\risDirtyAttrIx\x12\'.octaneapi.ApiItem.isDirtyAttrIxRequest\x1a(.octaneapi.ApiItem.isDirtyAttrIxResponse\x12N\n\x0c\x63opyAttrFrom\x12&.octaneapi.ApiItem.copyAttrFromRequest\x1a\x16.google.protobuf.Empty\x12P\n\rcopyAttrFrom1\x12\'.octaneapi.ApiItem.copyAttrFrom1Request\x1a\x16.google.protobuf.Empty\x12R\n\x0e\x63opyAttrFromIx\x12(.octaneapi.ApiItem.copyAttrFromIxRequest\x1a\x16.google.protobuf.Empty\x12P\n\rcopyAttrFrom2\x12\'.octaneapi.ApiItem.copyAttrFrom2Request\x1a\x16.google.protobuf.Empty\x12N\n\x0c\x63learAllAttr\x12&.octaneapi.ApiItem.clearAllAttrRequest\x1a\x16.google.protobuf.Empty\x12H\n\tclearAttr\x12#.octaneapi.ApiItem.clearAttrRequest\x1a\x16.google.protobuf.Empty\x12J\n\nclearAttr1\x12$.octaneapi.ApiItem.clearAttr1Request\x1a\x16.google.protobuf.Empty\x12L\n\x0b\x63learAttrIx\x12%.octaneapi.ApiItem.clearAttrIxRequest\x1a\x16.google.protobuf.Empty\x12H\n\tclearAnim\x12#.octaneapi.ApiItem.clearAnimRequest\x1a\x16.google.protobuf.Empty\x12J\n\nclearAnim1\x12$.octaneapi.ApiItem.clearAnim1Request\x1a\x16.google.protobuf.Empty\x12L\n\x0b\x63learAnimIx\x12%.octaneapi.ApiItem.clearAnimIxRequest\x1a\x16.google.protobuf.Empty\x12Y\n\nisAnimated\x12$.octaneapi.ApiItem.isAnimatedRequest\x1a%.octaneapi.ApiItem.isAnimatedResponse\x12\\\n\x0bisAnimated1\x12%.octaneapi.ApiItem.isAnimated1Request\x1a&.octaneapi.ApiItem.isAnimated1Response\x12_\n\x0cisAnimatedIx\x12&.octaneapi.ApiItem.isAnimatedIxRequest\x1a\'.octaneapi.ApiItem.isAnimatedIxResponse\x12\x46\n\x08\x65valuate\x12\".octaneapi.ApiItem.evaluateRequest\x1a\x16.google.protobuf.Empty\x12\x42\n\x06\x65xpand\x12 .octaneapi.ApiItem.expandRequest\x1a\x16.google.protobuf.Empty\x12\x65\n\x0e\x65xpandOutOfPin\x12(.octaneapi.ApiItem.expandOutOfPinRequest\x1a).octaneapi.ApiItem.expandOutOfPinResponse\x12S\n\x08\x63ollapse\x12\".octaneapi.ApiItem.collapseRequest\x1a#.octaneapi.ApiItem.collapseResponse\x12R\n\x0e\x64umpAttributes\x12(.octaneapi.ApiItem.dumpAttributesRequest\x1a\x16.google.protobuf.EmptyB\x02H\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'apinodesystem_3_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  _globals['DESCRIPTOR']._loaded_options = None
  _globals['DESCRIPTOR']._serialized_options = b'H\002'
  _globals['_APIITEM']._serialized_start=116
  _globals['_APIITEM']._serialized_end=7816
  _globals['_APIITEM_ATTRAREDIRTYREQUEST']._serialized_start=127
  _globals['_APIITEM_ATTRAREDIRTYREQUEST']._serialized_end=189
  _globals['_APIITEM_ATTRAREDIRTYRESPONSE']._serialized_start=191
  _globals['_APIITEM_ATTRAREDIRTYRESPONSE']._serialized_end=229
  _globals['_APIITEM_ATTRCOUNTREQUEST']._serialized_start=231
  _globals['_APIITEM_ATTRCOUNTREQUEST']._serialized_end=290
  _globals['_APIITEM_ATTRCOUNTRESPONSE']._serialized_start=292
  _globals['_APIITEM_ATTRCOUNTRESPONSE']._serialized_end=327
  _globals['_APIITEM_ATTRIDIXREQUEST']._serialized_start=329
  _globals['_APIITEM_ATTRIDIXREQUEST']._serialized_end=402
  _globals['_APIITEM_ATTRIDIXRESPONSE']._serialized_start=404
  _globals['_APIITEM_ATTRIDIXRESPONSE']._serialized_end=462
  _globals['_APIITEM_ATTRIDREQUEST']._serialized_start=464
  _globals['_APIITEM_ATTRIDREQUEST']._serialized_end=534
  _globals['_APIITEM_ATTRIDRESPONSE']._serialized_start=536
  _globals['_APIITEM_ATTRIDRESPONSE']._serialized_end=592
  _globals['_APIITEM_ATTRINFO1REQUEST']._serialized_start=594
  _globals['_APIITEM_ATTRINFO1REQUEST']._serialized_end=667
  _globals['_APIITEM_ATTRINFO1RESPONSE']._serialized_start=669
  _globals['_APIITEM_ATTRINFO1RESPONSE']._serialized_end=733
  _globals['_APIITEM_ATTRINFOIXREQUEST']._serialized_start=735
  _globals['_APIITEM_ATTRINFOIXREQUEST']._serialized_end=810
  _globals['_APIITEM_ATTRINFOIXRESPONSE']._serialized_start=812
  _globals['_APIITEM_ATTRINFOIXRESPONSE']._serialized_end=877
  _globals['_APIITEM_ATTRINFOREQUEST']._serialized_start=879
  _globals['_APIITEM_ATTRINFOREQUEST']._serialized_end=973
  _globals['_APIITEM_ATTRINFORESPONSE']._serialized_start=975
  _globals['_APIITEM_ATTRINFORESPONSE']._serialized_end=1038
  _globals['_APIITEM_ATTRNAMEIXREQUEST']._serialized_start=1040
  _globals['_APIITEM_ATTRNAMEIXREQUEST']._serialized_end=1115
  _globals['_APIITEM_ATTRNAMEIXRESPONSE']._serialized_start=1117
  _globals['_APIITEM_ATTRNAMEIXRESPONSE']._serialized_end=1153
  _globals['_APIITEM_ATTRNAMEREQUEST']._serialized_start=1155
  _globals['_APIITEM_ATTRNAMEREQUEST']._serialized_end=1249
  _globals['_APIITEM_ATTRNAMERESPONSE']._serialized_start=1251
  _globals['_APIITEM_ATTRNAMERESPONSE']._serialized_end=1285
  _globals['_APIITEM_ATTRTYPE1REQUEST']._serialized_start=1287
  _globals['_APIITEM_ATTRTYPE1REQUEST']._serialized_end=1364
  _globals['_APIITEM_ATTRTYPE1RESPONSE']._serialized_start=1366
  _globals['_APIITEM_ATTRTYPE1RESPONSE']._serialized_end=1427
  _globals['_APIITEM_ATTRTYPEIXREQUEST']._serialized_start=1429
  _globals['_APIITEM_ATTRTYPEIXREQUEST']._serialized_end=1504
  _globals['_APIITEM_ATTRTYPEIXRESPONSE']._serialized_start=1506
  _globals['_APIITEM_ATTRTYPEIXRESPONSE']._serialized_end=1568
  _globals['_APIITEM_ATTRTYPEREQUEST']._serialized_start=1570
  _globals['_APIITEM_ATTRTYPEREQUEST']._serialized_end=1664
  _globals['_APIITEM_ATTRTYPERESPONSE']._serialized_start=1666
  _globals['_APIITEM_ATTRTYPERESPONSE']._serialized_end=1726
  _globals['_APIITEM_CLEARALLATTRREQUEST']._serialized_start=1728
  _globals['_APIITEM_CLEARALLATTRREQUEST']._serialized_end=1808
  _globals['_APIITEM_CLEARANIM1REQUEST']._serialized_start=1810
  _globals['_APIITEM_CLEARANIM1REQUEST']._serialized_end=1884
  _globals['_APIITEM_CLEARANIMIXREQUEST']._serialized_start=1886
  _globals['_APIITEM_CLEARANIMIXREQUEST']._serialized_end=1962
  _globals['_APIITEM_CLEARANIMREQUEST']._serialized_start=1964
  _globals['_APIITEM_CLEARANIMREQUEST']._serialized_end=2059
  _globals['_APIITEM_CLEARATTR1REQUEST']._serialized_start=2061
  _globals['_APIITEM_CLEARATTR1REQUEST']._serialized_end=2153
  _globals['_APIITEM_CLEARATTRIXREQUEST']._serialized_start=2155
  _globals['_APIITEM_CLEARATTRIXREQUEST']._serialized_end=2249
  _globals['_APIITEM_CLEARATTRREQUEST']._serialized_start=2251
  _globals['_APIITEM_CLEARATTRREQUEST']._serialized_end=2364
  _globals['_APIITEM_COLLAPSEREQUEST']._serialized_start=2366
  _globals['_APIITEM_COLLAPSEREQUEST']._serialized_end=2424
  _globals['_APIITEM_COLLAPSERESPONSE']._serialized_start=2426
  _globals['_APIITEM_COLLAPSERESPONSE']._serialized_end=2460
  _globals['_APIITEM_COLLECTITEMTREEREQUEST']._serialized_start=2462
  _globals['_APIITEM_COLLECTITEMTREEREQUEST']._serialized_end=2568
  _globals['_APIITEM_COLLECTITEMTREERESPONSE']._serialized_start=2570
  _globals['_APIITEM_COLLECTITEMTREERESPONSE']._serialized_end=2636
  _globals['_APIITEM_COPYATTRFROM1REQUEST']._serialized_start=2639
  _globals['_APIITEM_COPYATTRFROM1REQUEST']._serialized_end=2820
  _globals['_APIITEM_COPYATTRFROM2REQUEST']._serialized_start=2822
  _globals['_APIITEM_COPYATTRFROM2REQUEST']._serialized_end=2942
  _globals['_APIITEM_COPYATTRFROMIXREQUEST']._serialized_start=2945
  _globals['_APIITEM_COPYATTRFROMIXREQUEST']._serialized_end=3125
  _globals['_APIITEM_COPYATTRFROMREQUEST']._serialized_start=3128
  _globals['_APIITEM_COPYATTRFROMREQUEST']._serialized_end=3326
  _globals['_APIITEM_DELETEUNCONNECTEDITEMSREQUEST']._serialized_start=3328
  _globals['_APIITEM_DELETEUNCONNECTEDITEMSREQUEST']._serialized_end=3400
  _globals['_APIITEM_DESTROYREQUEST']._serialized_start=3402
  _globals['_APIITEM_DESTROYREQUEST']._serialized_end=3459
  _globals['_APIITEM_DUMPATTRIBUTESREQUEST']._serialized_start=3461
  _globals['_APIITEM_DUMPATTRIBUTESREQUEST']._serialized_end=3544
  _globals['_APIITEM_EVALUATEREQUEST']._serialized_start=3546
  _globals['_APIITEM_EVALUATEREQUEST']._serialized_end=3604
  _globals['_APIITEM_EXPANDOUTOFPINREQUEST']._serialized_start=3606
  _globals['_APIITEM_EXPANDOUTOFPINREQUEST']._serialized_end=3670
  _globals['_APIITEM_EXPANDOUTOFPINRESPONSE']._serialized_start=3672
  _globals['_APIITEM_EXPANDOUTOFPINRESPONSE']._serialized_end=3734
  _globals['_APIITEM_EXPANDREQUEST']._serialized_start=3736
  _globals['_APIITEM_EXPANDREQUEST']._serialized_end=3792
  _globals['_APIITEM_FINDATTR1REQUEST']._serialized_start=3794
  _globals['_APIITEM_FINDATTR1REQUEST']._serialized_end=3867
  _globals['_APIITEM_FINDATTR1RESPONSE']._serialized_start=3869
  _globals['_APIITEM_FINDATTR1RESPONSE']._serialized_end=3924
  _globals['_APIITEM_FINDATTRREQUEST']._serialized_start=3926
  _globals['_APIITEM_FINDATTRREQUEST']._serialized_end=4020
  _globals['_APIITEM_FINDATTRRESPONSE']._serialized_start=4022
  _globals['_APIITEM_FINDATTRRESPONSE']._serialized_end=4076
  _globals['_APIITEM_GRAPHOWNEDREQUEST']._serialized_start=4078
  _globals['_APIITEM_GRAPHOWNEDREQUEST']._serialized_end=4138
  _globals['_APIITEM_GRAPHOWNEDRESPONSE']._serialized_start=4140
  _globals['_APIITEM_GRAPHOWNEDRESPONSE']._serialized_end=4176
  _globals['_APIITEM_GRAPHOWNERREQUEST']._serialized_start=4178
  _globals['_APIITEM_GRAPHOWNERREQUEST']._serialized_end=4238
  _globals['_APIITEM_GRAPHOWNERRESPONSE']._serialized_start=4240
  _globals['_APIITEM_GRAPHOWNERRESPONSE']._serialized_end=4298
  _globals['_APIITEM_HASATTR1REQUEST']._serialized_start=4300
  _globals['_APIITEM_HASATTR1REQUEST']._serialized_end=4372
  _globals['_APIITEM_HASATTR1RESPONSE']._serialized_start=4374
  _globals['_APIITEM_HASATTR1RESPONSE']._serialized_end=4408
  _globals['_APIITEM_HASATTRREQUEST']._serialized_start=4410
  _globals['_APIITEM_HASATTRREQUEST']._serialized_end=4503
  _globals['_APIITEM_HASATTRRESPONSE']._serialized_start=4505
  _globals['_APIITEM_HASATTRRESPONSE']._serialized_end=4538
  _globals['_APIITEM_HASOWNERREQUEST']._serialized_start=4540
  _globals['_APIITEM_HASOWNERREQUEST']._serialized_end=4598
  _globals['_APIITEM_HASOWNERRESPONSE']._serialized_start=4600
  _globals['_APIITEM_HASOWNERRESPONSE']._serialized_end=4634
  _globals['_APIITEM_ISANIMATED1REQUEST']._serialized_start=4636
  _globals['_APIITEM_ISANIMATED1REQUEST']._serialized_end=4711
  _globals['_APIITEM_ISANIMATED1RESPONSE']._serialized_start=4713
  _globals['_APIITEM_ISANIMATED1RESPONSE']._serialized_end=4750
  _globals['_APIITEM_ISANIMATEDIXREQUEST']._serialized_start=4752
  _globals['_APIITEM_ISANIMATEDIXREQUEST']._serialized_end=4829
  _globals['_APIITEM_ISANIMATEDIXRESPONSE']._serialized_start=4831
  _globals['_APIITEM_ISANIMATEDIXRESPONSE']._serialized_end=4869
  _globals['_APIITEM_ISANIMATEDREQUEST']._serialized_start=4871
  _globals['_APIITEM_ISANIMATEDREQUEST']._serialized_end=4967
  _globals['_APIITEM_ISANIMATEDRESPONSE']._serialized_start=4969
  _globals['_APIITEM_ISANIMATEDRESPONSE']._serialized_end=5005
  _globals['_APIITEM_ISDIRTYATTR1REQUEST']._serialized_start=5007
  _globals['_APIITEM_ISDIRTYATTR1REQUEST']._serialized_end=5083
  _globals['_APIITEM_ISDIRTYATTR1RESPONSE']._serialized_start=5085
  _globals['_APIITEM_ISDIRTYATTR1RESPONSE']._serialized_end=5123
  _globals['_APIITEM_ISDIRTYATTRIXREQUEST']._serialized_start=5125
  _globals['_APIITEM_ISDIRTYATTRIXREQUEST']._serialized_end=5203
  _globals['_APIITEM_ISDIRTYATTRIXRESPONSE']._serialized_start=5205
  _globals['_APIITEM_ISDIRTYATTRIXRESPONSE']._serialized_end=5244
  _globals['_APIITEM_ISDIRTYATTRREQUEST']._serialized_start=5246
  _globals['_APIITEM_ISDIRTYATTRREQUEST']._serialized_end=5343
  _globals['_APIITEM_ISDIRTYATTRRESPONSE']._serialized_start=5345
  _globals['_APIITEM_ISDIRTYATTRRESPONSE']._serialized_end=5382
  _globals['_APIITEM_ISGRAPHREQUEST']._serialized_start=5384
  _globals['_APIITEM_ISGRAPHREQUEST']._serialized_end=5441
  _globals['_APIITEM_ISGRAPHRESPONSE']._serialized_start=5443
  _globals['_APIITEM_ISGRAPHRESPONSE']._serialized_end=5476
  _globals['_APIITEM_ISINPUTLINKERREQUEST']._serialized_start=5478
  _globals['_APIITEM_ISINPUTLINKERREQUEST']._serialized_end=5541
  _globals['_APIITEM_ISINPUTLINKERRESPONSE']._serialized_start=5543
  _globals['_APIITEM_ISINPUTLINKERRESPONSE']._serialized_end=5582
  _globals['_APIITEM_ISLINKERREQUEST']._serialized_start=5584
  _globals['_APIITEM_ISLINKERREQUEST']._serialized_end=5642
  _globals['_APIITEM_ISLINKERRESPONSE']._serialized_start=5644
  _globals['_APIITEM_ISLINKERRESPONSE']._serialized_end=5678
  _globals['_APIITEM_ISNODEREQUEST']._serialized_start=5680
  _globals['_APIITEM_ISNODEREQUEST']._serialized_end=5736
  _globals['_APIITEM_ISNODERESPONSE']._serialized_start=5738
  _globals['_APIITEM_ISNODERESPONSE']._serialized_end=5770
  _globals['_APIITEM_ISOUTPUTLINKERREQUEST']._serialized_start=5772
  _globals['_APIITEM_ISOUTPUTLINKERREQUEST']._serialized_end=5836
  _globals['_APIITEM_ISOUTPUTLINKERRESPONSE']._serialized_start=5838
  _globals['_APIITEM_ISOUTPUTLINKERRESPONSE']._serialized_end=5878
  _globals['_APIITEM_NAMEREQUEST']._serialized_start=5880
  _globals['_APIITEM_NAMEREQUEST']._serialized_end=5934
  _globals['_APIITEM_NAMERESPONSE']._serialized_start=5936
  _globals['_APIITEM_NAMERESPONSE']._serialized_end=5966
  _globals['_APIITEM_OUTTYPEREQUEST']._serialized_start=5968
  _globals['_APIITEM_OUTTYPEREQUEST']._serialized_end=6025
  _globals['_APIITEM_OUTTYPERESPONSE']._serialized_start=6027
  _globals['_APIITEM_OUTTYPERESPONSE']._serialized_end=6084
  _globals['_APIITEM_PERSISTENTIDREQUEST']._serialized_start=6086
  _globals['_APIITEM_PERSISTENTIDREQUEST']._serialized_end=6148
  _globals['_APIITEM_PERSISTENTIDRESPONSE']._serialized_start=6150
  _globals['_APIITEM_PERSISTENTIDRESPONSE']._serialized_end=6188
  _globals['_APIITEM_PINOWNEDREQUEST']._serialized_start=6190
  _globals['_APIITEM_PINOWNEDREQUEST']._serialized_end=6248
  _globals['_APIITEM_PINOWNEDRESPONSE']._serialized_start=6250
  _globals['_APIITEM_PINOWNEDRESPONSE']._serialized_end=6284
  _globals['_APIITEM_PINOWNERREQUEST']._serialized_start=6286
  _globals['_APIITEM_PINOWNERREQUEST']._serialized_end=6344
  _globals['_APIITEM_PINOWNERRESPONSE']._serialized_start=6346
  _globals['_APIITEM_PINOWNERRESPONSE']._serialized_end=6417
  _globals['_APIITEM_POSITIONREQUEST']._serialized_start=6419
  _globals['_APIITEM_POSITIONREQUEST']._serialized_end=6477
  _globals['_APIITEM_POSITIONRESPONSE']._serialized_start=6479
  _globals['_APIITEM_POSITIONRESPONSE']._serialized_end=6533
  _globals['_APIITEM_ROOTGRAPH1REQUEST']._serialized_start=6535
  _globals['_APIITEM_ROOTGRAPH1REQUEST']._serialized_end=6595
  _globals['_APIITEM_ROOTGRAPH1RESPONSE']._serialized_start=6597
  _globals['_APIITEM_ROOTGRAPH1RESPONSE']._serialized_end=6655
  _globals['_APIITEM_ROOTGRAPHREQUEST']._serialized_start=6657
  _globals['_APIITEM_ROOTGRAPHREQUEST']._serialized_end=6716
  _globals['_APIITEM_ROOTGRAPHRESPONSE']._serialized_start=6718
  _globals['_APIITEM_ROOTGRAPHRESPONSE']._serialized_end=6775
  _globals['_APIITEM_SELECTREQUEST']._serialized_start=6777
  _globals['_APIITEM_SELECTREQUEST']._serialized_end=6833
  _globals['_APIITEM_SWITCHTOFILEDATAREQUEST']._serialized_start=6835
  _globals['_APIITEM_SWITCHTOFILEDATAREQUEST']._serialized_end=6925
  _globals['_APIITEM_TIMEREQUEST']._serialized_start=6927
  _globals['_APIITEM_TIMEREQUEST']._serialized_end=6981
  _globals['_APIITEM_TIMERESPONSE']._serialized_start=6983
  _globals['_APIITEM_TIMERESPONSE']._serialized_end=7031
  _globals['_APIITEM_TOGRAPH1REQUEST']._serialized_start=7033
  _globals['_APIITEM_TOGRAPH1REQUEST']._serialized_end=7091
  _globals['_APIITEM_TOGRAPH1RESPONSE']._serialized_start=7093
  _globals['_APIITEM_TOGRAPH1RESPONSE']._serialized_end=7149
  _globals['_APIITEM_TOGRAPHREQUEST']._serialized_start=7151
  _globals['_APIITEM_TOGRAPHREQUEST']._serialized_end=7208
  _globals['_APIITEM_TOGRAPHRESPONSE']._serialized_start=7210
  _globals['_APIITEM_TOGRAPHRESPONSE']._serialized_end=7265
  _globals['_APIITEM_TONODE1REQUEST']._serialized_start=7267
  _globals['_APIITEM_TONODE1REQUEST']._serialized_end=7324
  _globals['_APIITEM_TONODE1RESPONSE']._serialized_start=7326
  _globals['_APIITEM_TONODE1RESPONSE']._serialized_end=7381
  _globals['_APIITEM_TONODEREQUEST']._serialized_start=7383
  _globals['_APIITEM_TONODEREQUEST']._serialized_end=7439
  _globals['_APIITEM_TONODERESPONSE']._serialized_start=7441
  _globals['_APIITEM_TONODERESPONSE']._serialized_end=7495
  _globals['_APIITEM_UIOPERATIONFLAGSREQUEST']._serialized_start=7497
  _globals['_APIITEM_UIOPERATIONFLAGSREQUEST']._serialized_end=7563
  _globals['_APIITEM_UIOPERATIONFLAGSRESPONSE']._serialized_start=7565
  _globals['_APIITEM_UIOPERATIONFLAGSRESPONSE']._serialized_end=7626
  _globals['_APIITEM_UNIQUEIDREQUEST']._serialized_start=7628
  _globals['_APIITEM_UNIQUEIDREQUEST']._serialized_end=7686
  _globals['_APIITEM_UNIQUEIDRESPONSE']._serialized_start=7688
  _globals['_APIITEM_UNIQUEIDRESPONSE']._serialized_end=7722
  _globals['_APIITEM_VERSIONREQUEST']._serialized_start=7724
  _globals['_APIITEM_VERSIONREQUEST']._serialized_end=7781
  _globals['_APIITEM_VERSIONRESPONSE']._serialized_start=7783
  _globals['_APIITEM_VERSIONRESPONSE']._serialized_end=7816
  _globals['_APIITEMSERVICE']._serialized_start=7819
  _globals['_APIITEMSERVICE']._serialized_end=13588
# @@protoc_insertion_point(module_scope)
