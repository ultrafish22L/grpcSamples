#!/usr/bin/env python3
"""
🚨 CRASH DEBUGGING: Stage 2 Service Isolation Test
BUGIT: Systematic debugging to isolate which Stage 2 service crashes Octane
"""

import asyncio
import sys
import os
import grpc
from datetime import datetime

# Add proxy directory to path for protobuf imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'proxy'))

# Import all Stage 2 protobuf files
try:
    import apiimage_pb2_grpc, apiimage_pb2
    import apiimagebuffer_pb2_grpc, apiimagebuffer_pb2
    import apiimagecomponent_pb2_grpc, apiimagecomponent_pb2
    import apiimageinfo_pb2_grpc, apiimageinfo_pb2
    import apigeometryexporter_pb2_grpc, apigeometryexporter_pb2
    import apidbmaterialmanager_pb2_grpc, apidbmaterialmanager_pb2
    import apimaterialx_pb2_grpc, apimaterialx_pb2
    import apitimesampling_pb2_grpc, apitimesampling_pb2
    import common_pb2
    import apiprojectmanager_pb2_grpc, apiprojectmanager_pb2
except ImportError as e:
    print(f"❌ Import error: {e}")
    sys.exit(1)

class Stage2CrashDebugger:
    def __init__(self, host="host.docker.internal", port=51022):
        self.host = host
        self.port = port
        self.channel = None
        self.test_results = []
        
    async def connect(self):
        """Connect to Octane"""
        try:
            self.channel = grpc.aio.insecure_channel(f'{self.host}:{self.port}')
            # Test connection
            await self.channel.channel_ready()
            print(f"✅ Connected to Octane at {self.host}:{self.port}")
            return True
        except Exception as e:
            print(f"❌ Connection failed: {e}")
            return False
    
    async def disconnect(self):
        """Disconnect from Octane"""
        if self.channel:
            await self.channel.close()
            print("🔌 Disconnected from Octane")
    
    def create_object_ptr(self, handle, obj_type):
        """Create object pointer for requests"""
        ptr = common_pb2.ObjectRef()
        ptr.handle = handle
        ptr.type = obj_type
        return ptr
    
    def log_test(self, test_name, success, details="", error=None):
        """Log test result"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        status = "✅ PASS" if success else "❌ FAIL"
        result = {
            'name': test_name,
            'success': success,
            'timestamp': timestamp,
            'details': details,
            'error': str(error) if error else None
        }
        self.test_results.append(result)
        
        if error:
            print(f"[{timestamp}] {status} {test_name}")
            print(f"    ❌ Error: {error}")
        else:
            print(f"[{timestamp}] {status} {test_name}")
            if details:
                print(f"    📝 {details}")
    
    async def test_service_individually(self, service_name, test_func):
        """Test a single service and check if Octane crashes"""
        print(f"\n🔍 TESTING {service_name} INDIVIDUALLY")
        print("=" * 50)
        
        try:
            # Test the service
            await test_func()
            
            # Check if Octane is still responsive
            await asyncio.sleep(1)  # Give Octane time to crash if it's going to
            
            # Try a simple connectivity test
            stub = apiprojectmanager_pb2_grpc.ApiProjectManagerServiceStub(self.channel)
            response = await stub.isValid(apiprojectmanager_pb2.Empty())
            
            print(f"✅ {service_name}: Octane still responsive after test")
            return True
            
        except grpc.aio.AioRpcError as e:
            if "Socket closed" in str(e) or "Connection refused" in str(e):
                print(f"💥 {service_name}: CRASHED OCTANE! Error: {e}")
                return False
            else:
                print(f"⚠️ {service_name}: gRPC error but Octane may be OK: {e}")
                return True
        except Exception as e:
            print(f"❌ {service_name}: Unexpected error: {e}")
            return True
    
    async def test_image_service(self):
        """Test ApiImageService"""
        stub = apiimage_pb2_grpc.ApiImageServiceStub(self.channel)
        request = apiimage_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("ImageService.create", True, f"Response: {response}")
    
    async def test_image_buffer_service(self):
        """Test ApiImageBufferService"""
        stub = apiimagebuffer_pb2_grpc.ApiImageBufferServiceStub(self.channel)
        request = apiimagebuffer_pb2.applyBoxFilterRequest()
        request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
        request.filterSize = 1
        response = await stub.applyBoxFilter(request)
        self.log_test("ImageBufferService.applyBoxFilter", True, f"Response: {response}")
    
    async def test_image_component_service(self):
        """Test ApiImageComponentService"""
        stub = apiimagecomponent_pb2_grpc.ApiImageComponentServiceStub(self.channel)
        request = apiimagecomponent_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("ImageComponentService.create", True, f"Response: {response}")
    
    async def test_image_info_service(self):
        """Test ImageInfoService"""
        stub = apiimageinfo_pb2_grpc.ImageInfoServiceStub(self.channel)
        request = apiimageinfo_pb2.isCompressedRequest()
        request.objectPtr.CopyFrom(self.create_object_ptr(0, 0))
        response = await stub.isCompressed(request)
        self.log_test("ImageInfoService.isCompressed", True, f"Response: {response}")
    
    async def test_geometry_exporter_service(self):
        """Test GeometryExporterService"""
        stub = apigeometryexporter_pb2_grpc.GeometryExporterServiceStub(self.channel)
        request = apigeometryexporter_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("GeometryExporterService.create", True, f"Response: {response}")
    
    async def test_db_material_manager_service(self):
        """Test ApiDbMaterialManagerService"""
        stub = apidbmaterialmanager_pb2_grpc.ApiDbMaterialManagerServiceStub(self.channel)
        request = apidbmaterialmanager_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("DbMaterialManagerService.create", True, f"Response: {response}")
    
    async def test_materialx_service(self):
        """Test ApiMaterialXService"""
        stub = apimaterialx_pb2_grpc.ApiMaterialXServiceStub(self.channel)
        request = apimaterialx_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("MaterialXService.create", True, f"Response: {response}")
    
    async def test_time_sampling_service(self):
        """Test ApiTimeSamplingService"""
        stub = apitimesampling_pb2_grpc.ApiTimeSamplingServiceStub(self.channel)
        request = apitimesampling_pb2.createRequest()
        response = await stub.create(request)
        self.log_test("TimeSamplingService.create", True, f"Response: {response}")
    
    async def run_crash_isolation_test(self):
        """Run systematic crash isolation test"""
        print("🚨 STAGE 2 CRASH ISOLATION TEST")
        print("BUGIT: Testing each service individually to isolate crash culprit")
        print("=" * 60)
        
        if not await self.connect():
            return False
        
        # Define services to test
        services = [
            ("ApiImageService", self.test_image_service),
            ("ApiImageBufferService", self.test_image_buffer_service),
            ("ApiImageComponentService", self.test_image_component_service),
            ("ImageInfoService", self.test_image_info_service),
            ("GeometryExporterService", self.test_geometry_exporter_service),
            ("ApiDbMaterialManagerService", self.test_db_material_manager_service),
            ("ApiMaterialXService", self.test_materialx_service),
            ("ApiTimeSamplingService", self.test_time_sampling_service),
        ]
        
        crash_culprits = []
        
        for service_name, test_func in services:
            # Reconnect if needed
            if not self.channel or self.channel.get_state() != grpc.ChannelConnectivity.READY:
                await self.disconnect()
                if not await self.connect():
                    print(f"❌ Cannot reconnect to test {service_name}")
                    break
            
            # Test the service
            is_stable = await self.test_service_individually(service_name, test_func)
            
            if not is_stable:
                crash_culprits.append(service_name)
                print(f"💥 CRASH CULPRIT IDENTIFIED: {service_name}")
                break  # Stop testing after first crash
        
        await self.disconnect()
        
        # Report results
        print("\n" + "=" * 60)
        print("🔍 CRASH ISOLATION RESULTS")
        print("=" * 60)
        
        if crash_culprits:
            print(f"💥 CRASH CULPRITS FOUND: {len(crash_culprits)}")
            for culprit in crash_culprits:
                print(f"  - {culprit}")
        else:
            print("🤔 NO INDIVIDUAL SERVICE CRASHES DETECTED")
            print("   Crash may be caused by cumulative load or service interaction")
        
        return len(crash_culprits) == 0

async def main():
    """Main crash debugging function"""
    debugger = Stage2CrashDebugger()
    success = await debugger.run_crash_isolation_test()
    return 0 if success else 1

if __name__ == "__main__":
    try:
        exit_code = asyncio.run(main())
        sys.exit(exit_code)
    except KeyboardInterrupt:
        print("\n🛑 Crash debugging interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"💥 Crash debugging failed: {e}")
        sys.exit(1)