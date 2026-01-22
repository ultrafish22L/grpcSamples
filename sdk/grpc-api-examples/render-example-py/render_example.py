import grpc
import apiprojectmanager_pb2
import apiprojectmanager_pb2_grpc
from apiprojectmanager_pb2_grpc import ApiProjectManagerServiceStub
import apinodesystem_3_pb2 # apiitem
import apinodesystem_3_pb2_grpc
import apinodesystem_7_pb2 # apinode
import apinodesystem_7_pb2_grpc
import apichangemanager_pb2
import apichangemanager_pb2_grpc
import apirender_pb2
import apirender_pb2_grpc
import callbackstream_pb2
import callbackstream_pb2_grpc
from google.protobuf import empty_pb2
import common_pb2
from common_pb2 import float_3 as Float3  # or common_pb2.Float3 depending on your proto
import octaneenums_pb2
import octaneids_pb2
import os
from pathlib import Path
from PIL import Image
import numpy as np
import cv2
import math
from math import sin, cos, sqrt
import threading
from typing import List


OBJECTAMOUNT      =  100
CUBEAMOUNT        =  1
DIFFUSEMATAMOUNT  =  30
GLOSSYMATAMOUNT   =  30
RGBTEXAMOUNT      =  50
IMGTEXAMOUNT      =  5

# ---- Global Octane node handles ----
g_image_textures = []     # IMGTEXAMOUNT = 5
g_rgb_textures = []       # RGBTEXAMOUNT = 50
g_diffuse_materials = []  # DIFFUSEMATAMOUNT = 30
g_glossy_materials = []   # GLOSSYMATAMOUNT = 30
g_material_maps = []      # OBJECTAMOUNT + CUBEAMOUNT = 101
global_channel = None     
g_sphere_mesh = None
g_spin_cube = None
g_render_target = None
g_render_passes = None
g_cube_placement_node = None
g_cube_mat = None

# Cube initial translation
g_cube_init_translate = common_pb2.float_3(x=0.0, y=-2.2, z=0.0)

# Give the vector message an alias that matches C++ naming conventions.
# Adjust the message name if your .proto defines it differently
Float3 = common_pb2.float_3   # or common_pb2.Float3, depending on your proto

# Raw vertex data: simple numeric tuples
_SPHERE_VERTICES_RAW = [
    (0.0000, 0.0000, 0.0000),
    (0.0000, 0.0000, 1.0000),
    (0.5257, 0.0000, 0.8507),
    (0.1625, 0.5000, 0.8507),
    (0.8944, 0.0000, 0.4472),
    (0.6882, 0.5000, 0.5257),
    (0.2764, 0.8507, 0.4472),
    (-0.4253, 0.3090, 0.8507),
    (-0.2629, 0.8090, 0.5257),
    (-0.7236, 0.5257, 0.4472),
    (-0.4253, -0.3090, 0.8507),
    (-0.8507, -0.0000, 0.5257),
    (-0.7236, -0.5257, 0.4472),
    (0.1625, -0.5000, 0.8507),
    (-0.2629, -0.8090, 0.5257),
    (0.2764, -0.8507, 0.4472),
    (0.6882, -0.5000, 0.5257),
    (0.9511, -0.3090, 0.0000),
    (0.9511, 0.3090, 0.0000),
    (0.7236, -0.5257, -0.4472),
    (0.8507, 0.0000, -0.5257),
    (0.7236, 0.5257, -0.4472),
    (0.5878, 0.8090, 0.0000),
    (-0.0000, 1.0000, 0.0000),
    (0.2629, 0.8090, -0.5257),
    (-0.2764, 0.8507, -0.4472),
    (-0.5878, 0.8090, 0.0000),
    (-0.9511, 0.3090, 0.0000),
    (-0.6882, 0.5000, -0.5257),
    (-0.8944, -0.0000, -0.4472),
    (-0.9511, -0.3090, 0.0000),
    (-0.5878, -0.8090, 0.0000),
    (-0.6882, -0.5000, -0.5257),
    (-0.2764, -0.8507, -0.4472),
    (0.0000, -1.0000, 0.0000),
    (0.5878, -0.8090, 0.0000),
    (0.2629, -0.8090, -0.5257),
    (0.0000, 0.0000, -1.0000),
    (-0.1625, 0.5000, -0.8507),
    (0.4253, 0.3090, -0.8507),
    (-0.5257, -0.0000, -0.8507),
    (-0.1625, -0.5000, -0.8507),
    (0.4253, -0.3090, -0.8507),
]

# Sphere faces: flattened list of triangle vertex indices
SPHERE_FACES = [
    1, 2, 3, 2, 4, 5, 2, 5, 3, 3, 5, 6, 1, 3, 7, 3, 6, 8, 3, 8, 7,
    7, 8, 9, 1, 7, 10, 7, 9, 11, 7, 11, 10, 10, 11, 12, 1, 10, 13,
    10, 12, 14, 10, 14, 13, 13, 14, 15, 1, 13, 2, 13, 15, 16, 13,
    16, 2, 2, 16, 4, 4, 17, 18, 17, 19, 20, 17, 20, 18, 18, 20, 21,
    6, 22, 23, 22, 21, 24, 22, 24, 23, 23, 24, 25, 9, 26, 27, 26,
    25, 28, 26, 28, 27, 27, 28, 29, 12, 30, 31, 30, 29, 32, 30, 32,
    31, 31, 32, 33, 15, 34, 35, 34, 33, 36, 34, 36, 35, 35, 36, 19,
    21, 22, 18, 22, 6, 5, 22, 5, 18, 18, 5, 4, 25, 26, 23, 26, 9, 8,
    26, 8, 23, 23, 8, 6, 29, 30, 27, 30, 12, 11, 30, 11, 27, 27, 11,
    9, 33, 34, 31, 34, 15, 14, 34, 14, 31, 31, 14, 12, 19, 17, 35,
    17, 4, 16, 17, 16, 35, 35, 16, 15, 37, 38, 39, 38, 25, 24, 38,
    24, 39, 39, 24, 21, 37, 40, 38, 40, 29, 28, 40, 28, 38, 38, 28,
    25, 37, 41, 40, 41, 33, 32, 41, 32, 40, 40, 32, 29, 37, 42, 41,
    42, 19, 36, 42, 36, 41, 41, 36, 33, 37, 39, 42, 39, 21, 20, 39,
    20, 42, 42, 20, 19
]

