# Icon Testing Checklist

## Purpose
This checklist helps verify that icon mappings are working correctly and no blue folder icons remain in the UI.

## Before Testing
1. Ensure dev server is running: `npm run dev`
2. Open browser to http://localhost:58407
3. Load a scene with diverse node types (cameras, lights, materials, geometry, etc.)

## Scene Outliner Tests

### Core Scene Structure
- [ ] **Scene root** - Should show scene icon (not blue folder)
- [ ] **Render target** - Should show render target icon (`RENDER TARGET node.png`)
- [ ] **Camera** - Should show camera icon (`CAMERA node.png`)
- [ ] **Environment** - Should show environment icon (`ENVIRONMENT node.png`)
- [ ] **Film settings** - Should show film icon (`FILM node.png`)

### Render Elements
- [ ] **Render kernel** - Should show render kernel icon (`RENDER KERNEL node.png`)
- [ ] **Render layer** - Should show render layer icon (`render_layer.png`)
- [ ] **Render passes** - Should show render passes icon (`render_passes.png`)
- [ ] **AOV output group** - Should show AOV group icon (`aov-output-group.png`)
- [ ] **AOV output** - Should show AOV icon (`aov-output.png`)

### Scene Content
- [ ] **Mesh/Geometry** - Should show mesh icon (`MESH node.png`)
- [ ] **Placement** - Should show placement icon (if exists)
- [ ] **Light** - Should show light/emitter icon (`CATEGORY_EMITTER node.png`)
- [ ] **Material** - Should show material icon (`CATEGORY_MATERIAL node.png`)

### Special Nodes
- [ ] **Animation settings** - Should show animation settings icon (`animation_settings_node.png`)
- [ ] **Post-processing** - Should show post-proc icon (`POSTPROC node.png`)
- [ ] **Imager** - Should show imager icon (`IMAGER node.png`)

## Toolbar Tests

### Render Controls
- [ ] **Start render** - Should show render kernel icon
- [ ] **Pause render** - Should show pause icon
- [ ] **Stop render** - Should show stop icon
- [ ] **Realtime mode** - Should show render target icon
- [ ] **Clay mode** - Should show clay mode icon

### Camera Tools
- [ ] **Focus picker** - Should show pipette focus icon
- [ ] **White balance picker** - Should show pipette color icon
- [ ] **Material picker** - Should show pipette material icon
- [ ] **Object picker** - Should show pipette object icon
- [ ] **Camera target** - Should show pipette zoom icon

### Region Tools
- [ ] **Render region** - Should show pipette region icon
- [ ] **Film region** - Should show pipette film region icon

### Export/Save
- [ ] **Copy to clipboard** - Should show clipboard icon
- [ ] **Save render** - Should show save render icon
- [ ] **Export passes** - Should show export passes icon

### Viewport Controls
- [ ] **Resolution lock** - Should show lock resolution icon
- [ ] **Lock viewport** - Should show lock icon
- [ ] **Unlock viewport** - Should show unlock icon

### Gizmos
- [ ] **Translate gizmo** - Should show translate icon
- [ ] **Rotate gizmo** - Should show rotate icon
- [ ] **Scale gizmo** - Should show scale icon
- [ ] **World/Local mode** - Should show world/local icon

### Priority
- [ ] **Low priority** - Should show low priority icon
- [ ] **Normal priority** - Should show normal priority icon
- [ ] **High priority** - Should show high priority icon

## Node Inspector Tests

### Parameter Icons
These use Unicode symbols (not PNG icons) - verify they display correctly:
- [ ] **Bool parameters** - Should show checkbox symbol
- [ ] **Float parameters** - Should show numeric symbol
- [ ] **Int parameters** - Should show numeric symbol
- [ ] **Color parameters** - Should show color symbol
- [ ] **String parameters** - Should show text symbol
- [ ] **Dropdown parameters** - Should show dropdown symbol

## Known Issues to Watch For

### Blue Folder Icons
If you see blue folder icons, note:
1. **Which component** (Scene Outliner, Node Inspector, etc.)
2. **Which node/item type** (Render target, Camera, etc.)
3. **The node type string** (PT_XXX or NT_XXX if visible in console)

### Icon Loading Errors
Check browser console for:
- `404 errors` for missing icon files
- Failed image loads (broken image icons)
- Console errors about icon paths

### Icon Fallbacks
The following should show fallback icons gracefully:
- **Unknown node types** → `CATEGORY.png`
- **Missing icons** → Unicode symbols or category icons

## Testing Results Template

```
Date: ___________
Tester: ___________
Browser: ___________
Scene: ___________

Scene Outliner: ___/15 icons correct
Toolbar: ___/30 icons correct
Node Inspector: ___/6 icons correct

Issues Found:
1. ___________
2. ___________
3. ___________

Screenshots: ___________
```

## Comparison Reference

Compare octaneWebR (left) with Octane desktop (right):
- Scene Outliner icons should match
- Toolbar icons should match
- Overall visual appearance should be consistent

## Quick Visual Test

1. **Open Scene Outliner** - Expand all nodes
2. **Count blue folders** - Should be ZERO
3. **Check toolbar** - All buttons should have icons
4. **Select nodes** - Icons should appear in Node Inspector

## Automated Verification

Run this command to check for broken icon paths in the code:

```bash
# Find all icon references
grep -r "icons/" client/src --include="*.ts*" | grep -v "node_modules"

# Check if referenced icons exist
# (Manual verification needed - compare output with actual files)
```

## Icon File Reference

All icons are located in: `/client/public/icons/`

Total available: **386 icon files**

Currently mapped:
- **278** NT_ node types (IconMapping.ts)
- **17** PT_ parameter types (OctaneIconMapper.ts)
- **40+** toolbar actions (ToolbarIconMapping.ts)
- **Total: ~335 icons mapped**

## Success Criteria

✅ **PASS** if:
- No blue folder icons in Scene Outliner
- All toolbar buttons show proper icons
- Icons match Octane desktop UI
- No console errors for missing icons

❌ **FAIL** if:
- Any blue folder icons remain
- Broken image icons appear
- Console shows 404 errors for icons
- Icons don't match Octane desktop

## Next Steps After Testing

If issues found:
1. Document the specific node type showing blue folder
2. Search for the correct icon in `/icons/` directory
3. Update the appropriate mapping file:
   - `IconMapping.ts` for NT_ types
   - `OctaneIconMapper.ts` for PT_ types
   - `ToolbarIconMapping.ts` for toolbar actions
4. Verify the icon file exists
5. Commit the fix with descriptive message

---

**Last Updated:** 2025-01-23  
**Related Commits:** 0bb611e7, 2631a551, 3391e595, ad324cd4  
