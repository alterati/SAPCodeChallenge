//
//  MCSelectionInfo.h
//  ChartKit
//
//  Created by Brett Callaghan on 8/10/12.
//
//  TODO: MCPoint instead of CGPoint?
//


#ifndef ChartKit_MCSelectionInfo_h
#define ChartKit_MCSelectionInfo_h


typedef struct
{
    /**
     Index of the series to which the value belongs.
     */
    int seriesIndex;
    
    /**
     Index of the value.
     */
	int valueIndex;
    
	/**
     Position of a click, touch or slider that triggered the selection. In the case of a slider y is 0.f
     */
	CGPoint touchPosition;
    
    /**
     Position of the value. The value closest to the touchPosition.
     */
	CGPoint valuePosition;
    
	/**
     Value of the data point.
     */
	double value;
    
    /**
     Indicates whether the selection is associated with the first (0) or second (1) touch position.
     -1 if the selection is not associated with any user interaction. This happens in cases like Pulse where we sometimes automatically select the previous point in addition to the user's selection.
     */
    int touchIndex;
    
} MCSelectionValueInfo;


typedef struct
{    
    /**
     Number of selections.
     */
    unsigned int count;
    
    /**
     Array of current selections.
     */
    MCSelectionValueInfo *selections;
    
    /*
     Difference between two values.
     */
    double variation;
    
    /*
     Percent difference between two values.
     */
    double percentVariation;
    
} MCSelectionInfo;


/**
 Difference between two values.
 */
static inline double MCSelectionVariation(MCSelectionInfo *info)
{
    if (1 == info->count) {
        return 0.f;
    }
    else if (2 == info->count) {
        return info->selections[1].value - info->selections[0].value;
    }
    return NAN;
}


/**
 Percent difference between two values.
 */
static inline double MCSelectionPercentVariation(MCSelectionInfo *info)
{
    if (1 == info->count) {
        return 0.f;
    }
    else if (2 == info->count) {
        
        double v1 = info->selections[0].value;
        double v2 = info->selections[1].value;
        
        if (0 == v1) {
            return (v2 < 0) ? -INFINITY : INFINITY;
        } else {
            return (v2 - v1) / fabs(v1);
        }
    }
    return NAN;
}


/**
 */
static inline void MCSelectionValueClear(MCSelectionValueInfo *selection)
{
    if (NULL == selection) {
        return;
    }    
    selection->seriesIndex = -1;
    selection->valueIndex = -1;
    selection->touchPosition.x = 0.f;
    selection->touchPosition.y = 0.f;
    selection->valuePosition.x = 0.f;
    selection->valuePosition.y = 0.f;
    selection->value = NAN;
    selection->touchIndex = -1;
}


#pragma mark -

typedef struct {
    int seriesIndex;
    int index;
    unsigned int dataCount;
    double data[3];
} MCValueInfo;

#endif