# Cube vertex positions (8 vertices)
_CUBE_VERTICES_RAW = [
    (-0.500000, 0.000000,  0.500000),
    ( 0.500000, 0.000000,  0.500000),
    (-0.500000, 0.000000, -0.500000),
    ( 0.500000, 0.000000, -0.500000),
    (-0.500000, 1.000000,  0.500000),
    ( 0.500000, 1.000000,  0.500000),
    (-0.500000, 1.000000, -0.500000),
    ( 0.500000, 1.000000, -0.500000),
]

CUBE_VERTICES: List[Float3] = [
    Float3(x=float(x), y=float(y), z=float(z))
    for (x, y, z) in _CUBE_VERTICES_RAW
]

# Cube triangle faces (12 triangles / 36 indices)
CUBE_FACES = [
    0, 2, 3,  3, 1, 0,
    4, 5, 7,  7, 6, 4,
    0, 1, 5,  5, 4, 0,
    1, 3, 7,  7, 5, 1,
    3, 2, 6,  6, 7, 3,
    2, 0, 4,  4, 6, 2,
]

"""Flattened list of cube triangle vertex indices."""
# Convert to protobuf messages once at module import
SPHERE_VERTICES = [Float3(x=float(x), y=float(y), z=float(z))
                   for (x, y, z) in _SPHERE_VERTICES_RAW]
 
# Linear Congruential Generator identical to the C++ demo version
INIT_LCG_SEED = 123456789  # same starting value
g_random_state = INIT_LCG_SEED


def _update_lcg_random():
    global g_random_state
    g_random_state = (g_random_state * 1664525 + 1013904223) & 0xffffffff


def reset_lcg():
    """Reset the LCG state to its initial seed."""
    global g_random_state
    g_random_state = INIT_LCG_SEED


def lcg_random():
    """Return a 32‑bit value with the same endianness 'swizzle' as C++ version."""
    _update_lcg_random()
    result = ((g_random_state & 0xf0f0f0f0) >> 4) | ((g_random_state & 0x0f0f0f0f) << 4)
    result = ((result & 0xff000000) >> 24) | ((result & 0x00ff0000) >> 8) | \
             ((result & 0x0000ff00) << 8) | ((result & 0x000000ff) << 24)
    return result & 0xffffffff


def lcg_random_bool():
    _update_lcg_random()
    return g_random_state < 0x80000000


def lcg_random_float():
    """Generate a reproducible float [0,1] exactly like the C++ code."""
    _update_lcg_random()
    return 2.32830644e-10 * g_random_state  # (1 / 2**32)


def lcg_random_range(range_start, range_end=None):
    """Same as the two C++ overloads."""
    _update_lcg_random()
    if range_end is None:
        range_start, range_end = 0, range_start
    r = range_end - range_start
    return range_start + ((r * g_random_state) >> 32)

def get_random_rgb_texture():
    return g_rgb_textures[lcg_random_range(len(g_rgb_textures))]

def get_random_img_texture():
    return g_image_textures[lcg_random_range(len(g_image_textures))]

def get_random_texture():
    return get_random_rgb_texture() if lcg_random_bool() else get_random_img_texture()

def get_random_diffuse_mat():
    return g_diffuse_materials[lcg_random_range(DIFFUSEMATAMOUNT)]

def get_random_glossy_mat():
    return g_glossy_materials[lcg_random_range(GLOSSYMATAMOUNT)]

def normalized(x, y, z):
    """
    Return a unit-length (normalized) 3D vector.

    Args:
        x, y, z: floats – components of the vector

    Returns:
        tuple (nx, ny, nz)
    """
    length_sq = x * x + y * y + z * z
    if length_sq > 1e-16:
        inv_len = 1.0 / math.sqrt(length_sq)
        return x * inv_len, y * inv_len, z * inv_len
    return 0.0, 0.0, 0.0

def make_translation_matrix(tx, ty, tz):
    """
    Build a 3×4 translation matrix (MatrixF) identical to the C++ version.

    Args:
        tx, ty, tz: float – translation amounts along X, Y, Z axes

    Returns:
        apirender_pb2.MatrixF – protobuf matrix message
    """
    mat = common_pb2.MatrixF()

    # Row 0
    r0 = mat.m.add()
    r0.x, r0.y, r0.z, r0.w = 1.0, 0.0, 0.0, tx

    # Row 1
    r1 = mat.m.add()
    r1.x, r1.y, r1.z, r1.w = 0.0, 1.0, 0.0, ty

    # Row 2
    r2 = mat.m.add()
    r2.x, r2.y, r2.z, r2.w = 0.0, 0.0, 1.0, tz

    return mat

