# URL Prompt Dialog Update

## Summary
Modified Image and Video nodes to use a prompt dialog for URL entry instead of inline text input fields.

## Changes Made

### 1. ImageNode.tsx
- **Modified `addItem()` function**: Now shows `prompt('Enter image URL:')` when URL button is clicked
- **Removed inline URL input field**: No more text input inside the node item
- **Removed `updateItemUrl()` function**: No longer needed since URLs are set via prompt
- **Simplified render**: Items only show preview image when not collapsed

### 2. VideoNode.tsx
- **Modified `addItem()` function**: Now shows `prompt('Enter video URL:')` when URL button is clicked
- **Removed inline URL input field**: No more text input inside the node item
- **Removed `updateItemUrl()` function**: No longer needed since URLs are set via prompt
- **Simplified render**: Items only show video preview when not collapsed

## User Experience Improvements

### Before
1. Click "+🔗" button
2. Empty item appears with text input field
3. Type URL into the field
4. Image/video preview loads

### After
1. Click "+🔗" button
2. Prompt dialog appears: "Enter image/video URL:"
3. User types URL in dialog and clicks OK
4. Item appears with URL pre-populated and preview loaded
5. **No text input field visible** (matches file upload behavior)

## Benefits

✅ **Consistent UX**: URL items now match file items (no input fields)
✅ **Cleaner UI**: Less clutter in the node
✅ **Faster workflow**: Single action to add URL
✅ **Clear intent**: Dialog makes it obvious what to enter
✅ **Reduced code**: Removed unused updateItemUrl functions

## Technical Details

### Code Pattern
```typescript
if (type === 'url') {
  // Show prompt dialog for URL
  const url = prompt('Enter image URL:');
  if (url && url.trim()) {
    newItem.url = url.trim();
    newItem.name = url.split('/').pop() || url;
    typedData.items.push(newItem);
    updateNodeInternals(id);
    forceUpdate({});
  }
  return;
}
```

### Render Simplification
```typescript
// Before: Conditional input field + preview
{!item.collapsed && (
  <div className={styles.mediaItemContent}>
    {!item.file && <input ... />}  // ❌ Removed
    {(item.preview || item.url) && <img ... />}
  </div>
)}

// After: Preview only
{!item.collapsed && (item.preview || item.url) && (
  <div className={styles.mediaItemContent}>
    <img ... />  // ✅ Clean and simple
  </div>
)}
```

## Build Status
- ✅ TypeScript compilation: 0 errors
- ✅ Build time: 964ms
- ✅ Bundle size: 374KB

## Git Commit
- **Commit**: 71f7f7a2
- **Branch**: main
- **Status**: Pushed to origin/main

## Testing
To test the new functionality:
1. Navigate to http://localhost:60023
2. Add an Image or Video node
3. Click the "+🔗" button
4. Enter a URL in the prompt dialog
5. Verify the item appears with preview (no input field)

## Example URLs for Testing
- **Image**: `https://picsum.photos/400/300`
- **Image**: `https://via.placeholder.com/400x300`
- **Video**: `https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4`
