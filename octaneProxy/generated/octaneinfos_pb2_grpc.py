# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import octaneinfos_pb2 as octaneinfos__pb2


class ApiAttributeInfoServiceStub(object):
    """GRPC interface definition for class 'ApiAttributeInfo' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.isValidFor = channel.unary_unary(
                '/octaneapi.ApiAttributeInfoService/isValidFor',
                request_serializer=octaneinfos__pb2.ApiAttributeInfo.isValidForRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiAttributeInfo.isValidForResponse.FromString,
                _registered_method=True)


class ApiAttributeInfoServiceServicer(object):
    """GRPC interface definition for class 'ApiAttributeInfo' from 'octaneinfos.h'
    """

    def isValidFor(self, request, context):
        """/ fast version validity check
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiAttributeInfoServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'isValidFor': grpc.unary_unary_rpc_method_handler(
                    servicer.isValidFor,
                    request_deserializer=octaneinfos__pb2.ApiAttributeInfo.isValidForRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiAttributeInfo.isValidForResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiAttributeInfoService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiAttributeInfoService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiAttributeInfoService(object):
    """GRPC interface definition for class 'ApiAttributeInfo' from 'octaneinfos.h'
    """

    @staticmethod
    def isValidFor(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiAttributeInfoService/isValidFor',
            octaneinfos__pb2.ApiAttributeInfo.isValidForRequest.SerializeToString,
            octaneinfos__pb2.ApiAttributeInfo.isValidForResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiCompatibilityModeInfoServiceStub(object):
    """GRPC interface definition for class 'ApiBitMaskPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBitMaskPinInfo_Label' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBoolPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiCompatibilityModeInfo' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.startVersion = channel.unary_unary(
                '/octaneapi.ApiCompatibilityModeInfoService/startVersion',
                request_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionResponse.FromString,
                _registered_method=True)
        self.name = channel.unary_unary(
                '/octaneapi.ApiCompatibilityModeInfoService/name',
                request_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.nameRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.nameResponse.FromString,
                _registered_method=True)
        self.description = channel.unary_unary(
                '/octaneapi.ApiCompatibilityModeInfoService/description',
                request_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionResponse.FromString,
                _registered_method=True)


class ApiCompatibilityModeInfoServiceServicer(object):
    """GRPC interface definition for class 'ApiBitMaskPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBitMaskPinInfo_Label' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBoolPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiCompatibilityModeInfo' from 'octaneinfos.h'
    """

    def startVersion(self, request, context):
        """/ Gets the first version of Octane that has this behavior, i
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def name(self, request, context):
        """/ Gets the name of the compatibility mode
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def description(self, request, context):
        """/ Gets a brief description of how this behavior differs from the behavior of the current
        / version of Octane
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiCompatibilityModeInfoServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'startVersion': grpc.unary_unary_rpc_method_handler(
                    servicer.startVersion,
                    request_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionResponse.SerializeToString,
            ),
            'name': grpc.unary_unary_rpc_method_handler(
                    servicer.name,
                    request_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.nameRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.nameResponse.SerializeToString,
            ),
            'description': grpc.unary_unary_rpc_method_handler(
                    servicer.description,
                    request_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiCompatibilityModeInfoService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiCompatibilityModeInfoService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiCompatibilityModeInfoService(object):
    """GRPC interface definition for class 'ApiBitMaskPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBitMaskPinInfo_Label' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiBoolPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiCompatibilityModeInfo' from 'octaneinfos.h'
    """

    @staticmethod
    def startVersion(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiCompatibilityModeInfoService/startVersion',
            octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionRequest.SerializeToString,
            octaneinfos__pb2.ApiCompatibilityModeInfo.startVersionResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def name(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiCompatibilityModeInfoService/name',
            octaneinfos__pb2.ApiCompatibilityModeInfo.nameRequest.SerializeToString,
            octaneinfos__pb2.ApiCompatibilityModeInfo.nameResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def description(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiCompatibilityModeInfoService/description',
            octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionRequest.SerializeToString,
            octaneinfos__pb2.ApiCompatibilityModeInfo.descriptionResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiCompatibilityModeInfoSetServiceStub(object):
    """GRPC interface definition for class 'ApiCompatibilityModeInfoSet' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.size = channel.unary_unary(
                '/octaneapi.ApiCompatibilityModeInfoSetService/size',
                request_serializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeResponse.FromString,
                _registered_method=True)
        self.info = channel.unary_unary(
                '/octaneapi.ApiCompatibilityModeInfoSetService/info',
                request_serializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoResponse.FromString,
                _registered_method=True)


class ApiCompatibilityModeInfoSetServiceServicer(object):
    """GRPC interface definition for class 'ApiCompatibilityModeInfoSet' from 'octaneinfos.h'
    """

    def size(self, request, context):
        """/ Gets the number of compatibility modes
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def info(self, request, context):
        """/ Gets the info for one of the compatibility modes
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiCompatibilityModeInfoSetServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'size': grpc.unary_unary_rpc_method_handler(
                    servicer.size,
                    request_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeResponse.SerializeToString,
            ),
            'info': grpc.unary_unary_rpc_method_handler(
                    servicer.info,
                    request_deserializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiCompatibilityModeInfoSetService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiCompatibilityModeInfoSetService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiCompatibilityModeInfoSetService(object):
    """GRPC interface definition for class 'ApiCompatibilityModeInfoSet' from 'octaneinfos.h'
    """

    @staticmethod
    def size(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiCompatibilityModeInfoSetService/size',
            octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeRequest.SerializeToString,
            octaneinfos__pb2.ApiCompatibilityModeInfoSet.sizeResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def info(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiCompatibilityModeInfoSetService/info',
            octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoRequest.SerializeToString,
            octaneinfos__pb2.ApiCompatibilityModeInfoSet.infoResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiNodePinInfoServiceStub(object):
    """GRPC interface definition for class 'ApiEnumPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiEnumPinInfo_Value' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeGraphInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodePinInfo' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.isValidFor1 = channel.unary_unary(
                '/octaneapi.ApiNodePinInfoService/isValidFor1',
                request_serializer=octaneinfos__pb2.ApiNodePinInfo.isValidForRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiNodePinInfo.isValidForResponse.FromString,
                _registered_method=True)


class ApiNodePinInfoServiceServicer(object):
    """GRPC interface definition for class 'ApiEnumPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiEnumPinInfo_Value' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeGraphInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodePinInfo' from 'octaneinfos.h'
    """

    def isValidFor1(self, request, context):
        """/ fast version validity check
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiNodePinInfoServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'isValidFor1': grpc.unary_unary_rpc_method_handler(
                    servicer.isValidFor1,
                    request_deserializer=octaneinfos__pb2.ApiNodePinInfo.isValidForRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiNodePinInfo.isValidForResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiNodePinInfoService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiNodePinInfoService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiNodePinInfoService(object):
    """GRPC interface definition for class 'ApiEnumPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiEnumPinInfo_Value' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiFloatPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiIntPinInfo_DimInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeGraphInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodeInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiNodePinInfo' from 'octaneinfos.h'
    """

    @staticmethod
    def isValidFor1(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiNodePinInfoService/isValidFor1',
            octaneinfos__pb2.ApiNodePinInfo.isValidForRequest.SerializeToString,
            octaneinfos__pb2.ApiNodePinInfo.isValidForResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiTextureNodeTypeInfoServiceStub(object):
    """GRPC interface definition for class 'ApiOcioColorSpacePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioLookPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioViewPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiProjectionPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiStringPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.findConfiguration1 = channel.unary_unary(
                '/octaneapi.ApiTextureNodeTypeInfoService/findConfiguration1',
                request_serializer=octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Request.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Response.FromString,
                _registered_method=True)


class ApiTextureNodeTypeInfoServiceServicer(object):
    """GRPC interface definition for class 'ApiOcioColorSpacePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioLookPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioViewPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiProjectionPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiStringPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo' from 'octaneinfos.h'
    """

    def findConfiguration1(self, request, context):
        """/ Find the configuration that has the given node interface of texture value types of output and inputs
        /
        / 
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiTextureNodeTypeInfoServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'findConfiguration1': grpc.unary_unary_rpc_method_handler(
                    servicer.findConfiguration1,
                    request_deserializer=octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Request.FromString,
                    response_serializer=octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Response.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiTextureNodeTypeInfoService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiTextureNodeTypeInfoService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiTextureNodeTypeInfoService(object):
    """GRPC interface definition for class 'ApiOcioColorSpacePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioLookPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiOcioViewPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiProjectionPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiStringPinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo' from 'octaneinfos.h'
    """

    @staticmethod
    def findConfiguration1(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTextureNodeTypeInfoService/findConfiguration1',
            octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Request.SerializeToString,
            octaneinfos__pb2.ApiTextureNodeTypeInfo.findConfiguration1Response.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiTexturePinTypeInfoServiceStub(object):
    """GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Interface' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Parameters' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinTypeInfo' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.getTextureValueType = channel.unary_unary(
                '/octaneapi.ApiTexturePinTypeInfoService/getTextureValueType',
                request_serializer=octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeResponse.FromString,
                _registered_method=True)


class ApiTexturePinTypeInfoServiceServicer(object):
    """GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Interface' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Parameters' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinTypeInfo' from 'octaneinfos.h'
    """

    def getTextureValueType(self, request, context):
        """/ Get the texture value type of a pin for given configuration parameters
        /
        / 
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiTexturePinTypeInfoServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'getTextureValueType': grpc.unary_unary_rpc_method_handler(
                    servicer.getTextureValueType,
                    request_deserializer=octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiTexturePinTypeInfoService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiTexturePinTypeInfoService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiTexturePinTypeInfoService(object):
    """GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Interface' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTextureNodeTypeInfo_Configuration_Parameters' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinInfo' from 'octaneinfos.h'

    GRPC interface definition for class 'ApiTexturePinTypeInfo' from 'octaneinfos.h'
    """

    @staticmethod
    def getTextureValueType(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTexturePinTypeInfoService/getTextureValueType',
            octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeRequest.SerializeToString,
            octaneinfos__pb2.ApiTexturePinTypeInfo.getTextureValueTypeResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)


class ApiTextureValueTypeSetServiceStub(object):
    """GRPC interface definition for class 'ApiTextureValueTypeSet' from 'octaneinfos.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.size1 = channel.unary_unary(
                '/octaneapi.ApiTextureValueTypeSetService/size1',
                request_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.sizeRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.sizeResponse.FromString,
                _registered_method=True)
        self.at = channel.unary_unary(
                '/octaneapi.ApiTextureValueTypeSetService/at',
                request_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.atRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.atResponse.FromString,
                _registered_method=True)
        self.contains = channel.unary_unary(
                '/octaneapi.ApiTextureValueTypeSetService/contains',
                request_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.containsRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.containsResponse.FromString,
                _registered_method=True)
        self.bitField = channel.unary_unary(
                '/octaneapi.ApiTextureValueTypeSetService/bitField',
                request_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldRequest.SerializeToString,
                response_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldResponse.FromString,
                _registered_method=True)


class ApiTextureValueTypeSetServiceServicer(object):
    """GRPC interface definition for class 'ApiTextureValueTypeSet' from 'octaneinfos.h'
    """

    def size1(self, request, context):
        """/ Gets the number of texture value types
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def at(self, request, context):
        """/ Gets the TextureValueType at a given index (TEXTURE_VALUE_TYPE_UNKNOWN if out of bounds)
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def contains(self, request, context):
        """/ Checks if a given TextureValueType is included in the set
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def bitField(self, request, context):
        """/ Return the bitfield encoding all the texture value types in the set
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiTextureValueTypeSetServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'size1': grpc.unary_unary_rpc_method_handler(
                    servicer.size1,
                    request_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.sizeRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.sizeResponse.SerializeToString,
            ),
            'at': grpc.unary_unary_rpc_method_handler(
                    servicer.at,
                    request_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.atRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.atResponse.SerializeToString,
            ),
            'contains': grpc.unary_unary_rpc_method_handler(
                    servicer.contains,
                    request_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.containsRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.containsResponse.SerializeToString,
            ),
            'bitField': grpc.unary_unary_rpc_method_handler(
                    servicer.bitField,
                    request_deserializer=octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldRequest.FromString,
                    response_serializer=octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiTextureValueTypeSetService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiTextureValueTypeSetService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiTextureValueTypeSetService(object):
    """GRPC interface definition for class 'ApiTextureValueTypeSet' from 'octaneinfos.h'
    """

    @staticmethod
    def size1(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTextureValueTypeSetService/size1',
            octaneinfos__pb2.ApiTextureValueTypeSet.sizeRequest.SerializeToString,
            octaneinfos__pb2.ApiTextureValueTypeSet.sizeResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def at(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTextureValueTypeSetService/at',
            octaneinfos__pb2.ApiTextureValueTypeSet.atRequest.SerializeToString,
            octaneinfos__pb2.ApiTextureValueTypeSet.atResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def contains(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTextureValueTypeSetService/contains',
            octaneinfos__pb2.ApiTextureValueTypeSet.containsRequest.SerializeToString,
            octaneinfos__pb2.ApiTextureValueTypeSet.containsResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)

    @staticmethod
    def bitField(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(
            request,
            target,
            '/octaneapi.ApiTextureValueTypeSetService/bitField',
            octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldRequest.SerializeToString,
            octaneinfos__pb2.ApiTextureValueTypeSet.bitFieldResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
