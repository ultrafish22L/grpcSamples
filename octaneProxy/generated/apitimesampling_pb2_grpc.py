# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import apitimesampling_pb2 as apitimesampling__pb2


class ApiTimeSamplingServiceStub(object):
    """GRPC interface definition for class 'ApiTimeSampling' from 'apitimesampling.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.endTimeAuto = channel.unary_unary(
                '/octaneapi.ApiTimeSamplingService/endTimeAuto',
                request_serializer=apitimesampling__pb2.ApiTimeSampling.endTimeAutoRequest.SerializeToString,
                response_deserializer=apitimesampling__pb2.ApiTimeSampling.endTimeAutoResponse.FromString,
                _registered_method=True)


class ApiTimeSamplingServiceServicer(object):
    """GRPC interface definition for class 'ApiTimeSampling' from 'apitimesampling.h'
    """

    def endTimeAuto(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiTimeSamplingServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'endTimeAuto': grpc.unary_unary_rpc_method_handler(
                    servicer.endTimeAuto,
                    request_deserializer=apitimesampling__pb2.ApiTimeSampling.endTimeAutoRequest.FromString,
                    response_serializer=apitimesampling__pb2.ApiTimeSampling.endTimeAutoResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiTimeSamplingService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiTimeSamplingService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiTimeSamplingService(object):
    """GRPC interface definition for class 'ApiTimeSampling' from 'apitimesampling.h'
    """

    @staticmethod
    def endTimeAuto(request,
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
            '/octaneapi.ApiTimeSamplingService/endTimeAuto',
            apitimesampling__pb2.ApiTimeSampling.endTimeAutoRequest.SerializeToString,
            apitimesampling__pb2.ApiTimeSampling.endTimeAutoResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
