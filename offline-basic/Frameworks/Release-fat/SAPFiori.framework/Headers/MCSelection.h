//
//  MCSelection.h
//  ChartKit
//
//  Created by Brett Callaghan on 8/21/12.
//
//

#import <Foundation/Foundation.h>
#import "MCSelectionInfo.h"


/**
 Object containing info for a single selection in the chart. (One selection per dot.)
 */
@interface MCSelection : NSObject

/**
 Used by MCSelectionStrategy to initialize selection objects.
 */
- (id)initWithSelectionValueInfo:(const MCSelectionValueInfo *)selectionInfo;

/**
 Used by MCSelectionStrategy implementations to update the properties of a selection object.
 */
- (void)update:(const MCSelectionValueInfo *)selectionInfo;
- (void)update:(const MCSelectedState*)selectedState touchIndex:(int)touchIndex;

/**
 Index of the series to which the value belongs.
 This value may be -1 in special cases. In the stacked column chart, for example, -1 might be used to indicate that the entire column is selected.
 */
@property (nonatomic, readonly) NSInteger seriesIndex;

/**
 Index of the value.
 */
@property (nonatomic, readonly) NSInteger valueIndex;

/**
 Position of a click, touch or slider that triggered the selection. In the case of a slider y is 0.f
 */
@property (nonatomic, readonly) CGPoint touchPosition;

/**
 Value of the data point.
 */
@property (nonatomic, readonly) double value;

/**
 Position of the value. The value closest to the touchPosition.
 */
@property (nonatomic, readonly) CGPoint valuePosition;

/**
 Indicates whether the selection is associated with the first (0) or second (1) touch position.
 -1 if the selection is not associated with any user interaction. This happens in cases like Pulse where we sometimes automatically select the previous point in addition to the user's selection.
 */
@property (nonatomic, readonly) NSInteger touchIndex;


@property (nonatomic, readonly) NSUInteger events;
@end
