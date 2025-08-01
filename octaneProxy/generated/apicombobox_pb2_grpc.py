# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import apicombobox_pb2 as apicombobox__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2


class ApiComboBoxServiceStub(object):
    """GRPC interface definition for class 'ApiComboBox' from 'apicombobox.h'
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.create = channel.unary_unary(
                '/octaneapi.ApiComboBoxService/create',
                request_serializer=apicombobox__pb2.ApiComboBox.createRequest.SerializeToString,
                response_deserializer=apicombobox__pb2.ApiComboBox.createResponse.FromString,
                _registered_method=True)
        self.destroy = channel.unary_unary(
                '/octaneapi.ApiComboBoxService/destroy',
                request_serializer=apicombobox__pb2.ApiComboBox.destroyRequest.SerializeToString,
                response_deserializer=google_dot_protobuf_dot_empty__pb2.Empty.FromString,
                _registered_method=True)
        self.setSelectedId = channel.unary_unary(
                '/octaneapi.ApiComboBoxService/setSelectedId',
                request_serializer=apicombobox__pb2.ApiComboBox.setSelectedIdRequest.SerializeToString,
                response_deserializer=google_dot_protobuf_dot_empty__pb2.Empty.FromString,
                _registered_method=True)
        self.selectedId = channel.unary_unary(
                '/octaneapi.ApiComboBoxService/selectedId',
                request_serializer=apicombobox__pb2.ApiComboBox.selectedIdRequest.SerializeToString,
                response_deserializer=apicombobox__pb2.ApiComboBox.selectedIdResponse.FromString,
                _registered_method=True)
        self.text = channel.unary_unary(
                '/octaneapi.ApiComboBoxService/text',
                request_serializer=apicombobox__pb2.ApiComboBox.textRequest.SerializeToString,
                response_deserializer=apicombobox__pb2.ApiComboBox.textResponse.FromString,
                _registered_method=True)


class ApiComboBoxServiceServicer(object):
    """GRPC interface definition for class 'ApiComboBox' from 'apicombobox.h'
    """

    def create(self, request, context):
        """/ Creates a new combo box
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def destroy(self, request, context):
        """/ Destroys this combo box
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def setSelectedId(self, request, context):
        """/ Sets one of the items to be the current selection
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def selectedId(self, request, context):
        """/ Returns the ID of the item that's currently shown in the box
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def text(self, request, context):
        """/ Returns the text of the item currently selected in the combo box or an empty string if
        / nothing is selected
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ApiComboBoxServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'create': grpc.unary_unary_rpc_method_handler(
                    servicer.create,
                    request_deserializer=apicombobox__pb2.ApiComboBox.createRequest.FromString,
                    response_serializer=apicombobox__pb2.ApiComboBox.createResponse.SerializeToString,
            ),
            'destroy': grpc.unary_unary_rpc_method_handler(
                    servicer.destroy,
                    request_deserializer=apicombobox__pb2.ApiComboBox.destroyRequest.FromString,
                    response_serializer=google_dot_protobuf_dot_empty__pb2.Empty.SerializeToString,
            ),
            'setSelectedId': grpc.unary_unary_rpc_method_handler(
                    servicer.setSelectedId,
                    request_deserializer=apicombobox__pb2.ApiComboBox.setSelectedIdRequest.FromString,
                    response_serializer=google_dot_protobuf_dot_empty__pb2.Empty.SerializeToString,
            ),
            'selectedId': grpc.unary_unary_rpc_method_handler(
                    servicer.selectedId,
                    request_deserializer=apicombobox__pb2.ApiComboBox.selectedIdRequest.FromString,
                    response_serializer=apicombobox__pb2.ApiComboBox.selectedIdResponse.SerializeToString,
            ),
            'text': grpc.unary_unary_rpc_method_handler(
                    servicer.text,
                    request_deserializer=apicombobox__pb2.ApiComboBox.textRequest.FromString,
                    response_serializer=apicombobox__pb2.ApiComboBox.textResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'octaneapi.ApiComboBoxService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('octaneapi.ApiComboBoxService', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ApiComboBoxService(object):
    """GRPC interface definition for class 'ApiComboBox' from 'apicombobox.h'
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
            '/octaneapi.ApiComboBoxService/create',
            apicombobox__pb2.ApiComboBox.createRequest.SerializeToString,
            apicombobox__pb2.ApiComboBox.createResponse.FromString,
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
    def destroy(request,
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
            '/octaneapi.ApiComboBoxService/destroy',
            apicombobox__pb2.ApiComboBox.destroyRequest.SerializeToString,
            google_dot_protobuf_dot_empty__pb2.Empty.FromString,
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
    def setSelectedId(request,
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
            '/octaneapi.ApiComboBoxService/setSelectedId',
            apicombobox__pb2.ApiComboBox.setSelectedIdRequest.SerializeToString,
            google_dot_protobuf_dot_empty__pb2.Empty.FromString,
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
    def selectedId(request,
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
            '/octaneapi.ApiComboBoxService/selectedId',
            apicombobox__pb2.ApiComboBox.selectedIdRequest.SerializeToString,
            apicombobox__pb2.ApiComboBox.selectedIdResponse.FromString,
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
    def text(request,
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
            '/octaneapi.ApiComboBoxService/text',
            apicombobox__pb2.ApiComboBox.textRequest.SerializeToString,
            apicombobox__pb2.ApiComboBox.textResponse.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