def root_node_graph(channel) -> "apiprojectmanager_pb2.ObjectRef":
    """
    Calls ApiProjectManager.rootNodeGraph and returns an ObjectRef.
    Raises grpc.RpcError on failure.
    """
    stub = ApiProjectManagerServiceStub(channel)

    # Build the request (empty message)
    request = apiprojectmanager_pb2.ApiProjectManager.rootNodeGraphRequest()

    # Make the call
    response = stub.rootNodeGraph(request)

    # Return the ObjectRef (result field)
    return response.result

 


def reset_project(channel, suppress_ui: bool = True) -> bool:
    """
    Call ApiProjectManager.resetProject on the Octane gRPC server.

    Args:
        channel: gRPC channel connected to octane.exe
        suppress_ui: optional flag (default True) to suppress UI updates on reset

    Returns:
        bool – True if reset succeeded, False otherwise.

    Raises:
        grpc.RpcError – if the gRPC call itself fails (e.g. network or server error)
    """
    # 1) Build the stub for the ApiProjectManager service
    stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(channel)

    # 2) Construct the request message
    request = apiprojectmanager_pb2.ApiProjectManager.resetProjectRequest()
    request.suppressUI = suppress_ui

    # 3) Perform the RPC
    response = stub.resetProject(request)

    # 4) Return the Boolean result
    return response.result
 

def set_render_target_node(channel, target_node_ref) -> bool:
    """
    Calls ApiRenderEngine.setRenderTargetNode on the server.

    Args:
        channel: grpc.Channel connected to octane.exe
        target_node_ref: ObjectRef representing the render target node

    Returns:
        bool – True if successful, False otherwise.

    Raises:
        grpc.RpcError on connection or serialization error
    """
    # 1) Create stub for the ApiRenderEngine service
    stub = apirender_pb2_grpc.ApiRenderEngineServiceStub(channel)

    # 2) Build the request
    request = apirender_pb2.ApiRenderEngine.setRenderTargetNodeRequest()

    # Fill the ObjectRef for 'targetNode'
    request.targetNode.type = target_node_ref.type
    request.targetNode.handle = target_node_ref.handle

    # 3) Perform the RPC
    response = stub.setRenderTargetNode(request)

    # 4) Return the Boolean result field (server returns true/false)
    return response.result

def create_node(channel, owner_ref, node_type, configure_pins=True):
    """
    Create a new node (ApiNode.create RPC).

    Args:
        channel:          grpc.Channel  – active channel connected to octane.exe
        owner_ref:        ObjectRef     – reference to the owner graph (ApiNodeGraph)
        node_type:        int or enum   – NodeType to create (e.g., NT_GEO_MESH)
        configure_pins:   bool          – same as the C++ 'configurePins' argument

    Returns:
        ObjectRef of the newly created ApiNode.
    Raises:
        grpc.RpcError on connection or server failure.
    """
    # 1) Instantiate the stub for ApiNodeService (from apinodesystem_7)
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)

    # 2) Build the request message
    request = apinodesystem_7_pb2.ApiNode.createRequest()
    request.type = node_type
    request.configurePins = configure_pins

    # 3) Fill the ownerGraph reference
    request.ownerGraph.type = owner_ref.type
    request.ownerGraph.handle = owner_ref.handle

    # 4) Call the remote function
    response = stub.create(request)

    # 5) Return the resulting ObjectRef
    return response.result

def create_internal(channel, obj_ref, pin_id, node_type,
                    configure_pins=True, evaluate=True):
    """
    Create an internal node within another node (equivalent to C++ createInternal()).

    Args:
        channel:          grpc.Channel connected to octane.exe
        obj_ref:          ObjectRef of the parent node
        pin_id:           PinId enum/int – which pin to attach the internal node to
        node_type:        NodeType enum/int – type of internal node to create
        configure_pins:   bool – configure pins after creation
        evaluate:         bool – evaluate after creation

    Returns:
        bool – True if RPC succeeded, False otherwise.
    """
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)
    req = apinodesystem_7_pb2.ApiNode.createInternalRequest()

    req.objectPtr.type = obj_ref.type
    req.objectPtr.handle = obj_ref.handle
    req.pinId = pin_id
    req.type = node_type
    req.configurePins = configure_pins
    req.evaluate = evaluate

    try:
        stub.createInternal(req)  # returns ApiNode.createInternalResponse (no result field)
        return True
    except grpc.RpcError as e:
        print(f"[create_internal] RPC failed: {e.code()} — {e.details()}")
        return False
    
def connect_to(
    channel,
    this_ref,
    pin_id,
    source_ref,
    evaluate: bool = True,
    do_cycle_check: bool = False,
) -> bool:
    """
    Connect one node to another on the remote server.

    Args:
        channel:          grpc.Channel
        this_ref:         ObjectRef of the destination node (the one calling connectTo)
        pin_id:           PinId value (int or enum)
        source_ref:       ObjectRef of the source node being connected
        evaluate:         bool – whether to trigger evaluation after the connection
        do_cycle_check:   bool – whether to perform cyclic‑graph validation

    Returns:
        bool – True if the operation succeeded, False otherwise
    """
    # 1. Create the stub for ApiNodeService
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)

    # 2. Build the request message
    request = apinodesystem_7_pb2.ApiNode.connectToRequest()

    # Fill required fields (names must match your printed field names exactly)
    request.objectPtr.type = this_ref.type
    request.objectPtr.handle = this_ref.handle
    request.sourceNode.CopyFrom(source_ref)
    request.pinId = pin_id
    request.evaluate = evaluate
    request.doCycleCheck = do_cycle_check

    # 3. Send the RPC
    from google.protobuf import empty_pb2
    response = empty_pb2.Empty()
    stub.connectTo(request)  # returns Empty – no 'result' field

    return True

