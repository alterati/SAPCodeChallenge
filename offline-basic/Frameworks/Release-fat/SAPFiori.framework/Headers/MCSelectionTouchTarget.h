//
//  MCSelectionTouchTarget.h
//  ChartKit
//
//  Created by Daniel Cascais on 9/24/13.
//
//

#ifndef ChartKit_MCSelectionTouchTarget_h
#define ChartKit_MCSelectionTouchTarget_h

// Indicates what touch the adornment should follow.
typedef enum MCSelectionTouchTarget
{
    MCSelectionTouchTargetStart   = 1 << 0,
    MCSelectionTouchTargetEnd     = 1 << 1,

    // The default is the start selection, which means one touch.
    MCSelectionTouchTargetDefault = MCSelectionTouchTargetStart

} MCSelectionTouchTarget;

#endif
