// Test if service name exists in ObjectType
const ObjectType = {
  ApiFileName: 0,
  ApiGeometryExporter: 1,
  ApiItem: 16,
  ApiNode: 17,
  ApiRootNodeGraph: 18,
  ApiNodeGraph: 20,
  ApiItemArray: 31
}

console.log("Testing service in ObjectType:");
console.log("'ApiItem' in ObjectType:", 'ApiItem' in ObjectType);
console.log("ObjectType['ApiItem']:", ObjectType['ApiItem']);
console.log("(ObjectType as any)['ApiItem']:", ObjectType['ApiItem']);

const service = 'ApiItem';
console.log(`'${service}' in ObjectType:`, service in ObjectType);
console.log(`ObjectType[service]:`, ObjectType[service]);