def connect_to_ix(channel, this_ref, pin_index, source_ref,
                  evaluate=True, do_cycle_check=False):
    """
    Connect two nodes via a specific pin index (equivalent to C++ connectToIx).
    
    Args:
        channel:        grpc.Channel
        this_ref:       ObjectRef of the destination node (target)
        pin_index:      int – index of the pin to connect
        source_ref:     ObjectRef of the source node
        evaluate:       bool – evaluate after connecting
        do_cycle_check: bool – perform cycle checking if needed
        
    Returns:
        bool – True if the operation succeeded, False otherwise.
    """
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)
    req = apinodesystem_7_pb2.ApiNode.connectToIxRequest()

    req.objectPtr.type = this_ref.type
    req.objectPtr.handle = this_ref.handle
    req.pinIdx = pin_index
    req.sourceNode.type = source_ref.type
    req.sourceNode.handle = source_ref.handle
    req.evaluate = evaluate
    req.doCycleCheck = do_cycle_check

    try:
        stub.connectToIx(req)  # returns google.protobuf.Empty
        return True
    except grpc.RpcError as e:
        print(f"[connect_to_ix] RPC failed: {e.code()} — {e.details()}")
        return False
    
def change_manager_update(channel) -> bool:
    """
    Calls ApiChangeManager.update on the Octane gRPC server.

    Args:
        channel: grpc.Channel connected to octane.exe

    Returns:
        bool – True if the RPC succeeded (status OK), False otherwise.
    """
    stub = apichangemanager_pb2_grpc.ApiChangeManagerServiceStub(channel)
    request = apichangemanager_pb2.ApiChangeManager.updateRequest()

    try:
        # The RPC returns google.protobuf.Empty(), so no response fields to check
        stub.update(request)
        return True
    except grpc.RpcError as e:
        print(f"[change_manager_update] RPC failed: {e.code()} — {e.details()}")
        return False
    
def connected_node(channel, this_ref, pin_id, enter_wrapper_node=False):
    """
    Get the node connected to a particular pin on another node.

    Args:
        channel:             gRPC channel to Octane server
        this_ref:            ObjectRef of the node whose pin is queried
        pin_id:              int or enum (PinId)
        enter_wrapper_node:  bool, whether to drill into wrapper nodes

    Returns:
        ObjectRef of the connected node, or None if not connected or on failure.
    """
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)

    req = apinodesystem_7_pb2.ApiNode.connectedNodeRequest()
    req.objectPtr.type = this_ref.type
    req.objectPtr.handle = this_ref.handle
    req.pinId = pin_id
    req.enterWrapperNode = enter_wrapper_node

    try:
        resp = stub.connectedNode(req)
        return resp.result
    except grpc.RpcError as e:
        print(f"[connected_node] RPC failed: {e.code()} — {e.details()}")
        return None
    

def set_pin_value(channel, obj_ref, pin_id, request, evaluate=True):
    """
    Set the value of a specific pin on a node (equivalent to C++ setPinValue).

    Args:
        channel:   grpc.Channel connected to Octane
        obj_ref:   ObjectRef of the target node
        pin_id:    PinId enum/int identifying the pin
        request:   ApiNode.setPinValueByIDRequest() already populated with a value
        evaluate:  bool – evaluate immediately after setting

    Returns:
        bool – True if successful, False otherwise.
    """
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)

    # Fill required request fields
    request.evaluate = evaluate
    request.item_ref.type = obj_ref.type
    request.item_ref.handle = obj_ref.handle
    request.pin_id = pin_id

    try:
        stub.setPinValueByPinID(request)   # returns ApiNode.setPinValueResponse
        return True
    except grpc.RpcError as e:
        print(f"[set_pin_value] RPC failed: {e.code()} — {e.details()}")
        return False
    
def set(channel, obj_ref, attr_id, request, evaluate=True) -> bool:
    """
    Generic helper to set an attribute value on a node (ApiItem.setValueByAttrID).

    Args:
        channel:   grpc.Channel connected to octane.exe
        obj_ref:   ObjectRef for the node/item to modify
        attr_id:   AttributeId (int or enum constant from octaneids_pb2)
        request:   ApiItem.setValueByIDRequest protobuf message
        evaluate:  bool – whether to evaluate immediately

    Returns:
        bool – True if RPC succeeded, False otherwise.
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)

    # Fill mandatory fields before sending
    request.evaluate = evaluate
    request.item_ref.type = obj_ref.type
    request.item_ref.handle = obj_ref.handle
    request.attribute_id = attr_id

    try:
        stub.setValueByAttrID(request)  # server returns setValueResponse
        return True
    except grpc.RpcError as e:
        print(f"[set] RPC failed: {e.code()} — {e.details()}")
        return False


def set_array_floats(channel, obj_ref, attr_id, float3_list, evaluate=True):
    """
    Set an array of float3 values (x, y, z) on a node.
    Equivalent to the C++ overload that takes Float3*.

    Args:
        channel:       grpc.Channel
        obj_ref:       ObjectRef of the target node
        attr_id:       AttributeId enum (from octaneids_pb2)
        float3_list:   iterable of objects with x, y, z attributes or 3‑tuples
        evaluate:      bool — trigger evaluation after setting
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)
    request = apinodesystem_3_pb2.ApiItem.setArrayByIDRequest()

    # Basic fields
    request.item_ref.CopyFrom(obj_ref)
    request.attribute_id = attr_id
    request.evaluate = evaluate

    arr_msg = request.float3_array
    for f in float3_list:
        elem = arr_msg.data.add()
        # Accept either a protobuf float_3 or a tuple/(x,y,z)
        if hasattr(f, "x"):
            elem.x = f.x
            elem.y = f.y
            elem.z = f.z
        else:
            x, y, z = f
            elem.x = float(x)
            elem.y = float(y)
            elem.z = float(z)

    try:
        stub.setArrayByAttrID(request)
        return True
    except grpc.RpcError as e:
        print(f"[set_array_floats] RPC failed: {e.code()} — {e.details()}")
        return False
    

