import { memo, useState, useEffect, useCallback } from 'react';
import { useStore } from '../../store/useStore';
import { Endpoint } from '../../types';
import { logger } from '../../services/logger';
import styles from './Layout.module.css';

export const NodeBar = memo(() => {
  const { 
    endpoints, 
    loadingEndpoints, 
    fetchEndpoints, 
    addNode, 
    visibleEndpoints,
    removeVisibleEndpoint 
  } = useStore();
  
  // Filter endpoints to only show visible ones
  const visibleEndpointsList = endpoints.filter((e) =>
    visibleEndpoints.includes(e.endpoint_id)
  );

  const categories = Array.from(
    new Set(visibleEndpointsList.flatMap((e) => e.category))
  ).sort();

  // Default all categories expanded (including 'utility')
  const [expandedCategories, setExpandedCategories] = useState<Set<string>>(() => {
    return new Set(['utility', ...categories]);
  });
  
  const [contextMenu, setContextMenu] = useState<{
    x: number;
    y: number;
    endpointId: string;
  } | null>(null);

  useEffect(() => {
    fetchEndpoints();
  }, [fetchEndpoints]);

  // Update expanded categories when new categories are loaded
  useEffect(() => {
    setExpandedCategories(prev => {
      const newSet = new Set(prev);
      newSet.add('utility');
      categories.forEach(cat => newSet.add(cat));
      return newSet;
    });
  }, [categories.join(',')]); // eslint-disable-line react-hooks/exhaustive-deps

  const toggleCategory = (category: string) => {
    const newExpanded = new Set(expandedCategories);
    if (newExpanded.has(category)) {
      newExpanded.delete(category);
    } else {
      newExpanded.add(category);
    }
    setExpandedCategories(newExpanded);
  };

  const handleAddEndpoint = (endpoint: Endpoint) => {
    const id = `${endpoint.endpoint_id}-${Date.now()}`;
    const x = Math.random() * 500 + 100;
    const y = Math.random() * 500 + 100;

    logger.info('Adding AI endpoint node', { endpoint: endpoint.endpoint_id });

    addNode({
      id,
      type: 'aiEndpoint',
      position: { x, y },
      data: { 
        endpoint,
        parameters: {},
        isExecuting: false,
        selectedPin: 'output', // Default to showing output preview
      },
    });
  };

  const handleContextMenu = (e: React.MouseEvent, endpointId: string) => {
    e.preventDefault();
    setContextMenu({
      x: e.clientX,
      y: e.clientY,
      endpointId,
    });
  };

  const handleRemoveEndpoint = () => {
    if (contextMenu) {
      removeVisibleEndpoint(contextMenu.endpointId);
      setContextMenu(null);
    }
  };

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  useEffect(() => {
    if (contextMenu) {
      document.addEventListener('click', closeContextMenu);
      return () => document.removeEventListener('click', closeContextMenu);
    }
  }, [contextMenu, closeContextMenu]);

  const handleAddUtilityNode = (type: 'image' | 'video' | 'textInput') => {
    const id = `${type}-${Date.now()}`;
    const x = Math.random() * 500 + 100;
    const y = Math.random() * 500 + 100;

    logger.info('Adding utility node', { type });

    const nodeData = {
      image: { items: [] },
      video: { items: [] },
      textInput: { value: '', label: 'Text Input' },
    };

    addNode({
      id,
      type,
      position: { x, y },
      data: nodeData[type],
    });
  };

  const isUtilityExpanded = expandedCategories.has('utility');

  return (
    <>
      <div className={styles.contextMenu}>
        <h2 className={styles.contextMenuHeader}>Node Palette</h2>

        {/* Utility section as collapsible category */}
        <div className={styles.categorySection}>
          <div
            className={`${styles.categoryTitle} ${isUtilityExpanded ? styles.active : ''}`}
            onClick={() => toggleCategory('utility')}
          >
            <span>utility</span>
            <span>{isUtilityExpanded ? '▼' : '▶'}</span>
          </div>

          {isUtilityExpanded && (
            <div className={styles.endpointList}>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('textInput')}
                title="Text input node for prompts and text data"
              >
                <div className={styles.endpointItemTitle}>Text Input</div>
              </div>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('image')}
                title="Image input node for uploading and managing images"
              >
                <div className={styles.endpointItemTitle}>Image</div>
              </div>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('video')}
                title="Video input node for uploading and managing videos"
              >
                <div className={styles.endpointItemTitle}>Video</div>
              </div>
            </div>
          )}
        </div>

        {loadingEndpoints && <div className={styles.loading}>Loading endpoints...</div>}

        {categories.map((category) => {
          const categoryEndpoints = visibleEndpointsList.filter((e) =>
            e.category.includes(category)
          );
          const isExpanded = expandedCategories.has(category);

          return (
            <div key={category} className={styles.categorySection}>
              <div
                className={`${styles.categoryTitle} ${isExpanded ? styles.active : ''}`}
                onClick={() => toggleCategory(category)}
              >
                <span>{category}</span>
                <span>{isExpanded ? '▼' : '▶'}</span>
              </div>

              {isExpanded && (
                <div className={styles.endpointList}>
                  {categoryEndpoints.map((endpoint) => (
                    <div
                      key={endpoint._id}
                      className={styles.endpointItem}
                      onClick={() => handleAddEndpoint(endpoint)}
                      onContextMenu={(e) => handleContextMenu(e, endpoint.endpoint_id)}
                      title={endpoint.description}
                    >
                      <div className={styles.endpointItemTitle}>{endpoint.title}</div>
                    </div>
                  ))}
                </div>
              )}
            </div>
          );
        })}
      </div>

      {contextMenu && (
        <div
          className={styles.contextMenuOverlay}
          style={{
            position: 'fixed',
            left: contextMenu.x,
            top: contextMenu.y,
          }}
        >
          <div className={styles.contextMenuItem} onClick={handleRemoveEndpoint}>
            Remove from NodeBar
          </div>
        </div>
      )}
    </>
  );
});

NodeBar.displayName = 'NodeBar';
