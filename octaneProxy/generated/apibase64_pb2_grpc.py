# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import apibase64_pb2 as apibase64__pb2


class ApiBase64ServiceStub(object):
    """GRPC interface definition for class 'ApiBase64' from 'apibase64.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.encode = channel.unary_unary(
                '/octaneapi.ApiBase64Service/encode',
                request_serializer=apibase64__pb2.ApiBase64.encodeRequest.SerializeToString,
                response_deserializer=apibase64__pb2.ApiBase64.encodeResponse.FromString,
                _registered_method=True)
        self.decode = channel.unary_unary(
                '/octaneapi.ApiBase64Service/decode',
                request_serializer=apibase64__pb2.ApiBase64.decodeRequest.SerializeToString,
                response_deserializer=apibase64__pb2.ApiBase64.decodeResponse.FromString,
                _registered_method=True)


class ApiBase64ServiceServicer(object):
    """GRPC interface definition for class 'ApiBase64' from 'apibase64.h'
    """

    def encode(self, request, context):
        """/ Encodes the given data block as base64
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def decode(self, request, context):
        """/ Encodes the given data block as base64
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiBase64ServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'encode': grpc.unary_unary_rpc_method_handler(
                    servicer.encode,
                    request_deserializer=apibase64__pb2.ApiBase64.encodeRequest.FromString,
                    response_serializer=apibase64__pb2.ApiBase64.encodeResponse.SerializeToString,
            ),
            'decode': grpc.unary_unary_rpc_method_handler(
                    servicer.decode,
                    request_deserializer=apibase64__pb2.ApiBase64.decodeRequest.FromString,
                    response_serializer=apibase64__pb2.ApiBase64.decodeResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiBase64Service', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiBase64Service', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiBase64Service(object):
    """GRPC interface definition for class 'ApiBase64' from 'apibase64.h'
    """

    @staticmethod
    def encode(request,
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
            '/octaneapi.ApiBase64Service/encode',
            apibase64__pb2.ApiBase64.encodeRequest.SerializeToString,
            apibase64__pb2.ApiBase64.encodeResponse.FromString,
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
    def decode(request,
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
            '/octaneapi.ApiBase64Service/decode',
            apibase64__pb2.ApiBase64.decodeRequest.SerializeToString,
            apibase64__pb2.ApiBase64.decodeResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