def set_array_ints(channel, obj_ref, attr_id, values, evaluate=True):
    """
    Set an array of int32 values on a node (equivalent to setArray(int32_t*)).
    
    Args:
        channel:  grpc.Channel
        obj_ref:  ObjectRef of the target node
        attr_id:  AttributeId enum (from octaneids_pb2)
        values:   iterable of int
        evaluate: bool, whether to trigger evaluation after setting
        
    Returns:
        bool – True on success, False if RPC fails
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)
    request = apinodesystem_3_pb2.ApiItem.setArrayByIDRequest()

    request.item_ref.CopyFrom(obj_ref)
    request.attribute_id = attr_id
    request.evaluate = evaluate

    arr_msg = request.int_array
    arr_msg.data.extend(int(v) for v in values)

    try:
        stub.setArrayByAttrID(request)
        return True
    except grpc.RpcError as e:
        print(f"[set_array_ints] RPC failed: {e.code()} — {e.details()}")
        return False
    

def set_array_strings(channel, obj_ref, attr_id, strings, evaluate=True):
    """
    Set an array of string values on a node (equivalent to setArray(char**)).
    
    Args:
        channel:  grpc.Channel
        obj_ref:  ObjectRef of the target node
        attr_id:  AttributeId enum (from octaneids_pb2)
        strings:  iterable of str values
        evaluate: bool, whether to trigger evaluation after setting
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)
    request = apinodesystem_3_pb2.ApiItem.setArrayByIDRequest()

    # Fill base fields
    request.item_ref.CopyFrom(obj_ref)
    request.attribute_id = attr_id
    request.evaluate = evaluate

    # Fill the string array data
    arr_msg = request.string_array
    for s in strings:
        arr_msg.data.append(s or "")  # fallback to empty string if None

    try:
        stub.setArrayByAttrID(request)
        return True
    except grpc.RpcError as e:
        print(f"[set_array_strings] RPC failed")
        return False
              
