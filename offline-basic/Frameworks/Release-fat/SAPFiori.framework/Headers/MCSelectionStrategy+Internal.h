//
//  MCSelectionStrategy+Internal.h
//  ChartKit
//
//  Created by Brett Callaghan on 8/21/12.
//
//

#import "MCSelectionStrategy.h"
#import "MCContext.h"


@protocol MCSelectionStrategyDelegate;


#pragma mark -
@interface MCSelectionStrategy ()

/**
 Assigned internaly by MCChartLayer when the selectionStrategy property is set.
 The base class uses the context to translate coordinates into selected values.
 */
@property (nonatomic, assign) MCContextRef _Nonnull context;

/**
 Assigned internaly by MCChartLayer when the selectionStrategy property is set.
 The chart layer is the delegate.
 */
@property (nonatomic, weak) id <MCSelectionStrategyDelegate> _Nullable delegate;


/*
 These methods are currently only invoked by setSelectedPositions:count: and are not actually invoked in accordance with UIEvents.
 While that was originally the intention I realized that touch positions weren't a reliably way to identify selections from one touch/slider event to the next.
 Selections are now identified based on whether they are associated with the start or end position.
 To identify the start/end position I need all the selected positions at the same time which is why we use setSelectedPositions:count: to update selections rather than the methods below.
 */


/**
 Default implementation creates 0 or 1 selections associated with the given touch position using -makeSelectionsForPosition.
 Invokes -selectionStrategy:selectionsBegan:
 */
- (void)touchBeganAtPosition:(CGPoint)touchPosition;

/**
 View may use -[UITouch previousLocationInView] to obtain the value for previousTouchPosition.
 Invokes -selectionStrategy:selectionsChanged:
 */
- (void)touchMovedFromPosition:(CGPoint)previousTouchPosition to:(CGPoint)newTouchPosition;

/**
 Selection strategy invokes -selectionStrategy:selectionsEnded: for all touches at the current position.
 */
- (void)touchEndedAtPosition:(CGPoint)touchPosition;
@end



#pragma mark -
@protocol MCSelectionStrategyDelegate <NSObject>

/**
 @param selections  Selections that the strategy created.
 */
- (void)selectionStrategy:(nonnull MCSelectionStrategy *)selectionStrategy selectionsBegan:(nullable NSArray<MCSelection*>*)selections;

/**
 @param selections  Selections that have been updated by the selection strategy.
 */
- (void)selectionStrategy:(nonnull MCSelectionStrategy *)selectionStrategy selectionsChanged:(nullable NSArray<MCSelection*>*)selections;

/**
 @param selections  Selections that have ended by the selection strategy.
 */
- (void)selectionStrategy:(nonnull MCSelectionStrategy *)selectionStrategy selectionsEnded:(nullable NSArray<MCSelection*>*)selections;
@end
