# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc
import warnings

import apigaussiansplatting_pb2 as apigaussiansplatting__pb2

GRPC_GENERATED_VERSION = '1.73.1'
GRPC_VERSION = grpc.__version__
_version_not_supported = False

try:
    from grpc._utilities import first_version_is_lower
    _version_not_supported = first_version_is_lower(GRPC_VERSION, GRPC_GENERATED_VERSION)
except ImportError:
    _version_not_supported = True

if _version_not_supported:
    raise RuntimeError(
        f'The grpc package installed is at version {GRPC_VERSION},'
        + f' but the generated code in apigaussiansplatting_pb2_grpc.py depends on'
        + f' grpcio>={GRPC_GENERATED_VERSION}.'
        + f' Please upgrade your grpc module to grpcio>={GRPC_GENERATED_VERSION}'
        + f' or downgrade your generated code using grpcio-tools<={GRPC_VERSION}.'
    )


class ApiGaussianSplatCloudNodeServiceStub(object):
    """GRPC interface definition for class 'ApiGaussianSplatCloudNode' from 'apigaussiansplatting.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.create = channel.unary_unary(
                '/octaneapi.ApiGaussianSplatCloudNodeService/create',
                request_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createRequest.SerializeToString,
                response_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createResponse.FromString,
                _registered_method=True)
        self.obtain = channel.unary_unary(
                '/octaneapi.ApiGaussianSplatCloudNodeService/obtain',
                request_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainRequest.SerializeToString,
                response_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainResponse.FromString,
                _registered_method=True)
        self.setAttributesFromPly = channel.unary_unary(
                '/octaneapi.ApiGaussianSplatCloudNodeService/setAttributesFromPly',
                request_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyRequest.SerializeToString,
                response_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyResponse.FromString,
                _registered_method=True)


class ApiGaussianSplatCloudNodeServiceServicer(object):
    """GRPC interface definition for class 'ApiGaussianSplatCloudNode' from 'apigaussiansplatting.h'
    """

    def create(self, request, context):
        """/ Creates a new node of the NT_GEO_GAUSSIAN_SPLAT type
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def obtain(self, request, context):
        """/ Returns ApiGaussianSplatCloudNode interface for the ApiNode of NT_GEO_GAUSSIAN_SPLAT type
        / 
        / 
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def setAttributesFromPly(self, request, context):
        """/ Writes the Gaussian splat PLY attribute arrays into the node attributes
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiGaussianSplatCloudNodeServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'create': grpc.unary_unary_rpc_method_handler(
                    servicer.create,
                    request_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createRequest.FromString,
                    response_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createResponse.SerializeToString,
            ),
            'obtain': grpc.unary_unary_rpc_method_handler(
                    servicer.obtain,
                    request_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainRequest.FromString,
                    response_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainResponse.SerializeToString,
            ),
            'setAttributesFromPly': grpc.unary_unary_rpc_method_handler(
                    servicer.setAttributesFromPly,
                    request_deserializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyRequest.FromString,
                    response_serializer=apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiGaussianSplatCloudNodeService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiGaussianSplatCloudNodeService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiGaussianSplatCloudNodeService(object):
    """GRPC interface definition for class 'ApiGaussianSplatCloudNode' from 'apigaussiansplatting.h'
    """

    @staticmethod
    def create(request,
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
            '/octaneapi.ApiGaussianSplatCloudNodeService/create',
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createRequest.SerializeToString,
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.createResponse.FromString,
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
    def obtain(request,
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
            '/octaneapi.ApiGaussianSplatCloudNodeService/obtain',
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainRequest.SerializeToString,
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.obtainResponse.FromString,
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
    def setAttributesFromPly(request,
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
            '/octaneapi.ApiGaussianSplatCloudNodeService/setAttributesFromPly',
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyRequest.SerializeToString,
            apigaussiansplatting__pb2.ApiGaussianSplatCloudNode.setAttributesFromPlyResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