def set_array_matrix(channel, obj_ref, attr_id, matrices, evaluate=True):
    """
    Set an array of MatrixF values on a node (equivalent to setArray(MatrixF*) in C++).
    Each matrix must be a populated 'MatrixF' protobuf message.

    Args:
        channel:   grpc.Channel
        obj_ref:   ObjectRef of the target node
        attr_id:   AttributeId enum (from octaneids_pb2)
        matrices:  iterable of MatrixF messages
        evaluate:  bool, trigger evaluation after setting (default True)
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)
    request = apinodesystem_3_pb2.ApiItem.setArrayByIDRequest()

    # Fill metadata
    request.item_ref.CopyFrom(obj_ref)
    request.attribute_id = attr_id
    request.evaluate = evaluate

    # Fill the matrix array
    array_msg = request.matrix_array
    for m in matrices:
        array_msg.data.add().CopyFrom(m)

    try:
        stub.setArrayByAttrID(request)
        return True
    except grpc.RpcError as e:
        print(f"[set_array_matrix] RPC failed: {e.code()} — {e.details()}")
        return False
    
def evaluate(channel, obj_ref):
    """
    Trigger an evaluation on a node (same as C++ evaluate()).

    Args:
        channel:  grpc.Channel connected to octane.exe
        obj_ref:  ObjectRef of the node to evaluate

    Returns:
        bool – True if successful, False otherwise.
    """
    stub = apinodesystem_3_pb2_grpc.ApiItemServiceStub(channel)
    request = apinodesystem_3_pb2.ApiItem.evaluateRequest()

    request.objectPtr.CopyFrom(obj_ref)

    try:
        stub.evaluate(request)   # returns google.protobuf.Empty()
        return True
    except grpc.RpcError as e:
        print(f"[evaluate] RPC failed: {e.code()} — {e.details()}")
        return False

def static_pin_count(channel, obj_ref):
    """
    Get the number of static pins defined for a node.
    Equivalent to C++ staticPinCount().

    Args:
        channel:  grpc.Channel
        obj_ref:  ObjectRef of the node to query

    Returns:
        int - number of static pins, or -1 if the RPC fails
    """
    stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(channel)
    req = apinodesystem_7_pb2.ApiNode.staticPinCountRequest()

    req.objectPtr.type = obj_ref.type
    req.objectPtr.handle = obj_ref.handle

    try:
        resp = stub.staticPinCount(req)
        return resp.result
    except grpc.RpcError as e:
        print(f"[static_pin_count] RPC failed: {e.code()} — {e.details()}")
        return -1
    
def create_sphere(channel, mat_count):
    project_root = root_node_graph(channel)

    mesh_node = create_node(channel, project_root, octaneids_pb2.NT_GEO_MESH)

    verts_per_poly = [3] * (len(SPHERE_FACES) // 3)

    set_array_ints(channel, mesh_node, octaneids_pb2.A_VERTICES_PER_POLY, verts_per_poly, False)
    set_array_floats(channel, mesh_node, octaneids_pb2.A_VERTICES, SPHERE_VERTICES, False)
    set_array_floats(channel, mesh_node, octaneids_pb2.A_UVWS, SPHERE_VERTICES, False)
    set_array_floats(channel, mesh_node, octaneids_pb2.A_NORMALS, SPHERE_VERTICES, False)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_VERTEX_INDICES, SPHERE_FACES, False)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_UVW_INDICES, SPHERE_FACES, False)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_NORMAL_INDICES, SPHERE_FACES, False)

    # Material names
    mat_names = [f"Material {i+1}" for i in range(mat_count)]
    set_array_strings(channel, mesh_node, octaneids_pb2.A_MATERIAL_NAMES, mat_names, False)

    # Assign material indices
    poly_mat_indices = [i % mat_count for i in range(len(verts_per_poly))]
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_MATERIAL_INDICES, poly_mat_indices, False)

    evaluate(channel, mesh_node)
    return mesh_node

def create_cube(channel):
    """
    Create a simple cube mesh node in Octane via the gRPC API.
    Mirrors the C++ createCube() function.
    """
    project_root = root_node_graph(channel)

    # Create the mesh node
    mesh_node = create_node(channel, project_root, octaneids_pb2.NT_GEO_MESH)

    # 1. Vertices per polygon (each face a triangle)
    verts_per_poly = [3] * (len(CUBE_FACES) // 3)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_VERTICES_PER_POLY, verts_per_poly, False)

    # 2. Geometry arrays
    set_array_floats(channel, mesh_node, octaneids_pb2.A_VERTICES, CUBE_VERTICES, False)
    set_array_floats(channel, mesh_node, octaneids_pb2.A_UVWS, CUBE_VERTICES, False)
    set_array_floats(channel, mesh_node, octaneids_pb2.A_NORMALS, CUBE_VERTICES, False)

    # 3. Face index arrays
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_VERTEX_INDICES, CUBE_FACES, False)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_UVW_INDICES,   CUBE_FACES, False)
    set_array_ints(channel, mesh_node, octaneids_pb2.A_POLY_NORMAL_INDICES, CUBE_FACES, False)

    # 4. Material names (one material called "Material 1")
    set_array_strings(channel, mesh_node,
                      octaneids_pb2.A_MATERIAL_NAMES, ["Material 1"], False)

    # 5. Assign material index 0 for all polygons
    poly_mat_indices = [0] * len(verts_per_poly)
    set_array_ints(channel, mesh_node,
                   octaneids_pb2.A_POLY_MATERIAL_INDICES, poly_mat_indices, False)

    # 6. Evaluate the mesh
    evaluate(channel, mesh_node)

    print("[create_cube] Cube mesh created successfully.")
    return mesh_node

def init_materials(channel):
    """
    Initializes image and RGB texture nodes and stores them in global lists.
    """
    global g_image_textures, g_rgb_textures, g_diffuse_materials, g_glossy_materials
    global g_sphere_mesh, g_material_maps, g_spin_cube, g_cube_placement_node

    texture_dir = Path(__file__).resolve().parent.parent / "textures"

    tex_files = [
        "Bokeh2.jpg",
        "Mineral.jpg",
        "MultiScatter8.jpg",
        "OctaneDLDiffuse.jpg",
        "OctaneLogo.png",
    ]

    project_root = root_node_graph(channel)

    # --- Image textures ---
    g_image_textures.clear()
    for fname in tex_files:
        tex_node = create_node(channel, project_root, octaneids_pb2.NT_TEX_IMAGE)
        full_path = str(texture_dir / fname)

        req = apinodesystem_3_pb2.ApiItem.setValueByIDRequest()
        req.string_value = full_path
        set(channel, tex_node, octaneids_pb2.A_FILENAME, req)

        print(f"[init_materials] Image texture: {full_path}")
        g_image_textures.append(tex_node)

    # --- RGB textures ---
    g_rgb_textures.clear()
    for i in range(RGBTEXAMOUNT):
        tex_node = create_node(channel, project_root, octaneids_pb2.NT_TEX_RGB)

        req = apinodesystem_3_pb2.ApiItem.setValueByIDRequest()
        v3 = req.float3_value
        v3.z = lcg_random_float()
        v3.y = lcg_random_float()
        v3.x = lcg_random_float()

        set(channel, tex_node, octaneids_pb2.A_VALUE, req)

        print(f"[init_materials] RGB texture {i}: "
              f"({v3.x:.3f}, {v3.y:.3f}, {v3.z:.3f})")
        g_rgb_textures.append(tex_node)

     # --- Diffuse materials ---
    for i in range(DIFFUSEMATAMOUNT):
        mat = create_node(channel, project_root, octaneids_pb2.NT_MAT_DIFFUSE)
        tex = get_random_texture()        # ← deterministic RGB texture
        connect_to(channel, mat, octaneids_pb2.P_DIFFUSE, tex)
        g_diffuse_materials.append(mat)

    # --- Glossy materials ---
    for i in range(GLOSSYMATAMOUNT):
        mat = create_node(channel, project_root, octaneids_pb2.NT_MAT_GLOSSY)  # correct type
        tex = get_random_texture()        # ← deterministic RGB texture
        connect_to(channel, mat, octaneids_pb2.P_DIFFUSE, tex)
        g_glossy_materials.append(mat)

   # Only create the sphere mesh once
    if not g_sphere_mesh:
        g_sphere_mesh = create_sphere(channel, 2)

        # Create material‑map nodes and connect to the shared sphere mesh
        for _ in range(OBJECTAMOUNT):
            mat_map = create_node(channel, project_root, octaneids_pb2.NT_MAT_MAP)
            connect_to(channel, mat_map, octaneids_pb2.P_GEOMETRY, g_sphere_mesh)
            g_material_maps.append(mat_map)

    if not g_spin_cube:
        # Create the cube mesh if it doesn't exist
        g_spin_cube = create_cube(channel)

        # Create MAT_MAP nodes that reference the cube geometry
        for c in range(CUBEAMOUNT):
            mat_map = create_node(channel, project_root, octaneids_pb2.NT_MAT_MAP)
            connect_to(channel, mat_map, octaneids_pb2.P_GEOMETRY, g_spin_cube)
            g_material_maps.append(mat_map)

        # Create placement node for positioning the cube
        g_cube_placement_node = create_node(channel, project_root,
                                            octaneids_pb2.NT_GEO_PLACEMENT)

        # Create an RGB texture for cube color (green in this example)
        cube_texture = create_node(channel, project_root, octaneids_pb2.NT_TEX_RGB)
        req = apinodesystem_3_pb2.ApiItem.setValueByIDRequest()
        v3 = req.float3_value
        v3.x, v3.y, v3.z = 0.0, 1.0, 0.0  # RGB (0,1,0) -> bright green
        set(channel, cube_texture, octaneids_pb2.A_VALUE, req)

        # Create a Diffuse material and connect the RGB texture to its Diffuse input
        g_cube_mat = create_node(channel, project_root, octaneids_pb2.NT_MAT_DIFFUSE)
        connect_to(channel, g_cube_mat, octaneids_pb2.P_DIFFUSE, cube_texture)

    # --- For each sphere material map ---
    for i in range(OBJECTAMOUNT):
        mat_map = g_material_maps[i]
        base = static_pin_count(channel, mat_map)

        connect_to_ix(channel, mat_map, base + 0,
                      get_random_diffuse_mat())
        connect_to_ix(channel, mat_map, base + 1,
                      get_random_glossy_mat())

    # --- For cube material map(s) ---
    for c in range(CUBEAMOUNT):
        mat_map = g_material_maps[OBJECTAMOUNT + c]
        base = static_pin_count(channel, mat_map)
        connect_to_ix(channel, mat_map, base, g_cube_mat)

    return

def make_simple_scene(channel,  render_target_ref):
    
    global g_cube_placement_node

    # 1) Get the root node graph
    project_root = root_node_graph(channel)

    # 2) Try to get the connected geometry group from the render target’s MESH pin
    geo_group = None
    geo_group = connected_node(channel, render_target_ref, octaneids_pb2.P_MESH, False)

    # 3) If that connection exists, adjust its pin‑count attribute
    if geo_group:
        req = apinodesystem_3_pb2.ApiItem.setValueByIDRequest()
        req.int_value = OBJECTAMOUNT + CUBEAMOUNT
        set(channel, geo_group, octaneids_pb2.A_PIN_COUNT, req, True)

    init_materials(channel)

    geo_group = connected_node(channel, render_target_ref, octaneids_pb2.P_MESH, False)
    if not geo_group:
        print("[make_simple_scene] No geometry group connected to render target.")
        return

    # --- Create scatter instances for each sphere ---
    for i in range(OBJECTAMOUNT):
        t = math.sqrt(i * 0.001)
        scatter = create_node(channel, project_root, octaneids_pb2.NT_GEO_SCATTER)

        # translation for this scatter object
        tx = math.sin(120.0 * t) * t * 30.0
        ty = t * 15.0
        tz = math.cos(120.0 * t) * t * 30.0
        mat = make_translation_matrix(tx, ty, tz)

        # set transform
        set_array_matrix(channel, scatter, octaneids_pb2.A_TRANSFORMS, [mat])
        connect_to(channel, scatter, octaneids_pb2.P_GEOMETRY, g_material_maps[i])
        connect_to_ix(channel, geo_group, i, scatter)

    # --- Cube placement node and cube instance ---
    cube_mat = make_translation_matrix(
        g_cube_init_translate.x, g_cube_init_translate.y, g_cube_init_translate.z
    )

    req = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    v = req.matrix_value
    v.CopyFrom(cube_mat)
    set_pin_value(channel, g_cube_placement_node, octaneids_pb2.P_TRANSFORM, req)
    connect_to(channel, g_cube_placement_node, octaneids_pb2.P_GEOMETRY,
               g_material_maps[OBJECTAMOUNT])
    connect_to_ix(channel, geo_group, OBJECTAMOUNT, g_cube_placement_node)

    # --- Camera setup ---
    camera = create_node(channel, project_root, octaneids_pb2.NT_CAM_THINLENS)

    # Camera target
    req_target = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    v = req_target.float3_value
    v.x, v.y, v.z = 0.0, 0.0, 0.0
    set_pin_value(channel, camera, octaneids_pb2.P_TARGET, req_target)

    # Camera position
    req_pos = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    v = req_pos.float3_value
    v.x, v.y, v.z = 10.0, -2.0, 10.0
    set_pin_value(channel, camera, octaneids_pb2.P_POSITION, req_pos)

    connect_to(channel, render_target_ref, octaneids_pb2.P_CAMERA, camera)

    # --- Environment setup ---
    env = create_node(channel, project_root, octaneids_pb2.NT_ENV_DAYLIGHT)
    create_internal(channel, env, octaneids_pb2.P_SUN_DIR, octaneids_pb2.NT_FLOAT)

    # Sun direction vector (normalized)
    nx, ny, nz = normalized(-10.0, 0.1, -5.0)
    req_sundir = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    v = req_sundir.float3_value
    v.x, v.y, v.z = nx, ny, nz
    set_pin_value(channel, env, octaneids_pb2.P_SUN_DIR, req_sundir)

    # Daylight model
    req_model = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    req_model.int_value = octaneenums_pb2.DAYLIGHTMODEL_OCTANE
    set_pin_value(channel, env, octaneids_pb2.P_MODEL, req_model)

    connect_to(channel, render_target_ref, octaneids_pb2.P_ENVIRONMENT, env)

    # --- Kernel setup ---
    kernel = create_node(channel, project_root, octaneids_pb2.NT_KERN_PATHTRACING)
    req_samples = apinodesystem_7_pb2.ApiNode.setPinValueByIDRequest()
    req_samples.int_value = 1000
    set_pin_value(channel, kernel, octaneids_pb2.P_MAX_SAMPLES, req_samples)
    connect_to(channel, render_target_ref, octaneids_pb2.P_KERNEL, kernel)


def grab_render_result(channel):
    """
    Call ApiRenderEngineService.grabRenderResult and return a list of (width, height, raw_bytes).
    """
    stub = apirender_pb2_grpc.ApiRenderEngineServiceStub(channel)

    # Note: the request message is nested inside ApiRenderEngine
    req = apirender_pb2.ApiRenderEngine.grabRenderResultRequest()
    resp = stub.grabRenderResult(req)

    if not resp.result:
        print("No render result available (result=False).")
        return []

    images = []
    for img in resp.renderImages.data:
        width = img.size.x
        height = img.size.y
        buf = img.buffer.data  # raw bytes from Buffer message
        # For simplicity handle only LDR RGBA
        if img.type == octaneenums_pb2.IMAGE_TYPE_LDR_RGBA:
            images.append((width, height, buf))
    return images

import numpy as np
import cv2

window_name = "GRPC API Render Preview"

def show_render_images(images):
    if not images:
        return
    w, h, data = images[0]

    # Convert RGBA byte buffer → NumPy BGR for OpenCV
    arr = np.frombuffer(data, dtype=np.uint8).reshape((h, w, 4))
    bgr = cv2.cvtColor(arr, cv2.COLOR_RGBA2BGR)

    cv2.imshow(window_name, bgr)
    cv2.waitKey(1)         # let OpenCV process GUI events

def handle_event(req):
    payload = req.WhichOneof("payload")   # returns the active field name string

    if payload == "newImage":
        data = req.newImage
        print(f"[Client] NewImage event, user_data={data.user_data}")
        try:
            images = grab_render_result(global_channel)
            show_render_images(images)
        except grpc.RpcError as e:
            print(f"[Client] grabRenderResult failed: {e.code()} {e.details()}")
        # You can grab image results here
    elif payload == "renderFailure":
        data = req.renderFailure
        print(f"[Client] Render failed, user_data={data.user_data}")
    elif payload == "newStatistics":
        data = req.newStatistics
        print(f"[Client] New statistics update, user_data={data.user_data}")
    elif payload == "projectManagerChanged":
        data = req.projectManagerChanged
        print(f"[Client] ProjectManager changed, user_data={data.user_data}")
    else:
        print(f"[Client] Unknown payload type: {payload}")

def stream_events(channel, stop_event):
    stub = callbackstream_pb2_grpc.StreamCallbackServiceStub(channel)
    try:
        for req in stub.callbackChannel(empty_pb2.Empty()):
            if stop_event.is_set():
                print("[Client] Stop requested; exiting stream.")
                break
            handle_event(req)
    except grpc.RpcError as e:
        print(f"[Client] Stream ended: {e.code()} {e.details()}")

def start_event_listener(channel):
    stop_evt = threading.Event()
    t = threading.Thread(target=stream_events, args=(channel, stop_evt), daemon=True)
    t.start()
    return stop_evt

def main():

    server_url = "127.0.0.1:51022"

    global global_channel
    channel = grpc.insecure_channel(server_url)
    global_channel = channel

    # Block until the channel is ready
    grpc.channel_ready_future(channel).result(timeout=5)

    # ---- Start async event reader ----
    stop_evt = start_event_listener(channel)

    reset_project(channel)
    
    # Call helper
    obj = root_node_graph(channel)
    project_root = root_node_graph(channel)
    render_target_ref = create_node(channel, project_root, octaneids_pb2.NT_RENDERTARGET, configure_pins=True)

    ok = set_render_target_node(channel, render_target_ref)
    geo_node = create_node(channel, project_root, octaneids_pb2.NT_GEO_GROUP, True)
    connect_to(channel, render_target_ref, octaneids_pb2.P_MESH, geo_node, True, False)

    make_simple_scene(channel, render_target_ref )

    rp = create_node(channel, project_root, octaneids_pb2.NT_RENDER_PASSES)
    connect_to(channel, render_target_ref, octaneids_pb2.P_RENDER_PASSES, rp)
    change_manager_update(channel)
    print("Got ObjectRef:", obj)
    # -> Got ObjectRef: handle: 1000934

    # Let render run for a few seconds to receive images/statistics
    import time
    time.sleep(10)

    # Stop the event thread cleanly
    stop_evt.set()

if __name__ == "__main__":
    main()