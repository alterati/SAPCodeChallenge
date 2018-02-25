//
//  MCSelectionStrategy.h
//  ChartKit
//
//  Created by Daniel Cascais on 7/19/12.
//  Copyright (c) 2012 Mellmo. All rights reserved.
//
//  TODO: Add property to limit the number of touch positions (1 or 2 max).
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "MCEvents.h"
#import "MCSelectedState.h"
#import "MCSelection.h"


/**
 A selection strategy's role is to translate coordinates of user touch/slider positions to a set of one or more selections.
 
 The UIKit layer will determine when / how many / and the manner in which touches are received.
 
 MCChartLayer is responsible for determining what adornments, if any, will be displayed.
 
 Roambi currently employs several different types of strategies.
 - Single user selection.
 - Dual user selection.
 - Single user selection + fixed.
 - Single user selection + dynamic (vs previous).
 
 Other charting implementations support others that we might implement someday.
 - A selection in every series for a given value index (Google Charts).
 - The ability to select bubbles in a bubble chart by tapping on them.
 
 The default implementation transforms a single touch position into a single MCSelection object and supports up to two touches (start/end).
 
 The simplest way to create a custom strategy is to subclass MCSelectionStrategy.
 Override makeSelectionsForPosition: to provide any number of selections in addition to the MCSelection returned by the base class.
 Override updateSelections:withPosition: to update the properties of each custom selection.
 */
@interface MCSelectionStrategy : NSObject
{
@protected
    MCEvents _events;
    MCContextRef _context;
    CALayer* _superLayer;
    NSMutableArray* _adornments;
}

- (id)initWithChartContext:(MCContextRef)chartContext andSuperLayer:(CALayer*)superLayer;

/**
 Inspect the events property to figure out what has happened since the last delegate method was invoked.
 After each invocation this property is cleared (set to 0).
 */
@property (nonatomic, readonly) MCEvents events;

/**
 */
- (void)updateWithSelectedState:(const MCSelectedState*)selectedState;
- (void)zoomStart:(MCPoint)start end:(MCPoint)end;


#pragma mark Subclassing

/**
 Returns an array of MCSelection objects associated with the specified position.
 This method is invoked when a touch is first registered with the strategy in touchBeganAtPosition:.
 The default implementation returns a single selection for the given touch position.
 This is a good override method for subclasses.
 Many strategies can be implemented by providing additional selections based on super's implementation.
 */
- (NSArray *)makeSelectionsForPosition:(CGPoint)position;

/**
 Subclasses must update the selections using -[MCSelection update].
 Use -getSelectionInfo:atPosition: to get some info about the selection at the given position.
 */
- (void)updateSelections:(NSArray *)selections withPosition:(CGPoint)position;



#pragma mark Convenience / Subclass Helpers

- (MCContextRef)context;

/**
 Number of series currently displayed by the chart.
 */
@property (nonatomic, readonly) NSUInteger seriesCount;

/**
 Clears the selectionInfo struct and sets the valueIndex, seriesIndex, touchPosition, valuePosition and value properties.
 */
- (void)getSelectionInfo:(MCSelectionValueInfo *)selectionInfo atPosition:(CGPoint)position;

/**
 Convenience accessors provided to obtain the "start" and "end" positions along the x axis.
 The MCSelection object's touchIndex property refers to this as well. 0 for start. 1 for end.
 Although there may be many selections, ChartKit only allows two simultaneous touches.
 MCNullPoint is returned if there are no start/end positions.
 */
@property (nonatomic, readonly) CGPoint startPosition;
@property (nonatomic, readonly) CGPoint endPosition;

/**
 Returns all current selections for the given position.
 This will be helpful to find all the selections that need to be updated when touchMovedFromPosition:to: is received.
 It also implies that MCSelectionStrategy must store all of its current selections.
 */
- (NSArray *)selectionsForTouchPosition:(CGPoint)position;

/**
 Returns all current selections.
 */
- (NSArray<MCSelection*>*)selections;
@end
