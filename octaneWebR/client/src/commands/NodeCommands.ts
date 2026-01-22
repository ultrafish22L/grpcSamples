/**
 * Node Commands
 * Command implementations for node graph operations
 * 
 * NOTE: These commands use the correct proto method signatures:
 * - connectToIx: For connecting pins (and disconnecting with handle=0)
 * - setPinValueByName: For setting parameter values by name
 * 
 * All methods verified against apinodesystem_7.proto
 */

import { Command } from '../services/CommandHistory';
import { OctaneClient } from '../services/OctaneClient';

/**
 * Command to create a node
 */
export class CreateNodeCommand implements Command {
  description: string;
  private client: OctaneClient;
  private nodeType: number;
  private parentGraphId: number;
  private createdNodeId: number | null = null;

  constructor(client: OctaneClient, nodeType: number, parentGraphId: number, nodeTypeName?: string) {
    this.client = client;
    this.nodeType = nodeType;
    this.parentGraphId = parentGraphId;
    this.description = `Create node: ${nodeTypeName || `Type ${nodeType}`}`;
  }

  async execute(): Promise<void> {
    const response = await this.client.callApi('ApiNodeGraph', 'createNode', {
      nodeType: this.nodeType,
      nodeGraphId: this.parentGraphId
    });

    if (response && response.nodeId) {
      this.createdNodeId = response.nodeId;
      console.log(`Created node ID: ${this.createdNodeId}`);
    }
  }

  async undo(): Promise<void> {
    if (this.createdNodeId !== null) {
      await this.client.callApi('ApiNodeGraph', 'deleteNode', {
        nodeId: this.createdNodeId
      });
      console.log(`Deleted node ID: ${this.createdNodeId}`);
      this.createdNodeId = null;
    }
  }
}

/**
 * Command to delete a node
 */
export class DeleteNodeCommand implements Command {
  description: string;
  private client: OctaneClient;
  private nodeId: number;

  constructor(client: OctaneClient, nodeId: number, nodeName?: string) {
    this.client = client;
    this.nodeId = nodeId;
    this.description = `Delete node: ${nodeName || `ID ${nodeId}`}`;
  }

  async execute(): Promise<void> {
    // TODO: Store node data before deletion for proper undo
    // This would require getting node type, parameters, connections, etc.
    await this.client.callApi('ApiNodeGraph', 'deleteNode', {
      nodeId: this.nodeId
    });
    console.log(`Deleted node ID: ${this.nodeId}`);
  }

  async undo(): Promise<void> {
    // TODO: Recreate node with stored data
    console.warn('Undo delete not fully implemented - requires node data serialization');
    // Would need to:
    // 1. Recreate node of same type
    // 2. Restore all parameter values
    // 3. Restore all connections
  }
}

/**
 * Command to connect two pins
 */
export class ConnectPinsCommand implements Command {
  description: string;
  private client: OctaneClient;
  private sourceNodeId: number;
  private sourcePinIndex: number;
  private targetNodeId: number;
  private targetPinIndex: number;

  constructor(
    client: OctaneClient,
    sourceNodeId: number,
    sourcePinIndex: number,
    targetNodeId: number,
    targetPinIndex: number
  ) {
    this.client = client;
    this.sourceNodeId = sourceNodeId;
    this.sourcePinIndex = sourcePinIndex;
    this.targetNodeId = targetNodeId;
    this.targetPinIndex = targetPinIndex;
    this.description = `Connect pin ${sourcePinIndex} to pin ${targetPinIndex}`;
  }

  async execute(): Promise<void> {
    await this.client.callApi('ApiNode', 'connectToIx', this.targetNodeId, {
      pinIdx: this.targetPinIndex,
      sourceNode: {
        handle: this.sourceNodeId,
        type: 17, // ApiNode type
      },
      evaluate: true,
      doCycleCheck: true,
    });
    console.log(`Connected pins: ${this.sourceNodeId}[${this.sourcePinIndex}] -> ${this.targetNodeId}[${this.targetPinIndex}]`);
  }

  async undo(): Promise<void> {
    await this.client.callApi('ApiNode', 'connectToIx', this.targetNodeId, {
      pinIdx: this.targetPinIndex,
      sourceNode: {
        handle: 0, // 0 = disconnect
        type: 17,
      },
      evaluate: true,
      doCycleCheck: true,
    });
    console.log(`Disconnected pin: ${this.targetNodeId}[${this.targetPinIndex}]`);
  }
}

/**
 * Command to disconnect a pin
 */
export class DisconnectPinCommand implements Command {
  description: string;
  private client: OctaneClient;
  private nodeId: number;
  private pinIndex: number;
  private previousConnection: { sourceNodeId: number; sourcePinIndex: number } | null = null;

  constructor(client: OctaneClient, nodeId: number, pinIndex: number) {
    this.client = client;
    this.nodeId = nodeId;
    this.pinIndex = pinIndex;
    this.description = `Disconnect pin ${pinIndex}`;
  }

  async execute(): Promise<void> {
    // TODO: Store previous connection for undo
    // Would need to query current connection before disconnecting using connectedNodeIx
    await this.client.callApi('ApiNode', 'connectToIx', this.nodeId, {
      pinIdx: this.pinIndex,
      sourceNode: {
        handle: 0, // 0 = disconnect
        type: 17,
      },
      evaluate: true,
      doCycleCheck: true,
    });
    console.log(`Disconnected pin: ${this.nodeId}[${this.pinIndex}]`);
  }

  async undo(): Promise<void> {
    if (this.previousConnection) {
      await this.client.callApi('ApiNode', 'connectToIx', this.nodeId, {
        pinIdx: this.pinIndex,
        sourceNode: {
          handle: this.previousConnection.sourceNodeId,
          type: 17,
        },
        evaluate: true,
        doCycleCheck: true,
      });
      console.log(`Reconnected pin: ${this.nodeId}[${this.pinIndex}]`);
    } else {
      console.warn('Cannot undo disconnect: previous connection not stored');
    }
  }
}

/**
 * Command to set a parameter value
 */
export class SetParameterCommand implements Command {
  description: string;
  private client: OctaneClient;
  private nodeId: number;
  private paramName: string;
  private newValue: any;
  private oldValue: any = null;

  constructor(
    client: OctaneClient,
    nodeId: number,
    paramName: string,
    newValue: any,
    oldValue?: any
  ) {
    this.client = client;
    this.nodeId = nodeId;
    this.paramName = paramName;
    this.newValue = newValue;
    this.oldValue = oldValue;
    this.description = `Set ${paramName} to ${JSON.stringify(newValue)}`;
  }

  async execute(): Promise<void> {
    await this.client.callApi('ApiNode', 'setPinValueByName', this.nodeId, {
      pinName: this.paramName,
      value: this.newValue
    });
    console.log(`Set parameter: ${this.paramName} = ${JSON.stringify(this.newValue)}`);
  }

  async undo(): Promise<void> {
    if (this.oldValue !== null) {
      await this.client.callApi('ApiNode', 'setPinValueByName', this.nodeId, {
        pinName: this.paramName,
        value: this.oldValue
      });
      console.log(`Restored parameter: ${this.paramName} = ${JSON.stringify(this.oldValue)}`);
    } else {
      console.warn('Cannot undo parameter change: old value not stored');
    }
  }
}
