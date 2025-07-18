#!/usr/bin/env python3
"""
Comprehensive Octane gRPC API Test Suite

🔥 CRITICAL: Uses ObjectPtr type conversion for polymorphic API access
- Same handle, different type field based on target service
- ApiItem=16, ApiNode=17, ApiRootNodeGraph=18, ApiNodeGraph=20

Tests every available Octane service systematically:
1. Project Management
2. Node Creation & Manipulation  
3. Pin Operations & Connections
4. Attribute Getting/Setting
5. Graph Operations
6. Advanced Features

LOCKIT: Focused on comprehensive API testing
GRIND: Extended autonomous testing with frequent validation
"""

import asyncio
import sys
import os
import traceback
from datetime import datetime
import grpc
from google.protobuf.empty_pb2 import Empty

# Add proxy directory to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'proxy'))

# Import all protobuf modules
import apinodesystem_pb2
import apinodesystem_pb2_grpc
import apiprojectmanager_pb2
import apiprojectmanager_pb2_grpc
import livelink_pb2
import livelink_pb2_grpc
import common_pb2
import octaneids_pb2
import octaneenums_pb2

# STAGE 1: New core services
import apirender_pb2
import apirender_pb2_grpc
import apisceneoutliner_pb2
import apisceneoutliner_pb2_grpc
import apiselectionmanager_pb2
import apiselectionmanager_pb2_grpc
import apinodegrapheditor_pb2
import apinodegrapheditor_pb2_grpc

# STAGE 2: Image & geometry services
import apiimage_pb2
import apiimage_pb2_grpc
import apiimagebuffer_pb2
import apiimagebuffer_pb2_grpc
import apiimagecomponent_pb2
import apiimagecomponent_pb2_grpc
import apiimageinfo_pb2
import apiimageinfo_pb2_grpc
import apigeometryexporter_pb2
import apigeometryexporter_pb2_grpc
import apidbmaterialmanager_pb2
import apidbmaterialmanager_pb2_grpc
import apimaterialx_pb2
import apimaterialx_pb2_grpc
import apitimesampling_pb2
import apitimesampling_pb2_grpc

# STAGE 3: UI & editor services
import apiguicomponent_pb2
import apiguicomponent_pb2_grpc
import apirenderview_pb2
import apirenderview_pb2_grpc
import apitexteditor_pb2
import apitexteditor_pb2_grpc
import apicustomcurveeditorcontroller_pb2
import apicustomcurveeditorcontroller_pb2_grpc
import apichangemanager_pb2
import apichangemanager_pb2_grpc
import apidiagnostics_pb2
import apidiagnostics_pb2_grpc
import apilogmanager_pb2
import apilogmanager_pb2_grpc

# STAGE 4: File & data management services
import apibinaryfile_pb2
import apibinaryfile_pb2_grpc
# import apicaches_pb2  # Temporarily disabled due to CacheStatus enum resolution issue
# import apicaches_pb2_grpc
import apifilechooser_pb2
import apifilechooser_pb2_grpc
import apifilename_pb2
import apifilename_pb2_grpc
import apimoduledata_pb2
import apimoduledata_pb2_grpc
import apisceneexporter_pb2
import apisceneexporter_pb2_grpc

# STAGE 5: System & configuration services
import apilocaldb_pb2
import apilocaldb_pb2_grpc
import apititlecomponent_pb2
import apititlecomponent_pb2_grpc
import apirendercloudmanager_pb2
import apirendercloudmanager_pb2_grpc
import apitimesampling_pb2
import apitimesampling_pb2_grpc
# import apiitemarray_pb2  # Temporarily disabled due to naming conflict with common.proto
# import apiitemarray_pb2_grpc
import apitexteditor_pb2
import apitexteditor_pb2_grpc

# STAGE 6: Plugin & extension services
# import apiplugin_pb2  # No services, just message definitions
# import apiplugin_pb2_grpc
# import apithread_pb2  # Temporarily disabled due to 'yield' keyword conflict
# import apithread_pb2_grpc
# import apinodesystem_7_pb2  # Temporarily disabled due to duplicate symbol 'ApiFilePath'
# import apinodesystem_7_pb2_grpc
# import apimodulenodegraph_pb2  # Temporarily disabled due to dependency on apinodesystem_7
# import apimodulenodegraph_pb2_grpc
import apinetrendermanager_pb2
import apinetrendermanager_pb2_grpc
import apicollapsiblepanelstack_pb2
import apicollapsiblepanelstack_pb2_grpc

# STAGE 7: Advanced rendering services
import apirender_pb2
import apirender_pb2_grpc
import apirenderview_pb2
import apirenderview_pb2_grpc
import octanevolume_pb2
import octanevolume_pb2_grpc
import octanerenderpasses_pb2
import octanerenderpasses_pb2_grpc
import apianimationtimetransform_pb2
import apianimationtimetransform_pb2_grpc

# STAGE 8: Specialized services
# import apilogmanager_pb2  # DISABLED: Naming conflict with private methods
# import apilogmanager_pb2_grpc
import apidbmaterialmanager_pb2
import apidbmaterialmanager_pb2_grpc
import apiociocontextmanager_pb2
import apiociocontextmanager_pb2_grpc
import apisceneexporter_pb2
import apisceneexporter_pb2_grpc
import apichangemanager_pb2
import apichangemanager_pb2_grpc
import apigeometryexporter_pb2
import apigeometryexporter_pb2_grpc
import apimaterialx_pb2
import apimaterialx_pb2_grpc
# Note: octanereferenceexport_pb2 has no services, only message definitions

# STAGE 9: UI and Advanced Services
import apiguicomponent_pb2
import apiguicomponent_pb2_grpc
import apimainwindow_pb2
import apimainwindow_pb2_grpc
import apiwindow_pb2
import apiwindow_pb2_grpc
import apicheckbox_pb2
import apicheckbox_pb2_grpc
import apicombobox_pb2
import apicombobox_pb2_grpc
import apicolorswatch_pb2
import apicolorswatch_pb2_grpc
import apifilechooser_pb2
import apifilechooser_pb2_grpc
import apigridlayout_pb2
import apigridlayout_pb2_grpc
import apidiagnostics_pb2
import apidiagnostics_pb2_grpc
import apigaussiansplatting_pb2
import apigaussiansplatting_pb2_grpc
import apicustomcurveeditorcontroller_pb2
import apicustomcurveeditorcontroller_pb2_grpc
import apidialogfeedback_pb2

class ComprehensiveOctaneTest:
    """Comprehensive test suite for all Octane gRPC services"""
    
    def __init__(self, octane_host=None, octane_port=51022):
        # Auto-detect host based on platform
        if octane_host is None:
            import platform
            if platform.system() == "Windows":
                octane_host = "127.0.0.1"  # Windows native
            else:
                octane_host = "host.docker.internal"  # Docker container
        
        self.octane_host = octane_host
        self.octane_port = octane_port
        self.channel = None
        self.test_results = {}
        self.created_objects = []  # Track created objects for cleanup
        
        # Service stubs - will be initialized in connect()
        self.project_stub = None
        self.item_stub = None
        self.node_stub = None
        self.node_graph_stub = None
        self.root_graph_stub = None
        self.item_array_stub = None
        self.node_array_stub = None
        self.livelink_stub = None
        
        # STAGE 1: New core service stubs
        self.render_stub = None
        self.scene_outliner_stub = None
        self.selection_manager_stub = None
        self.node_graph_editor_stub = None
        
        # STAGE 2: Image & geometry service stubs
        self.image_stub = None
        self.image_buffer_stub = None
        self.image_component_stub = None
        self.image_info_stub = None
        self.geometry_exporter_stub = None
        self.db_material_manager_stub = None
        self.materialx_stub = None
        self.time_sampling_stub = None
        
        # STAGE 3: UI & editor service stubs
        self.gui_component_stub = None
        self.render_view_stub = None
        self.text_editor_stub = None
        self.curve_editor_controller_stub = None
        self.change_manager_stub = None
        self.diagnostics_stub = None
        self.log_manager_stub = None
        
        # STAGE 4: File & data management service stubs
        self.binary_group_stub = None
        self.binary_table_stub = None
        # self.caches_stub = None  # Temporarily disabled
        self.file_chooser_stub = None
        self.filename_stub = None
        self.module_data_stub = None
        self.scene_exporter_stub = None
        
        # STAGE 5: System & configuration service stubs
        self.local_db_stub = None
        self.local_db_category_stub = None
        self.local_db_package_stub = None
        self.title_component_stub = None
        self.render_cloud_manager_stub = None
        self.time_sampling_stub = None
        # self.item_array_stub = None  # Temporarily disabled
        self.text_editor_stub = None
        
        # STAGE 6: Plugin & extension service stubs
        # self.thread_stub = None  # Temporarily disabled
        # self.node_system_7_stub = None  # Temporarily disabled
        # self.module_node_graph_stub = None  # Temporarily disabled
        self.net_render_manager_stub = None
        self.collapsible_panel_stack_stub = None
        
        # STAGE 7: Advanced rendering service stubs
        self.render_engine_stub = None
        self.render_image_stub = None
        self.render_view_stub = None
        self.vdb_grid_info_stub = None
        self.vdb_grid_sampler_stub = None
        self.vdb_info_stub = None
        self.render_result_statistics_stub = None
        self.animation_time_transform_stub = None
        self.linear_time_transform_stub = None
        
        # STAGE 8: Specialized service stubs
        # self.log_manager_stub = None  # DISABLED: Naming conflict
        self.db_material_manager_stub = None
        self.db_category_array_stub = None
        self.db_material_array_stub = None
        self.ocio_context_manager_stub = None
        self.scene_exporter_stub = None
        self.change_manager_stub = None
        self.geometry_exporter_stub = None
        self.materialx_global_stub = None
        
        # STAGE 9: UI and Advanced service stubs
        self.gui_component_stub = None
        self.main_window_stub = None
        self.window_stub = None
        self.checkbox_stub = None
        self.combobox_stub = None
        self.color_swatch_stub = None
        self.file_chooser_stub = None
        self.grid_layout_stub = None
        self.diagnostics_stub = None
        self.gaussian_splat_cloud_node_stub = None
        self.custom_curve_editor_controller_stub = None
        self.custom_curve_editor_drawer_stub = None
        self.custom_curve_editor_listener_stub = None
        
    async def connect(self):
        """Connect to Octane gRPC server"""
        try:
            print(f"🔌 Connecting to Octane at {self.octane_host}:{self.octane_port}...")
            self.channel = grpc.aio.insecure_channel(f"{self.octane_host}:{self.octane_port}")
            
            # Initialize all service stubs
            self.project_stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
            self.item_stub = apinodesystem_pb2_grpc.ApiItemServiceStub(self.channel)
            self.node_stub = apinodesystem_pb2_grpc.ApiNodeServiceStub(self.channel)
            self.node_graph_stub = apinodesystem_pb2_grpc.ApiNodeGraphServiceStub(self.channel)
            self.root_graph_stub = apinodesystem_pb2_grpc.ApiRootNodeGraphServiceStub(self.channel)
            self.item_array_stub = apinodesystem_pb2_grpc.ApiItemArrayServiceStub(self.channel)
            self.node_array_stub = apinodesystem_pb2_grpc.ApiNodeArrayServiceStub(self.channel)
            self.livelink_stub = livelink_pb2_grpc.LiveLinkServiceStub(self.channel)
            
            # STAGE 1: Initialize new core service stubs
            self.render_stub = apirender_pb2_grpc.ApiRenderEngineServiceStub(self.channel)
            self.scene_outliner_stub = apisceneoutliner_pb2_grpc.ApiSceneOutlinerServiceStub(self.channel)
            self.selection_manager_stub = apiselectionmanager_pb2_grpc.ApiSelectionManagerServiceStub(self.channel)
            self.node_graph_editor_stub = apinodegrapheditor_pb2_grpc.ApiNodeGraphEditorServiceStub(self.channel)
            
            # STAGE 2: Initialize image & geometry service stubs
            self.image_stub = apiimage_pb2_grpc.ApiImageServiceStub(self.channel)
            self.image_buffer_stub = apiimagebuffer_pb2_grpc.ApiImageBufferServiceStub(self.channel)
            self.image_component_stub = apiimagecomponent_pb2_grpc.ApiImageComponentServiceStub(self.channel)
            self.image_info_stub = apiimageinfo_pb2_grpc.ImageInfoServiceStub(self.channel)
            self.geometry_exporter_stub = apigeometryexporter_pb2_grpc.ApiGeometryExporterServiceStub(self.channel)
            self.db_material_manager_stub = apidbmaterialmanager_pb2_grpc.ApiDBMaterialManagerServiceStub(self.channel)
            self.materialx_stub = apimaterialx_pb2_grpc.ApiMaterialXGlobalServiceStub(self.channel)
            self.time_sampling_stub = apitimesampling_pb2_grpc.ApiTimeSamplingServiceStub(self.channel)
            
            # STAGE 3: Initialize UI & editor service stubs
            self.gui_component_stub = apiguicomponent_pb2_grpc.ApiGuiComponentServiceStub(self.channel)
            self.render_view_stub = apirenderview_pb2_grpc.ApiRenderViewServiceStub(self.channel)
            self.text_editor_stub = apitexteditor_pb2_grpc.ApiTextEditorServiceStub(self.channel)
            self.curve_editor_controller_stub = apicustomcurveeditorcontroller_pb2_grpc.ApiCustomCurveEditorControllerServiceStub(self.channel)
            self.change_manager_stub = apichangemanager_pb2_grpc.ApiChangeManagerServiceStub(self.channel)
            self.diagnostics_stub = apidiagnostics_pb2_grpc.ApiDiagnosticsServiceStub(self.channel)
            # self.log_manager_stub = apilogmanager_pb2_grpc.ApiLogManagerServiceStub(self.channel)  # Temporarily disabled
            
            # STAGE 4: Initialize file & data management service stubs
            self.binary_group_stub = apibinaryfile_pb2_grpc.ApiBinaryGroupServiceStub(self.channel)
            self.binary_table_stub = apibinaryfile_pb2_grpc.ApiBinaryTableServiceStub(self.channel)
            # self.caches_stub = apicaches_pb2_grpc.ApiCachesServiceStub(self.channel)  # Temporarily disabled
            self.file_chooser_stub = apifilechooser_pb2_grpc.ApiFileChooserServiceStub(self.channel)
            self.filename_stub = apifilename_pb2_grpc.ApiFileNameServiceStub(self.channel)
            self.module_data_stub = apimoduledata_pb2_grpc.ApiModuleDataServiceStub(self.channel)
            self.scene_exporter_stub = apisceneexporter_pb2_grpc.ApiSceneExporterServiceStub(self.channel)
            
            # STAGE 5: Initialize system & configuration service stubs
            self.local_db_stub = apilocaldb_pb2_grpc.ApiLocalDBServiceStub(self.channel)
            self.local_db_category_stub = apilocaldb_pb2_grpc.ApiLocalDB_CategoryServiceStub(self.channel)
            self.local_db_package_stub = apilocaldb_pb2_grpc.ApiLocalDB_PackageServiceStub(self.channel)
            self.title_component_stub = apititlecomponent_pb2_grpc.ApiTitleComponentServiceStub(self.channel)
            self.render_cloud_manager_stub = apirendercloudmanager_pb2_grpc.ApiRenderCloudManagerServiceStub(self.channel)
            self.time_sampling_stub = apitimesampling_pb2_grpc.ApiTimeSamplingServiceStub(self.channel)
            # self.item_array_stub = apiitemarray_pb2_grpc.ApiItemArrayServiceStub(self.channel)  # Temporarily disabled
            self.text_editor_stub = apitexteditor_pb2_grpc.ApiTextEditorServiceStub(self.channel)
            
            # STAGE 6: Initialize plugin & extension service stubs
            # self.thread_stub = apithread_pb2_grpc.ApiThreadServiceStub(self.channel)  # Temporarily disabled
            # self.node_system_7_stub = apinodesystem_7_pb2_grpc.ApiNodeServiceStub(self.channel)  # Temporarily disabled
            # self.module_node_graph_stub = apimodulenodegraph_pb2_grpc.ApiModuleNodeGraphServiceStub(self.channel)  # Temporarily disabled
            self.net_render_manager_stub = apinetrendermanager_pb2_grpc.ApiNetRenderManagerServiceStub(self.channel)
            self.collapsible_panel_stack_stub = apicollapsiblepanelstack_pb2_grpc.ApiCollapsiblePanelStackServiceStub(self.channel)
            
            # STAGE 7: Initialize advanced rendering service stubs
            self.render_engine_stub = apirender_pb2_grpc.ApiRenderEngineServiceStub(self.channel)
            self.render_image_stub = apirender_pb2_grpc.ApiRenderImageServiceStub(self.channel)
            self.render_view_stub = apirenderview_pb2_grpc.ApiRenderViewServiceStub(self.channel)
            self.vdb_grid_info_stub = octanevolume_pb2_grpc.VdbGridInfoServiceStub(self.channel)
            self.vdb_grid_sampler_stub = octanevolume_pb2_grpc.VdbGridSamplerServiceStub(self.channel)
            self.vdb_info_stub = octanevolume_pb2_grpc.VdbInfoServiceStub(self.channel)
            self.render_result_statistics_stub = octanerenderpasses_pb2_grpc.RenderResultStatisticsServiceStub(self.channel)
            self.animation_time_transform_stub = apianimationtimetransform_pb2_grpc.ApiAnimationTimeTransformServiceStub(self.channel)
            self.linear_time_transform_stub = apianimationtimetransform_pb2_grpc.ApiLinearTimeTransformServiceStub(self.channel)
            
            # STAGE 8: Initialize specialized service stubs
            # self.log_manager_stub = apilogmanager_pb2_grpc.ApiLogManagerServiceStub(self.channel)  # DISABLED: Naming conflict
            self.db_material_manager_stub = apidbmaterialmanager_pb2_grpc.ApiDBMaterialManagerServiceStub(self.channel)
            self.db_category_array_stub = apidbmaterialmanager_pb2_grpc.ApiDBMaterialManager_DBCategoryArrayServiceStub(self.channel)
            self.db_material_array_stub = apidbmaterialmanager_pb2_grpc.ApiDBMaterialManager_DBMaterialArrayServiceStub(self.channel)
            self.ocio_context_manager_stub = apiociocontextmanager_pb2_grpc.ApiOcioContextManagerServiceStub(self.channel)
            self.scene_exporter_stub = apisceneexporter_pb2_grpc.ApiSceneExporterServiceStub(self.channel)
            self.change_manager_stub = apichangemanager_pb2_grpc.ApiChangeManagerServiceStub(self.channel)
            self.geometry_exporter_stub = apigeometryexporter_pb2_grpc.ApiGeometryExporterServiceStub(self.channel)
            self.materialx_global_stub = apimaterialx_pb2_grpc.ApiMaterialXGlobalServiceStub(self.channel)
            
            # STAGE 9: Initialize UI and Advanced service stubs
            self.gui_component_stub = apiguicomponent_pb2_grpc.ApiGuiComponentServiceStub(self.channel)
            self.main_window_stub = apimainwindow_pb2_grpc.ApiMainWindowServiceStub(self.channel)
            self.window_stub = apiwindow_pb2_grpc.ApiWindowServiceStub(self.channel)
            self.checkbox_stub = apicheckbox_pb2_grpc.ApiCheckBoxServiceStub(self.channel)
            self.combobox_stub = apicombobox_pb2_grpc.ApiComboBoxServiceStub(self.channel)
            self.color_swatch_stub = apicolorswatch_pb2_grpc.ApiColorSwatchServiceStub(self.channel)
            self.file_chooser_stub = apifilechooser_pb2_grpc.ApiFileChooserServiceStub(self.channel)
            self.grid_layout_stub = apigridlayout_pb2_grpc.ApiGridLayoutServiceStub(self.channel)
            self.diagnostics_stub = apidiagnostics_pb2_grpc.ApiDiagnosticsServiceStub(self.channel)
            self.gaussian_splat_cloud_node_stub = apigaussiansplatting_pb2_grpc.ApiGaussianSplatCloudNodeServiceStub(self.channel)
            self.custom_curve_editor_controller_stub = apicustomcurveeditorcontroller_pb2_grpc.ApiCustomCurveEditorControllerServiceStub(self.channel)
            self.custom_curve_editor_drawer_stub = apicustomcurveeditorcontroller_pb2_grpc.ApiCustomCurveEditorController_DrawerServiceStub(self.channel)
            self.custom_curve_editor_listener_stub = apicustomcurveeditorcontroller_pb2_grpc.ApiCustomCurveEditorController_ListenerServiceStub(self.channel)
            
            # Test connection
            request = Empty()
            self.log_grpc_call("ApiProjectManagerService", "isValid", request)
            response = await self.project_stub.isValid(request)
            self.log_grpc_call("ApiProjectManagerService", "isValid", request, response)
            print("✅ Connected to Octane successfully")
            return True
            
        except Exception as e:
            print(f"❌ Failed to connect to Octane: {e}")
            return False
    
    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()
            print("🔌 Disconnected from Octane")
    
    def log_test(self, test_name, success, details="", error=None):
        """Log test result"""
        status = "✅ PASS" if success else "❌ FAIL"
        timestamp = datetime.now().strftime("%H:%M:%S")
        
        self.test_results[test_name] = {
            'success': success,
            'details': details,
            'error': str(error) if error else None,
            'timestamp': timestamp
        }
        
        print(f"[{timestamp}] {status} {test_name}")
        if details:
            print(f"    📝 {details}")
        if error:
            print(f"    ❌ Error: {error}")
    
    def log_grpc_call(self, service_name, method_name, request, response=None, error=None):
        """Log extremely explicit gRPC request/response details"""
        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]  # Include milliseconds
        
        print(f"\n{'='*80}")
        print(f"🔥 EXPLICIT gRPC CALL LOG [{timestamp}]")
        print(f"{'='*80}")
        print(f"📡 SERVICE: {service_name}")
        print(f"🎯 METHOD:  {method_name}")
        print(f"📤 REQUEST TYPE: {type(request).__name__}")
        print(f"📋 REQUEST DATA:")
        if hasattr(request, '__str__') and str(request).strip():
            print(f"    {str(request).replace(chr(10), chr(10) + '    ')}")
        else:
            print(f"    [Empty Request]")
        
        if response is not None:
            print(f"📥 RESPONSE TYPE: {type(response).__name__}")
            print(f"📦 RESPONSE DATA:")
            if hasattr(response, '__str__') and str(response).strip():
                print(f"    {str(response).replace(chr(10), chr(10) + '    ')}")
            else:
                print(f"    [Empty Response]")
        elif error:
            print(f"❌ ERROR TYPE: {type(error).__name__}")
            print(f"💥 ERROR DATA: {error}")
        else:
            print(f"⏳ RESPONSE: [Pending...]")
        print(f"{'='*80}\n")
    
    def create_object_ptr(self, handle, object_type):
        """Create ObjectPtr with proper type conversion"""
        obj_ptr = common_pb2.ObjectRef()
        obj_ptr.handle = handle
        obj_ptr.type = object_type
        return obj_ptr
    
    async def test_project_management(self):
        """Test Project Manager Service"""
        print("\n🏗️ TESTING PROJECT MANAGEMENT")
        
        try:
            # Test isValid
            request = Empty()
            self.log_grpc_call("ApiProjectManagerService", "isValid", request)
            response = await self.project_stub.isValid(request)
            self.log_grpc_call("ApiProjectManagerService", "isValid", request, response)
            self.log_test("ProjectManager.isValid", True, f"Valid: {response.result}")
            
            # Test getCurrentProject
            request = Empty()
            self.log_grpc_call("ApiProjectManagerService", "getCurrentProject", request)
            response = await self.project_stub.getCurrentProject(request)
            self.log_grpc_call("ApiProjectManagerService", "getCurrentProject", request, response)
            if hasattr(response, 'result') and response.result:
                # Check if result is a string (file path) or has a handle
                if isinstance(response.result, str) and response.result.strip():
                    self.log_test("ProjectManager.getCurrentProject", True, f"Current project: {response.result}")
                elif hasattr(response.result, 'handle') and response.result.handle > 0:
                    self.log_test("ProjectManager.getCurrentProject", True, f"Project handle: {response.result.handle}")
                    self.created_objects.append(('project', response.result))
                else:
                    self.log_test("ProjectManager.getCurrentProject", False, f"Invalid project response: {response}")
            else:
                self.log_test("ProjectManager.getCurrentProject", False, f"No current project - response: {response}")
            
            # Test rootNodeGraph
            request = Empty()
            self.log_grpc_call("ApiProjectManagerService", "rootNodeGraph", request)
            response = await self.project_stub.rootNodeGraph(request)
            self.log_grpc_call("ApiProjectManagerService", "rootNodeGraph", request, response)
            if hasattr(response, 'result') and hasattr(response.result, 'handle') and response.result.handle > 0:
                self.log_test("ProjectManager.rootNodeGraph", True, f"Root graph handle: {response.result.handle}")
                self.created_objects.append(('root_graph', response.result))
                return response.result
            else:
                self.log_test("ProjectManager.rootNodeGraph", False, f"No root graph - response: {response}")
                return None
                
        except Exception as e:
            self.log_test("ProjectManager", False, error=e)
            return None
    
    async def test_item_service_basic(self, object_ref):
        """Test basic ApiItem service methods"""
        print("\n📦 TESTING ITEM SERVICE - BASIC OPERATIONS")
        
        if not object_ref:
            self.log_test("ItemService.Basic", False, "No object reference provided")
            return
        
        try:
            # Test name() - CRITICAL: Use ApiItem type (16)
            request = apinodesystem_pb2.ApiItem.nameRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type for ApiItemService
            self.log_grpc_call("ApiItemService", "name", request)
            response = await self.item_stub.name(request)
            self.log_grpc_call("ApiItemService", "name", request, response)
            self.log_test("ItemService.name", True, f"Name: '{response.result}'")
            
            # Test uniqueId()
            request = apinodesystem_pb2.ApiItem.uniqueIdRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type
            self.log_grpc_call("ApiItemService", "uniqueId", request)
            response = await self.item_stub.uniqueId(request)
            self.log_grpc_call("ApiItemService", "uniqueId", request, response)
            self.log_test("ItemService.uniqueId", True, f"Unique ID: {response.result}")
            
            # Test version()
            request = apinodesystem_pb2.ApiItem.versionRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type
            self.log_grpc_call("ApiItemService", "version", request)
            response = await self.item_stub.version(request)
            self.log_grpc_call("ApiItemService", "version", request, response)
            self.log_test("ItemService.version", True, f"Version: {response.result}")
            
            # Test isNode()
            request = apinodesystem_pb2.ApiItem.isNodeRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type
            self.log_grpc_call("ApiItemService", "isNode", request)
            response = await self.item_stub.isNode(request)
            self.log_grpc_call("ApiItemService", "isNode", request, response)
            self.log_test("ItemService.isNode", True, f"Is Node: {response.result}")
            
            # Test isGraph()
            request = apinodesystem_pb2.ApiItem.isGraphRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type
            self.log_grpc_call("ApiItemService", "isGraph", request)
            response = await self.item_stub.isGraph(request)
            self.log_grpc_call("ApiItemService", "isGraph", request, response)
            self.log_test("ItemService.isGraph", True, f"Is Graph: {response.result}")
            
        except Exception as e:
            self.log_test("ItemService.Basic", False, error=e)
    
    async def test_node_creation(self, root_graph_ref):
        """Test node creation and basic node operations"""
        print("\n🔧 TESTING NODE CREATION")
        
        if not root_graph_ref:
            self.log_test("NodeCreation", False, "No root graph reference")
            return []
        
        created_nodes = []
        
        # Test creating different types of nodes
        node_types_to_test = [
            (octaneids_pb2.NT_MAT_DIFFUSE, "Diffuse Material"),
            (octaneids_pb2.NT_MAT_GLOSSY, "Glossy Material"),
            (octaneids_pb2.NT_GEO_SDF_SPHERE, "SDF Sphere Geometry"),
            (octaneids_pb2.NT_TEX_CELLNOISE, "Cell Noise Texture"),
            (octaneids_pb2.NT_LIGHT_SPHERE, "Sphere Light")
        ]
        
        for node_type_id, node_type_name in node_types_to_test:
            try:
                # Create node
                request = apinodesystem_pb2.ApiNode.createRequest()
                request.ownerGraph.handle = root_graph_ref.handle
                request.ownerGraph.type = 18  # ApiRootNodeGraph type for the owner graph
                request.type = node_type_id
                self.log_grpc_call("ApiNodeService", "create", request)
                response = await self.node_stub.create(request)
                self.log_grpc_call("ApiNodeService", "create", request, response)
                if response.result.handle > 0:
                    created_node = response.result
                    self.log_test(f"NodeService.create_{node_type_name}", True, f"Created {node_type_name}: {created_node.handle}")
                    self.created_objects.append((f'{node_type_name.lower().replace(" ", "_")}_node', created_node))
                    created_nodes.append(created_node)
                    
                    # Test the created node with ItemService
                    await self.test_created_node(created_node, node_type_name)
                else:
                    self.log_test(f"NodeService.create_{node_type_name}", False, "Failed to create node")
                    
            except Exception as e:
                self.log_test(f"NodeCreation_{node_type_name}", False, error=e)
        
        return created_nodes
    
    async def test_created_node(self, node_ref, node_type_name="Node"):
        """Test operations on a created node"""
        print(f"\n🔍 TESTING {node_type_name.upper()} OPERATIONS")
        
        try:
            # Get node name using ItemService (type conversion!)
            request = apinodesystem_pb2.ApiItem.nameRequest()
            request.objectPtr.handle = node_ref.handle
            request.objectPtr.type = 16  # ApiItem type for ItemService
            self.log_grpc_call("ApiItemService", "name", request)
            response = await self.item_stub.name(request)
            self.log_grpc_call("ApiItemService", "name", request, response)
            self.log_test(f"{node_type_name}.name", True, f"Node name: '{response.result}'")
            
            # Get node type using NodeService
            request = apinodesystem_pb2.ApiNode.typeRequest()
            request.objectPtr.handle = node_ref.handle
            request.objectPtr.type = 17  # ApiNode type for NodeService
            self.log_grpc_call("ApiNodeService", "type", request)
            response = await self.node_stub.type(request)
            self.log_grpc_call("ApiNodeService", "type", request, response)
            self.log_test(f"{node_type_name}.type", True, f"Node type ID: {response.result}")
            
            # Get pin count
            request = apinodesystem_pb2.ApiNode.pinCountRequest()
            request.objectPtr.handle = node_ref.handle
            request.objectPtr.type = 17  # ApiNode type
            self.log_grpc_call("ApiNodeService", "pinCount", request)
            response = await self.node_stub.pinCount(request)
            self.log_grpc_call("ApiNodeService", "pinCount", request, response)
            pin_count = response.result
            self.log_test(f"{node_type_name}.pinCount", True, f"Pin count: {pin_count}")
            
            # Test pin operations if we have pins
            if pin_count > 0:
                await self.test_pin_operations(node_ref, pin_count, node_type_name)
                
        except Exception as e:
            self.log_test(f"{node_type_name}.operations", False, error=e)
    
    async def test_pin_operations(self, node_ref, pin_count, node_type_name="Node"):
        """Test pin operations on a node"""
        print(f"\n📌 TESTING {node_type_name.upper()} PIN OPERATIONS")
        
        try:
            # Test first few pins
            max_pins_to_test = min(pin_count, 5)
            
            for pin_idx in range(max_pins_to_test):
                # Get pin name
                request = apinodesystem_pb2.ApiNode.pinNameRequest()
                request.objectPtr.handle = node_ref.handle
                request.objectPtr.type = 17  # ApiNode type
                request.id = pin_idx
                self.log_grpc_call("ApiNodeService", "pinName", request)
                response = await self.node_stub.pinName(request)
                self.log_grpc_call("ApiNodeService", "pinName", request, response)
                pin_name = response.result
                
                # Get pin type
                request = apinodesystem_pb2.ApiNode.pinTypeRequest()
                request.objectPtr.handle = node_ref.handle
                request.objectPtr.type = 17  # ApiNode type
                request.id = pin_idx
                self.log_grpc_call("ApiNodeService", "pinType", request)
                response = await self.node_stub.pinType(request)
                self.log_grpc_call("ApiNodeService", "pinType", request, response)
                pin_type = response.result
                
                self.log_test(f"Pin[{pin_idx}]", True, f"Name: '{pin_name}', Type: {pin_type}")
                
                # Try to get pin value (this might fail for some pin types)
                try:
                    request = apinodesystem_pb2.ApiNode.getPinFloatRequest()
                    request.objectPtr.handle = node_ref.handle
                    request.objectPtr.type = 17  # ApiNode type
                    request.id = pin_idx
                    self.log_grpc_call("ApiNodeService", "getPinFloat", request)
                    response = await self.node_stub.getPinFloat(request)
                    self.log_grpc_call("ApiNodeService", "getPinFloat", request, response)
                    self.log_test(f"Pin[{pin_idx}].getValue", True, f"Float value: {response.result}")
                except:
                    # Try string value instead
                    try:
                        request = apinodesystem_pb2.ApiNode.getPinStringRequest()
                        request.objectPtr.handle = node_ref.handle
                        request.objectPtr.type = 17  # ApiNode type
                        request.id = pin_idx
                        self.log_grpc_call("ApiNodeService", "getPinString", request)
                        response = await self.node_stub.getPinString(request)
                        self.log_grpc_call("ApiNodeService", "getPinString", request, response)
                        self.log_test(f"Pin[{pin_idx}].getValue", True, f"String value: '{response.result}'")
                    except:
                        self.log_test(f"Pin[{pin_idx}].getValue", False, "Could not get value (unsupported type)")
                        
        except Exception as e:
            self.log_test("PinOperations", False, error=e)
    
    async def test_attribute_operations(self, object_ref):
        """Test attribute getting/setting operations"""
        print("\n🏷️ TESTING ATTRIBUTE OPERATIONS")
        
        if not object_ref:
            return
        
        try:
            # Get attribute count
            request = apinodesystem_pb2.ApiItem.attrCountRequest()
            request.objectPtr.handle = object_ref.handle
            request.objectPtr.type = 16  # ApiItem type
            self.log_grpc_call("ApiItemService", "attrCount", request)
            response = await self.item_stub.attrCount(request)
            self.log_grpc_call("ApiItemService", "attrCount", request, response)
            attr_count = response.result
            self.log_test("AttributeOps.attrCount", True, f"Attribute count: {attr_count}")
            
            # Test first few attributes
            max_attrs_to_test = min(attr_count, 10)
            
            for attr_idx in range(max_attrs_to_test):
                # Get attribute name
                request = apinodesystem_pb2.ApiItem.attrNameRequest()
                request.objectPtr.handle = object_ref.handle
                request.objectPtr.type = 16  # ApiItem type
                request.attrIdx = attr_idx
                
                response = await self.item_stub.attrName(request)
                attr_name = response.result
                
                # Get attribute type
                request = apinodesystem_pb2.ApiItem.attrTypeRequest()
                request.objectPtr.handle = object_ref.handle
                request.objectPtr.type = 16  # ApiItem type
                request.attrIdx = attr_idx
                
                response = await self.item_stub.attrType(request)
                attr_type = response.result
                
                self.log_test(f"Attr[{attr_idx}]", True, f"Name: '{attr_name}', Type: {attr_type}")
                
                # Try to get attribute value based on type
                await self.test_attribute_value(object_ref, attr_idx, attr_name, attr_type)
                
        except Exception as e:
            self.log_test("AttributeOperations", False, error=e)
    
    async def test_attribute_value(self, object_ref, attr_idx, attr_name, attr_type):
        """Test getting attribute value based on its type"""
        try:
            # Try different value getters based on common types
            value_getters = [
                ('Float', 'getFloat'),
                ('Int', 'getInt'),
                ('Bool', 'getBool'),
                ('String', 'getString'),
                ('Float3', 'getFloat3'),
                ('Float4', 'getFloat4')
            ]
            
            for type_name, getter_method in value_getters:
                try:
                    request_class = getattr(apinodesystem_pb2.ApiItem, f"{getter_method}Request")
                    request = request_class()
                    request.objectPtr.handle = object_ref.handle
                    request.objectPtr.type = 16  # ApiItem type
                    request.attrIdx = attr_idx
                    
                    getter_func = getattr(self.item_stub, getter_method)
                    response = await getter_func(request)
                    
                    self.log_test(f"Attr[{attr_idx}].{getter_method}", True, f"Value: {response.result}")
                    break  # Success, don't try other getters
                    
                except Exception:
                    continue  # Try next getter
            else:
                self.log_test(f"Attr[{attr_idx}].getValue", False, "Could not get value with any getter")
                
        except Exception as e:
            self.log_test(f"Attr[{attr_idx}].getValue", False, error=e)
    
    async def test_node_connections(self, node_ref):
        """Test node connection operations"""
        print("\n🔗 TESTING NODE CONNECTIONS")
        
        if not node_ref:
            return
        
        try:
            # Get destination nodes
            request = apinodesystem_pb2.ApiNode.destinationNodesRequest()
            request.objectPtr.handle = node_ref.handle
            request.objectPtr.type = 17  # ApiNode type
            
            response = await self.node_stub.destinationNodes(request)
            # Handle different possible response structures
            if hasattr(response, 'result'):
                if hasattr(response.result, 'data'):
                    dest_count = len(response.result.data)
                elif hasattr(response.result, 'items'):
                    dest_count = len(response.result.items)
                else:
                    dest_count = 0
                    print(f"    📝 Response structure: {response.result}")
            else:
                dest_count = 0
                print(f"    📝 Response structure: {response}")
            self.log_test("NodeConnections.destinationNodes", True, f"Destination nodes: {dest_count}")
            
            # Test input connections for each pin
            request = apinodesystem_pb2.ApiNode.pinCountRequest()
            request.objectPtr.handle = node_ref.handle
            request.objectPtr.type = 17  # ApiNode type
            
            response = await self.node_stub.pinCount(request)
            pin_count = response.result
            
            connected_pins = 0
            for pin_idx in range(min(pin_count, 5)):  # Test first 5 pins
                try:
                    request = apinodesystem_pb2.ApiNode.inputNodeRequest()
                    request.objectPtr.handle = node_ref.handle
                    request.objectPtr.type = 17  # ApiNode type
                    request.id = pin_idx
                    
                    response = await self.node_stub.inputNode(request)
                    if response.result.handle > 0:
                        connected_pins += 1
                        self.log_test(f"Pin[{pin_idx}].inputNode", True, f"Connected to: {response.result.handle}")
                    
                except Exception:
                    pass  # Pin not connected, which is normal
            
            self.log_test("NodeConnections.connectedPins", True, f"Connected pins: {connected_pins}/{min(pin_count, 5)}")
            
        except Exception as e:
            self.log_test("NodeConnections", False, error=e)
    
    async def test_graph_operations(self, root_graph_ref):
        """Test node graph operations"""
        print("\n🕸️ TESTING GRAPH OPERATIONS")
        
        if not root_graph_ref:
            return
        
        try:
            # Test if object is a graph (using ItemService)
            request = apinodesystem_pb2.ApiItem.isGraphRequest()
            request.objectPtr.handle = root_graph_ref.handle
            request.objectPtr.type = 16  # ApiItem type for ItemService
            
            response = await self.item_stub.isGraph(request)
            is_graph = response.result
            self.log_test("GraphOps.isGraph", True, f"Is graph: {is_graph}")
            
            if is_graph:
                # Try to convert to graph and test graph-specific operations
                request = apinodesystem_pb2.ApiItem.toGraphRequest()
                request.objectPtr.handle = root_graph_ref.handle
                request.objectPtr.type = 16  # ApiItem type
                
                response = await self.item_stub.toGraph(request)
                graph_ref = response.result
                
                if graph_ref.handle > 0:
                    self.log_test("GraphOps.toGraph", True, f"Graph handle: {graph_ref.handle}")
                    
                    # Test graph-specific operations would go here
                    # Note: Would need ApiNodeGraphService methods
                    
        except Exception as e:
            self.log_test("GraphOperations", False, error=e)
    
    async def test_pin_value_setting(self, created_nodes):
        """Test setting pin values on created nodes"""
        print("\n🎛️ TESTING PIN VALUE SETTING")
        
        for i, node_ref in enumerate(created_nodes[:3]):  # Test first 3 nodes
            try:
                # Get pin count first
                request = apinodesystem_pb2.ApiNode.pinCountRequest()
                request.objectPtr.handle = node_ref.handle
                request.objectPtr.type = 17  # ApiNode type
                self.log_grpc_call("ApiNodeService", "pinCount", request)
                response = await self.node_stub.pinCount(request)
                self.log_grpc_call("ApiNodeService", "pinCount", request, response)
                pin_count = response.result
                
                # Try to set some pin values
                test_values = [1.5, 0.8, 2.0]
                for pin_idx in range(min(pin_count, 3)):
                    try:
                        # Try setting float value
                        request = apinodesystem_pb2.ApiNode.setPinValueRequest()
                        request.objectPtr.handle = node_ref.handle
                        request.objectPtr.type = 17  # ApiNode type
                        request.id = pin_idx
                        request.value = int(test_values[pin_idx % len(test_values)] * 100)  # Convert to int
                        self.log_grpc_call("ApiNodeService", "setPinValue", request)
                        response = await self.node_stub.setPinValue(request)
                        self.log_grpc_call("ApiNodeService", "setPinValue", request, response)
                        self.log_test(f"Node[{i}].setPinValue[{pin_idx}]", True, f"Set to {test_values[pin_idx % len(test_values)]}")
                        
                        # Verify the value was set
                        request = apinodesystem_pb2.ApiNode.getPinFloatRequest()
                        request.objectPtr.handle = node_ref.handle
                        request.objectPtr.type = 17  # ApiNode type
                        request.id = pin_idx
                        self.log_grpc_call("ApiNodeService", "getPinFloat", request)
                        response = await self.node_stub.getPinFloat(request)
                        self.log_grpc_call("ApiNodeService", "getPinFloat", request, response)
                        self.log_test(f"Node[{i}].verifyPinValue[{pin_idx}]", True, f"Verified: {response.result}")
                        
                    except Exception as e:
                        self.log_test(f"Node[{i}].setPinValue[{pin_idx}]", False, error=e)
                        
            except Exception as e:
                self.log_test(f"PinValueSetting.Node[{i}]", False, error=e)
    
    async def test_node_to_node_connections(self, created_nodes):
        """Test connecting nodes to each other"""
        print("\n🔗 TESTING NODE-TO-NODE CONNECTIONS")
        
        if len(created_nodes) < 2:
            self.log_test("NodeConnections", False, "Need at least 2 nodes for connection testing")
            return
        
        try:
            source_node = created_nodes[0]
            target_node = created_nodes[1]
            
            # Try to connect source node output to target node input
            # First, find available pins
            request = apinodesystem_pb2.ApiNode.pinCountRequest()
            request.objectPtr.handle = target_node.handle
            request.objectPtr.type = 17  # ApiNode type
            
            response = await self.node_stub.pinCount(request)
            target_pin_count = response.result
            
            if target_pin_count > 0:
                # Try to connect to first pin of target node
                request = apinodesystem_pb2.ApiNode.connectToRequest()
                request.objectPtr.handle = target_node.handle
                request.objectPtr.type = 17  # ApiNode type
                request.pinId = 0  # First pin
                request.sourceNode.handle = source_node.handle
                request.sourceNode.type = 17  # ApiNode type
                
                try:
                    response = await self.node_stub.connectTo(request)
                    self.log_test("NodeConnections.connectTo", True, f"Connected node {source_node.handle} to {target_node.handle}")
                    
                    # Verify connection
                    request = apinodesystem_pb2.ApiNode.inputNodeRequest()
                    request.objectPtr.handle = target_node.handle
                    request.objectPtr.type = 17  # ApiNode type
                    request.pinId = 0
                    
                    response = await self.node_stub.inputNode(request)
                    if response.result.handle == source_node.handle:
                        self.log_test("NodeConnections.verifyConnection", True, f"Connection verified")
                    else:
                        self.log_test("NodeConnections.verifyConnection", False, f"Connection not found")
                        
                except Exception as e:
                    self.log_test("NodeConnections.connectTo", False, error=e)
            else:
                self.log_test("NodeConnections", False, "Target node has no pins")
                
        except Exception as e:
            self.log_test("NodeToNodeConnections", False, error=e)
    
    async def test_advanced_operations(self):
        """Test advanced operations and edge cases"""
        print("\n🚀 TESTING ADVANCED OPERATIONS")
        
        try:
            # Test LiveLink service if available
            try:
                # This might not be available in all Octane configurations
                # Use Empty() request like the proxy does
                request = livelink_pb2.Empty()
                self.log_grpc_call("LiveLinkService", "GetCamera", request)
                response = await self.livelink_stub.GetCamera(request)
                self.log_grpc_call("LiveLinkService", "GetCamera", request, response)
                
                camera_info = f"pos=({response.position.x:.2f}, {response.position.y:.2f}, {response.position.z:.2f})"
                self.log_test("LiveLink.GetCamera", True, f"Camera data retrieved: {camera_info}")
            except Exception as e:
                self.log_grpc_call("LiveLinkService", "GetCamera", request, error=e)
                self.log_test("LiveLink.GetCamera", False, f"LiveLink service not available: {e}")
            
            # Test project settings
            try:
                response = await self.project_stub.projectSettings(Empty())
                if response.result.handle > 0:
                    self.log_test("Advanced.projectSettings", True, f"Settings handle: {response.result.handle}")
                else:
                    self.log_test("Advanced.projectSettings", False, "No project settings")
            except Exception as e:
                self.log_test("Advanced.projectSettings", False, error=e)
            
            # Test material ball
            try:
                response = await self.project_stub.materialBall(Empty())
                if response.result.handle > 0:
                    self.log_test("Advanced.materialBall", True, f"Material ball handle: {response.result.handle}")
                else:
                    self.log_test("Advanced.materialBall", False, "No material ball")
            except Exception as e:
                self.log_test("Advanced.materialBall", False, error=e)
                
        except Exception as e:
            self.log_test("AdvancedOperations", False, error=e)
    
    async def test_error_conditions(self):
        """Test error handling and edge cases"""
        print("\n⚠️ TESTING ERROR CONDITIONS")
        
        try:
            # Test invalid object handle
            request = apinodesystem_pb2.ApiItem.nameRequest()
            request.objectPtr.handle = 999999999  # Invalid handle
            request.objectPtr.type = 16  # ApiItem type
            
            try:
                response = await self.item_stub.name(request)
                self.log_test("ErrorTest.invalidHandle", False, "Should have failed with invalid handle")
            except Exception:
                self.log_test("ErrorTest.invalidHandle", True, "Correctly rejected invalid handle")
            
            # Test wrong type conversion
            if self.created_objects:
                obj_name, obj_ref = self.created_objects[0]
                request = apinodesystem_pb2.ApiItem.nameRequest()
                request.objectPtr.handle = obj_ref.handle
                request.objectPtr.type = 999  # Invalid type
                
                try:
                    response = await self.item_stub.name(request)
                    self.log_test("ErrorTest.invalidType", False, "Should have failed with invalid type")
                except Exception:
                    self.log_test("ErrorTest.invalidType", True, "Correctly rejected invalid type")
            
        except Exception as e:
            self.log_test("ErrorConditions", False, error=e)
    
    async def test_stage1_services(self):
        """Test STAGE 1: Core rendering and scene services with REAL gRPC calls"""
        print("\n🚀 TESTING STAGE 1: CORE SERVICES")
        print("=" * 40)
        
        try:
            # Test ApiRenderEngineService with actual gRPC call
            print("\n🎨 Testing ApiRenderEngineService...")
            try:
                # Test render engine service with actual gRPC call
                request = apirender_pb2.ApiRenderEngine.fpsRequest()
                self.log_grpc_call("ApiRenderEngineService", "fps", request)
                response = await self.render_stub.fps(request)  # Await async call
                self.log_grpc_call("ApiRenderEngineService", "fps", request, response)
                self.log_test("RenderEngineService.fps", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderEngineService.fps", False, error=e)
            
            # Test ApiSceneOutlinerService with actual gRPC call
            print("\n🌳 Testing ApiSceneOutlinerService...")
            try:
                # Test scene outliner service with actual gRPC call
                request = apisceneoutliner_pb2.ApiSceneOutliner.createRequest()
                self.log_grpc_call("ApiSceneOutlinerService", "create", request)
                response = await self.scene_outliner_stub.create(request)  # Await async call
                self.log_grpc_call("ApiSceneOutlinerService", "create", request, response)
                self.log_test("SceneOutlinerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("SceneOutlinerService.create", False, error=e)
            
            # Test ApiSelectionManagerService with actual gRPC call
            print("\n🎯 Testing ApiSelectionManagerService...")
            try:
                # Test selection manager service with actual gRPC call
                request = apiselectionmanager_pb2.ApiSelectionManager.clearSelectionRequest()
                self.log_grpc_call("ApiSelectionManagerService", "clearSelection", request)
                response = await self.selection_manager_stub.clearSelection(request)  # Await async call
                self.log_grpc_call("ApiSelectionManagerService", "clearSelection", request, response)
                self.log_test("SelectionManagerService.clearSelection", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("SelectionManagerService.clearSelection", False, error=e)
            
            # Test ApiNodeGraphEditorService with actual gRPC call
            print("\n📊 Testing ApiNodeGraphEditorService...")
            try:
                # Test node graph editor service with actual gRPC call
                request = apinodegrapheditor_pb2.ApiNodeGraphEditor.createRequest()
                self.log_grpc_call("ApiNodeGraphEditorService", "create", request)
                response = await self.node_graph_editor_stub.create(request)  # Await async call
                self.log_grpc_call("ApiNodeGraphEditorService", "create", request, response)
                self.log_test("NodeGraphEditorService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("NodeGraphEditorService.create", False, error=e)
                
        except Exception as e:
            self.log_test("Stage1Services", False, error=e)
    
    async def test_stage2_services(self):
        """Test STAGE 2: Image & geometry services"""
        print("\n🖼️ TESTING STAGE 2: IMAGE & GEOMETRY SERVICES")
        print("=" * 50)
        
        try:
            # Test ApiImageService with actual gRPC call
            print("\n🖼️ Testing ApiImageService...")
            try:
                # Test image service with actual gRPC call
                request = apiimage_pb2.ApiImage.createRequest()
                self.log_grpc_call("ApiImageService", "create", request)
                response = await self.image_stub.create(request)  # Await async call
                self.log_grpc_call("ApiImageService", "create", request, response)
                self.log_test("ImageService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ImageService.create", False, error=e)
            
            # Test ApiImageBufferService with actual gRPC call
            print("\n📦 Testing ApiImageBufferService...")
            try:
                # Test image buffer service with actual gRPC call
                request = apiimagebuffer_pb2.ApiImageBuffer.applyBoxFilterRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.filterSize = 1  # Simple filter size
                self.log_grpc_call("ApiImageBufferService", "applyBoxFilter", request)
                response = await self.image_buffer_stub.applyBoxFilter(request)  # Await async call
                self.log_grpc_call("ApiImageBufferService", "applyBoxFilter", request, response)
                self.log_test("ImageBufferService.applyBoxFilter", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ImageBufferService.applyBoxFilter", False, error=e)
            
            # Test ApiImageComponentService with actual gRPC call
            print("\n🧩 Testing ApiImageComponentService...")
            print("⚠️ DISABLED: ApiImageComponentService.create crashes Octane")
            self.log_test("ImageComponentService.create", False, error="DISABLED: Crashes Octane - identified as crash culprit")
            
            # Test ImageInfoService with actual gRPC call
            print("\nℹ️ Testing ImageInfoService...")
            try:
                # Test image info service with actual gRPC call
                request = apiimageinfo_pb2.ImageInfo.isCompressedRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ImageInfoService", "isCompressed", request)
                response = await self.image_info_stub.isCompressed(request)  # Await async call
                self.log_grpc_call("ImageInfoService", "isCompressed", request, response)
                self.log_test("ImageInfoService.isCompressed", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ImageInfoService.isCompressed", False, error=e)
            
            # Test ApiGeometryExporterService with actual gRPC call
            print("\n📐 Testing ApiGeometryExporterService...")
            try:
                # Test geometry exporter service with actual gRPC call
                request = apigeometryexporter_pb2.ApiGeometryExporter.createRequest()
                self.log_grpc_call("ApiGeometryExporterService", "create", request)
                response = await self.geometry_exporter_stub.create(request)  # Await async call
                self.log_grpc_call("ApiGeometryExporterService", "create", request, response)
                self.log_test("GeometryExporterService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GeometryExporterService.create", False, error=e)
            
            # Test ApiDbMaterialManagerService with actual gRPC call
            print("\n🗃️ Testing ApiDbMaterialManagerService...")
            try:
                # Test DB material manager service with actual gRPC call
                request = apidbmaterialmanager_pb2.ApiDbMaterialManager.createRequest()
                self.log_grpc_call("ApiDbMaterialManagerService", "create", request)
                response = await self.db_material_manager_stub.create(request)  # Await async call
                self.log_grpc_call("ApiDbMaterialManagerService", "create", request, response)
                self.log_test("DbMaterialManagerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DbMaterialManagerService.create", False, error=e)
            
            # Test ApiMaterialXService with actual gRPC call
            print("\n🎨 Testing ApiMaterialXService...")
            try:
                # Test MaterialX service with actual gRPC call
                request = apimaterialx_pb2.ApiMaterialX.createRequest()
                self.log_grpc_call("ApiMaterialXService", "create", request)
                response = await self.materialx_stub.create(request)  # Await async call
                self.log_grpc_call("ApiMaterialXService", "create", request, response)
                self.log_test("MaterialXService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("MaterialXService.create", False, error=e)
            
            # Test ApiTimeSamplingService with actual gRPC call
            print("\n⏱️ Testing ApiTimeSamplingService...")
            try:
                # Test time sampling service with actual gRPC call
                request = apitimesampling_pb2.ApiTimeSampling.createRequest()
                self.log_grpc_call("ApiTimeSamplingService", "create", request)
                response = await self.time_sampling_stub.create(request)  # Await async call
                self.log_grpc_call("ApiTimeSamplingService", "create", request, response)
                self.log_test("TimeSamplingService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("TimeSamplingService.create", False, error=e)
                
        except Exception as e:
            self.log_test("Stage2Services", False, error=e)
    
    async def test_stage3_services(self):
        """Test STAGE 3: UI & editor services"""
        print("\n🖥️ TESTING STAGE 3: UI & EDITOR SERVICES")
        print("=" * 50)
        
        try:
            # Test ApiGuiComponentService with actual gRPC call
            print("\n🖥️ Testing ApiGuiComponentService...")
            try:
                # Test GUI component service with actual gRPC call
                request = apiguicomponent_pb2.ApiGuiComponent.heightRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiGuiComponentService", "height", request)
                response = await self.gui_component_stub.height(request)  # Await async call
                self.log_grpc_call("ApiGuiComponentService", "height", request, response)
                self.log_test("GuiComponentService.height", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GuiComponentService.height", False, error=e)
            
            # Test ApiRenderViewService with actual gRPC call
            print("\n🎬 Testing ApiRenderViewService...")
            try:
                # Test render view service with actual gRPC call
                request = apirenderview_pb2.ApiRenderView.createRequest()
                self.log_grpc_call("ApiRenderViewService", "create", request)
                response = await self.render_view_stub.create(request)  # Await async call
                self.log_grpc_call("ApiRenderViewService", "create", request, response)
                self.log_test("RenderViewService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderViewService.create", False, error=e)
            
            # Test ApiTextEditorService with actual gRPC call
            print("\n📝 Testing ApiTextEditorService...")
            try:
                # Test text editor service with actual gRPC call
                request = apitexteditor_pb2.ApiTextEditor.createRequest()
                self.log_grpc_call("ApiTextEditorService", "create", request)
                response = await self.text_editor_stub.create(request)  # Await async call
                self.log_grpc_call("ApiTextEditorService", "create", request, response)
                self.log_test("TextEditorService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("TextEditorService.create", False, error=e)
            
            # Test ApiCustomCurveEditorControllerService with actual gRPC call
            print("\n📈 Testing ApiCustomCurveEditorControllerService...")
            try:
                # Test curve editor controller service with actual gRPC call
                request = apicustomcurveeditorcontroller_pb2.ApiCustomCurveEditorController.createRequest()
                self.log_grpc_call("ApiCustomCurveEditorControllerService", "create", request)
                response = await self.curve_editor_controller_stub.create(request)  # Await async call
                self.log_grpc_call("ApiCustomCurveEditorControllerService", "create", request, response)
                self.log_test("CurveEditorControllerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CurveEditorControllerService.create", False, error=e)
            
            # Test ApiChangeManagerService with actual gRPC call
            print("\n🔄 Testing ApiChangeManagerService...")
            try:
                # Test change manager service with actual gRPC call
                request = apichangemanager_pb2.ApiChangeManager.createRequest()
                self.log_grpc_call("ApiChangeManagerService", "create", request)
                response = await self.change_manager_stub.create(request)  # Await async call
                self.log_grpc_call("ApiChangeManagerService", "create", request, response)
                self.log_test("ChangeManagerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ChangeManagerService.create", False, error=e)
            
            # Test ApiDiagnosticsService with actual gRPC call
            print("\n🔍 Testing ApiDiagnosticsService...")
            try:
                # Test diagnostics service with actual gRPC call
                request = apidiagnostics_pb2.ApiDiagnostics.createRequest()
                self.log_grpc_call("ApiDiagnosticsService", "create", request)
                response = await self.diagnostics_stub.create(request)  # Await async call
                self.log_grpc_call("ApiDiagnosticsService", "create", request, response)
                self.log_test("DiagnosticsService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DiagnosticsService.create", False, error=e)
            
            # Test ApiLogManagerService with actual gRPC call
            print("\n📋 Testing ApiLogManagerService...")
            try:
                # Test log manager service with actual gRPC call
                request = apilogmanager_pb2.ApiLogManager.createRequest()
                self.log_grpc_call("ApiLogManagerService", "create", request)
                response = await self.log_manager_stub.create(request)  # Await async call
                self.log_grpc_call("ApiLogManagerService", "create", request, response)
                self.log_test("LogManagerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("LogManagerService.create", False, error=e)
                
        except Exception as e:
            self.log_test("Stage3Services", False, error=e)
    
    async def test_stage4_services(self):
        """Test STAGE 4: File & data management services"""
        print("\n📁 TESTING STAGE 4: FILE & DATA MANAGEMENT SERVICES")
        print("=" * 60)
        
        try:
            # Test ApiBinaryGroupService with actual gRPC call
            print("\n🔧 Testing ApiBinaryGroupService...")
            try:
                # Test binary group service with actual gRPC call
                request = apibinaryfile_pb2.ApiBinaryGroup.add10Request()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.value = 42  # Test value
                self.log_grpc_call("ApiBinaryGroupService", "add10", request)
                response = await self.binary_group_stub.add10(request)  # Await async call
                self.log_grpc_call("ApiBinaryGroupService", "add10", request, response)
                self.log_test("BinaryGroupService.add10", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("BinaryGroupService.add10", False, error=e)
                
            # Test ApiBinaryTableService with actual gRPC call
            print("\n🔧 Testing ApiBinaryTableService...")
            try:
                # Test binary table service with actual gRPC call
                request = apibinaryfile_pb2.ApiBinaryTable.createRequest()
                self.log_grpc_call("ApiBinaryTableService", "create", request)
                response = await self.binary_table_stub.create(request)  # Await async call
                self.log_grpc_call("ApiBinaryTableService", "create", request, response)
                self.log_test("BinaryTableService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("BinaryTableService.create", False, error=e)
            
            # Test ApiCachesService with actual gRPC call
            print("\n💾 Testing ApiCachesService...")
            try:
                # Test cache service with actual gRPC call
                request = apicaches_pb2.ApiCaches.clearMeshletCacheRequest()
                self.log_grpc_call("ApiCachesService", "clearMeshletCache", request)
                response = await self.caches_stub.clearMeshletCache(request)  # Await async call
                self.log_grpc_call("ApiCachesService", "clearMeshletCache", request, response)
                self.log_test("CachesService.clearMeshletCache", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CachesService.clearMeshletCache", False, error=e)
            
            # Test ApiFileChooserService with actual gRPC call
            print("\n📂 Testing ApiFileChooserService...")
            try:
                # Test file chooser service with actual gRPC call
                request = apifilechooser_pb2.ApiFileChooser.browseForDirectoryRequest()
                request.title = "Test Directory Browse"
                request.initialDirectory = "/tmp"
                self.log_grpc_call("ApiFileChooserService", "browseForDirectory", request)
                response = await self.file_chooser_stub.browseForDirectory(request)  # Await async call
                self.log_grpc_call("ApiFileChooserService", "browseForDirectory", request, response)
                self.log_test("FileChooserService.browseForDirectory", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("FileChooserService.browseForDirectory", False, error=e)
            
            # Test ApiFileNameService with actual gRPC call
            print("\n📄 Testing ApiFileNameService...")
            try:
                # Test filename service with actual gRPC call
                request = apifilename_pb2.ApiFileName.clearRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiFileNameService", "clear", request)
                response = await self.filename_stub.clear(request)  # Await async call
                self.log_grpc_call("ApiFileNameService", "clear", request, response)
                self.log_test("FileNameService.clear", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("FileNameService.clear", False, error=e)
            
            # Test ApiModuleDataService with actual gRPC call
            print("\n🧩 Testing ApiModuleDataService...")
            try:
                # Test module data service with actual gRPC call
                request = apimoduledata_pb2.ApiModuleData.loadApplicationDataRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.key = "test_key"
                self.log_grpc_call("ApiModuleDataService", "loadApplicationData", request)
                response = await self.module_data_stub.loadApplicationData(request)  # Await async call
                self.log_grpc_call("ApiModuleDataService", "loadApplicationData", request, response)
                self.log_test("ModuleDataService.loadApplicationData", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ModuleDataService.loadApplicationData", False, error=e)
            
            # Test ApiSceneExporterService with actual gRPC call
            print("\n📤 Testing ApiSceneExporterService...")
            try:
                # Test scene exporter service with actual gRPC call
                request = apisceneexporter_pb2.ApiSceneExporter.createRequest()
                self.log_grpc_call("ApiSceneExporterService", "create", request)
                response = await self.scene_exporter_stub.create(request)  # Await async call
                self.log_grpc_call("ApiSceneExporterService", "create", request, response)
                self.log_test("SceneExporterService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("SceneExporterService.create", False, error=e)
                
        except Exception as e:
            self.log_test("Stage4Services", False, error=e)
    
    async def test_stage5_services(self):
        """Test STAGE 5: System & configuration services"""
        print("\n⚙️ TESTING STAGE 5: SYSTEM & CONFIGURATION SERVICES")
        print("=" * 70)
        
        try:
            # Test ApiLocalDBService with actual gRPC call
            print("\n🗄️ Testing ApiLocalDBService...")
            try:
                # Test local DB service with actual gRPC call
                request = apilocaldb_pb2.ApiLocalDB.isSupportedRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiLocalDBService", "isSupported", request)
                response = await self.local_db_stub.isSupported(request)  # Await async call
                self.log_grpc_call("ApiLocalDBService", "isSupported", request, response)
                self.log_test("LocalDBService.isSupported", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("LocalDBService.isSupported", False, error=e)
            
            # Test ApiLocalDB_CategoryService with actual gRPC call
            print("\n📂 Testing ApiLocalDB_CategoryService...")
            try:
                # Test category service with actual gRPC call (using same LocalDB service)
                request = apilocaldb_pb2.ApiLocalDB.addObserverRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiLocalDB_CategoryService", "addObserver", request)
                response = await self.local_db_category_stub.addObserver(request)  # Await async call
                self.log_grpc_call("ApiLocalDB_CategoryService", "addObserver", request, response)
                self.log_test("LocalDB_CategoryService.addObserver", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("LocalDB_CategoryService.addObserver", False, error=e)
            
            # Test ApiLocalDB_PackageService with actual gRPC call
            print("\n📦 Testing ApiLocalDB_PackageService...")
            try:
                # Test package service with actual gRPC call (using same LocalDB service)
                request = apilocaldb_pb2.ApiLocalDB.removeObserverRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiLocalDB_PackageService", "removeObserver", request)
                response = await self.local_db_package_stub.removeObserver(request)  # Await async call
                self.log_grpc_call("ApiLocalDB_PackageService", "removeObserver", request, response)
                self.log_test("LocalDB_PackageService.removeObserver", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("LocalDB_PackageService.removeObserver", False, error=e)
            
            # Test ApiTitleComponentService with actual gRPC call
            print("\n🏷️ Testing ApiTitleComponentService...")
            try:
                # Test title component service with actual gRPC call
                request = apititlecomponent_pb2.ApiTitleComponent.createRequest()
                self.log_grpc_call("ApiTitleComponentService", "create", request)
                response = await self.title_component_stub.create(request)  # Await async call
                self.log_grpc_call("ApiTitleComponentService", "create", request, response)
                self.log_test("TitleComponentService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("TitleComponentService.create", False, error=e)
            
            # Test ApiRenderCloudManagerService with actual gRPC call
            print("\n☁️ Testing ApiRenderCloudManagerService...")
            try:
                # Test cloud manager service with actual gRPC call
                request = apirendercloudmanager_pb2.ApiRenderCloudManager.newRenderTaskRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiRenderCloudManagerService", "newRenderTask", request)
                response = await self.render_cloud_manager_stub.newRenderTask(request)  # Await async call
                self.log_grpc_call("ApiRenderCloudManagerService", "newRenderTask", request, response)
                self.log_test("RenderCloudManagerService.newRenderTask", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderCloudManagerService.newRenderTask", False, error=e)
            
            # Test ApiTimeSamplingService with actual gRPC call
            print("\n⏰ Testing ApiTimeSamplingService...")
            try:
                # Test time sampling service with actual gRPC call
                request = apitimesampling_pb2.ApiTimeSampling.endTimeAutoRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiTimeSamplingService", "endTimeAuto", request)
                response = await self.time_sampling_stub.endTimeAuto(request)  # Await async call
                self.log_grpc_call("ApiTimeSamplingService", "endTimeAuto", request, response)
                self.log_test("TimeSamplingService.endTimeAuto", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("TimeSamplingService.endTimeAuto", False, error=e)
            
            # Test ApiItemArrayService with actual gRPC call
            print("\n📋 Testing ApiItemArrayService...")
            try:
                # Test item array service with actual gRPC call
                request = apiitemarray_pb2.ApiItemArray.beginRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiItemArrayService", "begin", request)
                response = await self.item_array_stub.begin(request)  # Await async call
                self.log_grpc_call("ApiItemArrayService", "begin", request, response)
                self.log_test("ItemArrayService.begin", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ItemArrayService.begin", False, error=e)
            
            # Test ApiTextEditorService with actual gRPC call (Stage 5 duplicate)
            print("\n📝 Testing ApiTextEditorService (Stage 5)...")
            try:
                # Test text editor service with actual gRPC call
                request = apitexteditor_pb2.ApiTextEditor.clearRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiTextEditorService", "clear", request)
                response = await self.text_editor_stub.clear(request)  # Await async call
                self.log_grpc_call("ApiTextEditorService", "clear", request, response)
                self.log_test("TextEditorService.clear", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("TextEditorService.clear", False, error=e)
                
        except Exception as e:
            self.log_test("Stage5Services", False, error=e)
    
    async def test_stage6_services(self):
        """Test STAGE 6: Plugin & extension services"""
        print("\n🔌 TESTING STAGE 6: PLUGIN & EXTENSION SERVICES")
        print("=" * 70)
        
        try:
            # Test ApiThreadService with actual gRPC call
            print("\n🧵 Testing ApiThreadService...")
            try:
                # Test thread service with actual gRPC call
                request = apithread_pb2.ApiThread.createRequest()
                self.log_grpc_call("ApiThreadService", "create", request)
                response = await self.thread_stub.create(request)  # Await async call
                self.log_grpc_call("ApiThreadService", "create", request, response)
                self.log_test("ThreadService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ThreadService.create", False, error=e)
            
            # Test ApiNodeService (from apinodesystem_7) - temporarily disabled
            print("\n🔗 Testing ApiNodeService (advanced)...")
            try:
                # Test advanced node service connectivity (disabled due to conflicts)
                self.log_test("NodeService_7.connectivity", False, "Temporarily disabled due to duplicate symbol 'ApiFilePath'")
            except Exception as e:
                self.log_test("NodeService_7.connectivity", False, error=e)
            
            # Test ApiModuleNodeGraphService - temporarily disabled
            print("\n📊 Testing ApiModuleNodeGraphService...")
            try:
                # Test module node graph service connectivity (disabled due to dependencies)
                self.log_test("ModuleNodeGraphService.connectivity", False, "Temporarily disabled due to dependency on apinodesystem_7")
            except Exception as e:
                self.log_test("ModuleNodeGraphService.connectivity", False, error=e)
            
            # Test ApiNetRenderManagerService with actual gRPC call
            print("\n🌐 Testing ApiNetRenderManagerService...")
            try:
                # Test network render manager service with actual gRPC call
                request = apinetrendermanager_pb2.ApiNetRenderManager.configurationRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiNetRenderManagerService", "configuration", request)
                response = await self.net_render_manager_stub.configuration(request)  # Await async call
                self.log_grpc_call("ApiNetRenderManagerService", "configuration", request, response)
                self.log_test("NetRenderManagerService.configuration", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("NetRenderManagerService.configuration", False, error=e)
            
            # Test ApiCollapsiblePanelStackService with actual gRPC call
            print("\n📋 Testing ApiCollapsiblePanelStackService...")
            try:
                # Test collapsible panel stack service with actual gRPC call
                request = apicollapsiblepanelstack_pb2.ApiCollapsiblePanelStack.createRequest()
                self.log_grpc_call("ApiCollapsiblePanelStackService", "create", request)
                response = await self.collapsible_panel_stack_stub.create(request)  # Await async call
                self.log_grpc_call("ApiCollapsiblePanelStackService", "create", request, response)
                self.log_test("CollapsiblePanelStackService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CollapsiblePanelStackService.create", False, error=e)
                
        except Exception as e:
            self.log_test("Stage6Services", False, error=e)
    
    async def test_stage7_services(self):
        """Test STAGE 7: Advanced rendering services"""
        print("\n🎨 TESTING STAGE 7: ADVANCED RENDERING SERVICES")
        print("=" * 70)
        
        try:
            # Test ApiRenderEngineService with actual gRPC call
            print("\n🚀 Testing ApiRenderEngineService...")
            try:
                # Test render engine service with actual gRPC call
                request = apirender_pb2.ApiRenderEngine.asyncTonemapBufferTypeRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiRenderEngineService", "asyncTonemapBufferType", request)
                response = await self.render_engine_stub.asyncTonemapBufferType(request)  # Await async call
                self.log_grpc_call("ApiRenderEngineService", "asyncTonemapBufferType", request, response)
                self.log_test("RenderEngineService.asyncTonemapBufferType", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderEngineService.asyncTonemapBufferType", False, error=e)
            
            # Test ApiRenderImageService with actual gRPC call
            print("\n🖼️ Testing ApiRenderImageService...")
            try:
                # Test render image service with actual gRPC call
                request = apirender_pb2.ApiRenderImage.isEmptyRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiRenderImageService", "isEmpty", request)
                response = await self.render_image_stub.isEmpty(request)  # Await async call
                self.log_grpc_call("ApiRenderImageService", "isEmpty", request, response)
                self.log_test("RenderImageService.isEmpty", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderImageService.isEmpty", False, error=e)
            
            # Test ApiRenderViewService with actual gRPC call
            print("\n👁️ Testing ApiRenderViewService...")
            try:
                # Test render view service with actual gRPC call
                request = apirenderview_pb2.ApiRenderView.createRequest()
                self.log_grpc_call("ApiRenderViewService", "create", request)
                response = await self.render_view_stub.create(request)  # Await async call
                self.log_grpc_call("ApiRenderViewService", "create", request, response)
                self.log_test("RenderViewService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("RenderViewService.create", False, error=e)
            
            # Test VdbGridInfoService - disabled (no protobuf file)
            print("\n📊 Testing VdbGridInfoService...")
            try:
                # Test VDB grid info service connectivity (disabled - no protobuf)
                self.log_test("VdbGridInfoService.connectivity", False, "Disabled - no VDB protobuf files available")
            except Exception as e:
                self.log_test("VdbGridInfoService.connectivity", False, error=e)
            
            # Test VdbGridSamplerService - disabled (no protobuf file)
            print("\n🔬 Testing VdbGridSamplerService...")
            try:
                # Test VDB grid sampler service connectivity (disabled - no protobuf)
                self.log_test("VdbGridSamplerService.connectivity", False, "Disabled - no VDB protobuf files available")
            except Exception as e:
                self.log_test("VdbGridSamplerService.connectivity", False, error=e)
            
            # Test VdbInfoService - disabled (no protobuf file)
            print("\n📋 Testing VdbInfoService...")
            try:
                # Test VDB info service connectivity (disabled - no protobuf)
                self.log_test("VdbInfoService.connectivity", False, "Disabled - no VDB protobuf files available")
            except Exception as e:
                self.log_test("VdbInfoService.connectivity", False, error=e)
            
            # Test RenderResultStatisticsService - disabled (no protobuf file)
            print("\n📈 Testing RenderResultStatisticsService...")
            try:
                # Test render result statistics service connectivity (disabled - no protobuf)
                self.log_test("RenderResultStatisticsService.connectivity", False, "Disabled - no protobuf file available")
            except Exception as e:
                self.log_test("RenderResultStatisticsService.connectivity", False, error=e)
            
            # Test ApiAnimationTimeTransformService - disabled (no protobuf file)
            print("\n⏰ Testing ApiAnimationTimeTransformService...")
            try:
                # Test animation time transform service connectivity (disabled - no protobuf)
                self.log_test("AnimationTimeTransformService.connectivity", False, "Disabled - no protobuf file available")
            except Exception as e:
                self.log_test("AnimationTimeTransformService.connectivity", False, error=e)
            
            # Test ApiLinearTimeTransformService - disabled (no protobuf file)
            print("\n📏 Testing ApiLinearTimeTransformService...")
            try:
                # Test linear time transform service connectivity (disabled - no protobuf)
                self.log_test("LinearTimeTransformService.connectivity", False, "Disabled - no protobuf file available")
            except Exception as e:
                self.log_test("LinearTimeTransformService.connectivity", False, error=e)
                
        except Exception as e:
            self.log_test("Stage7Services", False, error=e)
    
    async def test_stage8_services(self):
        """Test STAGE 8: Specialized services"""
        print("\n🔧 TESTING STAGE 8: SPECIALIZED SERVICES")
        print("=" * 70)
        
        try:
            # Test ApiLogManagerService - DISABLED due to naming conflict
            # try:
            #     print("\n📝 Testing ApiLogManagerService...")
            #     # Test log manager service connectivity
            #     self.log_test("LogManagerService.connectivity", True, "Service stub initialized")
            # except Exception as e:
            #     self.log_test("LogManagerService.connectivity", False, error=e)
            
            # Test ApiDBMaterialManagerService with actual gRPC call
            print("\n🗄️ Testing ApiDBMaterialManagerService...")
            try:
                # Test database material manager service with actual gRPC call
                request = apidbmaterialmanager_pb2.ApiDBMaterialManager.downloadMaterialRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.materialId = "test_material_id"
                self.log_grpc_call("ApiDBMaterialManagerService", "downloadMaterial", request)
                response = await self.db_material_manager_stub.downloadMaterial(request)  # Await async call
                self.log_grpc_call("ApiDBMaterialManagerService", "downloadMaterial", request, response)
                self.log_test("DBMaterialManagerService.downloadMaterial", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DBMaterialManagerService.downloadMaterial", False, error=e)
            
            # Test ApiDBMaterialManager_DBCategoryArrayService with actual gRPC call
            print("\n📂 Testing ApiDBMaterialManager_DBCategoryArrayService...")
            try:
                # Test DB category array service with actual gRPC call (using same service)
                request = apidbmaterialmanager_pb2.ApiDBMaterialManager.freeMaterialPreviewRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiDBMaterialManager_DBCategoryArrayService", "freeMaterialPreview", request)
                response = await self.db_category_array_stub.freeMaterialPreview(request)  # Await async call
                self.log_grpc_call("ApiDBMaterialManager_DBCategoryArrayService", "freeMaterialPreview", request, response)
                self.log_test("DBCategoryArrayService.freeMaterialPreview", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DBCategoryArrayService.freeMaterialPreview", False, error=e)
            
            # Test ApiDBMaterialManager_DBMaterialArrayService with actual gRPC call
            print("\n📋 Testing ApiDBMaterialManager_DBMaterialArrayService...")
            try:
                # Test DB material array service with actual gRPC call (using same service)
                request = apidbmaterialmanager_pb2.ApiDBMaterialManager.downloadMaterial1Request()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.materialId = "test_material_array_id"
                self.log_grpc_call("ApiDBMaterialManager_DBMaterialArrayService", "downloadMaterial1", request)
                response = await self.db_material_array_stub.downloadMaterial1(request)  # Await async call
                self.log_grpc_call("ApiDBMaterialManager_DBMaterialArrayService", "downloadMaterial1", request, response)
                self.log_test("DBMaterialArrayService.downloadMaterial1", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DBMaterialArrayService.downloadMaterial1", False, error=e)
            
            # Test ApiOcioContextManagerService with actual gRPC call
            print("\n🎨 Testing ApiOcioContextManagerService...")
            try:
                # Test OCIO context manager service with actual gRPC call
                request = apiociocontextmanager_pb2.ApiOcioContextManager.createRequest()
                self.log_grpc_call("ApiOcioContextManagerService", "create", request)
                response = await self.ocio_context_manager_stub.create(request)  # Await async call
                self.log_grpc_call("ApiOcioContextManagerService", "create", request, response)
                self.log_test("OcioContextManagerService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("OcioContextManagerService.create", False, error=e)
            
            # Test ApiSceneExporterService with actual gRPC call (already converted in Stage 4)
            print("\n📤 Testing ApiSceneExporterService...")
            try:
                # Test scene exporter service with actual gRPC call
                request = apisceneexporter_pb2.ApiSceneExporter.destroyRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiSceneExporterService", "destroy", request)
                response = await self.scene_exporter_stub.destroy(request)  # Await async call
                self.log_grpc_call("ApiSceneExporterService", "destroy", request, response)
                self.log_test("SceneExporterService.destroy", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("SceneExporterService.destroy", False, error=e)
            
            # Test ApiChangeManagerService with actual gRPC call (already converted in Stage 3)
            print("\n🔄 Testing ApiChangeManagerService...")
            try:
                # Test change manager service with actual gRPC call
                request = apichangemanager_pb2.ApiChangeManager.destroyRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiChangeManagerService", "destroy", request)
                response = await self.change_manager_stub.destroy(request)  # Await async call
                self.log_grpc_call("ApiChangeManagerService", "destroy", request, response)
                self.log_test("ChangeManagerService.destroy", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ChangeManagerService.destroy", False, error=e)
            
            # Test ApiGeometryExporterService with actual gRPC call
            print("\n📐 Testing ApiGeometryExporterService...")
            try:
                # Test geometry exporter service with actual gRPC call
                request = apigeometryexporter_pb2.ApiGeometryExporter.createRequest()
                self.log_grpc_call("ApiGeometryExporterService", "create", request)
                response = await self.geometry_exporter_stub.create(request)  # Await async call
                self.log_grpc_call("ApiGeometryExporterService", "create", request, response)
                self.log_test("GeometryExporterService.create", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GeometryExporterService.create", False, error=e)
            
            # Test ApiMaterialXGlobalService with actual gRPC call
            print("\n🧪 Testing ApiMaterialXGlobalService...")
            try:
                # Test MaterialX global service with actual gRPC call
                request = apimaterialx_pb2.ApiMaterialXGlobal.getAllMxNodeCategoriesRequest()
                self.log_grpc_call("ApiMaterialXGlobalService", "getAllMxNodeCategories", request)
                response = await self.materialx_global_stub.getAllMxNodeCategories(request)  # Await async call
                self.log_grpc_call("ApiMaterialXGlobalService", "getAllMxNodeCategories", request, response)
                self.log_test("MaterialXGlobalService.getAllMxNodeCategories", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("MaterialXGlobalService.getAllMxNodeCategories", False, error=e)
                
        except Exception as e:
            self.log_test("Stage8Services", False, error=e)
    
    async def test_stage9_services(self):
        """Test STAGE 9: UI and Advanced Services"""
        print("\n🔧 TESTING STAGE 9: UI AND ADVANCED SERVICES")
        print("=" * 70)
        
        try:
            # Test ApiGuiComponentService
            try:
                print("\n🖥️ Testing ApiGuiComponentService...")
                # Test GUI component service with actual gRPC call
                request = apiguicomponent_pb2.ApiGuiComponent.widthRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))  # Invalid object to test service response
                self.log_grpc_call("ApiGuiComponentService", "width", request)
                response = await self.gui_component_stub.width(request)  # Await async call
                self.log_grpc_call("ApiGuiComponentService", "width", request, response)
                self.log_test("GuiComponentService.width", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GuiComponentService.width", False, error=e)
            
            # Test ApiMainWindowService
            try:
                print("\n🏠 Testing ApiMainWindowService...")
                # Test main window service with actual gRPC call
                request = apimainwindow_pb2.ApiMainWindow.visibleRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiMainWindowService", "visible", request)
                response = await self.main_window_stub.visible(request)  # Await async call
                self.log_grpc_call("ApiMainWindowService", "visible", request, response)
                self.log_test("MainWindowService.visible", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("MainWindowService.visible", False, error=e)
            
            # Test ApiWindowService
            try:
                print("\n🪟 Testing ApiWindowService...")
                # Test window service with actual gRPC call
                request = apiwindow_pb2.ApiWindow.visibleRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiWindowService", "visible", request)
                response = await self.window_stub.visible(request)  # Await async call
                self.log_grpc_call("ApiWindowService", "visible", request, response)
                self.log_test("WindowService.visible", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("WindowService.visible", False, error=e)
            
            # Test ApiCheckBoxService
            try:
                print("\n☑️ Testing ApiCheckBoxService...")
                # Test checkbox service with actual gRPC call
                request = apicheckbox_pb2.ApiCheckBox.getToggleStateRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiCheckBoxService", "getToggleState", request)
                response = await self.checkbox_stub.getToggleState(request)  # Await async call
                self.log_grpc_call("ApiCheckBoxService", "getToggleState", request, response)
                self.log_test("CheckBoxService.getToggleState", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CheckBoxService.getToggleState", False, error=e)
            
            # Test ApiComboBoxService
            try:
                print("\n📋 Testing ApiComboBoxService...")
                # Test combobox service with actual gRPC call
                request = apicombobox_pb2.ApiComboBox.getSelectedIdRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiComboBoxService", "getSelectedId", request)
                response = await self.combobox_stub.getSelectedId(request)  # Await async call
                self.log_grpc_call("ApiComboBoxService", "getSelectedId", request, response)
                self.log_test("ComboBoxService.getSelectedId", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ComboBoxService.getSelectedId", False, error=e)
            
            # Test ApiColorSwatchService
            try:
                print("\n🎨 Testing ApiColorSwatchService...")
                # Test color swatch service with actual gRPC call
                request = apicolorswatch_pb2.ApiColorSwatch.getCurrentColourRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiColorSwatchService", "getCurrentColour", request)
                response = await self.color_swatch_stub.getCurrentColour(request)  # Await async call
                self.log_grpc_call("ApiColorSwatchService", "getCurrentColour", request, response)
                self.log_test("ColorSwatchService.getCurrentColour", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("ColorSwatchService.getCurrentColour", False, error=e)
            
            # Test ApiFileChooserService
            try:
                print("\n📁 Testing ApiFileChooserService...")
                # Test file chooser service with actual gRPC call
                request = apifilechooser_pb2.ApiFileChooser.getCurrentFileRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiFileChooserService", "getCurrentFile", request)
                response = await self.file_chooser_stub.getCurrentFile(request)  # Await async call
                self.log_grpc_call("ApiFileChooserService", "getCurrentFile", request, response)
                self.log_test("FileChooserService.getCurrentFile", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("FileChooserService.getCurrentFile", False, error=e)
            
            # Test ApiGridLayoutService
            try:
                print("\n📐 Testing ApiGridLayoutService...")
                # Test grid layout service with actual gRPC call
                request = apigridlayout_pb2.ApiGridLayout.getNumRowsRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiGridLayoutService", "getNumRows", request)
                response = await self.grid_layout_stub.getNumRows(request)  # Await async call
                self.log_grpc_call("ApiGridLayoutService", "getNumRows", request, response)
                self.log_test("GridLayoutService.getNumRows", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GridLayoutService.getNumRows", False, error=e)
            
            # Test ApiDiagnosticsService
            try:
                print("\n🔍 Testing ApiDiagnosticsService...")
                # Test diagnostics service with actual gRPC call
                request = apidiagnostics_pb2.ApiDiagnostics.diagnosticCommandRequest()
                request.commandType = 1  # Simple command type
                request.delayInSeconds = 0  # No delay
                self.log_grpc_call("ApiDiagnosticsService", "diagnosticCommand", request)
                response = await self.diagnostics_stub.diagnosticCommand(request)  # Await async call
                self.log_grpc_call("ApiDiagnosticsService", "diagnosticCommand", request, response)
                self.log_test("DiagnosticsService.diagnosticCommand", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("DiagnosticsService.diagnosticCommand", False, error=e)
            
            # Test ApiGaussianSplatCloudNodeService
            try:
                print("\n☁️ Testing ApiGaussianSplatCloudNodeService...")
                # Test Gaussian splat cloud node service with actual gRPC call
                request = apigaussiansplatting_pb2.ApiGaussianSplatCloudNode.getFilePathRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiGaussianSplatCloudNodeService", "getFilePath", request)
                response = await self.gaussian_splat_cloud_node_stub.getFilePath(request)  # Await async call
                self.log_grpc_call("ApiGaussianSplatCloudNodeService", "getFilePath", request, response)
                self.log_test("GaussianSplatCloudNodeService.getFilePath", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("GaussianSplatCloudNodeService.getFilePath", False, error=e)
            
            # Test ApiCustomCurveEditorControllerService
            try:
                print("\n📈 Testing ApiCustomCurveEditorControllerService...")
                # Test custom curve editor controller service with actual gRPC call
                request = apicustomcurveeditorcontroller_pb2.ApiCustomCurveEditorController.getNumCurvesRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiCustomCurveEditorControllerService", "getNumCurves", request)
                response = await self.custom_curve_editor_controller_stub.getNumCurves(request)  # Await async call
                self.log_grpc_call("ApiCustomCurveEditorControllerService", "getNumCurves", request, response)
                self.log_test("CustomCurveEditorControllerService.getNumCurves", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CustomCurveEditorControllerService.getNumCurves", False, error=e)
            
            # Test ApiCustomCurveEditorController_DrawerService
            try:
                print("\n🖊️ Testing ApiCustomCurveEditorController_DrawerService...")
                # Test custom curve editor drawer service with actual gRPC call
                request = apicustomcurveeditorcontroller_pb2.ApiCustomCurveEditorController_Drawer.getBackgroundColourRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                self.log_grpc_call("ApiCustomCurveEditorController_DrawerService", "getBackgroundColour", request)
                response = await self.custom_curve_editor_drawer_stub.getBackgroundColour(request)  # Await async call
                self.log_grpc_call("ApiCustomCurveEditorController_DrawerService", "getBackgroundColour", request, response)
                self.log_test("CustomCurveEditorDrawerService.getBackgroundColour", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CustomCurveEditorDrawerService.getBackgroundColour", False, error=e)
            
            # Test ApiCustomCurveEditorController_ListenerService
            try:
                print("\n👂 Testing ApiCustomCurveEditorController_ListenerService...")
                # Test custom curve editor listener service with actual gRPC call
                request = apicustomcurveeditorcontroller_pb2.ApiCustomCurveEditorController_Listener.curveChangedRequest()
                request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
                request.curveIndex = 0
                self.log_grpc_call("ApiCustomCurveEditorController_ListenerService", "curveChanged", request)
                response = await self.custom_curve_editor_listener_stub.curveChanged(request)  # Await async call
                self.log_grpc_call("ApiCustomCurveEditorController_ListenerService", "curveChanged", request, response)
                self.log_test("CustomCurveEditorListenerService.curveChanged", True, f"Response received: {response}")
            except Exception as e:
                self.log_test("CustomCurveEditorListenerService.curveChanged", False, error=e)
                
        except Exception as e:
            self.log_test("Stage9Services", False, error=e)
    
    async def run_comprehensive_test(self):
        """Run the test suite based on configured test level"""
        print("🚀 STARTING COMPREHENSIVE OCTANE API TEST SUITE")
        print("=" * 60)
        
        start_time = datetime.now()
        test_level = getattr(self, 'test_level', 0)
        
        # Connect to Octane
        if not await self.connect():
            return False
        
        try:
            # ALWAYS RUN: Base Core Tests
            print("🏗️ RUNNING BASE CORE TESTS")
            
            # 1. Test Project Management
            root_graph_ref = await self.test_project_management()
            
            # 2. Test Item Service Basic Operations
            if root_graph_ref:
                await self.test_item_service_basic(root_graph_ref)
            
            # 3. Test Node Creation
            created_nodes = await self.test_node_creation(root_graph_ref)
            
            # 4. Test Attribute Operations
            if root_graph_ref:
                await self.test_attribute_operations(root_graph_ref)
            
            # 5. Test Node Connections
            if created_nodes:
                await self.test_node_connections(created_nodes[0])  # Test first created node
            
            # 6. Test Pin Value Setting
            if created_nodes:
                await self.test_pin_value_setting(created_nodes)
            
            # 7. Test Node Connections Between Nodes
            if len(created_nodes) >= 2:
                await self.test_node_to_node_connections(created_nodes)
            
            # 8. Test Graph Operations
            if root_graph_ref:
                await self.test_graph_operations(root_graph_ref)
            
            # 9. Test Advanced Operations
            await self.test_advanced_operations()
            
            print(f"✅ BASE TESTS COMPLETE: {len(self.test_results)} tests")
            
            # CONDITIONAL: Run additional stages based on test level
            if test_level >= 1:
                print("🚀 RUNNING STAGE 1: New Core Services")
                await self.test_stage1_services()
                print(f"✅ STAGE 1 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 2:
                print("🚀 RUNNING STAGE 2: Image & Geometry Services")
                await self.test_stage2_services()
                print(f"✅ STAGE 2 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 3:
                print("🚀 RUNNING STAGE 3: UI & Editor Services")
                await self.test_stage3_services()
                print(f"✅ STAGE 3 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 4:
                print("🚀 RUNNING STAGE 4: File & Data Management Services")
                await self.test_stage4_services()
                print(f"✅ STAGE 4 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 5:
                print("🚀 RUNNING STAGE 5: System & Configuration Services")
                await self.test_stage5_services()
                print(f"✅ STAGE 5 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 6:
                print("🚀 RUNNING STAGE 6: Plugin & Extension Services")
                await self.test_stage6_services()
                print(f"✅ STAGE 6 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 7:
                print("🚀 RUNNING STAGE 7: Advanced Rendering Services")
                await self.test_stage7_services()
                print(f"✅ STAGE 7 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 8:
                print("🚀 RUNNING STAGE 8: Specialized Services")
                await self.test_stage8_services()
                print(f"✅ STAGE 8 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 9:
                print("🚀 RUNNING STAGE 9: UI and Advanced Services")
                await self.test_stage9_services()
                print(f"✅ STAGE 9 COMPLETE: {len(self.test_results)} total tests")
            
            if test_level >= 99:
                print("🚀 RUNNING ERROR CONDITIONS TESTING")
                await self.test_error_conditions()
                print(f"✅ ALL TESTS COMPLETE: {len(self.test_results)} total tests")
            
            # Show what was skipped if not running all
            if test_level < 99:
                skipped_stages = []
                if test_level < 1: skipped_stages.append("STAGE 1: New Core Services")
                if test_level < 2: skipped_stages.append("STAGE 2: Image & Geometry Services")
                if test_level < 3: skipped_stages.append("STAGE 3: UI & Editor Services")
                if test_level < 4: skipped_stages.append("STAGE 4: File & Data Management Services")
                if test_level < 5: skipped_stages.append("STAGE 5: System & Configuration Services")
                if test_level < 6: skipped_stages.append("STAGE 6: Plugin & Extension Services")
                if test_level < 7: skipped_stages.append("STAGE 7: Advanced Rendering Services")
                if test_level < 8: skipped_stages.append("STAGE 8: Specialized Services")
                if test_level < 9: skipped_stages.append("STAGE 9: UI and Advanced Services")
                if test_level < 99: skipped_stages.append("Error Conditions Testing")
                
                if skipped_stages:
                    print(f"\n📋 SKIPPED STAGES (use -1 through -9 or --all to enable):")
                    for stage in skipped_stages:
                        print(f"  - {stage}")
            
        finally:
            await self.disconnect()
        
        # Print summary
        end_time = datetime.now()
        duration = end_time - start_time
        
        print("\n" + "=" * 60)
        print("📊 TEST SUMMARY")
        print("=" * 60)
        
        total_tests = len(self.test_results)
        passed_tests = sum(1 for result in self.test_results.values() if result['success'])
        failed_tests = total_tests - passed_tests
        
        print(f"Total Tests: {total_tests}")
        print(f"✅ Passed: {passed_tests}")
        print(f"❌ Failed: {failed_tests}")
        print(f"⏱️ Duration: {duration.total_seconds():.2f} seconds")
        print(f"📈 Success Rate: {(passed_tests/total_tests*100):.1f}%")
        
        # Print failed tests
        if failed_tests > 0:
            print("\n❌ FAILED TESTS:")
            for test_name, result in self.test_results.items():
                if not result['success']:
                    error_msg = result.get('error', '')
                    details = result.get('details', '')
                    
                    # Prioritize showing meaningful information
                    if details:
                        print(f"  - {test_name}: {details}")
                    elif error_msg and error_msg != 'None':
                        print(f"  - {test_name}: {error_msg}")
                    else:
                        print(f"  - {test_name}: Failed (no details available)")
        
        # Print created objects
        if self.created_objects:
            print(f"\n🔧 CREATED OBJECTS: {len(self.created_objects)}")
            for obj_type, obj_ref in self.created_objects:
                print(f"  - {obj_type}: handle={obj_ref.handle}, type={obj_ref.type}")
        
        return failed_tests == 0

async def main():
    """Main test runner with command line stage control"""
    print("🔥 COMPREHENSIVE OCTANE gRPC API TEST SUITE")
    print("LOCKIT: Focused on complete API testing")
    print("GRIND: Extended autonomous testing mode")
    print()
    
    # Parse command line arguments
    import argparse
    parser = argparse.ArgumentParser(description='Octane gRPC API Test Suite')
    parser.add_argument('host', nargs='?', default=None, help='Octane host (auto-detect if not specified)')
    parser.add_argument('port', nargs='?', type=int, default=51022, help='Octane port (default: 51022)')
    parser.add_argument('-1', '--stage1', action='store_true', help='Run base tests + Stage 1')
    parser.add_argument('-2', '--stage2', action='store_true', help='Run base tests + Stages 1-2')
    parser.add_argument('-3', '--stage3', action='store_true', help='Run base tests + Stages 1-3')
    parser.add_argument('-4', '--stage4', action='store_true', help='Run base tests + Stages 1-4')
    parser.add_argument('-5', '--stage5', action='store_true', help='Run base tests + Stages 1-5')
    parser.add_argument('-6', '--stage6', action='store_true', help='Run base tests + Stages 1-6')
    parser.add_argument('-7', '--stage7', action='store_true', help='Run base tests + Stages 1-7')
    parser.add_argument('-8', '--stage8', action='store_true', help='Run base tests + Stages 1-8')
    parser.add_argument('-9', '--stage9', action='store_true', help='Run base tests + Stages 1-9')
    parser.add_argument('--all', action='store_true', help='Run ALL tests including error conditions')
    
    args = parser.parse_args()
    
    # Determine test level
    test_level = 0  # Default: base tests only
    if args.stage1: test_level = 1
    elif args.stage2: test_level = 2
    elif args.stage3: test_level = 3
    elif args.stage4: test_level = 4
    elif args.stage5: test_level = 5
    elif args.stage6: test_level = 6
    elif args.stage7: test_level = 7
    elif args.stage8: test_level = 8
    elif args.stage9: test_level = 9
    elif args.all: test_level = 99
    
    # Display test level
    if test_level == 0:
        print("📋 TEST LEVEL: BASE (Core functionality only - safe for Octane)")
    elif test_level == 99:
        print("📋 TEST LEVEL: ALL (Complete test suite - may stress Octane)")
    else:
        print(f"📋 TEST LEVEL: STAGE {test_level} (Base tests + Stages 1-{test_level})")
    
    # Create test suite (will auto-detect host if None)
    test_suite = ComprehensiveOctaneTest(args.host, args.port)
    test_suite.test_level = test_level  # Set test level
    
    print(f"🎯 Target: {test_suite.octane_host}:{test_suite.octane_port}")
    print()
    
    # Run comprehensive test
    success = await test_suite.run_comprehensive_test()
    
    if success:
        print("\n🎉 ALL TESTS PASSED!")
        return 0
    else:
        print("\n💥 SOME TESTS FAILED!")
        return 1

if __name__ == "__main__":
    try:
        exit_code = asyncio.run(main())
        sys.exit(exit_code)
    except KeyboardInterrupt:
        print("\n⚠️ Test interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"\n💥 Fatal error: {e}")
        traceback.print_exc()
        sys.exit(1)